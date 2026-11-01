#!/usr/bin/env python3
"""
Compare functions from a build against the original executable.

A function matches when every instruction word is identical, ignoring
  * j/jal targets,
  * the immediates of lui and of the instructions that use a lui'd register or $gp
    (global addresses are not pinned to their original location in this build).

usage: check_match.py SLUS_008.54 func [func ...]
       check_match.py SLUS_008.54 --all     (every function preceded by "// Matched")
Run from anywhere; --repo overrides the repository root.
"""
import argparse
import glob
import os
import re
import struct
import sys

BASE = 0x80010000


def load_symbols(repo):
    syms = {}
    for line in open(os.path.join(repo, "symbol_addrs.txt")):
        m = re.match(r"(\w+)=0x([0-9a-fA-F]+);", line)
        if m:
            syms[m.group(1)] = int(m.group(2), 16)
    return syms


def load_map(repo):
    built = {}
    for line in open(os.path.join(repo, "build_psyq", "jade_cocoon.map")):
        m = re.match(r"\s*([0-9A-F]{8})\s+(\w+)\s*$", line)
        if m:
            built[m.group(2)] = int(m.group(1), 16)
    return built


class Checker:
    def __init__(self, orig_exe, repo, load=True):
        self.orig = open(orig_exe, "rb").read()[0x800:]
        self.repo = repo
        self.syms = load_symbols(repo)
        if load:
            self.reload()

    def reload(self):
        self.built = open(os.path.join(self.repo, "build_psyq", "jade_cocoon.exe"), "rb").read()[0x800:]
        self.map = load_map(self.repo)
        self.map_addrs = sorted(self.map.values())

    def check(self, name):
        """returns number of mismatching words (0 = match), or None if the function is not in the build"""
        if name not in self.map or name not in self.syms:
            return None
        start = self.map[name]
        nxt = [a for a in self.map_addrs if a > start]
        size = (nxt[0] - start) // 4 if nxt else 0
        orig = self.orig[self.syms[name] - BASE:][:size * 4]
        built = self.built[start - BASE:][:size * 4]
        lui = set()
        bad = 0
        for i in range(size):
            a = struct.unpack("<I", orig[i * 4:i * 4 + 4])[0]
            b = struct.unpack("<I", built[i * 4:i * 4 + 4])[0]
            op = a >> 26
            if a == b:
                if op == 15:
                    lui.add((a >> 16) & 31)
                continue
            if op == b >> 26 and op in (2, 3):
                continue
            if op == 15 and op == b >> 26 and (a >> 16 & 31) == (b >> 16 & 31):
                lui.add((a >> 16) & 31)
                continue
            if op == b >> 26 and ((a >> 21) & 31) == ((b >> 21) & 31) and ((a >> 16) & 31) == ((b >> 16) & 31):
                rs = (a >> 21) & 31
                if op >= 8 and (rs in lui or rs == 28):
                    continue
            bad += 1
        return bad


def matched_names(repo):
    names = set()
    for path in glob.glob(os.path.join(repo, "src", "*.c")):
        lines = open(path).read().split("\n")
        for i, line in enumerate(lines[:-1]):
            if line.strip() == "// Matched":
                m = re.search(r"(\w+)\(", lines[i + 1])
                if m:
                    names.add(m.group(1))
    return sorted(names)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("exe")
    ap.add_argument("funcs", nargs="*")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--repo", default=os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
    args = ap.parse_args()
    repo = os.path.abspath(args.repo)
    chk = Checker(args.exe, repo)
    names = matched_names(repo) if args.all else args.funcs
    failed = 0
    for n in names:
        r = chk.check(n)
        status = "NOTBUILT" if r is None else ("OK" if r == 0 else f"DIFF ({r} words)")
        if r != 0:
            failed += 1
        if r != 0 or not args.all:
            print(n, status)
    print(f"{len(names) - failed}/{len(names)} match")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
