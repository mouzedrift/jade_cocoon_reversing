#!/usr/bin/env python3
"""
Find the PSY-Q library objects in the library part of the main executable.

usage: lib_match.py EXE [SDK_DIR ...] [--write]
       lib_match.py EXE --commons

Every module of every .LIB of the given SDKs (default: libs/psyq4.4 and ../psyq_sdk/psyq_4.*) is compared
with the code behind the game (GAME_TEXT_END..LIB_TEXT_END), ignoring the words the linker patches. Prints
the objects in address order (with the SDK versions whose module has identical code) and the gaps nothing
matched; --write puts the link order into config/lib_objs.txt.

--commons reads the addresses of the common (.comm) symbols of the modules in config/lib_objs.txt from the
code that uses them (the %hi/%lo pairs) and writes config/lib_commons.txt. build.py defines them itself: with
common symbols psylink aligns every .bss contribution to 8 bytes, which the game's .bss isn't.
"""
import glob
import os
import re
import struct
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from objlib.sections import parse_obj_sections  # noqa: E402
from layout import BASE, GAME_TEXT_END, LIB_TEXT_END  # noqa: E402


def lib_modules(path):
    """(module name, obj bytes) of a PSY-Q .LIB"""
    data = open(path, "rb").read()
    assert data[:4] == b"LIB\x01", path
    pos = 4
    while pos < len(data):
        name = data[pos:pos + 8].decode().strip()
        hdr, size = struct.unpack("<II", data[pos + 12:pos + 20])
        yield name, data[pos + hdr:pos + size]
        pos += size


def text_of(obj):
    secs = parse_obj_sections(obj)
    t = secs.get(".text")
    if t is None or not t.code:
        return None
    masked = set(off & ~3 for _, off, _ in t.patches)
    words = struct.unpack("<%dI" % (len(t.code) // 4), bytes(t.code[:len(t.code) // 4 * 4]))
    return words, masked, secs


def sdk_libs(sdks):
    for sdk in sdks:
        ver = os.path.basename(sdk.rstrip("/")).replace("psyq_", "").replace("psyq", "")
        for lib in sorted(glob.glob(os.path.join(sdk, "[Ll][Ii][Bb]", "*.[Ll][Ii][Bb]"))):
            yield ver, os.path.basename(lib).upper(), lib


def known_symbols():
    syms = {}
    for line in open(os.path.join(REPO, "symbol_addrs.txt")):
        m = re.match(r"(\w+)\s*=\s*0x([0-9a-fA-F]+)", line)
        if m:
            syms[m.group(1)] = int(m.group(2), 16)
    # some library symbols were named without their leading underscore
    for n, a in list(syms.items()):
        syms.setdefault("_" + n, a)
    return syms


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    write = "--write" in sys.argv
    exe = open(args[0], "rb").read()[0x800:]
    sdks = args[1:] or [os.path.join(REPO, "libs", "psyq4.4")] + \
        sorted(glob.glob(os.path.join(REPO, "..", "psyq_sdk", "psyq_4.[3-6]")))
    lo, hi = GAME_TEXT_END - BASE, LIB_TEXT_END - BASE
    ewords = struct.unpack("<%dI" % ((hi - lo) // 4), exe[lo:hi])
    index = {}
    for i, w in enumerate(ewords):
        index.setdefault(w, []).append(i)
    known = known_symbols()

    found = {}  # word index -> {(lib, module): {"size":, "vers": set, "score":}}
    for ver, libname, lib in sdk_libs(sdks):
        for mod, obj in lib_modules(lib):
            try:
                r = text_of(obj)
            except Exception as e:  # noqa: BLE001
                print("skip %s %s %s: %s" % (ver, libname, mod, e), file=sys.stderr)
                continue
            if r is None:
                continue
            words, masked, secs = r
            tid = secs[".text"].id
            tdefs = [(n, o) for n, (s, o) in secs["__xdefs__"].items() if s == tid]
            # trailing zero words are alignment padding, which the game's copy of a module may lack
            n = len(words)
            while n > 1 and words[n - 1] == 0 and (n - 1) * 4 not in masked:
                n -= 1
            keys = [k for k in range(n) if k * 4 not in masked and words[k] != 0]
            if not keys:
                continue
            cands = range(len(ewords)) if len(keys) < 2 else \
                [p - keys[0] for p in index.get(words[keys[0]], ())]
            if len(keys) < 2:
                # too little code to find by itself: only where its symbols are already known
                cands = [(known[nm] - BASE - lo) // 4 - o // 4 for nm, o in tdefs
                         if lo <= known.get(nm, 0) - BASE < hi]
            for s in cands:
                if s < 0 or s + n > len(ewords):
                    continue
                if all(ewords[s + k] == words[k] for k in keys):
                    score = sum(1 for nm, o in tdefs if known.get(nm) == BASE + lo + (s * 4) + o)
                    e = found.setdefault(s, {}).setdefault((libname, mod), {"size": len(words) * 4, "vers": set(),
                                                                            "score": score, "used": n * 4,
                                                                            "keys": len(keys), "exact": not masked})
                    e["vers"].add(ver)

    uses = {}
    for cands in found.values():
        for (libname, _), v in cands.items():
            if v["keys"] >= 4:
                uses[libname] = uses.get(libname, 0) + 1
    out = []  # ["obj", lib, module, start, size] / ["asm", start, size] (word indices / bytes)
    end = 0      # end of the last object including its padding
    used_end = 0  # end of its real code
    for s in sorted(found):
        if s < used_end:
            continue
        # a module with only a few words to compare is accepted only where its symbol is already known
        # (or when nothing in it is patched, like the BIOS call stubs)
        cands = {k: v for k, v in found[s].items() if v["keys"] >= 4 or v["score"] > 0 or
                 (v["exact"] and v["keys"] >= 2)}
        if not cands:
            continue
        # known symbol names first, then the longest code (a short module can match inside a bigger one)
        (libname, mod), e = max(cands.items(), key=lambda kv: (kv[1]["score"], kv[1]["used"], uses.get(kv[0][0], 0)))
        if s < end:
            # starts in the padding of the previous module: the game's copy of that one has less padding
            prev = out.pop()
            out.append(["asm", prev[3], (s - prev[3]) * 4])
        elif s > end:
            out.append(["asm", end, (s - end) * 4])
        out.append(["obj", libname, mod, s, e["size"], cands, e["vers"]])
        end = s + e["size"] // 4
        used_end = s + e["used"] // 4
    if end > len(ewords):
        prev = out.pop()
        out.append(["asm", prev[3], (len(ewords) - prev[3]) * 4])
    elif end < len(ewords):
        out.append(["asm", end, (len(ewords) - end) * 4])
    for o in out:
        if o[0] == "obj":
            print("OBJ  %08X %6x %-12s %-8s %s%s" % (BASE + lo + o[3] * 4, o[4], o[1], o[2], ",".join(sorted(o[6])),
                                                   "" if len(o[5]) == 1 else "  (also: %s)" % " ".join(
                                                       "%s/%s" % c for c in o[5] if c != (o[1], o[2]))))
        else:
            print("ASM  %08X %6x" % (BASE + lo + o[1] * 4, o[2]))
    if write:
        with open(os.path.join(REPO, "config", "lib_objs.txt"), "w") as f:
            f.write("# PSY-Q objects of the main executable in link order (scripts/lib_match.py --write).\n"
                    "# 'LIB MODULE' links that module of libs/psyq4.4/LIB/LIB; 'asm ADDR SIZE' is code that is\n"
                    "# not a 4.4 module (kept as assembly from the executable).\n")
            for o in out:
                f.write("%s %s\n" % (o[1], o[2]) if o[0] == "obj" else "asm %08X %x\n" % (BASE + lo + o[1] * 4, o[2]))


def lib_obj_paths():
    """(LIB, MODULE, obj bytes) of the modules in config/lib_objs.txt, in link order (None for asm pieces)"""
    mods = {}
    out = []
    for line in open(os.path.join(REPO, "config", "lib_objs.txt")):
        f = line.split("#")[0].split()
        if not f or f[0] == "bsshead":
            continue
        if f[0] == "asm":
            out.append(("asm", int(f[1], 16), int(f[2], 16)))
            continue
        if f[0] not in mods:
            mods[f[0]] = dict(lib_modules(os.path.join(REPO, "libs", "psyq4.4", "LIB", f[0])))
        out.append((f[0], f[1], mods[f[0]][f[1]]))
    return out


def commons(exe):
    def word(a):
        return struct.unpack("<I", exe[a - BASE:a - BASE + 4])[0]

    def sym_plus(x):
        if x[0] == "sym":
            return x[1], 0
        if x[0] == "op" and x[1] == 44:  # +
            a, b = x[2], x[3]
            if a[0] == "const" and b[0] == "sym":
                return b[1], a[1]
            if b[0] == "const" and a[0] == "sym":
                return a[1], b[1]
        return None

    pc = GAME_TEXT_END
    found = {}
    order = []  # (module, name, size)
    for lib, mod, obj in lib_obj_paths():
        if lib == "asm":
            pc += obj
            continue
        secs = parse_obj_sections(obj)
        defined = set(n for _, n, _ in order)
        for n, (sec, size) in secs["__xdefs__"].items():
            if sec == -1 and n not in defined:
                order.append(("%s %s" % (lib, mod), n, size))
        t = secs.get(".text")
        if t is None:
            continue
        his, los = {}, {}
        for ptype, off, x in t.patches:
            sp = sym_plus(x)
            if not sp or sp[0] not in secs["__xrefs__"]:
                continue
            key = (secs["__xrefs__"][sp[0]], sp[1])
            v = word(pc + off) & 0xFFFF
            if ptype == 82:    # %hi
                his.setdefault(key, set()).add(v)
            elif ptype == 84:  # %lo
                los.setdefault(key, set()).add(v - 0x10000 if v & 0x8000 else v)
        for key, hs in his.items():
            for h in hs:
                for lo in los.get(key, ()):
                    found.setdefault(key[0], {}).setdefault(((h << 16) + lo - key[1]) & 0xFFFFFFFF, 0)
                    found[key[0]][((h << 16) + lo - key[1]) & 0xFFFFFFFF] += 1
        pc += len(t.code)
    lines = []
    for mod, n, size in order:
        a = max(found[n].items(), key=lambda kv: kv[1])[0] if n in found else None
        lines.append((mod, n, size, a))
    # the ones no code uses: a hole among their module's commons that isn't just alignment padding of the next
    # one, else behind the commons before them (in link order)
    def nat(size):
        return 8 if size >= 8 else 4 if size >= 4 else 2 if size >= 2 else 1

    for k, (mod, n, size, a) in enumerate(lines):
        if a is not None:
            continue
        own = sorted((l[3], l[2]) for l in lines if l[0] == mod and l[3] is not None)
        p = None
        for (a0, s0), (a1, s1) in zip(own, own[1:]):
            hole = a0 + s0
            q = (hole + nat(size) - 1) // nat(size) * nat(size)
            if q + size <= a1 and (hole + nat(s1) - 1) // nat(s1) * nat(s1) != a1:
                p = q
                break
        if p is None:
            # a module's commons start on 8 bytes
            prev = [l for l in lines[:k] if l[3] is not None][-1]
            p = (prev[3] + prev[2] + 7) // 8 * 8
        lines[k] = (mod, n, size, p)
        print("no use of %s (%s): put at %08X" % (n, mod, p))
    with open(os.path.join(REPO, "config", "lib_commons.txt"), "w") as f:
        f.write("# Common symbols of the PSY-Q modules at their address in the executable (lib_match.py --commons):\n"
                "# LIB MODULE NAME SIZE ADDR. build.py defines them behind their module.\n")
        for mod, n, size, a in sorted(lines, key=lambda l: l[3]):
            f.write("%s %s %x %08X\n" % (mod, n, size, a))


if __name__ == "__main__":
    if "--commons" in sys.argv:
        commons(open(sys.argv[1], "rb").read()[0x800:])
    else:
        main()
