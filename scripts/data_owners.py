#!/usr/bin/env python3
"""
Which TU a data symbol that is still INCLUDE_DATA belongs to, by the code that uses it.

  python scripts/data_owners.py SLUS_008.54 [--sec=.data|.bss] [--write]

split.py gives a data symbol to the smallest TU that references anything at or after it, which puts whole runs
of .data/.bss into the first TU that uses something late in the run (main.c had all of the .bss). Here a symbol
belongs to the first TU whose code references it (any address inside it), but never to a TU before the owner of
the symbol in front of it (each section is laid out TU by TU in link order); symbols nobody references stay with
the one in front. Any assignment in that order builds the same executable: --write moves the INCLUDE_DATA
lines to the end of their TU's file (in address order), for the C definitions to replace them there (behind the
declarations of the file).
"""
import bisect
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import split  # noqa: E402
from layout import *  # noqa: E402,F401,F403
import gendata  # noqa: E402

REPO = split.REPO


def references(exe, funcs):
    """address -> set of function indices that load/store/address it (lui + offset)"""
    fa = [a for a, _ in funcs]
    refs = {}
    lui = {}
    for pc in range(BASE, GAME_TEXT_END, 4):
        w = struct.unpack("<I", exe[pc - BASE:pc - BASE + 4])[0]
        i = bisect.bisect_right(fa, pc) - 1
        if i >= 0 and pc == fa[i]:
            lui = {}
        op, rs, rt, imm = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 0xffff
        s = imm - 0x10000 if imm >= 0x8000 else imm
        if op == 15:
            lui[rt] = imm << 16
            continue
        if op in (9, 35, 36, 32, 33, 37, 43, 40, 41, 34, 38) and rs in lui and i >= 0:
            refs.setdefault(lui[rs] + s, set()).add(i)
        if op == 0:
            lui.pop((w >> 11) & 31, None)
        elif op not in (43, 40, 41, 42, 46, 4, 5, 6, 7, 1, 2, 3):
            lui.pop(rt, None)
    return refs


def section_of(a):
    for sec, lo, hi in ((".rdata", RDATA_START, RDATA_GAME_END), (".data", DATA_START, DATA_GAME_END),
                        (".bss", BSS_START, BSS_GAME_END)):
        if lo <= a < hi:
            return sec
    return None


def line_definition(line):
    """the name a top-level data definition line defines, or None"""
    if not line[:1].isalpha() or line.startswith(("typedef", "extern", "static ", "INCLUDE", "struct", "union", "enum")):
        return None
    m = re.match(r"^[^=;(]*?[\s*(]+(\w+)\s*(\[[^\]]*\]\s*)*\)?\s*(\[[^\]]*\]\s*)*(=|BSS\s*;)", line)
    return m.group(1) if m else None


def c_definitions(tu):
    """names of the data a TU's file defines in C (top-level definitions with an initialiser or BSS)"""
    out = []
    for line in open(os.path.join(REPO, "src", tu + ".c"), encoding="latin1"):
        if not line[:1].isalpha() or line.startswith(("typedef", "extern", "static ", "INCLUDE", "struct", "union", "enum")):
            continue
        m = re.match(r"^[^=;(]*?[\s*(]+(\w+)\s*(\[[^\]]*\]\s*)*\)?\s*(\[[^\]]*\]\s*)*(=|BSS\s*;)", line)
        if m:
            out.append(m.group(1))
    return out


def main(argv):
    exe = open(argv[0], "rb").read()[0x800:]
    secs = [a.split("=", 1)[1] for a in argv if a.startswith("--sec=")] or [".data", ".bss"]
    syms = split.load_symbols()
    code = [(a, n) for a, n in syms if BASE <= a < GAME_TEXT_END]
    import gen_asm
    funcs = [(a, n) for a, n in code if not n.startswith(gen_asm.DATA_PREFIXES)]
    tus = split.load_tus()
    starts = [a for _, a in tus]
    tu_index = {n: k for k, (n, _) in enumerate(tus)}

    def tu_of(a):
        return bisect.bisect_right(starts, a) - 1
    refs = references(exe, funcs)
    # the INCLUDE_DATA symbols, where they are now
    where = {}
    for tu, _ in tus:
        for n in gendata.tu_data(tu):
            where[n] = tu
    s = gendata.Syms(exe)
    # data that is C already stays where it is: (address, TU index) per section
    fixed = {".rdata": [], ".data": [], ".bss": []}
    for tu, _ in tus:
        for n in c_definitions(tu):
            a = s.addr.get(n)
            for sec, lo, hi in ((".rdata", RDATA_START, RDATA_GAME_END), (".data", DATA_START, DATA_GAME_END),
                                (".bss", BSS_START, BSS_GAME_END)):
                if a is not None and lo <= a < hi:
                    fixed[sec].append((a, tu_index[tu]))
    moves = {}
    for sec in secs:
        fx = sorted(fixed[sec])
        items = sorted((s.addr[n], n) for n in where if gendata.chunk_info(n)[0] == sec and n in s.addr)
        prev = 0
        ra = sorted(refs)
        for k, (a, n) in enumerate(items):
            size = gendata.chunk_info(n)[1]
            lo = bisect.bisect_left(ra, a)
            hi = bisect.bisect_left(ra, a + size)
            users = set()
            for x in ra[lo:hi]:
                users |= {tu_of(funcs[f][0]) for f in refs[x]}
            before = [t for fa, t in fx if fa < a]
            after = [t for fa, t in fx if fa > a]
            low = max([prev] + before)
            up = min(after) if after else len(tus) - 1
            own = min(users) if users else low
            own = max(low, min(own, up))
            prev = own
            if tus[own][0] != where[n]:
                moves[n] = (where[n], tus[own][0], a, sec)
    for n, (old, new, a, sec) in sorted(moves.items(), key=lambda m: m[1][2]):
        print("%-6s %08X %-32s %s -> %s" % (sec, a, n, old, new))
    print(len(moves), "moves")
    if "--write" in argv:
        by_file = {}
        for n, (old, new, a, sec) in moves.items():
            by_file.setdefault(old, []).append(n)
        lines = {}
        for old, ns in by_file.items():
            p = os.path.join(REPO, "src", old + ".c")
            text = open(p).read()
            for n in ns:
                m = re.search(r"^INCLUDE_DATA\(%s\);[^\n]*\n" % n, text, re.M)
                lines[n] = m.group(0)
                text = text[:m.start()] + text[m.end():]
            open(p, "w").write(text)
        to = {}
        for n, (old, new, a, sec) in moves.items():
            to.setdefault(new, []).append((a, n))
        for new, items in to.items():
            p = os.path.join(REPO, "src", new + ".c")
            for a, n in sorted(items, reverse=True):
                sec = moves[n][3]
                text = open(p).read()
                # in front of the file's first data of the section that lies behind it, else at the end
                k = None
                for m in re.finditer(r"^(INCLUDE_DATA\((\w+)\);|[^\n]*)\n", text, re.M):
                    name = m.group(2) or line_definition(m.group(1))
                    if name and name in s.addr and s.addr[name] > a and section_of(s.addr[name]) == sec and \
                            (m.group(2) is None or gendata.chunk_info(name)[0] == sec):
                        k = m.start()
                        break
                if k is None:
                    text = text.rstrip("\n") + "\n\n" + lines[n]
                else:
                    text = text[:k] + lines[n] + text[k:]
                open(p, "w").write(text)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
