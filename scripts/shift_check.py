#!/usr/bin/env python3
"""
Check that the build is shiftable: build with JC_SHIFT=N (N bytes of padding in every section in front of the
game code of the executable and of every overlay) and compare each image with the normal build, word by word:

* code: j/jal targets, %hi/%lo pairs (lui + addiu/load/store) and data pointers that point into an image must
  point to the same place in the shifted build (the symbol that moved, plus the same offset),
* everything else must be identical.

A pointer that did not move with its target is a fixed address left in the source or the build.

usage: shift_check.py [N]   (default 0x40; needs a normal build first, which it restores at the end)
"""
import bisect
import os
import re
import shutil
import struct
import subprocess
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
BUILD = os.path.join(REPO, "build_psyq")
REF = os.path.join(BUILD, "shift_ref")
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from overlays import LOAD_ADDRESSES  # noqa: E402

EXE_BASE = 0x80010000
LINKER_SYMBOL = re.compile(r"_+\w+_(org|obj|orgend|objend|size)$")


def read_map(path):
    """({name: address}, [(start, end, group)] of the sections)"""
    text = open(path).read()
    syms = {m.group(2): int(m.group(1), 16) for m in re.finditer(r"^ ([0-9A-F]{8})  (\w+)$", text, re.M)}
    secs = [(int(m.group(1), 16), int(m.group(2), 16) + 1, m.group(3))
            for m in re.finditer(r"^ ([0-9A-F]{8}) ([0-9A-F]{8}) [0-9A-F]{8} [0-9A-F]{8} (\w+)", text, re.M)]
    return syms, secs


class Image:
    def __init__(self, name, data, base, map_path):
        self.name, self.data, self.base = name, data, base
        self.syms, self.secs = read_map(map_path)
        self.end = max(e for _, e, _ in self.secs)
        # the symbols this image defines (not the equates of other images' names)
        # (not the linker's section symbols __bss_org, _data_obj etc., which sit in front of the padding)
        own = sorted((a, n) for n, a in self.syms.items() if base <= a < self.end and not LINKER_SYMBOL.match(n))
        self.addrs = [a for a, _ in own]
        self.names = [n for _, n in own]

    def word(self, a):
        i = a - self.base
        return struct.unpack("<I", self.data[i:i + 4])[0] if 0 <= i <= len(self.data) - 4 else 0

    def section_of(self, a):
        for s, e, g in self.secs:
            if s <= a < e or (a == e and a == self.end):
                return s, e
        return None

    def symbol_at(self, a):
        """(name, offset) of a defined symbol of a's section, the one at or before a if there is one (statics have
        none in the map, but everything of a section behind the padding moves by the same amount)"""
        sec = self.section_of(a)
        k = bisect.bisect_right(self.addrs, a) - 1
        if k >= 0 and (sec is None or self.addrs[k] >= sec[0]):
            return self.names[k], a - self.addrs[k]
        if sec:
            k += 1
            if k < len(self.addrs) and self.addrs[k] < sec[1]:
                return self.names[k], a - self.addrs[k]
        return None, 0

    def code_ranges(self):
        return [(s, e) for s, e, g in self.secs if g == "text" and e > s]

    def data_ranges(self):
        return [(s, e) for s, e, g in self.secs if g in ("rdata", "data", "head") and e > s]


def load(directory):
    images = {"EXE": Image("EXE", open(os.path.join(directory, "jade_cocoon.exe"), "rb").read()[0x800:], EXE_BASE,
                           os.path.join(directory, "jade_cocoon.map"))}
    for name, base in LOAD_ADDRESSES.items():
        b, m = os.path.join(directory, name + ".BIN"), os.path.join(directory, "overlay_%s.map" % name.lower())
        if os.path.exists(b) and os.path.exists(m):
            images[name] = Image(name, open(b, "rb").read(), base, m)
    return images


def mapper(old, new, own):
    """old address -> new address, for addresses in an image; None if not in one; "?" if ambiguous"""
    def inside(name, a):
        # the executable's end is its own (the start-up clears the bss up to there); an overlay's is not
        o = old[name]
        return o.base <= a < o.end or (name == "EXE" and a == o.end)

    def in_image(name, a):
        o, n = old[name], new[name]
        if not inside(name, a):
            return None
        sym, off = o.symbol_at(a)
        return n.syms[sym] + off if sym in n.syms else "?"

    def f(a):
        for name in ("EXE", own, "GAME"):
            if name in old and inside(name, a):
                return in_image(name, a)
        got = {in_image(name, a) for name in old if name not in ("EXE", own, "GAME")} - {None}
        return None if not got else (got.pop() if len(got) == 1 else "?")
    return f


def check(name, old, new, f, bad, stats, deltas, bases):
    """deltas: how far the symbols of the images moved (an address computed out of an object, like
    &array[-1], moves with the object but is not inside it); bases: the overlays' load addresses (fixed)"""
    o, n = old[name], new[name]

    def to_new(a):
        sym, off = o.symbol_at(a)
        return n.syms[sym] + off if sym in n.syms else None

    def expect(where, old_target, new_target, kind=""):
        want = f(old_target)
        stats["refs"] += want is not None
        moved = (new_target - old_target) & 0xFFFFFFFF
        if want == "?":
            stats["ambiguous"] += 1
        elif want is None:
            if moved and moved not in deltas:
                bad.append("%s %08X: %s %08X became %08X (not an image address)" % (name, where, kind, old_target, new_target))
        elif new_target != want:
            if not moved:
                if old_target not in bases:
                    bad.append("%s %08X: %s %08X did not move (expected %08X)" % (name, where, kind, old_target, want))
            elif moved not in deltas:
                bad.append("%s %08X: %s %08X -> %08X, expected %08X" % (name, where, kind, old_target, new_target, want))

    for start, end in o.code_ranges():
        # branch targets: a lui seen on the way there need not be what the register holds
        targets = set()
        for a in range(start, end, 4):
            w = o.word(a)
            if w >> 26 in (1, 4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17):
                off = w & 0xFFFF
                targets.add(a + 4 + ((off - 0x10000 if off & 0x8000 else off) << 2))
        hi_o, hi_n, last_o, last_n = {}, {}, {}, {}
        clear_after = None
        for a in range(start, end, 4):
            if o.symbol_at(a)[1] == 0:  # a new function: no lui carries over
                hi_o, hi_n, last_o, last_n = {}, {}, {}, {}
            if a in targets or a == clear_after:
                hi_o, hi_n = {}, {}
            w0 = o.word(a)
            if w0 >> 26 in (1, 2, 3, 4, 5, 6, 7) or (w0 >> 26 == 0 and (w0 & 0x3F) in (8, 9)):
                clear_after = a + 8  # behind the delay slot
            na = to_new(a)
            if na is None:
                continue
            ow, nw = o.word(a), n.word(na)
            stats["words"] += 1
            op, rs, rt = ow >> 26, (ow >> 21) & 31, (ow >> 16) & 31
            if op in (2, 3):
                expect(a, ((a + 4) & 0xF0000000) | ((ow & 0x3FFFFFF) << 2),
                       ((na + 4) & 0xF0000000) | ((nw & 0x3FFFFFF) << 2), "j target")
                continue
            if op == 0x0F:
                hi_o[rt], hi_n[rt] = (ow & 0xFFFF) << 16, (nw & 0xFFFF) << 16
                last_o.setdefault(rt, []).insert(0, (hi_o[rt], hi_n[rt]))
                if ow >> 16 != nw >> 16:
                    bad.append("%s %08X: lui changed register" % (name, a))
                continue
            if op in (0x09, 0x20, 0x21, 0x23, 0x24, 0x25, 0x28, 0x29, 0x2B, 0x22, 0x26, 0x2A, 0x2E, 0x32, 0x3A) and rs in hi_o:
                if ow >> 16 != nw >> 16:
                    bad.append("%s %08X: %08X -> %08X" % (name, a, ow, nw))
                so, sn = ow & 0xFFFF, nw & 0xFFFF
                so, sn = so - 0x10000 if so & 0x8000 else so, sn - 0x10000 if sn & 0x8000 else sn
                expect(a, (hi_o[rs] + so) & 0xFFFFFFFF, (hi_n[rs] + sn) & 0xFFFFFFFF, "%hi/%lo")
                if op not in (0x28, 0x29, 0x2B, 0x2A, 0x2E, 0x32, 0x3A):  # it wrote rt
                    hi_o.pop(rt, None), hi_n.pop(rt, None)
                continue
            # anything else that writes a register ends what a lui put there
            w = (ow >> 11) & 31 if op == 0 else (31 if op == 3 else (rt if 8 <= op <= 0x0E or 0x20 <= op <= 0x26 else None))
            if w is not None:
                hi_o.pop(w, None), hi_n.pop(w, None)
            if ow != nw:
                lo_op = op in (0x09, 0x20, 0x21, 0x23, 0x24, 0x25, 0x28, 0x29, 0x2B, 0x22, 0x26, 0x2A, 0x2E, 0x32, 0x3A)
                if lo_op and ow >> 16 == nw >> 16 and rs in last_o:
                    # a %lo whose lui is on another path (a jump table case, ...): one of the luis of that
                    # register before it in the function, the latest one that explains the change
                    so, sn = ow & 0xFFFF, nw & 0xFFFF
                    so, sn = so - 0x10000 if so & 0x8000 else so, sn - 0x10000 if sn & 0x8000 else sn
                    pairs = [((ho + so) & 0xFFFFFFFF, (hn + sn) & 0xFFFFFFFF) for ho, hn in last_o[rs]]
                    good = [p for p in pairs if f(p[0]) not in (None, "?") and f(p[0]) == p[1]]
                    expect(a, *(good[0] if good else pairs[0]), kind="%hi/%lo")
                elif not (lo_op and ow >> 16 == nw >> 16 and ((nw - ow) & 0xFFFF) in {d & 0xFFFF for d in deltas}):
                    bad.append("%s %08X: %08X -> %08X" % (name, a, ow, nw))
    for start, end in o.data_ranges():
        for a in range(start, end, 4):
            na = to_new(a)
            if na is None or a - o.base >= len(o.data):
                continue
            ow, nw = o.word(a), n.word(na)
            stats["words"] += 1
            if f(ow) is not None or ow != nw:
                expect(a, ow, nw, "pointer")


def compare(old, new):
    deltas = {(new[i].syms[s] - a) & 0xFFFFFFFF for i in old if i in new for s, a in old[i].syms.items()
              if s in new[i].syms and not LINKER_SYMBOL.match(s)} - {0}
    # the overlays' load addresses and config/fixed_symbols.txt are fixed on purpose
    bases = set(LOAD_ADDRESSES.values())
    for line in open(os.path.join(REPO, "config", "fixed_symbols.txt")):
        f = line.split("#")[0].split()
        if f:
            bases.add(int(f[1], 16))
    bad, stats = [], {"words": 0, "refs": 0, "ambiguous": 0}
    for name in old:
        if name in new:
            check(name, old, new, mapper(old, new, name), bad, stats, deltas, bases)
    return bad, stats


def main(argv):
    shift = int(argv[0], 0) if argv else 0x40
    env = dict(os.environ, JC_SHIFT=str(shift))
    py = sys.executable

    def build(e):
        r = subprocess.run([py, os.path.join(REPO, "build.py")], cwd=REPO, env=e, capture_output=True, text=True)
        if r.returncode:
            sys.stdout.write(r.stdout[-3000:] + r.stderr[-3000:])
            sys.exit("build failed")

    plain = dict(os.environ)
    plain.pop("JC_SHIFT", None)
    print("normal build ...")
    build(plain)
    if os.path.exists(REF):
        shutil.rmtree(REF)
    os.makedirs(REF)
    for f in os.listdir(BUILD):
        if f == "jade_cocoon.exe" or f == "jade_cocoon.map" or f.endswith(".BIN") or re.match(r"overlay_\w+\.map$", f):
            shutil.copy(os.path.join(BUILD, f), REF)
    print("build with JC_SHIFT=0x%X ..." % shift)
    try:
        build(env)
        old, new = load(REF), load(BUILD)
    finally:
        print("normal build again ...")
        build(plain)
    bad, stats = compare(old, new)
    print("%d words of %d images compared, %d references into images followed (%d ambiguous, not checked)"
          % (stats["words"], len(old), stats["refs"], stats["ambiguous"]))
    for line in bad[:40]:
        print("  " + line)
    if bad:
        print("NOT SHIFTABLE: %d problems" % len(bad))
        return 1
    print("shiftable: every reference moved with its target")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
