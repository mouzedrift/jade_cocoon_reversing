#!/usr/bin/env python3
"""
Generate PSY-Q (aspsx) assembly for functions of the original executable.

The text is meant to be pulled into a C file with INCLUDE_ASM (see build.py) so a whole
translation unit can be built even if some of its functions are not decompiled yet.

usage: gen_asm.py SLUS_008.54 OUTDIR [--all] [--combined FILE]
  OUTDIR/<function>.s   one file per function (only functions that are not marked "// Matched",
                        unless --all is given)
  --combined FILE       additionally write every selected function, in address order, to one file
"""
import argparse
import glob
import os
import re
import struct
import sys

from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32, CS_MODE_LITTLE_ENDIAN

BASE = 0x80010000
CODE_END = 0x8004D924  # end of the game code, PSY-Q library code follows

REGS = ["zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"]
REGNUM = {n: i for i, n in enumerate(REGS)}
REGNUM["s8"] = 30

DATA_PREFIXES = ("dword_", "word_", "byte_", "stru_", "off_", "jpt_", "flt_", "dbl_")


def configure(base, code_end):
    """retarget the generator, e.g. at an overlay that is loaded somewhere else"""
    global BASE, CODE_END
    BASE, CODE_END = base, code_end


def load_symbols(repo, path="symbol_addrs.txt"):
    syms = []
    for line in open(os.path.join(repo, path)):
        m = re.match(r"(\w+)=0x([0-9a-fA-F]+);", line)
        if m:
            syms.append((int(m.group(2), 16), m.group(1)))
    syms.sort()
    return syms


def matched_names(repo):
    names = set()
    for path in glob.glob(os.path.join(repo, "src", "*.c")):
        lines = open(path).read().split("\n")
        for i, line in enumerate(lines[:-1]):
            if line.strip() == "// Matched":
                m = re.search(r"(\w+)\(", lines[i + 1])
                if m:
                    names.add(m.group(1))
    return names


def reg(m):
    return "$%d" % REGNUM[m.group(1)]


# instructions of the R3000 (MIPS I); anything else is data that merely looks like code
R3000 = set("""add addi addiu addu and andi beq bgez bgezal bgtz blez bltz bltzal bne break div divu j jal jalr jr
lb lbu lh lhu lui lw lwl lwr mfhi mflo mthi mtlo mult multu nor or ori sb sh sll sllv slt slti sltiu sltu sra srav
srl srlv sub subu sw swl swr xor xori syscall nop move beqz bnez b bal negu neg not li sltu""".split())


def format_insn(i, names, labels):
    mn, op = i.mnemonic, i.op_str
    if mn not in R3000:
        return None
    if mn in ("break", "syscall"):
        return None
    if mn.startswith(("cop", "mfc", "mtc", "cfc", "ctc", "lwc", "swc", "rfe", "tlb")) or mn == "invalid":
        return None
    # branch / jump targets
    if mn in ("j", "jal"):
        t = int(op, 16)
        # only code in this executable is referenced by name, library code by address
        return "%s\t%s" % (mn, names[t] if t in names and BASE <= t < CODE_END else "0x%08x" % t)
    if mn in ("beq", "bne", "beqz", "bnez", "bgez", "bgtz", "blez", "bltz", "bgezal", "bltzal", "b", "bal"):
        parts = [p.strip() for p in op.split(",")]
        t = int(parts[-1], 16)
        parts[-1] = labels[t]
        parts = [re.sub(r"\$(\w+)", reg, p) for p in parts[:-1]] + [parts[-1]]
        return "%s\t%s" % (mn, ",".join(parts))
    if mn in ("divu", "div") and op.count(",") == 2:
        parts = [p.strip() for p in op.split(",")]
        op = ",".join(parts[1:])
    op = re.sub(r"\$(\w+)", reg, op)
    op = re.sub(r"(^|,)\s*\(", r"\g<1>0(", op)       # "(" with no offset -> "0("
    op = re.sub(r"(-?)0x([0-9a-f]+)\(", lambda m: "%s0x%s(" % (m.group(1), m.group(2)), op)
    op = op.replace(", ", ",")
    if mn == "nop":
        return "nop"
    return "%s\t%s" % (mn, op) if op else mn


def decode(md, exe, pc):
    w = exe[pc - BASE:pc - BASE + 4]
    for i in md.disasm(w, pc):
        return i
    return None


BRANCHES = ("beq", "bne", "beqz", "bnez", "bgez", "bgtz", "blez", "bltz", "b", "bal", "bgezal", "bltzal")


def emit_function(md, exe, name, addr, size, names):
    insns = [decode(md, exe, pc) for pc in range(addr, addr + size, 4)]
    labels = {}
    for i in insns:
        if i is not None and i.mnemonic in BRANCHES:
            t = int(i.op_str.split(",")[-1].strip(), 16)
            labels[t] = ".L%08x" % t
    out = ["\t.text", "\t.globl\t%s" % name, "%s:" % name, "\t.set\tnoreorder", "\t.set\tnoat"]
    for k, pc in enumerate(range(addr, addr + size, 4)):
        if pc in labels:
            out.append("%s:" % labels[pc])
        ins = format_insn(insns[k], names, labels) if insns[k] is not None else None
        if ins is None:
            out.append("\t.word\t0x%08x" % struct.unpack("<I", exe[pc - BASE:pc - BASE + 4])[0])
        else:
            out.append("\t" + ins)
    out.append("\t.set\tat")
    out.append("\t.set\treorder")
    return "\n".join(out) + "\n"


def emit_data(exe, name, addr, size, section=".text", header=False):
    """header: the first word goes to .sdata, which the overlay link puts in front of everything else, so
    that the alignment of the compiler's .rdata (jump tables) starts behind it"""
    out = ["\t" + (".sdata" if header else section), "\t.globl\t%s" % name, "%s:" % name]
    for off in range(0, size - size % 4, 4):
        if header and off == 4:
            out.append("\t" + section)
        out.append("\t.word\t0x%08x" % struct.unpack("<I", exe[addr - BASE + off:addr - BASE + off + 4])[0])
    for off in range(size - size % 4, size):
        out.append("\t.byte\t0x%02x" % exe[addr - BASE + off])
    if section != ".text":
        out.append("\t.text")  # gcc does not know that the include switched sections
    return "\n".join(out) + "\n"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("exe")
    ap.add_argument("outdir")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--combined")
    ap.add_argument("--repo", default=os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
    args = ap.parse_args()

    repo = os.path.abspath(args.repo)
    exe = open(args.exe, "rb").read()[0x800:]
    syms = load_symbols(repo)
    code = [(a, n) for a, n in syms if BASE <= a < CODE_END]
    names = {a: n for a, n in syms}
    matched = set() if args.all else matched_names(repo)

    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32 + CS_MODE_LITTLE_ENDIAN)
    os.makedirs(args.outdir, exist_ok=True)
    combined = []
    count = 0
    for (a, n), (b, _) in zip(code, code[1:] + [(CODE_END, "")]):
        if n in matched:
            continue
        size = b - a
        text = emit_data(exe, n, a, size) if n.startswith(DATA_PREFIXES) else emit_function(md, exe, n, a, size, names)
        open(os.path.join(args.outdir, n + ".s"), "w").write(text)
        combined.append(text)
        count += 1
    if args.combined:
        open(args.combined, "w").write("".join(combined))
    print("wrote %d files to %s" % (count, args.outdir))


if __name__ == "__main__":
    sys.exit(main())
