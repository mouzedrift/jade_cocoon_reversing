#!/usr/bin/env python3
"""
List symbols whose address in the build differs from symbol_addrs.txt, in address order. The first entry of
each section is where the layout starts to drift (usually the symbol before it has the wrong size).
usage: sym_diff.py [N]
"""
import re
import sys

REPO = __file__.rsplit("/scripts/", 1)[0]
m = {}
for l in open(REPO + "/build_psyq/jade_cocoon.map"):
    x = re.match(r"\s*([0-9A-F]{8})\s+(\w+)\s*$", l)
    if x:
        m[x.group(2)] = int(x.group(1), 16)
s = {}
for l in open(REPO + "/symbol_addrs.txt"):
    x = re.match(r"(\w+)=0x([0-9a-fA-F]+);", l)
    if x:
        s[x.group(1)] = int(x.group(2), 16)
names = sorted((n for n in m if n in s and 0x80010000 <= s[n] < 0x800A05A0), key=lambda n: s[n])
bad = [n for n in names if m[n] != s[n]]
print("%d of %d symbols in the image are at their original address" % (len(names) - len(bad), len(names)))
last = None
shown = 0
for i, n in enumerate(names):
    if m[n] != s[n]:
        d = m[n] - s[n]
        if d != last:
            prev = names[i - 1] if i else "-"
            print("%-36s orig %08x built %08x (%+d)   previous symbol: %s" % (n, s[n], m[n], d, prev))
            shown += 1
            if shown >= int(sys.argv[1] if len(sys.argv) > 1 else 15):
                break
        last = d
