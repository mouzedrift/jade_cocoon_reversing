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
    import ovldata
    code = [a for a, n in osyms if not ovldata.is_data(n)]
    lo = min(code)
    hi = next((a for a, n in osyms if a > max(code)), base + len(data))
    return lo, hi


def ovldata_is_data(n):
    import ovldata
    return ovldata.is_data(n)


def gendata_prefixes():
    import gen_asm
    return gen_asm.DATA_PREFIXES


def includes(text, oname):
    """[(name, match)] of the INCLUDE_OVERLAY_ASM lines of a source text that are data (not jump tables)"""
    out = []
    for m in re.finditer(r"^INCLUDE_OVERLAY_ASM\(%s, (\w+)\);[^\n]*\n?" % oname, text, re.M):
        n = m.group(1)
        if ovldata_is_data(n) and not n.startswith("jpt_"):
            out.append((n, m))
    return out


def preproc_path(name, k):
    return os.path.join(REPO, "build_psyq", "overlay_" + name.lower() + ("_%d" % (k + 1) if k else "") + ".preproc")


def header_path(name):
    return os.path.join(REPO, "src", "overlays", name.lower() + ".h")


def main(name, exe, data, base, osyms, lib_ranges, only, write):
    import ovldata
    ovldata.load_data_names(name)   # (this runs as ovldata's __main__, which is another module object)
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
    other_types = {}
    srcs = ovldata.sources(name)
    texts = {p: open(p).read() for p in srcs}
    renames = {}        # .sym name -> the name the definition has
    new_syms = {}       # name -> addr of definitions the .sym file doesn't have
    report = []
    for k, src in enumerate(srcs):
        incs = includes(texts[src], oname)
        # a zero word in front of a jump table is the table's alignment (it goes once the function is C)
        # a table of places inside functions is a jump table of a function that is still assembly
        def jump_table(n):
            sec, size = chunk(n)
            if size < 8 or size % 4:
                return False
            ws = struct.unpack("<%dI" % (size // 4), syms.rd(syms.addr[n], size))
            fstarts = {a for a, nn in sym_list if not ovldata.is_data(nn)}
            return all(lo <= w < hi for w in ws) and any(w not in fstarts for w in ws)
        incs = [x for x in incs if not jump_table(x[0])]
        incs = [x for x in incs if not (chunk(x[0])[1] == 4 and not any(syms.rd(syms.addr[x[0]], 4)) and any(
            a == syms.addr[x[0]] + 4 and nn.startswith("jpt_") for a, nn in sym_list))]
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
        # the functions the overlay's other files define (without their parameters, which may use those files'
        # own types): pointers to them in the data are typed by these, and get a prototype in the header
        types.foreign = set()
        if len(srcs) > 1:
            import copy
            for k2 in range(len(srcs)):
                if k2 == k:
                    continue
                if k2 not in other_types:
                    other_types[k2] = gendata.Types(gendata.parse_preproc(preproc_path(name, k2)))
                for fname, fnode in other_types[k2].funcnodes.items():
                    if fname not in types.funcnodes:
                        fnode = copy.deepcopy(fnode)
                        fnode.args = None
                        types.funcnodes[fname] = fnode
                        types.funcs.add(fname)
                        types.foreign.add(fname)
        propagate(types, syms, names, chunk)
        for n in names:
            sec, size = chunk(n)
            if n in types.decls or sec in (".bss", ".sdata") or syms.addr[n] % 4:
                continue
            b = syms.rd(syms.addr[n], size)
            s0 = b.split(b"\0")[0]
            if len(s0) >= 2 and gendata.is_text(s0) and len(s0) < len(b) and gendata.split_strings(b, rest=True) is None:
                # a string with bytes behind its terminator: one char array
                from pycparser import c_ast
                td = c_ast.TypeDecl(n, [], None, c_ast.IdentifierType(["char"]))
                arr = c_ast.ArrayDecl(td, c_ast.Constant("int", str(size)), [])
                types.decls[n] = c_ast.Decl(n, [], [], [], [], arr, None, None)
        gen = gendata.Gen(syms, types)
        gen.int_refs = True

        def chunk_of(n, _gen=gen):
            return chunk(n) if n in syms.addr and base <= syms.addr[n] < end and any(
                x == n for _, x in sym_list) else gendata.Gen.chunk_of(n)
        gen.chunk_of = chunk_of
        info = {}
        for n in names:
            sec, size = chunk(n)
            info[n] = (".rdata" if sec == ".sdata" else sec, size)
        # places inside a chunk the source declares (not split by ovldata.py split: not on 4 bytes, or the
        # generated assembly has no symbol there yet) are chunks of their own, defined in place of the chunk's line
        parent = {}
        declared = {}
        for dn in types.decls:
            m = re.search(r"_([0-9A-F]{8})$", dn)
            if m:
                declared.setdefault(int(m.group(1), 16), dn)
        allnames = []
        for n in names:
            a = syms.addr[n]
            sec, size = info[n]
            lim = a
            hd = next((x for x in syms.by_addr.get(a, []) if x in types.decls), None)
            if hd is not None:
                try:
                    lim = a + types.resolve(types.decls[hd].type).size()
                except GenError:
                    lim = a + size      # an array of unknown length: what follows is more of it
            inner = sorted(x for x in declared if max(a, lim - 1) < x < a + size and x not in syms.by_addr)
            cuts = [a] + inner + [a + size]
            allnames.append(n)
            info[n] = (sec, cuts[1] - a)
            for x, y in zip(inner, cuts[2:]):
                vn = declared[x]
                syms.add(vn, x)
                parent[vn] = n
                info[vn] = (sec, y - x)
                allnames.append(vn)
        names = allnames
        todo, defs, absorbed, errors, types, syms, gen = gendata.generate_chunks(syms, types, gen, names, info)
        for vn, n in parent.items():
            if vn in errors and n not in errors:
                errors[n] = "%s: %s" % (vn, errors[vn])
        for d in defs:
            d.head = parent.get(d.head, d.head)
        todo = [n for n in todo if n not in parent]
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
        # an object that is smaller than its chunk by less than a word leaves a gap; when the next object's
        # alignment doesn't produce it (a byte behind a byte array), the bytes become objects of their own
        bysec = {}
        for d in ok:
            bysec.setdefault(d.sec, []).append(d)
        for sec, ds in bysec.items():
            ds.sort(key=lambda d: d.addr)
            for prev, d in zip(ds, ds[1:]):
                pe = prev.addr + prev.t.size()
                al = 4 if d.t.kind in ("array", "struct", "union") else d.t.align()
                if not (0 < d.addr - pe < 4) or (pe + al - 1) // al * al == d.addr:
                    continue
                x = pe
                fill = []
                while (x + al - 1) // al * al != d.addr:
                    fn = "byte_%08X" % x
                    v = syms.rd(x, 1)[0]
                    f = Def(prev.head, fn, x, sec, gendata.U8, "unsigned char %s" % fn, False)
                    f.text = ("unsigned char %s BSS = 0;" % fn) if sec == ".bss" else (
                        "%sunsigned char %s = %d;" % ("const " if sec == ".rdata" else "", fn, v))
                    f.refs = set()
                    fill.append(f)
                    x += 1
                k = ok.index(prev)
                ok[k + 1:k + 1] = fill
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
                elif absorbed.get(n) in heads and absorbed[n] not in dropped:
                    continue        # part of a definition (its line goes)
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
        for r in sorted(gen.protos) + sorted(x for x in d.refs if x in types.foreign):
            if r not in protos:
                protos.append(r)
    defined = {d.name for _, d, _, _ in all_defs}
    for p in texts:
        t = texts[p]
        # (the declarations of code in #if 0 blocks stay as they are)
        for n in defined:
            live = mask_if0(t)
            for m in reversed(list(re.finditer(r"^extern\b[^;\n]*[\s*(]%s\s*[\[);][^\n]*\n" % re.escape(n), t, re.M))):
                if live[m.start():m.start() + 6] == "extern":
                    t = t[:m.start()] + t[m.end():]
        texts[p] = t
    # symbols of the executable the initialisers use that the overlay doesn't see: the header that declares them
    hdrs = []
    extra = []
    for src, d, types, gen in all_defs:
        for r in sorted(d.refs):
            if r in defined or r in types.decls or r in types.funcs:
                continue
            if r in gen.outside or (r in syms.addr and base <= syms.addr[r] < end and ovldata.is_data(r)):
                # a place outside the images, or one of the overlay's chunks that stays assembly
                t = gen.type_of(r)
                line = "extern char %s[];" % r if r in gen.outside or (t is not None and t.kind == "array") else \
                    "extern int %s;" % r
                if line not in extra:
                    extra.append(line)
                continue
            hs = [x for x in gendata.find_extern(r) if x[0].endswith(".h")] or gendata.find_proto(r)
            hs = [x for x in hs if os.sep + "overlays" + os.sep not in x[0]] or [
                x for x in gendata.find_extern(r) if os.sep + "overlays" + os.sep not in x[0]]
            if hs:
                # the declaration itself when the overlay knows its types, else the header
                line = hs[0][1].split("//")[0].strip()
                words = re.findall(r"[A-Za-z_]\w*", re.split(r"\b%s\b" % re.escape(r), line)[0])
                if all(w in gendata.C_WORDS or w in types.typedefs for w in words):
                    if line not in extra:
                        extra.append(line)
                    continue
                h = os.path.relpath(hs[0][0], os.path.join(REPO, "src"))
                if h not in hdrs:
                    hdrs.append(h)
            elif r not in protos:
                print("// %s uses %s, which nothing declares" % (d.name, r))
    # prototypes: from the definition when one of the overlay's files has the function in C
    ptext = []
    parsed = None
    for r in protos:
        node = None
        for _, d, types, _ in all_defs:
            node = types.funcnodes.get(r) or node
        if node is None:
            if parsed is None:
                parsed = [gendata.Types(gendata.parse_preproc(preproc_path(name, k))) for k in range(len(srcs))]
            for ty in parsed:
                node = ty.funcnodes.get(r) or node
        if node is not None:
            import copy
            node = copy.deepcopy(node)
            node.args = None    # (the parameter types may be the .c file's own)
        ptext.append(("extern %s;" % gendata.decl_text(gendata.named(node, r), r)) if node is not None
                     else "extern void %s();" % r)
    write_header(name, texts, extra + exts, list(zip(protos, ptext)), hdrs)
    for p, t in texts.items():
        open(p, "w").write(t)
    # the .sym file names every definition (the link script equates the other address names of the source)
    path = ovldata.sym_path(name)
    st = open(path).read()
    for old, new in renames.items():
        if not re.search(r"^%s=" % re.escape(old), st, re.M):
            new_syms[new] = syms.addr.get(new, None) or next(a for a, x in sym_list if x == old)
            continue
        st = re.sub(r"^%s=(0x[0-9a-fA-F]+;)(.*)$" % re.escape(old), lambda m: new + "=" + m.group(1) + (
            m.group(2) if ovldata.is_data(new) or "data" in m.group(2) else (m.group(2) + " // data" if m.group(2) else " // data")),
            st, flags=re.M)
    lines = st.rstrip("\n").split("\n")
    for n, a in sorted(new_syms.items(), key=lambda x: x[1]):
        k = 0
        while k < len(lines):
            m = re.match(r"\w+=0x([0-9a-fA-F]+);", lines[k])
            if m and int(m.group(1), 16) > a:
                break
            k += 1
        lines.insert(k, ovldata.sym_line(n, a))
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


def write_header(name, texts, exts, protos, hdrs=()):
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
    # declarations the header already has for the names are replaced
    for e in exts:
        live = mask_if0(hdr)
        m = re.search(r"(\w+)\s*(\[[^\]]*\]\s*)*(\)\s*\(\))?;$", e)
        n = m.group(1) if m else None
        if n is None:
            continue
        for mm in reversed(list(re.finditer(r"^extern\b[^;\n]*[\s*(]%s\s*[\[);][^\n]*\n" % re.escape(n), hdr, re.M))):
            if live[mm.start():mm.start() + 6] == "extern":
                hdr = hdr[:mm.start()] + hdr[mm.end():]
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
        body += "\n" + "".join(t + "\n" for r, t in protos if not re.search(r"\b%s\s*\(" % r, hdr))
    body += "\n" + "\n".join(exts) + "\n"
    add = "".join('#include "%s"\n' % h for h in hdrs if '#include "%s"' % h not in hdr)
    if add:
        ms = list(re.finditer(r'^#include .*\n', hdr, re.M))
        k = ms[-1].end() if ms else hdr.index("\n", hdr.index("#define")) + 1
        hdr = hdr[:k] + add + hdr[k:]
    k = hdr.rindex("#endif") if re.search(r"^#endif", hdr, re.M) else len(hdr)
    hdr = hdr[:k].rstrip("\n") + "\n" + body + ("\n" + hdr[k:] if k < len(hdr) else "")
    open(path, "w").write(hdr)
