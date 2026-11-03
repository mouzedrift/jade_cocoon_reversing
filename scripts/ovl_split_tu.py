#!/usr/bin/env python3
"""
Split an overlay's C source into several source files (the original's translation units).

usage: ovl_split_tu.py NAME TEXT:RDATA [TEXT:RDATA ...]

Every TEXT:RDATA pair starts a new file at the function at TEXT, whose .rdata starts at RDATA (needs a
symbol there; the data blob in front is split if there is none). Declarations (typedefs, externs, defines)
move to src/overlays/<name>.h, which every part includes; functions, INCLUDE_OVERLAY_ASM lines and #if 0
near-misses go to src/overlays/<name>.c, <name>_2.c, ... by address (a near-miss goes with the
INCLUDE_OVERLAY_ASM line behind it, .data behind the code to the last part). Run overlays.py after it.
"""
import os
import re
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
DATA = re.compile(r"(dword|word|byte|jpt|stru|off)_")


def chunks(text):
    """top-level pieces of a C file; comments and blank lines stay with the piece behind them"""
    out, cur, depth, pp = [], [], 0, 0
    for ln in text.split("\n"):
        cur.append(ln)
        s = ln.strip()
        if re.match(r"#\s*if", s):
            pp += 1
        elif re.match(r"#\s*endif", s):
            pp -= 1
        if not s.startswith(("#", "//")):
            depth += ln.count("{") - ln.count("}")
        if depth == 0 and pp == 0 and s and not s.startswith("//") and (
                s.endswith((";", "}")) or s.startswith("#") or s.endswith("*/")):
            out.append("\n".join(cur))
            cur = []
    if any(l.strip() for l in cur):
        out.append("\n".join(cur))
    return out


def code_lines(c):
    return [l.strip() for l in c.split("\n") if l.strip() and not l.strip().startswith(("//", "/*", "*"))]


def main(argv):
    name = argv[0].lower()
    cuts = [tuple(int(x, 16) for x in a.split(":")) for a in argv[1:]]
    symfile = os.path.join(REPO, "overlays", name + ".sym")
    symtext = open(symfile).read()
    addr = {m.group(1): int(m.group(2), 16) for m in re.finditer(r"(\w+)=0x([0-9a-f]+);", symtext)}
    code = [a for n, a in addr.items() if not DATA.match(n)]
    first_code = min(code)
    # a symbol at each part's .rdata start
    created = set()
    for _, r in cuts:
        if r not in addr.values():
            n = "dword_%08X" % r
            symtext = symtext.rstrip("\n") + "\n%s=0x%08x; // .rdata of the next source file\n" % (n, r)
            addr[n] = r
            created.add(n)
    lines = sorted(symtext.rstrip("\n").split("\n"), key=lambda l: int(re.search(r"=0x([0-9a-f]+);", l).group(1), 16)
                   if re.search(r"=0x([0-9a-f]+);", l) else -1)
    open(symfile, "w").write("\n".join(lines) + "\n")

    def part(a, is_data):
        if is_data and a < first_code:
            return sum(1 for _, r in cuts if a >= r)
        if is_data:
            return len(cuts)
        return sum(1 for t, _ in cuts if a >= t)

    src = os.path.join(REPO, "src", "overlays", name + ".c")
    pieces = chunks(open(src).read())
    header, parts, pending = [], [[] for _ in range(len(cuts) + 1)], []
    new_includes = created  # (an existing symbol there is included already, or replaced by compiler output)
    seen_includes = set()
    for c in pieces:
        cl = code_lines(c)
        first = cl[0] if cl else ""
        m = re.match(r"INCLUDE_OVERLAY_ASM\(\w+,\s*(\w+)\);", first)
        if m:
            n = m.group(1)
            seen_includes.add(n)
            p = part(addr[n], bool(DATA.match(n)))
            parts[p] += pending + [c]
            pending = []
            continue
        if first.startswith("#if 0"):
            pending.append(c)
            continue
        f = re.match(r"^[A-Za-z_][\w \*]*?\b(\w+)\s*\(", first)
        is_func = (f and not first.endswith(";") and not first.startswith(("typedef", "struct", "enum", "union", "extern"))
                   and "{" in c)
        if is_func and first.startswith("static"):
            header.append(c)  # static (inline) helpers: every part that uses them gets its own copy
            continue
        if is_func:
            n = f.group(1)
            if n not in addr:
                sys.exit("function %s has no symbol in %s" % (n, symfile))
            parts[part(addr[n], False)] += pending + [c]
            pending = []
            continue
        if first.startswith("#include"):
            header.append(c)
        elif first.startswith("#undef"):
            continue  # all macros live in the header now
        else:
            header.append(c)
    if pending:
        parts[-1] += pending
    # the blob behind each new .rdata symbol: its INCLUDE_OVERLAY_ASM goes in front of the part's first piece
    for n in sorted(new_includes - seen_includes, key=lambda n: addr[n]):
        parts[part(addr[n], True)].insert(0, "INCLUDE_OVERLAY_ASM(%s, %s);" % (name, n))
    hdr = os.path.join(REPO, "src", "overlays", name + ".h")
    open(hdr, "w").write("// %s.BIN: declarations shared by its source files\n" % name.upper()
                         + "\n\n".join(h.strip("\n") for h in header if h.strip()) + "\n")
    for i, p in enumerate(parts):
        path = src if i == 0 else os.path.join(REPO, "src", "overlays", "%s_%d.c" % (name, i + 1))
        what = "" if i == 0 else " from 0x%08X (.rdata from 0x%08X)" % cuts[i - 1]
        open(path, "w").write("// %s.BIN, source file %d of %d%s\n#include \"%s.h\"\n\n" % (
            name.upper(), i + 1, len(parts), what, name) + "\n\n".join(x.strip("\n") for x in p) + "\n")
        print(path, len(p), "pieces")
    print(hdr, len(header), "pieces")


if __name__ == "__main__":
    main(sys.argv[1:])
