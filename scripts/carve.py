#!/usr/bin/env python3
"""
Carve the jump tables of a switch function out of an overlay's data in front of the code, so that the
compiler can emit them in place.

usage: carve.py NAME FUNC       (needs build_psyq/NAME.orig from a previous overlays.py run)

The tables are the runs of words pointing into FUNC that sit in the data before the first function. For
every table jpt_<addr> and the data behind it dword_<end> are added to overlays/<name>.sym, and in
src/overlays/<name>.c the INCLUDE_OVERLAY_ASM lines for them are put behind FUNC (the table first, so
the build stays identical while FUNC is still assembly). When FUNC is written in C, delete the jpt_ line:
the compiler emits the table and the dword_ piece behind it keeps the data in the right order.
"""
import os
import re
import struct
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))


def main(name, func):
    sym = os.path.join(REPO, "overlays", name.lower() + ".sym")
    lines = open(sym).read().splitlines()
    syms = [(int(m.group(2), 16), m.group(1)) for m in (re.match(r"(\w+)=0x([0-9a-f]+);", l) for l in lines) if m]
    syms.sort()
    base = syms[0][0]
    data = open(os.path.join(REPO, "build_psyq", name.upper() + ".orig"), "rb").read()
    code = [(a, n) for a, n in syms if n.startswith("sub_")]
    first = code[0][0]
    fa = dict((n, a) for a, n in code)[func]
    fend = next((a for a, n in syms if a > fa and n.startswith(("sub_", "dword_"))), base + len(data))
    out = []
    i = 0
    while base + i < first:
        w = struct.unpack("<I", data[i:i + 4])[0]
        if fa <= w < fend and w % 4 == 0:
            j = i
            while base + j < first and fa <= struct.unpack("<I", data[j:j + 4])[0] < fend:
                j += 4
            if (j - i) // 4 >= 3:
                out.append((base + i, base + j))
            i = j
        else:
            i += 4
    if not out:
        sys.exit("no jump table for %s found" % func)
    have = {a for a, _ in syms}
    add = []
    # the source file (of an overlay built from several: <name>.c, <name>_2.c, ...) that has FUNC
    import glob
    inc = "INCLUDE_OVERLAY_ASM(%s, %s);" % (name.lower(), func)
    cands = sorted(glob.glob(os.path.join(REPO, "src", "overlays", name.lower() + "*.c")))
    c = next((p for p in cands if inc in open(p).read()), os.path.join(REPO, "src", "overlays", name.lower() + ".c"))
    src = open(c).read()
    ins = []
    for s, e in out:
        print("table 0x%08x..0x%08x (%d entries)" % (s, e, (e - s) // 4))
        if s not in have:
            add.append("jpt_%08X=0x%08x; // jump table of %s" % (s, s, func))
            ins.append("jpt_%08X" % s)
        if e not in have and e < first:
            add.append("dword_%08X=0x%08x; // data behind the jump table" % (e, e))
            ins.append("dword_%08X" % e)
    new = sorted(lines + add, key=lambda l: int(re.match(r"\w+=0x([0-9a-f]+)", l).group(1), 16))
    open(sym, "w").write("\n".join(new) + "\n")
    # behind FUNC in the source (its INCLUDE line or the end of its C definition's INCLUDE line)
    if inc in src and ins:
        src = src.replace(inc, inc + "".join("\nINCLUDE_OVERLAY_ASM(%s, %s);" % (name.lower(), n) for n in ins))
        open(c, "w").write(src)
    elif ins:
        print("put these behind %s by hand: %s" % (func, ", ".join(ins)))


main(sys.argv[1], sys.argv[2])
