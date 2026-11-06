#!/usr/bin/env python3
"""
Overlay support: extract an overlay from the disc image and build it from its C source
(src/overlays/<name>.c, <name>_2.c, ...) against the executable built by build.py.

usage: overlays.py NAME ISO.bin SLUS_008.54
  e.g. overlays.py NAME "Jade Cocoon (USA).bin" SLUS_008.54
       overlays.py NAME orig SLUS_008.54   (no disc: use build_psyq/NAME.orig from an earlier run, checked
                                            against config/hashes.txt)

The overlay file is looked up through the executable's file table (Data001Files), which holds
positions relative to DATA.001. Load addresses are the ones used by the game
(see scripts/ida/load_overlay_into_idb.py). Symbols live in overlays/<name>.sym, C code in
src/overlays/<name>.c.
"""
import glob
import os
import re
import struct
import subprocess
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

BUILD = os.path.join(REPO, "build_psyq")
PSYQ = os.path.join(REPO, "libs", "psyq4.4")
BIN = os.path.join(PSYQ, "bin")


def run(cmd):
    r = subprocess.run((["wine"] + cmd) if sys.platform.startswith("linux") else cmd,
                       stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    if r.returncode != 0:
        sys.stdout.write(r.stdout.decode(errors="replace"))
        sys.exit("command failed: %s" % " ".join(cmd))


def load_symbols(path):
    """[(address, name)] of a NAME=0xADDR; file, by address"""
    out = []
    for line in open(os.path.join(REPO, path)):
        m = re.match(r"(\w+)=0x([0-9a-fA-F]+);", line)
        if m:
            out.append((int(m.group(2), 16), m.group(1)))
    return sorted(out)

LOAD_ADDRESSES = {
    "TITLE": 0x800A05A0, "COMBAT": 0x800A05A0, "SOUNDTST": 0x800A05A0, "TSTMODEL": 0x800A05A0,
    "TSTCOMPO": 0x800A05A0, "GAME": 0x800A05A0, "BATTLE": 0x800B66C0, "MENU": 0x800B66C0,
    "PLCOM": 0x800C9E88, "ENCOM": 0x800C9E88, "MAP": 0x800B66C0, "SHOPCTRL": 0x800B66C0,
    "SHOP": 0x800B6D00, "WPNSHOP": 0x800B66C0, "CONFIG": 0x800C29D0, "LOAD": 0x800B66C0,
    "NAME": 0x800B6D00, "EQUIP": 0x800C29D0, "SHOPENTR": 0x800B6D00, "CHAPTER": 0x800B66C0,
    "PIERCE": 0x800C6F40, "COMBCHUI": 0x800A4088, "COMBSEL": 0x800A4088, "COMBLOAD": 0x800A4088,
    "COMBCOM": 0x800C9E88, "COMBSTRT": 0x800A4088, "COMBBTL": 0x800A4088, "COMBRSLT": 0x800A4088,
    "EVENTFNC": 0x800B6D00, "BTLEXEC": 0x800C9E88,
}


# end of the executable's image (.bss included), where GAME/TITLE/... are loaded
EXE_END = 0x800A05A0


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


def lib_objs(name):
    """the PSY-Q modules config/ovl_lib_objs.txt links into the overlay: [obj path], in link order"""
    from lib_match import lib_modules
    for line in open(os.path.join(REPO, "config", "ovl_lib_objs.txt")):
        f = line.split("#", 1)[0].split()
        if not f or f[0] != name:
            continue
        lib, mods = f[1], f[2].split(",")
        objs = {m: d for m, d in lib_modules(os.path.join(PSYQ, "LIB", lib)) if m in mods}
        out = os.path.join(BUILD, "libobj", lib.split(".")[0])
        os.makedirs(out, exist_ok=True)
        paths = []
        for m in mods:
            path = os.path.join(out, m + ".OBJ")
            if not os.path.exists(path) or open(path, "rb").read() != objs[m]:
                open(path, "wb").write(objs[m])
            paths.append(path)
        return paths
    return []


def load_orig(name):
    """the original overlay saved by an earlier build (build_psyq/NAME.orig), only if its hash is the recorded one"""
    import hashlib
    path = os.path.join(REPO, "build_psyq", name + ".orig")
    if not os.path.exists(path):
        sys.exit("%s missing: build once from the disc image" % path)
    data = open(path, "rb").read()
    want = {l.split()[0]: l.split()[1] for l in open(os.path.join(REPO, "config", "hashes.txt"))
            if l.strip() and not l.startswith("#")}.get("overlay-" + name)
    if want != hashlib.sha1(data).hexdigest():
        sys.exit("%s does not match config/hashes.txt" % path)
    return data


def overlay_opt(src_name):
    """optimisation level of an overlay source file (config/overlay_cc.txt: "battle_4 -O1"; default -O2)"""
    path = os.path.join(REPO, "config", "overlay_cc.txt")
    if os.path.exists(path):
        for line in open(path):
            f = line.split("#")[0].split()
            if len(f) == 2 and f[0] == src_name:
                return f[1]
    return "-O2"


def main(argv):
    name = argv[0].upper()
    iso_path, exe_path = argv[1], argv[2]
    if iso_path == "orig":
        data = load_orig(name)
    else:
        data = extract(name, iso_path, open(exe_path, "rb").read()[0x800:])
    base = LOAD_ADDRESSES[name]
    data = data + b"\0" * (-len(data) % 4)
    print("%s.BIN: %d bytes, loaded at 0x%08X" % (name, len(data), base))
    syms = load_symbols(os.path.join("overlays", name.lower() + ".sym"))
    libs = lib_objs(name)
    # an overlay built from several source files (as the original was, which matters for the .rdata alignment
    # of each file) has src/overlays/<name>.c, <name>_2.c, <name>_3.c, ..., linked in that order
    srcs = [os.path.join(REPO, "src", "overlays", name.lower() + ".c")]
    while os.path.exists(os.path.join(REPO, "src", "overlays", "%s_%d.c" % (name.lower(), len(srcs) + 1))):
        srcs.append(os.path.join(REPO, "src", "overlays", "%s_%d.c" % (name.lower(), len(srcs) + 1)))
    src_text = "".join(open(p).read() for p in srcs)
    b = BUILD
    tag = "overlay_" + name.lower()
    inc = ["-I", os.path.join(PSYQ, "INCLUDE"), "-I", os.path.join(REPO, "src")]
    # extra defines for experiments, e.g. JC_DEFINES=DEBUG_TTY (see docs/testing_in_emulator.md); unset = matching build
    inc += ["-D" + d for d in os.environ.get("JC_DEFINES", "").split()]
    objs = []
    for i, src in enumerate(srcs):
        pre, cc, obj = (os.path.join(b, tag + ("_%d" % (i + 1) if i else "") + e) for e in (".preproc", ".o", ".obj"))
        run([os.path.join(BIN, "CPPPSX.EXE"), "-undef", "-D__GNUC__=2", "-v", "-D__OPTIMIZE__"] + inc + [
            "-lang-c", "-Dmips", "-D__mips__", "-D__mips", "-Dpsx", "-D__psx__", "-D__psx", "-D_PSYQ",
            "-D__EXTENSIONS__", "-D_MIPSEL", "-D__CHAR_UNSIGNED__", "-D_LANGUAGE_C", "-DLANGUAGE_C", src, pre])
        opt = overlay_opt(os.path.basename(src)[:-2])
        run([os.path.join(BIN, "CC1PSX.EXE"), "-quiet", "-G0", opt, pre, "-o", cc])
        run([os.path.join(BIN, "ASPSX.EXE"), "-G0", "-q", "-0", cc, "-o", obj])
        objs.append(obj)
    link = os.path.join(b, tag + "_link.txt")
    # the executable's symbols where its link put them (build.py first), so that the overlays follow the
    # executable when it moves (its own equates for this overlay's range aside)
    equ = {m.group(2): int(m.group(1), 16) for m in re.finditer(
        r"^ ([0-9A-F]{8})  (\w+)$", open(os.path.join(BUILD, "jade_cocoon.map")).read(), re.M)}
    equ = {n: a for n, a in equ.items() if not base <= a < base + len(data)}
    # names of the source outside of the executable and of this overlay: other overlays' symbols (overlays/*.sym),
    # else buffers by their _XXXXXXXX suffix
    own = {n for _, n in syms}
    others = {}
    for path in glob.glob(os.path.join(REPO, "overlays", "*.sym")):
        if os.path.basename(path) != name.lower() + ".sym":
            for a, n in load_symbols(os.path.relpath(path, REPO)):
                others.setdefault(n, set()).add(a)
    for n in sorted(set(re.findall(r"\b[A-Za-z_]\w*\b", src_text)) - own - set(equ)):
        if n in others:
            if len(others[n]) > 1:
                sys.exit("%s: %s is at several addresses in overlays/*.sym" % (name, n))
            equ[n] = next(iter(others[n]))
        else:
            m = re.match(r"\w+_([0-9A-F]{8})$", n)
            if m and not base <= int(m.group(1), 16) < base + len(data):
                equ[n] = int(m.group(1), 16)
    sys.path.insert(0, REPO)
    import build as bp  # config/aliases.txt
    aliases = bp.read_aliases(name)

    def map_symbols():
        path = os.path.join(b, tag + ".map")
        if not os.path.exists(path):
            return {}
        return {m.group(2): int(m.group(1), 16) for m in re.finditer(r"^ ([0-9A-F]{8})  (\w+)$", open(path).read(), re.M)}

    def link_once():
        syms_map = map_symbols()
        for n, base_sym, off in aliases:
            equ[n] = syms_map.get(base_sym, 0) + off
        with open(link, "w") as f:
            f.write("\torg\t$%08x\n" % base)
            for g, kw in (("head", ""), ("rdata", ""), ("text", ""), ("data", ""), ("bss", "\tbss")):
                f.write("%s\tgroup%s\n" % (g, kw))
            for sec, g in ((".sdata", "head"), (".rdata", "rdata"), (".text", "text"), (".data", "data"),
                           (".sbss", "bss"), (".bss", "bss")):
                f.write("\tsection\t%s,%s\n" % (sec, g))
            for obj in objs:
                f.write('\tinclude "%s"\n' % os.path.basename(obj))
            for path in libs:
                f.write('\tinclude "%s"\n' % os.path.relpath(path, b))
            for n, a in sorted(equ.items(), key=lambda x: (x[1], x[0])):
                f.write("%s\tequ\t$%08x\n" % (n, a))
        cpe = os.path.join(b, tag + ".cpe")
        # the SN tools crash on long paths: run them from the build folder with relative names
        cwd = os.getcwd()
        os.chdir(b)
        try:
            run([os.path.relpath(os.path.join(BIN, "psylink.exe")), "/l", os.path.relpath(os.path.join(PSYQ, "LIB")),
                    "/c", "/n", "4000", "/q", "/m", "@%s,%s,%s,%s" % (tag + "_link.txt", tag + ".cpe", tag + ".sym", tag + ".map")])
            run([os.path.relpath(os.path.join(BIN, "cpe2exe.exe")), "-CA", tag + ".cpe"])
        finally:
            os.chdir(cwd)

    # names inside C objects (config/aliases.txt): BASE + OFFSET from where this link put BASE, so link again
    # when it moved (nothing else depends on the values)
    for _ in range(2):
        link_once()
        got = map_symbols()
        if all(got.get(n) == got.get(base_sym, -1) + off for n, base_sym, off in aliases):
            break
    else:
        sys.exit("%s: aliases (config/aliases.txt) not at BASE + OFFSET after relinking" % name)
    built = open(os.path.join(b, tag + ".exe"), "rb").read()[0x800:]
    # end of everything linked (.bss included) from the map; more than the original only for modified
    # (e.g. debug) builds, which are then written in full (scripts/patch_disc.py can place them)
    end = max(int(m.group(1), 16) + 1 for m in re.finditer(r"^ [0-9A-F]{8} ([0-9A-F]{8}) [0-9A-F]{8} ",
                                                              open(os.path.join(b, tag + ".map")).read(), re.M))
    size = max(len(data), end - base + (-(end - base) % 4))
    built = built[:size]
    built += b"\0" * (size - len(built))  # .bss at the end of the overlay file
    diff = sum(1 for i in range(0, len(data), 4) if data[i:i + 4] != built[i:i + 4])
    print("%s.BIN: %d of %d words identical" % (name, len(data) // 4 - diff, len(data) // 4))
    if size > len(data):
        print("%s.BIN: %d bytes longer than the original" % (name, size - len(data)))
    # the generated assembly refers to code and data by number (j to non-symbol targets, lui/addiu pairs,
    # pointer tables in .word data), so a modified build is only usable if nothing moved
    mapped = {m.group(2): int(m.group(1), 16) for m in re.finditer(r"^ ([0-9A-F]{8})  (\w+)$",
                                                                       open(os.path.join(b, tag + ".map")).read(), re.M)}
    moved = sorted((a, n) for a, n in syms if n in mapped and mapped[n] != a)
    if moved:
        print("%s.BIN: warning: %d symbols moved (first %s 0x%08X -> 0x%08X): the generated assembly still uses "
              "the old addresses, this build will not run correctly" % (name, len(moved), moved[0][1], moved[0][0],
                                                                         mapped[moved[0][1]]))
    open(os.path.join(b, name + ".BIN"), "wb").write(built)
    open(os.path.join(b, name + ".orig"), "wb").write(data)
    return 1 if diff else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
