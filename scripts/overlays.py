#!/usr/bin/env python3
"""
Overlay support: extract an overlay from the disc image, find its functions and build it
with full_build.py (decompiled C + generated assembly in address order).

usage: overlays.py NAME ISO.bin SLUS_008.54 [--discover]
  e.g. overlays.py NAME "Jade Cocoon (USA).bin" SLUS_008.54
       overlays.py NAME orig SLUS_008.54   (no disc: use build_psyq/NAME.orig from an earlier run, checked
                                            against config/hashes.txt)

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
    "PIERCE": 0x800C6F40, "COMBCHUI": 0x800A4088, "COMBSEL": 0x800A4088, "COMBLOAD": 0x800A4088,
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


def lib_objs(name):
    """the PSY-Q modules config/ovl_lib_objs.txt links into the overlay: ([obj path], {section: (start, end)}, gamebss)"""
    import full_build as fb
    sys.path.insert(0, os.path.join(REPO, "scripts", "objlib"))
    from lib_match import lib_modules
    from sections import parse_obj_sections
    for line in open(os.path.join(REPO, "config", "ovl_lib_objs.txt")):
        f = line.split("#", 1)[0].split()
        if not f or f[0] != name:
            continue
        lib, mods = f[1], f[2].split(",")
        at = {k: int(v, 16) for k, v in (x.split("=") for x in f[3:])}
        objs = {m: d for m, d in lib_modules(os.path.join(fb.PSYQ, "LIB", lib)) if m in mods}
        out = os.path.join(fb.BUILD, "libobj", lib.split(".")[0])
        os.makedirs(out, exist_ok=True)
        paths, size = [], dict.fromkeys(("rdata", "text", "data", "bss"), 0)
        for m in mods:
            path = os.path.join(out, m + ".OBJ")
            if not os.path.exists(path) or open(path, "rb").read() != objs[m]:
                open(path, "wb").write(objs[m])
            paths.append(path)
            secs = parse_obj_sections(objs[m])
            for k in size:
                n = secs["." + k].size
                size[k] += n if isinstance(n, int) else n()
        return paths, {k: (at[k], at[k] + size[k]) for k in size if size[k]}, at["gamebss"]
    return [], {}, None


def split(name, data, base, syms, lib_ranges={}, gamebss=None):
    """asm/overlays/<name>/<symbol>.s for every symbol of the overlay (git-ignored, derived from the disc)
    (none for the ranges of linked library modules; the overlay's .bss in front of them as .space)"""
    import gen_asm
    from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32, CS_MODE_LITTLE_ENDIAN
    gen_asm.configure(base, base + len(data))
    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32 + CS_MODE_LITTLE_ENDIAN)
    names = {a: n for a, n in syms}
    out = os.path.join(REPO, "asm", "overlays", name.lower())
    os.makedirs(out, exist_ok=True)
    datas = gen_asm.overlay_data_names(REPO, os.path.join("overlays", name.lower() + ".sym"))
    datas |= {n for _, n in syms if n.startswith(gen_asm.DATA_PREFIXES)}
    code = [a for a, n in syms if n not in datas]
    first_code, last_code = min(code), max(code)
    pairs = list(zip(syms, syms[1:] + [(base + len(data), "")]))
    # the targets of the jump tables get global labels (jtgt_XXXXXXXX) for the C tables of asm functions
    targets = gen_asm.jump_targets(data, [(a, b) for (a, n), (b, _) in pairs if n in datas],
                                   [(a, b - a) for (a, n), (b, _) in pairs if n not in datas])
    for (a, n), (b, _) in pairs:
        if any(lo <= a < hi for lo, hi in lib_ranges.values()):
            continue
        if gamebss is not None and a >= gamebss:
            assert not any(data[a - base:b - base]), n
            text = "\t.bss\n\t.globl\t%s\n%s:\n\t.space\t%d\n\t.text\n" % (n, n, b - a)
            open(os.path.join(out, n + ".s"), "w", newline="").write(text.replace("\n", "\r\n"))
            continue
        # data in front of the code is .rdata (jump tables and strings come out of the compiler in the same
        # place), data behind it .data
        sec = ".rdata" if a < first_code else ".data"
        text = (gen_asm.emit_data(data, n, a, b - a, sec, header=(a == base and a < first_code and name.upper() not in ("GAME", "MENU"))) if n in datas
                else gen_asm.emit_function(md, data, n, a, b - a, names, targets))
        open(os.path.join(out, n + ".s"), "w", newline="").write(text.replace("\n", "\r\n"))


def init_src(name, syms):
    """first version of src/overlays/<name>.c: functions already written in C stay, the others become INCLUDE_ASM"""
    import full_build as fb
    path = os.path.join(REPO, "src", "overlays", name.lower() + ".c")
    old = open(path).read() if os.path.exists(path) else ""
    blocks = fb.split_blocks(old)
    funcs = {b[1]: b for b in blocks if b[0] == "func"}
    head = [b[2] for b in blocks if b[0] != "func"]
    out = ["\n".join(head)] if head else [
        "// %s.BIN\n#include \"common.h\"\n#include \"funcs.h\"\n#include \"globals.h\"" % name]
    for a, n in syms:
        b = funcs.get(n)
        if b and b[3]:
            out.append(b[2])
        else:
            if b:
                out.append("#if 0\n" + b[2] + "\n#endif")
            out.append("INCLUDE_OVERLAY_ASM(%s, %s);" % (name.lower(), n))
    open(path, "w").write("\n\n".join(out) + "\n")


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
    import gen_asm
    import full_build as fb
    name = argv[0].upper()
    iso_path, exe_path = argv[1], argv[2]
    if iso_path == "orig":
        data = load_orig(name)
    else:
        data = extract(name, iso_path, open(exe_path, "rb").read()[0x800:])
    base = LOAD_ADDRESSES[name]
    data = data + b"\0" * (-len(data) % 4)
    print("%s.BIN: %d bytes, loaded at 0x%08X" % (name, len(data), base))
    symfile = os.path.join(REPO, "overlays", name.lower() + ".sym")
    if "--discover" in argv or not os.path.exists(symfile):
        first, last, starts = discover(data, base)
        write_symbols(name, base, len(data), first, last, starts)
        print("found %d functions, wrote %s" % (len(starts), symfile))
    syms = gen_asm.load_symbols(REPO, os.path.join("overlays", name.lower() + ".sym"))
    libs, lib_ranges, gamebss = lib_objs(name)
    # every library range and the overlay's .bss start at a symbol, so that no data blob runs into them
    have = {a for a, _ in syms}
    edges = {x for r in lib_ranges.values() for x in r} | ({gamebss} if gamebss else set())
    syms = sorted(syms + [(a, "dword_%08X" % a) for a in edges if a not in have and a < base + len(data)])
    split(name, data, base, syms, lib_ranges, gamebss)
    if "--init-src" in argv:
        init_src(name, syms)
    # an overlay built from several source files (as the original was, which matters for the .rdata alignment
    # of each file) has src/overlays/<name>.c, <name>_2.c, <name>_3.c, ..., linked in that order
    srcs = [os.path.join(REPO, "src", "overlays", name.lower() + ".c")]
    while os.path.exists(os.path.join(REPO, "src", "overlays", "%s_%d.c" % (name.lower(), len(srcs) + 1))):
        srcs.append(os.path.join(REPO, "src", "overlays", "%s_%d.c" % (name.lower(), len(srcs) + 1)))
    src_text = "".join(open(p).read() for p in srcs)
    b = fb.BUILD
    tag = "overlay_" + name.lower()
    inc = ["-I", os.path.join(fb.PSYQ, "INCLUDE"), "-I", os.path.join(REPO, "src")]
    # extra defines for experiments, e.g. JC_DEFINES=DEBUG_TTY (see docs/testing_in_emulator.md); unset = matching build
    inc += ["-D" + d for d in os.environ.get("JC_DEFINES", "").split()]
    objs = []
    for i, src in enumerate(srcs):
        pre, cc, obj = (os.path.join(b, tag + ("_%d" % (i + 1) if i else "") + e) for e in (".preproc", ".o", ".obj"))
        fb.run([os.path.join(fb.BIN, "CPPPSX.EXE"), "-undef", "-D__GNUC__=2", "-v", "-D__OPTIMIZE__"] + inc + [
            "-lang-c", "-Dmips", "-D__mips__", "-D__mips", "-Dpsx", "-D__psx__", "-D__psx", "-D_PSYQ",
            "-D__EXTENSIONS__", "-D_MIPSEL", "-D__CHAR_UNSIGNED__", "-D_LANGUAGE_C", "-DLANGUAGE_C", src, pre])
        opt = overlay_opt(os.path.basename(src)[:-2])
        fb.run([os.path.join(fb.BIN, "CC1PSX.EXE"), "-quiet", "-G0", opt, pre, "-o", cc])
        fb.run([os.path.join(fb.BIN, "ASPSX.EXE"), "-G0", "-q", "-0", cc, "-o", obj])
        objs.append(obj)
    link = os.path.join(b, tag + "_link.txt")
    main_syms = gen_asm.load_symbols(REPO)
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
        for a, n in main_syms:
            if not (base <= a < base + len(data)):
                f.write("%s\tequ\t$%08x\n" % (n, a))
        # buffers behind the overlay that are only named in the C source (name_XXXXXXXX)
        # (main-exe symbols inside the overlay range are not written above, so they count as unknown here)
        known = {n for a, n in main_syms if not (base <= a < base + len(data))} | {n for _, n in syms}
        for n, addr in sorted(set(re.findall(r"\b(\w+_([0-9A-F]{8}))\b", src_text))):
            if n not in known and not n.startswith("jtgt_"):  # jump labels come from the asm (gen_asm.jump_label)
                f.write("%s\tequ\t$%s\n" % (n, addr))
        # library code of the executable is named by its linked objects (SetDrawMove, MulMatrix0, and for the
        # linked library modules open, lseek, _card_load, ...): take those from the executable's link map
        # (build.py first)
        known |= set(re.findall(r"\b(\w+_[0-9A-F]{8})\b", src_text))
        for m in re.finditer(r"^ ([0-9A-F]{8})  (\w+)$", open(os.path.join(b, "jade_cocoon.map")).read(), re.M):
            if m.group(2) not in known:
                known.add(m.group(2))
                f.write("%s\tequ\t$%s\n" % (m.group(2), m.group(1)))
    cpe = os.path.join(b, tag + ".cpe")
    # the SN tools crash on long paths: run them from the build folder with relative names
    cwd = os.getcwd()
    os.chdir(b)
    try:
        fb.run([os.path.relpath(os.path.join(fb.BIN, "psylink.exe")), "/l", os.path.relpath(os.path.join(fb.PSYQ, "LIB")),
                "/c", "/n", "4000", "/q", "/m", "@%s,%s,%s,%s" % (tag + "_link.txt", tag + ".cpe", tag + ".sym", tag + ".map")])
        fb.run([os.path.relpath(os.path.join(fb.BIN, "cpe2exe.exe")), "-CA", tag + ".cpe"])
    finally:
        os.chdir(cwd)
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
