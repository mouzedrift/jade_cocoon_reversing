#!/usr/bin/env python3
"""usage: ovl_fdiff.py NAME FUNC  -- side-by-side disassembly of FUNC in build_psyq/NAME.BIN vs the disc's NAME.orig

Build first with the full `python build.py` (--no-verify does not rebuild the overlays, the BINs would be stale). The function is located by its address in overlays/NAME.sym in
the original and by the symbol table of the built overlay's map (falls back to the same address). Lines that differ
are marked with '*'. Exit code 0 when the function is identical."""
import os
import re
import sys

import capstone

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))


def syms_of(name):
    out = []
    for l in open("%s/overlays/%s.sym" % (REPO, name.lower())):
        m = re.match(r"(\w+)=0x([0-9a-f]+);", l)
        if m:
            out.append((int(m.group(2), 16), m.group(1)))
    return out


def built_addr(name, func):
    # the built overlay is linked at the same base; find the symbol in the map if there is one
    for cand in ("%s/build_psyq/%s.map" % (REPO, name), "%s/build_psyq/%s.MAP" % (REPO, name)):
        if os.path.exists(cand):
            for l in open(cand, errors="replace"):
                m = re.search(r"([0-9A-Fa-f]{8})\s+" + re.escape(func) + r"\b", l)
                if m:
                    return int(m.group(1), 16)
    return None


def dis(data, addr):
    md = capstone.Cs(capstone.CS_ARCH_MIPS, capstone.CS_MODE_MIPS32 + capstone.CS_MODE_LITTLE_ENDIAN)
    res = []
    for i in range(0, len(data) - 3, 4):
        w = data[i:i + 4]
        ins = list(md.disasm(w, addr + i))
        if ins:
            t = "%s %s" % (ins[0].mnemonic, ins[0].op_str)
        else:
            t = ".word 0x%08x" % int.from_bytes(w, "little")
        # jal/branch targets are absolute; keep them, the overlay base is the same
        res.append(t)
    return res


def main():
    name, func = sys.argv[1].upper(), sys.argv[2]
    syms = syms_of(name)
    base = syms[0][0]  # the first entry of the .sym file is the overlay start (not the lowest address)
    syms = sorted(syms)
    orig = open("%s/build_psyq/%s.orig" % (REPO, name), "rb").read()
    built = open("%s/build_psyq/%s.BIN" % (REPO, name), "rb").read()
    idx = [i for i, (a, n) in enumerate(syms) if n == func]
    if not idx:
        sys.exit("no symbol " + func)
    i = idx[0]
    a = syms[i][0]
    b = syms[i + 1][0] if i + 1 < len(syms) else base + len(orig)
    o = dis(orig[a - base:b - base], a)
    ba = built_addr(name, func) or a
    n = len(o) + 16
    x = dis(built[ba - base:ba - base + 4 * n], ba)
    diff = 0
    for k in range(max(len(o), len(x))):
        l = o[k] if k < len(o) else ""
        r = x[k] if k < len(x) else ""
        mark = " " if l == r else "*"
        if l != r and k < len(o):
            diff += 1
        print("%s %4x  %-40s %s" % (mark, 4 * k, l, r))
    print("%d of %d words differ" % (diff, len(o)))
    sys.exit(1 if diff else 0)


main()
