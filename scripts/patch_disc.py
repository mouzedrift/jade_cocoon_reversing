#!/usr/bin/env python3
"""
Write rebuilt overlays (and optionally the rebuilt executable) into a copy of the disc image, so that
modified code can be run in an emulator (PCSX-Redux).

usage: patch_disc.py ISO.bin [NAME | NAME=FILE ...] [--exe [EXE]] [-o OUT.bin] [--selftest]

  NAME        overlay name (BATTLE, MENU, ...): writes build_psyq/NAME.BIN (built by scripts/overlays.py)
  NAME=FILE   writes FILE as overlay NAME
  --all       every overlay that has a build_psyq/NAME.BIN
  --exe [EXE] also writes the executable as SLUS_008.54 (default build_psyq/jade_cocoon.exe)
  -o OUT.bin  output image (default build_psyq/jade_cocoon_patched.bin); a .cue is written next to it
  --selftest  check the EDC/ECC code against every sector of the files it would write, then exit

  e.g. patch_disc.py "Jade Cocoon (USA).bin" BATTLE MENU --exe

The input image is never modified. It must be a single MODE2/2352 track (the redump image is).

Where the data goes: the game finds a file through the table in the executable at 0x80075AA0 (12 byte
entries: BCD minute/second/frame, track, sector count, byte size, see DATA_GetFile_8003C7CC). Positions
are relative to entry 2 (DATA.001), which the game locates at run time. An overlay that fits in its
original slot (sector count * 2048 bytes) is written in place. An overlay that is bigger cannot grow in
place (the next file follows directly, and DATA.001 is followed by VOICE.XA), so it is written to new
sectors appended to the end of the image and its table entry is pointed there; the table entry also
changes when the byte size changes. Both mean the executable on the disc is rewritten (the one given
with --exe, or the disc's own one with just the table changed).

Every rewritten sector (MODE2 Form1) gets its EDC and ECC recomputed; sectors whose data does not
change are not touched, so patching with unmodified (matching) builds gives an identical image.

The rebuilt executable is shorter than the original file (which carries 250 KB of bss/garbage after the
linked image, and a bigger size in the header): it is laid over the original file, the header keeps
the larger t_size, so the original trailing bytes stay in place and a matching build gives an identical
file.
"""
import os
import shutil
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from overlays import LOAD_ADDRESSES, REPO, file_id  # noqa: E402

SECTOR = 2352
TABLE = 0x80075AA0 - 0x80010000 + 0x800  # file offset of the file table in the PS-X EXE
BUILD = os.path.join(REPO, "build_psyq")

# ---------------------------------------------------------------------------------------------- EDC/ECC

EDC_LUT = []
for _i in range(256):
    _e = _i
    for _ in range(8):
        _e = (_e >> 1) ^ (0xD8018001 if _e & 1 else 0)
    EDC_LUT.append(_e)
ECC_F = [0] * 256
ECC_B = [0] * 256
for _i in range(256):
    _j = ((_i << 1) ^ (0x11D if _i & 0x80 else 0)) & 0xFF
    ECC_F[_i] = _j
    ECC_B[_i ^ _j] = _i


def edc(data):
    e = 0
    for b in data:
        e = (e >> 8) ^ EDC_LUT[(e ^ b) & 0xFF]
    return e


def _ecc_block(s, major_count, minor_count, major_mult, minor_inc, dest):
    # s: sector from offset 0xC (header + subheader + data [+ P parity])
    size = major_count * minor_count
    f, bl = ECC_F, ECC_B
    for major in range(major_count):
        index = (major >> 1) * major_mult + (major & 1)
        a = b = 0
        for _ in range(minor_count):
            t = s[index]
            index += minor_inc
            if index >= size:
                index -= size
            a ^= t
            b ^= t
            a = f[a]
        a = bl[f[a] ^ b]
        s[dest + major - 0xC] = a
        s[dest + major + major_count - 0xC] = a ^ b


def fix_form1(sec):
    """sec: bytearray of a full MODE2 Form1 sector; recomputes EDC (0x818) and ECC (0x81C..0x92F)"""
    struct.pack_into("<I", sec, 0x818, edc(sec[0x10:0x818]))
    s = bytearray(sec[0xC:])
    s[0:4] = b"\0\0\0\0"  # MODE2: the header is taken as zero for the ECC
    _ecc_block(s, 86, 24, 2, 86, 0x81C)
    _ecc_block(s, 52, 43, 86, 88, 0x8C8)
    sec[0x81C:SECTOR] = s[0x81C - 0xC:SECTOR - 0xC]


def to_bcd(x):
    return (x // 10) << 4 | (x % 10)


def from_bcd(x):
    return (x >> 4) * 10 + (x & 15)


def new_sector(lba, data, subheader):
    sec = bytearray(SECTOR)
    sec[0:12] = b"\0" + b"\xff" * 10 + b"\0"
    m = lba + 150
    sec[12:16] = bytes((to_bcd(m // 4500), to_bcd(m // 75 % 60), to_bcd(m % 75), 2))
    sec[16:24] = subheader * 2
    sec[24:24 + len(data)] = data
    fix_form1(sec)
    return sec


# ---------------------------------------------------------------------------------------------- image


class Image:
    def __init__(self, path, writable):
        self.f = open(path, "r+b" if writable else "rb")
        self.f.seek(0, 2)
        self.nsectors = self.f.tell() // SECTOR
        self.written = 0

    def raw(self, lba):
        self.f.seek(lba * SECTOR)
        return bytearray(self.f.read(SECTOR))

    def read(self, lba, count=1):
        return b"".join(bytes(self.raw(lba + i)[24:24 + 2048]) for i in range(count))

    def write_data(self, lba, data):
        """writes user data from the start of sector lba; only sectors whose data changes are rewritten"""
        for i in range(0, len(data), 2048):
            chunk = data[i:i + 2048]
            sec = self.raw(lba + i // 2048)
            if sec[15] != 2 or sec[18] & 0x20:
                sys.exit("sector %d is not MODE2 Form1" % (lba + i // 2048))
            if sec[24:24 + len(chunk)] == chunk:
                continue
            sec[24:24 + len(chunk)] = chunk
            fix_form1(sec)
            self.f.seek((lba + i // 2048) * SECTOR)
            self.f.write(sec)
            self.written += 1

    def append(self, data, subheader=b"\0\0\x08\0"):
        lba = self.nsectors
        self.f.seek(lba * SECTOR)
        for i in range(0, len(data), 2048):
            self.f.write(new_sector(lba + i // 2048, data[i:i + 2048], subheader))
        self.nsectors += (len(data) + 2047) // 2048
        self.written += (len(data) + 2047) // 2048
        return lba


def dir_records(img, lba, size):
    """(name, record lba, offset in sector, extent lba, size) of a directory's entries"""
    out = []
    for s in range((size + 2047) // 2048):
        d = img.read(lba + s)
        i = 0
        while i < 2048 and d[i]:
            rec = d[i:i + d[i]]
            name = rec[33:33 + rec[32]]
            if name not in (b"\0", b"\1"):
                out.append((name.split(b";")[0].decode(), lba + s, i, struct.unpack("<I", rec[2:6])[0],
                            struct.unpack("<I", rec[10:14])[0]))
            i += d[i]
    return out


def find(img, path):
    root = img.read(16)[156:190]
    lba, size = struct.unpack("<I", root[2:6])[0], struct.unpack("<I", root[10:14])[0]
    rec = None
    for part in path.split("/"):
        rec = next((r for r in dir_records(img, lba, size) if r[0] == part), None)
        if rec is None:
            sys.exit("%s not found on the disc" % path)
        lba, size = rec[3], rec[4]
    return rec


def set_dir_size(img, rec, size):
    sec = img.read(rec[1])
    sec = sec[:rec[2] + 10] + struct.pack("<I", size) + struct.pack(">I", size) + sec[rec[2] + 18:]
    img.write_data(rec[1], sec)


# ---------------------------------------------------------------------------------------------- table


def get_entry(exe, idx):
    m, s, f, t, secs, size = struct.unpack_from("<4B2I", exe, TABLE + idx * 12)
    return (from_bcd(m) * 60 + from_bcd(s)) * 75 + from_bcd(f), t, secs, size


def set_entry(exe, idx, pos, t, secs, size):
    struct.pack_into("<4B2I", exe, TABLE + idx * 12, to_bcd(pos // 4500), to_bcd(pos // 75 % 60),
                     to_bcd(pos % 75), t, secs, size)


def merge_exe(orig, built):
    """lays the rebuilt executable over the original file (see the module doc)"""
    if len(built) > len(orig):
        sys.exit("the rebuilt executable (%d bytes) is bigger than SLUS_008.54 on the disc (%d bytes): "
                 "growing the executable is not supported" % (len(built), len(orig)))
    exe = bytearray(orig)
    exe[:len(built)] = built
    t_orig = struct.unpack_from("<I", orig, 0x1C)[0]
    t_built = struct.unpack_from("<I", built, 0x1C)[0]
    struct.pack_into("<I", exe, 0x1C, max(t_orig, t_built))
    return exe


# ---------------------------------------------------------------------------------------------- main


def selftest(img, lbas):
    bad = 0
    for lba in lbas:
        sec = img.raw(lba)
        if sec[18] & 0x20:
            continue
        fixed = bytearray(sec)
        fix_form1(fixed)
        bad += fixed != sec
    print("EDC/ECC self test: %d sectors, %d mismatches" % (len(lbas), bad))
    return 1 if bad else 0


def main(argv):
    iso, out, exe_path, files, test = None, os.path.join(BUILD, "jade_cocoon_patched.bin"), None, [], False
    i = 0
    while i < len(argv):
        a = argv[i]
        if a == "-o":
            out = argv[i + 1]
            i += 1
        elif a == "--exe":
            if i + 1 < len(argv) and not argv[i + 1].startswith("-") and argv[i + 1].lower().endswith(".exe"):
                exe_path = argv[i + 1]
                i += 1
            else:
                exe_path = os.path.join(BUILD, "jade_cocoon.exe")
        elif a == "--all":
            files += [(n, os.path.join(BUILD, n + ".BIN")) for n in sorted(LOAD_ADDRESSES)
                      if os.path.exists(os.path.join(BUILD, n + ".BIN"))]
        elif a == "--selftest":
            test = True
        elif iso is None:
            iso = a
        else:
            name, _, path = a.partition("=")
            files.append((name.upper(), path or os.path.join(BUILD, name.upper() + ".BIN")))
        i += 1
    if iso is None:
        sys.exit(__doc__)
    if os.path.abspath(out) == os.path.abspath(iso):
        sys.exit("the output must not be the input image")

    src = Image(iso, False)
    slus = find(src, "SLUS_008.54")
    data001 = find(src, "DATA/DATA.001")
    orig_exe = src.read(slus[3], (slus[4] + 2047) // 2048)[:slus[4]]
    exe = bytearray(orig_exe)
    if exe_path:
        exe = merge_exe(orig_exe, open(exe_path, "rb").read())
    base = get_entry(exe, 2)[0]

    jobs = []
    for name, path in files:
        if name not in LOAD_ADDRESSES:
            sys.exit("unknown overlay %s" % name)
        idx = file_id(name)
        pos, t, secs, size = get_entry(exe, idx)
        data = open(path, "rb").read()
        # overlays.py pads to 4 bytes: drop zeros behind the original size
        if len(data) > size and not data[size:].strip(b"\0"):
            data = data[:size]
        jobs.append((name, idx, data001[3] + pos - base, pos, t, secs, size, data))

    if test:
        lbas = list(range(slus[3], slus[3] + (slus[4] + 2047) // 2048))
        for job in jobs:
            lbas += range(job[2], job[2] + job[5])
        return selftest(src, lbas)
    src.f.close()

    print("copying %s -> %s" % (iso, out))
    shutil.copyfile(iso, out)
    img = Image(out, True)
    exe_dirty = exe != orig_exe
    for name, idx, lba, pos, t, secs, size, data in jobs:
        end = LOAD_ADDRESSES[name] + len(data)
        if len(data) <= secs * 2048:
            # the bytes of the old file behind the new end are cleared (up to its old size)
            img.write_data(lba, data + b"\0" * max(0, size - len(data)))
            where = "in place at sector %d" % lba
            new_pos, new_secs = pos, secs
        else:
            new_lba = img.append(data)
            new_pos, new_secs = base + new_lba - data001[3], (len(data) + 2047) // 2048
            where = "moved to sector %d (appended; was %d sectors at %d)" % (new_lba, secs, lba)
        if (new_pos, new_secs, len(data)) != (pos, secs, size):
            set_entry(exe, idx, new_pos, t, new_secs, len(data))
            exe_dirty = True
        print("%-8s %6d bytes (was %6d), %s" % (name, len(data), size, where))
        if len(data) > size:
            print("         warning: loads up to 0x%08X, %d bytes past the original end 0x%08X - make sure "
                  "nothing else lives there" % (end, len(data) - size, LOAD_ADDRESSES[name] + size))
    if img.nsectors * SECTOR != os.path.getsize(iso):
        # volume space size in the primary volume descriptor (both byte orders)
        pvd = img.read(16)
        pvd = pvd[:80] + struct.pack("<I", img.nsectors) + struct.pack(">I", img.nsectors) + pvd[88:]
        img.write_data(16, pvd)
    if exe_dirty:
        img.write_data(slus[3], bytes(exe))
        print("SLUS_008.54 rewritten%s" % ("" if exe_path else " (file table only)"))
    img.f.close()

    cue = os.path.splitext(out)[0] + ".cue"
    with open(cue, "w") as f:
        f.write('FILE "%s" BINARY\n  TRACK 01 MODE2/2352\n    INDEX 01 00:00:00\n' % os.path.basename(out))
    print("%d sectors written, wrote %s" % (img.written, cue))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
