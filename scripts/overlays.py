#!/usr/bin/env python3
"""
Overlay support: extract an overlay from the disc image, find its functions and build it
with full_build.py (decompiled C + generated assembly in address order).

usage: overlays.py NAME ISO.bin SLUS_008.54 [--discover]
  e.g. overlays.py NAME "Jade Cocoon (USA).bin" SLUS_008.54

The overlay file is looked up through the executable's file table (Data001Files), which holds
positions relative to DATA.001. Load addresses are the ones used by the game
(see scripts/ida/load_overlay_into_idb.py). Symbols live in overlays/<name>.sym, C code in
src/overlays/<name>.c.
"""
import os
import re
import struct
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

LOAD_ADDRESSES = {
    "TITLE": 0x800A05A0, "COMBAT": 0x800A05A0, "SOUNDTST": 0x800A05A0, "TSTMODEL": 0x800A05A0,
    "TSTCOMPO": 0x800A05A0, "GAME": 0x800A05A0, "BATTLE": 0x800B66C0, "MENU": 0x800B66C0,
    "PLCOM": 0x800C9E88, "ENCOM": 0x800C9E88, "MAP": 0x800B66C0, "SHOPCTRL": 0x800B66C0,
    "SHOP": 0x800B6D00, "WPNSHOP": 0x800B66C0, "CONFIG": 0x800C29D0, "LOAD": 0x800B66C0,
    "NAME": 0x800B6D00, "EQUIP": 0x800C29D0, "SHOPENTR": 0x800B6D00, "CHAPTER": 0x800B66C0,
    "PIERCE": 0x800B66C0, "COMBCHUI": 0x800A4088, "COMBSEL": 0x800A4088, "COMBLOAD": 0x800A4088,
    "COMBCOM": 0x800C9E88, "COMBSTRT": 0x800A4088, "COMBBTL": 0x800A4088, "COMBRSLT": 0x800A4088,
    "EVENTFNC": 0x800B6D00, "BTLEXEC": 0x800C9E88,
}


def file_id(name):
    for line in open(os.path.join(REPO, "src", "enums.h")):
        m = re.match(r"\s*OVER_%s_BIN = (\d+)u" % name, line)
        if m:
            return int(m.group(1))
    sys.exit("no OVER_%s_BIN in enums.h" % name)


def bcd(x):
    return (x >> 4) * 10 + (x & 15)


def extract(name, iso_path, exe):
    """exe: the executable image without header (as loaded at 0x80010000)"""
    idx = file_id(name)
    table = 0x80075AA0 - 0x80010000

    def entry(i):
        m, s, f, _t, secs, size = struct.unpack("<4B2I", exe[table + i * 12:table + i * 12 + 12])
        return (bcd(m) * 60 + bcd(s)) * 75 + bcd(f), secs, size

    pos, _, size = entry(idx)
    rel = pos - entry(2)[0]  # DATA.001 is entry 2

    f = open(iso_path, "rb")

    def sector(n):
        f.seek(n * 2352 + 24)
        return f.read(2048)

    # find DATA.001 in the DATA directory (second root entry named DATA)
    root = sector(16)[156:190]
    lba = struct.unpack("<I", root[2:6])[0]
    rootdir = b"".join(sector(lba + i) for i in range((struct.unpack("<I", root[10:14])[0] + 2047) // 2048))
    data_dir = None
    i = 0
    while i < len(rootdir):
        n = rootdir[i]
        if n == 0:
            i = (i // 2048 + 1) * 2048
            continue
        rec = rootdir[i:i + n]
        if rec[33:33 + rec[32]] == b"DATA":
            data_dir = struct.unpack("<I", rec[2:6])[0]
        i += n
    d = sector(data_dir)
    data001 = None
    i = 0
    while i < 2048 and d[i]:
        rec = d[i:i + d[i]]
        if rec[33:33 + rec[32]].startswith(b"DATA.001"):
            data001 = struct.unpack("<I", rec[2:6])[0]
        i += d[i]
    start = data001 + rel
    return b"".join(sector(start + k) for k in range((size + 2047) // 2048))[:size]


def discover(data, base):
    """function starts of an overlay: jal targets, code after every 'jr ra' and entries of pointer tables"""
    words = struct.unpack("<%dI" % (len(data) // 4), data[:len(data) // 4 * 4])
    n = len(words)
    jr = [i for i, w in enumerate(words) if w == 0x03e00008]
    # first function: the first prologue (addiu $sp,$sp,-N) that is followed by sane code
    first = next(i for i, w in enumerate(words) if (w >> 16) == 0x27bd and (w & 0x8000))
    last = jr[-1] + 2  # word after the delay slot of the last 'jr ra'
    starts = {first}
    for i, w in enumerate(words):
        if w >> 26 == 3:
            t = (((w & 0x3ffffff) << 2) | 0x80000000) - base
            if first * 4 <= t < last * 4 and t % 4 == 0:
                starts.add(t // 4)
    for j in jr:
        if j + 2 < last:
            starts.add(j + 2)
    # pointer tables behind the code
    for w in words[last:]:
        t = w - base
        if first * 4 <= t < last * 4 and t % 4 == 0 and w >= base:
            starts.add(t // 4)
    # a branch may never leave its function: drop guessed boundaries (not call targets) it crosses
    calls = {first}
    for w in words[first:last]:
        if w >> 26 == 3:
            calls.add((((w & 0x3ffffff) << 2) | 0x80000000) - base >> 2 if False else ((((w & 0x3ffffff) << 2) | 0x80000000) - base) // 4)
    branches = []
    for i in range(first, last):
        w = words[i]
        op = w >> 26
        if op == 2:  # j stays inside the function as well
            branches.append((i, ((((w & 0x3ffffff) << 2) | 0x80000000) - base) // 4))
        elif op in (4, 5, 6, 7) or (op == 1 and ((w >> 16) & 31) in (0, 1, 16, 17)):
            off = w & 0xffff
            off = off - 0x10000 if off & 0x8000 else off
            branches.append((i, i + 1 + off))
    changed = True
    while changed:
        changed = False
        bounds = sorted(starts)
        for s in bounds[1:]:
            if s in calls:
                continue
            if any((src < s) != (dst < s) for src, dst in branches):
                starts.discard(s)
                changed = True
                break
    return first, last, sorted(starts)


def write_symbols(name, base, size, first, last, starts):
    path = os.path.join(REPO, "overlays", name.lower() + ".sym")
    os.makedirs(os.path.dirname(path), exist_ok=True)
    out = []
    if first > 0:
        out.append("dword_%08X=0x%08x; // overlay header / data\n" % (base, base))
    for s in starts:
        a = base + s * 4
        out.append("sub_%08X=0x%08x;\n" % (a, a))
    if last * 4 < size:
        a = base + last * 4
        out.append("dword_%08X=0x%08x; // data behind the code\n" % (a, a))
    open(path, "w").write("".join(out))
    return path


def main(argv):
    import full_build
    name = argv[0].upper()
    iso_path, exe_path = argv[1], argv[2]
    exe = open(exe_path, "rb").read()[0x800:]
    data = extract(name, iso_path, exe)
    base = LOAD_ADDRESSES[name]
    data = data + b"\0" * (-len(data) % 4)
    print("%s.BIN: %d bytes, loaded at 0x%08X" % (name, len(data), base))
    symfile = os.path.join("overlays", name.lower() + ".sym")
    if "--discover" in argv or not os.path.exists(os.path.join(REPO, symfile)):
        first, last, starts = discover(data, base)
        write_symbols(name, base, len(data), first, last, starts)
        print("found %d functions, wrote %s" % (len(starts), symfile))
    import gen_asm
    main_syms = gen_asm.load_symbols(REPO)
    src = os.path.join("overlays", name.lower() + ".c")
    t = full_build.Target("overlay_" + name.lower(), data, base, base + len(data), symfile, [src],
                          extra_syms=main_syms)
    r = full_build.build(t, pin_data="--pin-data" in argv)
    full_build.report(r, name + ".BIN")
    open(os.path.join(full_build.BUILD, name + ".BIN"), "wb").write(r["built"])
    return 0 if r["diff"] - r["addr_only"] == 0 else 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
