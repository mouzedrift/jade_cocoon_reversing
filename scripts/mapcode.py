"""The code that map files (SCENE_*.SBH) bring along: the map loader (OnMapFileLoaded_80028808) copies it to
mapCodeAddr_80073210 (0x800B22C0, behind GAME) and calls into it there.

A map file is: code size, code, then the map's data (events, meshes, models, ...). A map with a source file
src/maps/NAME.c (NAME: the file's enum name without SCENE_ and _SBH, lower case, e.g. psyrus2_lookout_sce01)
is compiled and linked at 0x800B22C0 against the executable's and GAME's symbols; the map file is then
written again with that code (build_psyq/maps/NAME.SBH, the code reinjected), and its SHA-1 is checked
against config/hashes.txt (map-NAME) like the other images.

usage: mapcode.py ISO.bin|orig EXE [NAME...]   (no NAME: every map with a source file)
  ISO.bin: the map files from the disc image (saved as build_psyq/maps/NAME.orig); orig: from an earlier run
  prints "map-NAME SHA1" per map; exit code 1 if a map's code differs from the original's
"""
import glob
import hashlib
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import overlays as ov

REPO = ov.REPO
MAP_CODE = 0x800B22C0  # mapCodeAddr_80073210
OUT = os.path.join(ov.BUILD, "maps")


def map_files():
    """{name: file id} of the map files (src/enums.h SCENE_..._SBH)"""
    out = {}
    for line in open(os.path.join(REPO, "src", "enums.h")):
        m = re.match(r"\s*SCENE_(\w+)_SBH = (\d+)u", line)
        if m:
            out[m.group(1).lower()] = int(m.group(2))
    return out


def sources():
    return sorted(os.path.basename(p)[:-2] for p in glob.glob(os.path.join(REPO, "src", "maps", "*.c")))


def original(name, iso, exe):
    path = os.path.join(OUT, name + ".orig")
    if iso != "orig":
        os.makedirs(OUT, exist_ok=True)
        data = ov.extract_file(map_files()[name], iso, exe)
        open(path, "wb").write(data)
        return data
    if not os.path.exists(path):
        sys.exit("%s missing: build once from the disc image" % path)
    return open(path, "rb").read()


def own_symbols(srcs, size):
    """the names of the map's own functions and data: those with an address (NAME_800Bxxxx) in its code"""
    out = set()
    for p in srcs:
        for n, a in re.findall(r"\b(\w+_(800[BC][0-9A-F]{4}))\b", open(p).read()):
            if MAP_CODE <= int(a, 16) < MAP_CODE + size:
                out.add(n)
    return out


def build(name, iso, exe):
    """returns (map file with the built code, number of differing code words)"""
    data = original(name, iso, exe)
    size = struct.unpack("<I", data[:4])[0]
    code = data[4:4 + size]
    srcs = [os.path.join(REPO, "src", "maps", name + ".c")]
    built = ov.build_image("MAPCODE", MAP_CODE, srcs, own_symbols(srcs, size), [], "map_" + name, shift=False)
    built = built[:max(size, len(built))]
    diff = sum(1 for i in range(0, max(len(code), len(built)), 4) if code[i:i + 4] != built[i:i + 4])
    out = struct.pack("<I", len(built)) + built + data[4 + size:]
    open(os.path.join(OUT, name + ".SBH"), "wb").write(out)
    return out, diff


def main(argv):
    iso, exe_path = argv[0], argv[1]
    exe = open(exe_path, "rb").read()[0x800:]
    bad = 0
    for name in argv[2:] or sources():
        out, diff = build(name, iso, exe)
        if diff:
            print("%s: %d code words differ" % (name, diff), file=sys.stderr)
            bad = 1
        print("map-%s %s" % (name, hashlib.sha1(out).hexdigest()))
    return bad


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
