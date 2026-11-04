#!/usr/bin/env python3
"""
The data of an overlay in C: split its data blobs into symbols, then generate C definitions for them.

  python scripts/ovldata.py split NAME ISO.bin SLUS_008.54 [--write]
  python scripts/ovldata.py gen NAME ISO.bin SLUS_008.54 [SYMBOL ...] [--write]

split: the overlay's data in front of / behind its code is one INCLUDE_OVERLAY_ASM blob per gap between the
symbols of overlays/<name>.sym. The places the code refers to (lui/addiu and lui/load/store pairs, also through an
index added to the high part), the pointers in the data and the names the C source uses (name_XXXXXXXX,
dword_XXXXXXXX) become symbols of their own (dword_XXXXXXXX in the .sym file, an INCLUDE_OVERLAY_ASM line each in
the source, in address order where the blob's line was). Only places on 4 bytes split a blob (the generated
assembly is .word data); an object the C source declares (with a known size) is not split.
Run overlays.py afterwards (it writes the assembly of the new symbols).

gen: the INCLUDE_OVERLAY_ASM data lines (not jump tables) become C definitions like gendata.py makes them for the
executable: the type the overlay's source declares (build_psyq/overlay_<name>.preproc), else one guessed from the
bytes; pointers become references to their symbols (overlay or executable). The definitions replace the lines, the
externs go to the overlay's header (src/overlays/<name>.h, created if needed), the extern lines of the .c files for
them are removed. A name_XXXXXXXX the C code uses for a symbol becomes the symbol's name in the .sym file.
"""
import bisect
import os
import re
import struct
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_asm  # noqa: E402
import overlays  # noqa: E402

LOADS = {0x20, 0x21, 0x23, 0x24, 0x25, 0x22, 0x26, 0x28, 0x29, 0x2b, 0x2a, 0x2e, 0x32, 0x3a}  # incl. lwc2/swc2


def load(name, iso, exe_path):
    exe = open(exe_path, "rb").read()[0x800:]
    data = overlays.extract(name.upper(), iso, exe)
    data += b"\0" * (-len(data) % 4)
    return exe, data, overlays.LOAD_ADDRESSES[name.upper()]


def sym_path(name):
    return os.path.join(REPO, "overlays", name.lower() + ".sym")


def sources(name):
    srcs = [os.path.join(REPO, "src", "overlays", name.lower() + ".c")]
    while os.path.exists(os.path.join(REPO, "src", "overlays", "%s_%d.c" % (name.lower(), len(srcs) + 1))):
        srcs.append(os.path.join(REPO, "src", "overlays", "%s_%d.c" % (name.lower(), len(srcs) + 1)))
    return srcs


_DATA = {}


def is_data(n, name=None):
    """a data symbol of the overlay (prefix or '// data' in the .sym file)"""
    if n.startswith(gen_asm.DATA_PREFIXES):
        return True
    return any(n in d for d in _DATA.values()) if name is None else n in _DATA.get(name, ())


def load_data_names(name):
    _DATA[name] = gen_asm.overlay_data_names(REPO, os.path.join("overlays", name.lower() + ".sym"))


def code_refs(data, base, lo, hi):
    """addresses the code in [lo, hi) builds with lui + addiu / load / store (forward scan, no control flow)"""
    words = struct.unpack("<%dI" % (len(data) // 4), data)
    out = set()
    for i in range((lo - base) // 4, (hi - base) // 4):
        w = words[i]
        if w >> 26 != 0x0f:
            continue
        rt = (w >> 16) & 31
        if rt == 0:
            continue
        hival = (w & 0xffff) << 16
        for j in range(i + 1, min(i + 40, (hi - base) // 4)):
            x = words[j]
            op = x >> 26
            rs, xt = (x >> 21) & 31, (x >> 16) & 31
            simm = (x & 0xffff) - (0x10000 if x & 0x8000 else 0)
            if op == 0x09 and rs == rt:          # addiu
                out.add((hival + simm) & 0xffffffff)
                if xt == rt:
                    break
                continue
            if op in LOADS and rs == rt:
                out.add((hival + simm) & 0xffffffff)
                if op < 0x28 and op not in (0x32,) and xt == rt:
                    break
                continue
            if op == 0 and (x & 0x3f) in (0x21, 0x20) and ((x >> 11) & 31) == rt and rt in (rs, xt):
                continue                          # addu rt, rt, index: still the high part of a table
            # anything else that writes rt ends it
            dst = None
            if op == 0:
                dst = (x >> 11) & 31
            elif op in (0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f) or 0x20 <= op < 0x28:
                dst = xt
            elif op == 0x03:
                dst = 31
            if op == 0x10 or op == 0x12:          # mfc0/mfc2/cfc2
                if ((x >> 21) & 31) in (0, 2):
                    dst = xt
            if dst == rt:
                break
            if x == 0x03e00008:
                break
    return out


def blobs(name, syms, lib_ranges, size_end):
    """[(addr, end, name)] of the data symbols the C source includes"""
    text = "".join(open(p).read() for p in sources(name))
    inc = set(re.findall(r"^INCLUDE_OVERLAY_ASM\(\w+, (\w+)\);", text, re.M))
    out = []
    for (a, n), (b, _) in zip(syms, syms[1:] + [(size_end, "")]):
        if is_data(n) and not n.startswith("jpt_") and n in inc and not any(lo <= a < hi for lo, hi in lib_ranges.values()):
            out.append((a, b, n))
    return out


def declared_sizes(name):
    """{addr: size} of the objects with an address name the overlay's preprocessed source declares"""
    import gendata
    out = {}
    tag = "overlay_" + name.lower()
    for k in range(len(sources(name))):
        pre = os.path.join(REPO, "build_psyq", tag + ("_%d" % (k + 1) if k else "") + ".preproc")
        if not os.path.exists(pre):
            continue
        types = gendata.Types(gendata.parse_preproc(pre))
        for n, d in types.decls.items():
            m = re.search(r"_([0-9A-F]{8})$", n)
            if not m:
                continue
            try:
                t = types.resolve(d.type)
                out[int(m.group(1), 16)] = t.size()
            except Exception:  # noqa: BLE001
                pass
    return out


def split_points(name, data, base, syms, lib_ranges):
    code = [a for a, n in syms if not is_data(n)]
    lo, hi = min(code), max(code)
    hi = next((a for a, n in syms if a > hi), base + len(data))
    bl = blobs(name, syms, lib_ranges, base + len(data))
    refs = code_refs(data, base, lo, hi)
    for a, b, n in bl:
        for off in range(a - base, b - base - 3, 4):
            v = struct.unpack("<I", data[off:off + 4])[0]
            refs.add(v)
    text = "".join(open(p).read() for p in sources(name))
    refs |= {int(x, 16) for x in re.findall(r"\b[A-Za-z]\w*_([0-9A-F]{8})\b", text)}
    sizes = declared_sizes(name)
    inside = []
    for a, s in sizes.items():
        if s > 4:
            inside.append((a, a + s))
    out = {}
    for a, b, n in bl:
        pts = sorted(r for r in refs if a < r < b and r % 4 == 0 and not any(x < r < y for x, y in inside))
        # the overlay's first word goes to .sdata (overlays.py): a symbol of its own
        if a == base and name.upper() not in ("GAME", "MENU") and b > a + 4 and a + 4 not in pts:
            pts.insert(0, a + 4)
        out[n] = (a, b, pts)
    return out


def sym_name(data, base, a, b):
    """aName_XXXXXXXX for a place that starts with a string (as gendata.py names them), else dword_XXXXXXXX"""
    import gendata
    parts = gendata.split_strings(data[a - base:b - base], rest=True)
    if parts and parts[0][0] == 0 and parts[0][1]:
        s = parts[0][1]
        an = gendata.ascii_name(s.decode("latin1")) if all(c < 0x80 for c in s) else None
        if an is None:
            a2 = gendata.sjis_ascii(s)
            an = gendata.ascii_name(a2) if a2 else None
        return "%s_%08X" % (an or "asc", a)
    return "dword_%08X" % a


def sym_line(n, a):
    return "%s=0x%08x;%s" % (n, a, "" if n.startswith(gen_asm.DATA_PREFIXES) else " // data")


def write_split(name, points, data, base):
    path = sym_path(name)
    lines = open(path).read().split("\n")
    new = {}
    for n, (a, b, pts) in points.items():
        for p, q in zip(pts, pts[1:] + [b]):
            new[p] = sym_name(data, base, p, q)
    have = set()
    for l in lines:
        m = re.match(r"(\w+)=0x([0-9a-fA-F]+);", l)
        if m:
            have.add(int(m.group(2), 16))
    add = sorted(p for p in new if p not in have)
    out = []
    for l in lines:
        m = re.match(r"(\w+)=0x([0-9a-fA-F]+);", l)
        if m:
            a = int(m.group(2), 16)
            while add and add[0] < a:
                out.append(sym_line(new[add[0]], add[0]))
                add.pop(0)
        out.append(l)
    while out and out[-1] == "":
        out.pop()
    out += [sym_line(new[p], p) for p in add] + [""]
    open(path, "w").write("\n".join(out))
    for src in sources(name):
        text = open(src).read()
        for n, (a, b, pts) in points.items():
            line = "INCLUDE_OVERLAY_ASM(%s, %s);" % (name.lower(), n)
            if line in text and pts:
                more = "".join("\nINCLUDE_OVERLAY_ASM(%s, %s);" % (name.lower(), new[p]) for p in pts)
                text = text.replace(line, line + more, 1)
        open(src, "w").write(text)


def main(argv):
    args = [a for a in argv if not a.startswith("--")]
    cmd, name, iso, exe_path = args[:4]
    exe, data, base = load(name, iso, exe_path)
    syms = gen_asm.load_symbols(REPO, os.path.join("overlays", name.lower() + ".sym"))
    load_data_names(name)
    _, lib_ranges, gamebss = overlays.lib_objs(name.upper())
    have = {a for a, _ in syms}
    edges = {x for r in lib_ranges.values() for x in r} | ({gamebss} if gamebss else set())
    syms = sorted(syms + [(a, "dword_%08X" % a) for a in edges if a not in have and a < base + len(data)])
    if cmd == "split":
        pts = split_points(name, data, base, syms, lib_ranges)
        for n, (a, b, p) in pts.items():
            print("%s %08X-%08X: %d new symbols" % (n, a, b, len(p)))
        if "--write" in argv:
            write_split(name, pts, data, base)
    elif cmd == "gen":
        import ovlgen
        return ovlgen.main(name, exe, data, base, syms, lib_ranges, args[4:], "--write" in argv)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
