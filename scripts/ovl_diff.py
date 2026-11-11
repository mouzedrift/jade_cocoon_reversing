#!/usr/bin/env python3
"""usage: ovl_diff.py NAME  -- functions of build_psyq/NAME.BIN that differ from the disc (needs the previous overlays.py run)"""
import re, sys
REPO = __file__.rsplit("/scripts/", 1)[0]
name = sys.argv[1].upper()
syms = []
for l in open("%s/overlays/%s.sym" % (REPO, name.lower())):
    m = re.match(r"(\w+)=0x([0-9a-f]+);", l)
    if m:
        syms.append((int(m.group(2), 16), m.group(1)))
orig = open("%s/build_psyq/%s.orig" % (REPO, name), "rb").read()
built = open("%s/build_psyq/%s.BIN" % (REPO, name), "rb").read()
base = syms[0][0]
for (a, n), (b, _) in zip(syms, syms[1:] + [(base + len(orig), "")]):
    o, x = orig[a - base:b - base], built[a - base:b - base]
    d = sum(1 for i in range(0, len(o), 4) if o[i:i + 4] != x[i:i + 4])
    if d:
        print(n, d, "of", len(o) // 4, "words")
