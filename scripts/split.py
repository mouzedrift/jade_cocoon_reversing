#!/usr/bin/env python3
"""
Split the original executable into translation units, "INCLUDE_ASM" style.

  asm/f/<symbol>.s        one file per code symbol of the game code (0x80010000 - 0x8004D924)
  asm/d/<symbol>.s        one file per data symbol (.rdata / .data / .bss) of the game's data
  asm/lib/*.s             the PSY-Q library part (code, data, bss) as raw blobs: library code is not decompiled,
                          but it has to be there so the data of the game lands at its real address
  asm/units.txt           for every TU in config/tus.txt: its code symbols and data symbols, in link order
  src/<tu>.c              (--init-src) first version of the TU sources: INCLUDE_ASM / INCLUDE_DATA lines, plus the
                          functions already decompiled in the old src/*.c files

Nothing under asm/ is committed (it is derived from the user's own copy of the executable).

usage: split.py SLUS_008.54 [--init-src] [--propose-tus]
"""
import bisect
import os
import re
import struct
import subprocess
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_asm  # noqa: E402

OLD_REV = "14e1ab6"             # last commit with the old src/{main,funcs,globals,sound}.c
BASE = 0x80010000
GAME_TEXT_END = 0x8004D924
LIB_TEXT_END = 0x80071B0C       # padding up to the first game .rdata follows
RDATA_START = 0x80071B18
RDATA_GAME_END = 0x80074BE0     # PSY-Q .rdata follows (strings of libcd, libgpu, ...)
DATA_START = 0x80075AA0         # Data001Files, first game .data
DATA_GAME_END = 0x80087154      # PSY-Q .data / .sdata follows
DATA_END = 0x8008B450           # .bss starts
SBSS_START = 0x8008B450         # PSY-Q .sbss
BSS_START = 0x8008B484          # = $gp, game .bss
BSS_GAME_END = 0x8009AE60       # PSY-Q .bss follows
BSS_END = 0x800A05A0

DATA_RE = re.compile(r"(dword|byte|word|stru|off|jpt|flt|dbl|asc|a[A-Z0-9_])")


def load_symbols():
    syms = []
    for line in open(os.path.join(REPO, "symbol_addrs.txt")):
        m = re.match(r"(\w+)=0x([0-9a-fA-F]+);", line)
        if m:
            syms.append((int(m.group(2), 16), m.group(1)))
    syms.sort()
    return syms


def c_data_names(known, known_addrs=()):
    """name -> address; names whose address is already known under another name are returned too"""
    """data symbols the C sources/headers use that are named after their address but are not in symbol_addrs.txt"""
    """A name only becomes a new split point when it is declared as data (extern or initialised definition):
    macros, typedefs or comments that merely end in an address are ignored (SIN_TBL_80084540 once shifted the data)."""
    found = {}
    srcs = [open(os.path.join(REPO, "src", fn)).read() for fn in os.listdir(os.path.join(REPO, "src")) if fn.endswith((".c", ".h"))]
    text = "\n".join(srcs)
    for name, addr in re.findall(r"\b(\w+_([0-9A-F]{8}))\b", text):
        a = int(addr, 16)
        if RDATA_START <= a < BSS_GAME_END and name not in known and name not in found:
            dims = r"\s*(?:\[[^\]]*\]\s*)*"
            declared = re.search(r"\bextern\s[^;(){}]*?\b" + name + r"\b" + dims + ";", text) or \
                re.search(r"^[\w \t*]*\b" + name + r"\b" + dims + "=", text, re.M)
            if declared or a in known_addrs:
                found[name] = a
            else:
                print("split.py: ignoring %s (not declared as data; rename it or add it to symbol_addrs.txt)" % name)
    return found


def crlf(text):
    return text.replace("\r\n", "\n").replace("\n", "\r\n")


def write(path, text):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    open(path, "w", newline="").write(crlf(text))


ALIASES = {}   # address -> other names the C sources use for the symbol there


def data_chunk(exe, name, addr, size, section):
    out = ["\t.section\t%s" % section, "\t.globl\t%s" % name, "%s:" % name]
    for alias in ALIASES.get(addr, []):
        out += ["\t.globl\t%s" % alias, "%s:" % alias]
    if section == ".bss":
        out.append("\t.space\t%d" % size)
    else:
        off = addr - BASE
        if addr % 4 == 0 and size % 4 == 0:
            for i in range(0, size, 16):
                n = min(16, size - i)
                out.append("\t.word\t" + ",".join("0x%08x" % struct.unpack("<I", exe[off + i + j:off + i + j + 4])[0]
                                                  for j in range(0, n, 4)))
        else:
            for i in range(0, size, 16):
                out.append("\t.byte\t" + ",".join("0x%02x" % b for b in exe[off + i:off + i + min(16, size - i)]))
    out.append("\t.text")
    return "\n".join(out) + "\n"


def section_of(addr):
    if RDATA_START <= addr < RDATA_GAME_END:
        return ".rdata"
    if DATA_START <= addr < DATA_GAME_END:
        return ".data"
    return None


def first_references(exe, funcs):
    """address -> index of the first function (in address order) that loads/stores/addresses it through lui"""
    fa = [a for a, _ in funcs]
    first = {}
    lui = {}
    for pc in range(BASE, GAME_TEXT_END, 4):
        w = struct.unpack("<I", exe[pc - BASE:pc - BASE + 4])[0]
        i = bisect.bisect_right(fa, pc) - 1
        if i >= 0 and pc == fa[i]:
            lui = {}
        op, rs, rt, imm = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 0xffff
        s = imm - 0x10000 if imm >= 0x8000 else imm
        if op == 15:
            lui[rt] = imm << 16
            continue
        if op in (9, 35, 36, 32, 33, 37, 43, 40, 41, 34, 38) and rs in lui and i >= 0:
            first.setdefault(lui[rs] + s, i)
        if op == 0:
            lui.pop((w >> 11) & 31, None)
        elif op not in (43, 40, 41, 42, 46, 4, 5, 6, 7, 1, 2, 3):
            lui.pop(rt, None)
    return first


def load_tus():
    tus = []
    for line in open(os.path.join(REPO, "config", "tus.txt")):
        line = line.split("#")[0].strip()
        if line:
            n, a = line.split()
            tus.append((n, int(a, 16)))
    return tus


INCLUDES = """#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
"""


def init_src(tus, code, dsyms, owner, tu_of_addr, addr_of):
    """one-off: distribute the functions of the old src/*.c files into one file per translation unit"""
    import full_build as fb
    old = ["main.c", "funcs.c", "sound.c", "globals.c"]
    c_funcs, c_data, decls = {}, {}, []
    data_names = {n for _, _, _, n in dsyms}
    declared = set()
    for fn in os.listdir(os.path.join(REPO, "src")):
        if fn.endswith(".h") and fn != "data_decls.h":
            declared |= set(re.findall(r"^extern\s[^;(]*?(\w+)\s*(?:\[[^;]*)?;", open(os.path.join(REPO, "src", fn)).read(), re.M))
    skipped = []
    for fn in old:
        # the sources as they were before the split (HEAD of the commit that introduced this script)
        r = subprocess.run(["git", "show", "%s:src/%s" % (OLD_REV, fn)], cwd=REPO, stdout=subprocess.PIPE)
        if r.returncode != 0:
            continue
        for kind, name, text, matched in fb.split_blocks(r.stdout.decode()):
            if kind == "func":
                if name in addr_of and addr_of[name] < GAME_TEXT_END:
                    c_funcs[name] = (text, matched)
                else:
                    skipped.append(name)
                continue
            if text.startswith("#include"):
                continue
            m = fb.VARDEF.match(text.strip())
            vname = None
            if m:
                d = re.split(r"[\[;=]", m.group("decl").strip())[0].split()
                vname = d[-1].lstrip("*") if d else None
            if vname in data_names and "=" in text:
                c_data[vname] = text
                decls.append("extern " + text.split("=")[0].strip() + ";")
            elif m and vname and vname not in declared:
                decls.append("extern " + text.strip())
            elif not m:
                decls.append(text)
    with open(os.path.join(REPO, "src", "data_decls.h"), "w") as f:
        f.write("#ifndef DATA_DECLS_H\n#define DATA_DECLS_H\n\n/* data that is still defined by the original asm (asm/d); see scripts/split.py */\n\n")
        f.write("\n".join(d for d in decls if d.strip()) + "\n\n#endif\n")
    units = {}
    for k, (tu, _) in enumerate(tus):
        units[k] = ([], [])
    for a, n in code:
        units[tu_of_addr(a)][0].append(n)
    for sec, a, size, n in dsyms:
        units[owner[n]][1].append(n)
    for k, (tu, _) in enumerate(tus):
        out = [INCLUDES.rstrip() + '\n#include "data_decls.h"\n']
        for n in units[k][1]:
            out.append(c_data[n] if n in c_data else "INCLUDE_DATA(%s);" % n)
        out.append("")
        for n in units[k][0]:
            t = c_funcs.get(n)
            if t and t[1]:
                out.append(t[0])
            else:
                if t:
                    out.append("#if 0\n" + t[0] + "\n#endif")
                out.append("INCLUDE_ASM(%s);" % n)
        open(os.path.join(REPO, "src", tu + ".c"), "w").write("\n".join(out) + "\n")
    print("wrote %d TU sources; %d old functions not part of the game code: %s" % (len(tus), len(skipped), " ".join(skipped[:40])))


def main(argv):
    exe = open(argv[0], "rb").read()[0x800:]
    gen_asm.configure(BASE, GAME_TEXT_END)
    syms = load_symbols()
    have = {a for a, _ in syms}
    extra = c_data_names({n for _, n in syms}, have)
    for n, a in extra.items():
        if a in have:
            ALIASES.setdefault(a, []).append(n)
    syms = sorted(syms + [(a, n) for n, a in extra.items() if a not in have])
    names = {a: n for a, n in syms}
    from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32, CS_MODE_LITTLE_ENDIAN
    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32 + CS_MODE_LITTLE_ENDIAN)

    code = [(a, n) for a, n in syms if BASE <= a < GAME_TEXT_END]
    funcs = [(a, n) for a, n in code if not n.startswith(gen_asm.DATA_PREFIXES)]
    tus = load_tus()
    tu_starts = [a for _, a in tus]

    def tu_of_addr(a):
        return bisect.bisect_right(tu_starts, a) - 1

    # --- code
    spans = {}
    for (a, n), (b, _) in zip(code, code[1:] + [(GAME_TEXT_END, "")]):
        spans[n] = (a, b - a)
        text = (gen_asm.emit_data(exe, n, a, b - a) if n.startswith(gen_asm.DATA_PREFIXES)
                else gen_asm.emit_function(md, exe, n, a, b - a, names))
        write(os.path.join(REPO, "asm", "f", n + ".s"), text)

    c_sizes = {}
    for line in open(os.path.join(REPO, "config", "c_data.txt")):
        line = line.split("#")[0].split()
        if line:
            c_sizes[line[0]] = int(line[1])

    c_trunc = {}
    for line in open(os.path.join(REPO, "config", "c_rodata.txt")):
        line = line.split("#")[0].split()
        if line:
            c_trunc[line[0]] = int(line[1], 0)

    # --- data symbols of the game, each owns the bytes up to the next symbol (or section end)
    ends = {".rdata": RDATA_GAME_END, ".data": DATA_GAME_END}
    first = first_references(exe, funcs)
    dsyms = []
    for sec, lo, hi in ((".rdata", RDATA_START, RDATA_GAME_END), (".data", DATA_START, DATA_GAME_END),
                        (".bss", BSS_START, BSS_GAME_END)):
        pts = [(a, n) for a, n in syms if lo <= a < hi]
        if not pts or pts[0][0] != lo:
            pts.insert(0, (lo, "%s_%08X" % ("rdata" if sec == ".rdata" else "data", lo)))
        for (a, n), (b, _) in zip(pts, pts[1:] + [(hi, "")]):
            b = min(b, a + c_trunc.get(n, b - a))
            dsyms.append((sec, a, b - a, n))
            write(os.path.join(REPO, "asm", "d", n + ".s"), data_chunk(exe, n, a, b - a, sec))
            if n in c_sizes and c_sizes[n] < b - a:
                tail = n + "_tail"
                write(os.path.join(REPO, "asm", "d", tail + ".s"),
                      data_chunk(exe, tail, a + c_sizes[n], b - a - c_sizes[n], sec))

    # TU of a data symbol: smallest TU index of anything referenced at or after it (monotone), i.e. the data
    # of a TU is never placed after data that an earlier TU needs
    owner = {}
    for sec in (".rdata", ".data", ".bss"):
        part = [d for d in dsyms if d[0] == sec]
        refs = []
        for _, a, size, n in part:
            r = [first[x] for x in range(a, a + size) if x in first]
            refs.append(tu_of_addr(funcs[min(r)][0]) if r else None)
        best = len(tus) - 1
        for k in range(len(part) - 1, -1, -1):
            if refs[k] is not None:
                best = min(best, refs[k])
            owner[part[k][3]] = best

    # --- the library part
    def blob(name, lo, hi, section):
        out = ["\t.section\t%s" % section, "\t.globl\t%s" % name, "%s:" % name]
        if section == ".bss":
            out.append("\t.space\t%d" % (hi - lo))
        else:
            for a in range(lo, hi, 16):
                n = min(16, hi - a)
                if n % 4 == 0 and a % 4 == 0:
                    out.append("\t.word\t" + ",".join("0x%08x" % struct.unpack("<I", exe[a - BASE + j:a - BASE + j + 4])[0]
                                                      for j in range(0, n, 4)))
                else:
                    out.append("\t.byte\t" + ",".join("0x%02x" % b for b in exe[a - BASE:a - BASE + n]))
        out.append("\t.text")
        write(os.path.join(REPO, "asm", "lib", name + ".s"), "\n".join(out) + "\n")

    # code of the library keeps its symbols so the game can call it by name
    lib_syms = [(a, n) for a, n in syms if GAME_TEXT_END <= a < LIB_TEXT_END]
    lib_text = ["\t.text"]
    pos = GAME_TEXT_END
    pts = lib_syms
    if not pts or pts[0][0] != GAME_TEXT_END:
        pts = [(GAME_TEXT_END, "libtext_%08X" % GAME_TEXT_END)] + pts
    for (a, n), (b, _) in zip(pts, pts[1:] + [(LIB_TEXT_END, "")]):
        lib_text.append("\t.globl\t%s" % n)
        lib_text.append("%s:" % n)
        for pc in range(a, b, 4):
            lib_text.append("\t.word\t0x%08x" % struct.unpack("<I", exe[pc - BASE:pc - BASE + 4])[0])
    write(os.path.join(REPO, "asm", "lib", "text.s"), "\n".join(lib_text) + "\n")
    blob("lib_pad", LIB_TEXT_END, RDATA_START, ".text")
    blob("lib_rdata", RDATA_GAME_END, DATA_START, ".rdata")
    blob("lib_data", DATA_GAME_END, DATA_END, ".data")
    blob("lib_sbss", SBSS_START, BSS_START, ".sbss")
    blob("lib_bss", BSS_GAME_END, BSS_END, ".bss")

    # --- unit list
    with open(os.path.join(REPO, "asm", "units.txt"), "w") as f:
        for k, (tu, start) in enumerate(tus):
            end = tus[k + 1][1] if k + 1 < len(tus) else GAME_TEXT_END
            f.write("[%s]\n" % tu)
            for a, n in code:
                if start <= a < end:
                    f.write("code %s\n" % n)
            for sec, a, size, n in dsyms:
                if owner[n] == k:
                    f.write("data %s %s\n" % (sec, n))
    print("wrote asm/: %d code symbols, %d data symbols" % (len(code), len(dsyms)))
    if "--init-src" in argv:
        init_src(tus, code, dsyms, owner, tu_of_addr, {n: a for a, n in syms})


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
