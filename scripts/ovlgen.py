"""
gendata.py for an overlay (run through scripts/ovldata.py gen): the overlay's INCLUDE_OVERLAY_ASM data lines become C
definitions, their externs go to src/overlays/<name>.h.
"""
import bisect
import os
import re
import struct

import gendata
from gendata import GenError, T, Def, const_decl  # noqa: F401

REPO = gendata.REPO
HEADERLESS = ("GAME", "MENU")   # overlays whose first word is ordinary .rdata (overlays.py)


class OvlSyms(gendata.Syms):
    """the executable's symbols (those outside the overlay) and the overlay's, bytes from both images"""

    def __init__(self, exe, data, base, osyms):
        gendata.Syms.__init__(self, exe)
        self.data, self.base, self.end = data, base, base + len(data)
        for n in [n for n, a in self.addr.items() if base <= a < self.end]:
            del self.addr[n]
        for a, n in osyms:
            self.addr[n] = a
        by = {}
        for n, a in self.addr.items():
            by.setdefault(a, []).append(n)
        self.by_addr = by
        self.sorted = sorted(by)

    def rd(self, addr, n):
        if self.base <= addr < self.end:
            return self.data[addr - self.base:addr - self.base + n]
        return gendata.Syms.rd(self, addr, n)

    def rename(self, old, new):
        a = self.addr.pop(old)
        self.addr[new] = a
        lst = self.by_addr[a]
        lst[lst.index(old)] = new


def section_ranges(name, data, base, osyms):
    code = [a for a, n in osyms if not n.startswith(gendata_prefixes())]
    lo = min(code)
    hi = next((a for a, n in osyms if a > max(code)), base + len(data))
    return lo, hi


def gendata_prefixes():
    import gen_asm
    return gen_asm.DATA_PREFIXES


def includes(text, oname):
    """[(name, match)] of the INCLUDE_OVERLAY_ASM lines of a source text that are data (not jump tables)"""
    out = []
    for m in re.finditer(r"^INCLUDE_OVERLAY_ASM\(%s, (\w+)\);[^\n]*\n?" % oname, text, re.M):
        n = m.group(1)
        if n.startswith(gendata_prefixes()) and not n.startswith("jpt_"):
            out.append((n, m))
    return out


def preproc_path(name, k):
    return os.path.join(REPO, "build_psyq", "overlay_" + name.lower() + ("_%d" % (k + 1) if k else "") + ".preproc")


def header_path(name):
    return os.path.join(REPO, "src", "overlays", name.lower() + ".h")


def main(name, exe, data, base, osyms, lib_ranges, only, write):
    import ovldata
    oname = name.lower()
    end = base + len(data)
    lo, hi = section_ranges(name, data, base, osyms)
    gendata.EXTRA_CODE[:] = [(lo, hi)]
    gendata.EXTRA_RODATA[:] = [(base, lo)]
    gendata.EXTRA_IMAGE[:] = [(base, end)]
    _, _, gamebss = ovldata.overlays.lib_objs(name.upper())
    syms = OvlSyms(exe, data, base, osyms)
    sym_list = sorted(osyms)
    starts = [a for a, _ in sym_list]

    def chunk(n):
        a = syms.addr[n]
        i = bisect.bisect_right(starts, a)
        b = starts[i] if i < len(starts) else end
        if gamebss is not None and a >= gamebss:
            sec = ".bss"
        elif a == base and name.upper() not in HEADERLESS and a < lo:
            sec = ".sdata"
        else:
            sec = ".rdata" if a < lo else ".data"
        return sec, b - a

    all_defs = []
    srcs = ovldata.sources(name)
    texts = {p: open(p).read() for p in srcs}
    renames = {}        # .sym name -> the name the definition has
    new_syms = {}       # name -> addr of definitions the .sym file doesn't have
    report = []
    for k, src in enumerate(srcs):
        incs = includes(texts[src], oname)
        if only:
            incs = [x for x in incs if x[0] in only]
        if not incs:
            continue
        types = gendata.Types(gendata.parse_preproc(preproc_path(name, k)))
        types.adopted, types.others = {}, set()
        # names the source declares for a place of the overlay (name_XXXXXXXX): aliases of the symbol there
        for dn in types.decls:
            m = re.search(r"_([0-9A-F]{8})$", dn)
            if m and base <= int(m.group(1), 16) < end and dn not in syms.addr:
                a = int(m.group(1), 16)
                if a in syms.by_addr:
                    syms.by_addr[a].insert(0, dn)
                    syms.addr[dn] = a
        names = [n for n, _ in incs]
        propagate(types, syms, names, chunk)
        gen = gendata.Gen(syms, types)

        def chunk_of(n, _gen=gen):
            return chunk(n) if n in syms.addr and base <= syms.addr[n] < end and any(
                x == n for _, x in sym_list) else gendata.Gen.chunk_of(n)
        gen.chunk_of = chunk_of
        info = {}
        for n in names:
            sec, size = chunk(n)
            info[n] = (".rdata" if sec == ".sdata" else sec, size)
        todo, defs, absorbed, errors, types, syms, gen = gendata.generate_chunks(syms, types, gen, names, info)
        ok = [d for d in defs if d.head not in errors]
        # an INCLUDE_OVERLAY_ASM can't stay between two C definitions of its section: nothing behind a failed
        # chunk is written (up to the next function, where the compiler switches sections itself)
        for n in todo:
            if n in errors:
                report.append("// %s: %s" % (n, errors[n]))
        for d in ok:
            if chunk(d.head)[0] == ".sdata" and d.head == d.name:
                d.sec = ".sdata"
                d.text = re.sub(r"^const ", "", d.text)
                d.text = d.text.replace(" = ", " SDATA = ", 1)
        text = texts[src]
        heads = {}
        for d in ok:
            heads.setdefault(d.head, []).append(d)
        failed = {n for n in todo if n in errors}
        # the compiler only switches sections when it thinks it is in another one: a definition whose section the
        # previous C item (function or definition) left it in, with assembly in between (which ends in .text),
        # would land in .text. Those stay assembly (and so may the ones behind them).
        units = []
        live = mask_if0(text)
        for m in re.finditer(r"^INCLUDE_OVERLAY_ASM\(%s, (\w+)\);" % oname, live, re.M):
            units.append((m.start(), "asm", m.group(1)))
        for m in FUNC.finditer(live):
            units.append((m.start(), "func", None))
        units.sort()
        dropped = set()
        while True:
            state, asm_since = None, False
            bad = None
            for _, kind, n in units:
                if kind == "func":
                    state, asm_since = ".text", False
                elif n in heads and n not in dropped:
                    sec = heads[n][0].sec
                    if state == sec and asm_since:
                        bad = n
                        break
                    state, asm_since = sec, False
                else:
                    asm_since = True
            if bad is None:
                break
            dropped.add(bad)
            report.append("// %s stays assembly: behind assembly that follows a C definition of its section" % bad)
        for h in dropped:
            del heads[h]
        for h, ds in heads.items():
            body = "\n".join(d.text for d in ds)
            text = re.sub(r"^INCLUDE_OVERLAY_ASM\(%s, %s\);[^\n]*$" % (oname, h), lambda _m: body, text, count=1,
                          flags=re.M)
            for x, hh in absorbed.items():
                if hh == h:
                    text = re.sub(r"^INCLUDE_OVERLAY_ASM\(%s, %s\);[^\n]*\n" % (oname, x), "", text, count=1,
                                  flags=re.M)
            for d in ds:
                all_defs.append((src, d, types, gen))
                at = [x for _, x in sym_list if syms.addr.get(x) == d.addr and x != d.name] if False else None
                # the .sym name of the place
                sname = next((x for a, x in sym_list if a == d.addr), None)
                if sname is None:
                    new_syms[d.name] = d.addr
                elif sname != d.name:
                    renames[sname] = d.name
        texts[src] = text
    for line in report:
        print(line)
    for src, d, types, gen in all_defs:
        print(d.text)
    if not write:
        return 0
    # externs into the header, out of the .c files
    exts = []
    protos = []
    for src, d, types, gen in all_defs:
        decl = const_decl(d.decl, d.name) if d.sec == ".rdata" else d.decl
        exts.append("extern %s;" % decl)
        for r in sorted(gen.protos):
            if all(r not in p for p in protos):
                protos.append(r)
    defined = {d.name for _, d, _, _ in all_defs}
    for p in texts:
        t = texts[p]
        for n in defined:
            t = re.sub(r"^extern\b[^;\n]*[\s*(]%s\s*[\[);][^;\n]*;[^\n]*\n" % re.escape(n), "", t, flags=re.M)
        texts[p] = t
    write_header(name, texts, exts, protos)
    for p, t in texts.items():
        open(p, "w").write(t)
    # the .sym file names every definition (the link script equates the other address names of the source)
    path = ovldata.sym_path(name)
    st = open(path).read()
    for old, new in renames.items():
        st = re.sub(r"^%s=" % re.escape(old), new + "=", st, flags=re.M)
    lines = st.rstrip("\n").split("\n")
    for n, a in sorted(new_syms.items(), key=lambda x: x[1]):
        k = 0
        while k < len(lines):
            m = re.match(r"\w+=0x([0-9a-fA-F]+);", lines[k])
            if m and int(m.group(1), 16) > a:
                break
            k += 1
        lines.insert(k, "%s=0x%08x;" % (n, a))
    open(path, "w").write("\n".join(lines) + "\n")
    print("wrote %d definitions" % len(all_defs))
    return 0


def pointers(t, addr, syms):
    """(PtrT, value) of the pointers in an object of type t at addr"""
    if t.kind == "ptr":
        yield t, struct.unpack("<I", syms.rd(addr, 4))[0]
    elif t.kind == "array" and t.n:
        es = t.of.size()
        for i in range(t.n):
            for x in pointers(t.of, addr + i * es, syms):
                yield x
    elif t.kind == "struct":
        for mn, mt, mo, bp, bs in t.members:
            if bp is None:
                for x in pointers(mt, addr + mo, syms):
                    yield x


def propagate(types, syms, names, chunk):
    """a chunk nobody declares that a typed pointer of a declared one points at gets the pointer's type (an array of
    what it points at): declarations are added to types.decls (and so on, for what those point at)"""
    import copy
    from pycparser import c_ast
    todo = [n for n in names if n in types.decls]
    pending = set(n for n in names if n not in types.decls)
    while todo:
        n = todo.pop()
        try:
            t = types.resolve(types.decls[n].type)
        except GenError:
            continue
        a = syms.addr[n]
        if t.kind == "array" and t.n is None:
            es = t.of.size() if t.of.kind not in ("void", "func") else 0
            if not es:
                continue
            t = T("array", of=t.of, n=chunk(n)[1] // es)
        try:
            ptrs = list(pointers(t, a, syms))
        except GenError:
            continue
        for pt, v in ptrs:
            hit = [x for x in syms.by_addr.get(v, []) if x in pending]
            if not hit or pt.pnode is None:
                continue
            x = hit[0]
            try:
                to = pt.to
                es = to.size()
            except (GenError, AttributeError):
                continue
            if to.kind in ("void", "func", "opaque") or not es:
                continue
            size = chunk(x)[1]
            if size % es and size - size // es * es >= 4 or size < es:
                continue
            node = copy.deepcopy(pt.pnode.type)
            q = node
            while not isinstance(q, c_ast.TypeDecl):
                q = q.type
            q.declname = x
            q.quals = [z for z in q.quals if z != "const"]
            arr = c_ast.ArrayDecl(node, c_ast.Constant("int", str(size // es)), [])
            types.decls[x] = c_ast.Decl(x, [], [], [], [], arr, None, None)
            pending.discard(x)
            todo.append(x)


FUNC = re.compile(r"^(?!typedef|extern|static\s+const)[A-Za-z_][\w \t\*]*\b\w+\s*\([^;{]*\)\s*\{", re.M)
TYPEDEF = re.compile(r"^(typedef\b|struct\s+\w+\s*\{|union\s+\w+\s*\{|enum\s+\w+\s*\{)")


def mask_if0(text):
    """text with the #if 0 ... #endif blocks blanked (same length)"""
    out = list(text)
    i = 0
    for m in re.finditer(r"^[ \t]*#\s*(if|ifdef|ifndef|else|elif|endif)\b([^\n]*)", text, re.M):
        pass
    lines = text.split("\n")
    pos, depth, off = 0, 0, []
    for ln in lines:
        s = ln.strip()
        if depth:
            if s.startswith("#if"):
                depth += 1
            elif s.startswith("#endif"):
                depth -= 1
            off.append((pos, pos + len(ln)))
        elif s.startswith("#if 0"):
            depth = 1
            off.append((pos, pos + len(ln)))
        pos += len(ln) + 1
    for a, b in off:
        for k in range(a, b):
            out[k] = " "
    return "".join(out)


def top_blocks(text):
    """[(start, end, text)] of the top-level statements of a C text outside #if 0 blocks"""
    out = []
    i, n = 0, len(text)
    depth_if = 0
    while i < n:
        j = text.find("\n", i)
        j = n if j < 0 else j + 1
        line = text[i:j]
        s = line.strip()
        if s.startswith("#if 0"):
            depth_if = 1
            k = j
            while depth_if and k < n:
                e = text.find("\n", k)
                e = n if e < 0 else e + 1
                ls = text[k:e].strip()
                if ls.startswith("#if"):
                    depth_if += 1
                elif ls.startswith("#endif"):
                    depth_if -= 1
                k = e
            i = k
            continue
        if TYPEDEF.match(line):
            # up to the ';' at brace depth 0
            d, k = 0, i
            while k < n:
                c = text[k]
                if c == "{":
                    d += 1
                elif c == "}":
                    d -= 1
                elif c == ";" and d == 0:
                    break
                k += 1
            e = text.find("\n", k)
            e = n if e < 0 else e + 1
            out.append((i, e, text[i:e]))
            i = e
            continue
        i = j
    return out


def defined_types(block):
    m = re.search(r"\}\s*([\w\s,*]+);\s*$", block.strip())
    names = set()
    if block.startswith("typedef"):
        if m:
            names |= {x.strip(" *") for x in m.group(1).split(",")}
        else:
            m2 = re.search(r"\(\s*\*\s*(\w+)\s*\)", block) or re.search(r"(\w+)\s*(\[[^\]]*\])?\s*;\s*$", block.strip())
            if m2:
                names.add(m2.group(1))
    t = re.match(r"(?:typedef\s+)?(struct|union|enum)\s+(\w+)", block)
    if t:
        names.add(t.group(1) + " " + t.group(2))
    return names


def write_header(name, texts, exts, protos):
    """externs (and the prototypes of the functions their initialisers use) into the overlay's header; the
    typedefs of the .c files they need move there too"""
    path = header_path(name)
    guard = "_%s_H_" % os.path.basename(path)[:-2].upper()
    new = not os.path.exists(path)
    srcs = list(texts)
    if new:
        incs = []
        for p in srcs:
            for line in re.findall(r'^#include "[^"]+"\n', texts[p], re.M):
                if line not in incs:
                    incs.append(line)
        hdr = "// %s.BIN: declarations shared by its source files\n#ifndef %s\n#define %s\n\n%s\n#endif\n" % (
            name.upper(), guard, guard, "".join(incs))
    else:
        hdr = open(path).read()
    inc = '#include "%s"' % os.path.basename(path)
    for p in srcs:
        t = texts[p]
        if inc not in t:
            ms = list(re.finditer(r'^#include .*\n', t, re.M))
            k = ms[-1].end() if ms else 0
            t = t[:k] + inc + "\n" + t[k:]
        texts[p] = t
    # typedefs the externs use (and the ones those use), in source order
    need_text = "\n".join(exts)
    moved = []
    changed = True
    while changed:
        changed = False
        for p in srcs:
            for s, e, b in top_blocks(texts[p]):
                if b in moved:
                    continue
                for tn in defined_types(b):
                    word = tn.split()[-1]
                    pat = (r"\b%s\s+%s\b" % tuple(tn.split())) if " " in tn else r"\b%s\b" % re.escape(word)
                    if re.search(pat, need_text):
                        moved.append(b)
                        need_text += "\n" + b
                        changed = True
                        break
    if moved:
        order = []
        for p in srcs:
            for s, e, b in top_blocks(texts[p]):
                if b in moved:
                    order.append(b)
            for b in moved:
                if b + "\n" in texts[p]:
                    texts[p] = texts[p].replace(b + "\n", "", 1)
                elif b in texts[p]:
                    texts[p] = texts[p].replace(b, "", 1)
    else:
        order = []
    body = ""
    if order:
        body += "\n" + "\n".join(x.rstrip("\n") + "\n" for x in order)
    if protos:
        body += "\n" + "".join("extern void %s();\n" % r for r in protos if not re.search(r"\b%s\s*\(" % r, hdr))
    body += "\n" + "\n".join(exts) + "\n"
    k = hdr.rindex("#endif")
    hdr = hdr[:k].rstrip("\n") + "\n" + body + "\n" + hdr[k:]
    open(path, "w").write(hdr)
