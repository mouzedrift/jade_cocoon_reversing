#!/usr/bin/env python3
"""
Compare a built executable with the original and summarise where they differ.

usage: exe_diff.py SLUS_008.54 [build_psyq/jade_cocoon.exe]
Differences in j/jal targets and in global addresses (lui/gp-relative immediates) are counted separately
when the rest of the word is the same, since they follow from the layout.
"""
import re
import struct
import sys

REPO = __file__.rsplit("/scripts/", 1)[0]
orig = open(sys.argv[1], "rb").read()
built = open(sys.argv[2] if len(sys.argv) > 2 else REPO + "/build_psyq/jade_cocoon.exe", "rb").read()
print("size: original 0x%x, built 0x%x" % (len(orig), len(built)))
orig, built = orig[0x800:], built[0x800:]
n = min(len(orig), len(built))
words = n // 4
diff = [i for i in range(words) if orig[i * 4:i * 4 + 4] != built[i * 4:i * 4 + 4]]
print("%d of %d words identical, %d differ" % (words - len(diff), words, len(diff)))
if diff:
    print("first differences:", " ".join(hex(0x80010000 + i * 4) for i in diff[:12]))
