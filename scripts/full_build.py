#!/usr/bin/env python3
"""
Build a whole image (the game code of the executable, or an overlay), mixing decompiled C
and assembly generated from the original.

  * functions marked "// Matched" in the C sources are compiled from C,
  * every other function is generated from the original image (scripts/gen_asm.py) and pulled
    in as inline asm() - the "INCLUDE_ASM" idea, it goes through CC1PSX and ASPSX like any C file,
  * everything is emitted in address order into one generated C file, so each function lands at its
    real address,
  * a C function that does not reproduce the original bytes in the linked image is replaced by
    assembly and the image is rebuilt, so the result is always at the right addresses.

       full_build.py --overlay NAME ISO.bin SLUS_008.54   overlay -> build_psyq/overlay_name.bin  (see overlays.py)
"""
import os
import re
import struct
import subprocess
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_asm  # noqa: E402

BUILD = os.path.join(REPO, "build_psyq")
PSYQ = os.path.join(REPO, "libs", "psyq4.4")
BIN = os.path.join(PSYQ, "bin")


def wine(cmd):
    return ["wine"] + cmd if sys.platform.startswith("linux") else cmd


def run(cmd, check=True):
    r = subprocess.run(wine(cmd), stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    out = r.stdout.decode(errors="replace")
    if check and r.returncode != 0:
        sys.stdout.write(out)
        sys.exit("command failed: %s" % " ".join(cmd))
    return r.returncode, out

# ----------------------------------------------------------------------------
# splitting the C sources into top-level blocks

SIG = re.compile(r"^[A-Za-z_][\w \*]*?\b(\w+)\(.*\)\s*$")
VARDEF = re.compile(r"^(?P<decl>(?!typedef|extern|struct\s*\{|enum|union|#)[^=;{}()]+?)\s*(=.*)?;$", re.S)


def split_blocks(text):
    """returns [(kind, name, text, matched)] with kind in 'func', 'other'; comments stay with the next block"""
    lines = text.split("\n")
    blocks, cur, depth = [], [], 0
    for ln in lines:
        cur.append(ln)
        depth += ln.count("{") - ln.count("}")
        if depth == 0 and ln.strip() and (ln.rstrip().endswith((";", "}")) or ln.startswith("#")):
            blocks.append(cur)
            cur = []
        elif depth == 0 and not ln.strip() and all(not l.strip() for l in cur):
            cur = []
    if cur:
        blocks.append(cur)
    out = []
    for b in blocks:
        body = [l for l in b if l.strip() and not l.strip().startswith("//")]
        name = None
        if len(body) >= 2 and body[1].strip() == "{" and SIG.match(body[0]):
            name = SIG.match(body[0]).group(1)
        out.append(("func" if name else "other", name, "\n".join(b).strip("\n"),
                    any(l.strip() == "// Matched" for l in b)))
    return out


def to_extern(text):
    """data definitions become declarations, the link script pins them to their original address"""
    body = "\n".join(l for l in text.split("\n") if not l.strip().startswith("//"))
    m = VARDEF.match(body.strip())
    if m and "(" not in body.split("=")[0]:
        decl = m.group("decl").strip()
        if decl.startswith("static"):
            return text
        return "extern " + decl + ";"
    return text


def asm_stmt(text):
    lines = text.rstrip("\n").split("\n")
    return "asm(\n" + "\n".join('    "%s\\n"' % l.replace("\\", "\\\\").replace('"', '\\"') for l in lines).lstrip() + ");"

# ----------------------------------------------------------------------------

def masked_equal(orig, built):
    """same rule as check_match.py: j/jal targets and global address immediates are ignored"""
    lui = set()
    for i in range(0, len(orig), 4):
        a = struct.unpack("<I", orig[i:i + 4])[0]
        b = struct.unpack("<I", built[i:i + 4])[0]
        op = a >> 26
        if a == b:
            if op == 15:
                lui.add((a >> 16) & 31)
            continue
        if op == b >> 26 and op in (2, 3):
            continue
        if op == 15 and op == b >> 26 and (a >> 16 & 31) == (b >> 16 & 31):
            lui.add((a >> 16) & 31)
            continue
        if op == b >> 26 and ((a >> 21) & 31) == ((b >> 21) & 31) and ((a >> 16) & 31) == ((b >> 16) & 31):
            if op >= 8 and (((a >> 21) & 31) in lui or ((a >> 21) & 31) == 28):
                continue
        return False
    return True


class Target:
    def __init__(self, name, image, base, end, symfile, sources, extra_syms=()):
        self.name, self.image, self.base, self.end = name, image, base, end
        self.symfile, self.sources = symfile, sources
        self.extra_syms = extra_syms


def build(target, verbose=True, pin_data=False):
    gen_asm.configure(target.base, target.end)
    syms = sorted(set(gen_asm.load_symbols(REPO, target.symfile)) |
                  {x for x in target.extra_syms if not (target.base <= x[0] < target.end)})
    code = [(a, n) for a, n in syms if target.base <= a < target.end]
    names = {a: n for a, n in syms}
    addr_of = {n: a for a, n in syms}
    spans = {n: b - a for (a, n), (b, _) in zip(code, code[1:] + [(target.end, "")])}
    from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32, CS_MODE_LITTLE_ENDIAN
    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32 + CS_MODE_LITTLE_ENDIAN)

    c_funcs, others, seen = {}, [], set()
    for fn in target.sources:
        path = os.path.join(REPO, "src", fn)
        if not os.path.exists(path):
            continue
        for kind, name, text, matched in split_blocks(open(path).read()):
            if kind == "func":
                if matched and name in addr_of:
                    c_funcs[name] = text
                continue
            if text.startswith("#include"):
                if text in seen:
                    continue
                seen.add(text)
            others.append(to_extern(text) if pin_data else text)

    use_c = set(c_funcs)
    os.makedirs(BUILD, exist_ok=True)
    # Symbols the linker cannot find (library code, other images, data that is not defined in C yet) are
    # given their original address. Data defined in C is NOT pinned unless pin_data is set, so a
    # difference in data layout stays visible in the result.
    equs = {}
    if pin_data:
        equs = {n: a for a, n in syms if not (target.base <= a < target.end)}

    saved_try = False
    for attempt in range(40):
        parts = ["/* generated by scripts/full_build.py, do not edit */"] + others
        for (a, n) in code:
            size = spans[n]
            if n in use_c:
                parts.append(c_funcs[n])
            elif n.startswith(gen_asm.DATA_PREFIXES):
                parts.append(asm_stmt(gen_asm.emit_data(target.image, n, a, size)))
            else:
                parts.append(asm_stmt(gen_asm.emit_function(md, target.image, n, a, size, names)))
        src = os.path.join(BUILD, target.name + ".c")
        open(src, "w").write("\n\n".join(parts) + "\n")

        inc = ["-I", os.path.join(PSYQ, "INCLUDE"), "-I", os.path.join(REPO, "src")]
        pre, cc, obj = (os.path.join(BUILD, target.name + e) for e in (".preproc", ".o", ".obj"))
        run([os.path.join(BIN, "CPPPSX.EXE"), "-undef", "-D__GNUC__=2", "-v", "-D__OPTIMIZE__"] + inc + [
            "-lang-c", "-Dmips", "-D__mips__", "-D__mips", "-Dpsx", "-D__psx__", "-D__psx", "-D_PSYQ",
            "-D__EXTENSIONS__", "-D_MIPSEL", "-D__CHAR_UNSIGNED__", "-D_LANGUAGE_C", "-DLANGUAGE_C", src, pre])
        rc, out = run([os.path.join(BIN, "CC1PSX.EXE"), "-quiet", "-G0", "-O2", pre, "-o", cc], check=False)
        if rc != 0:
            # a C function that does not compile any more (e.g. wrong prototype) falls back to assembly
            bad = re.findall(r"in function `(\w+)'", out)
            bad = [b for b in bad if b in use_c]
            if not bad:
                sys.stdout.write(out)
                sys.exit("compile failed")
            use_c -= set(bad[:1])
            continue
        run([os.path.join(BIN, "ASPSX.EXE"), "-G0", "-q", cc, "-o", obj])

        cmd = os.path.join(BUILD, target.name + "_link.txt")
        with open(cmd, "w") as f:
            f.write("\torg\t$%08x\n" % target.base)
            for g, kw in (("text", ""), ("rdata", ""), ("data", ""), ("bss", "\tbss")):
                f.write("%s\tgroup%s\n" % (g, kw))
            for sec, g in ((".text", "text"), (".rdata", "rdata"), (".data", "data"), (".sdata", "data"),
                           (".sbss", "bss"), (".bss", "bss")):
                f.write("\tsection\t%s,%s\n" % (sec, g))
            f.write('\tinclude "%s"\n' % obj)
            for n, a in sorted(equs.items()):
                f.write("%s\tequ\t$%08x\n" % (n, a))
        cpe = os.path.join(BUILD, target.name + ".cpe")
        mapf = os.path.join(BUILD, target.name + ".map")
        rc, out = run([os.path.join(BIN, "psylink.exe"), "/l", os.path.join(PSYQ, "LIB"), "/c", "/n", "4000",
                       "/q", "/m", "@%s,%s,%s,%s" % (cmd, cpe, os.path.join(BUILD, target.name + ".sym"), mapf)],
                      check=False)
        missing = set(re.findall(r"Symbol '(\w+)' not defined", out))
        if rc != 0:
            new = {}
            for m in missing:
                g = re.fullmatch(r"\w*?_?([0-9A-Fa-f]{8})", m)
                if m in addr_of:
                    new[m] = addr_of[m]
                elif g:
                    new[m] = int(g.group(1), 16)
            new = {k: v for k, v in new.items() if k not in equs}
            if not new:
                sys.stdout.write(out)
                sys.exit("link failed")
            equs.update(new)
            continue
        run([os.path.join(BIN, "cpe2exe.exe"), "-CA", cpe])

        built = open(os.path.join(BUILD, target.name + ".exe"), "rb").read()[0x800:]
        if not saved_try:  # keep the first image (every candidate built from C) around for diffing
            open(os.path.join(BUILD, target.name + "_try.exe"), "wb").write(
                open(os.path.join(BUILD, target.name + ".exe"), "rb").read())
            saved_try = True
        if not saved_try:  # keep the first image (all candidates as C) around for diffing
            open(os.path.join(BUILD, target.name + "_try.exe"), "wb").write(open(os.path.join(BUILD, target.name + ".exe"), "rb").read())
        bmap = {}
        for line in open(mapf):
            m = re.match(r"\s*([0-9A-F]{8})\s+(\w+)\s*$", line)
            if m:
                bmap[m.group(2)] = int(m.group(1), 16)
        # a C function is only kept if it is at its real address and reproduces the original bytes
        bad = []
        for (a, n) in code:
            if n not in use_c:
                continue
            size = spans[n]
            o = target.image[a - target.base:a - target.base + size]
            b = built[a - target.base:a - target.base + size]
            if bmap.get(n) != a or len(b) < size or not masked_equal(o, b):
                bad.append(n)
                break  # later functions may only be wrong because this one shifted them
        if not bad:
            break
        if verbose:
            print("  falling back to assembly for", bad[0])
        use_c -= set(bad)
    else:
        sys.exit("did not converge")

    total = (target.end - target.base) // 4
    diff = 0
    addr_only = 0  # differing words in functions that only differ in the address of a global (data layout)
    for (a, n) in code:
        size = spans[n]
        o = target.image[a - target.base:a - target.base + size]
        b = built[a - target.base:a - target.base + size]
        words = sum(1 for i in range(0, size, 4) if o[i:i + 4] != b[i:i + 4])
        diff += words
        if words and masked_equal(o, b):
            addr_only += words
    return {"c": len(use_c), "asm": len(code) - len(use_c), "words": total, "diff": diff, "addr_only": addr_only,
            "exe": os.path.join(BUILD, target.name + ".exe"), "built": built[:total * 4]}


def report(r, what):
    print("%d functions from C, %d from assembly" % (r["c"], r["asm"]))
    print("%s: %d / %d words identical to the original" % (what, r["words"] - r["diff"], r["words"]))
    if r["diff"]:
        print("  %d differing words only differ in the address of a global (data layout), %d are real differences"
              % (r["addr_only"], r["diff"] - r["addr_only"]))


def main():
    if len(sys.argv) >= 2 and sys.argv[1] == "--overlay":
        import overlays
        return overlays.main(sys.argv[2:])
    sys.exit("the executable is built from the TU sources now: run scripts/split.py once, then build.py (docs/full_build.md)")


if __name__ == "__main__":
    sys.exit(main())
