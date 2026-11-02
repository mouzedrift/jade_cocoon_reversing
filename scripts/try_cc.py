#!/usr/bin/env python3
"""
Try every "#if 0 ... #endif INCLUDE_ASM(x)" near miss one by one with the psyq 4.4 and 4.3 compilers
(the latter is selected per TU in config/cc43.txt) and report which ones match.

usage: try_cc.py SLUS_008.54 [func ...]
Temporarily rewrites src/, restored after every attempt.
"""
import os
import re
import subprocess
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
PAT = re.compile(r"#if 0\n((?:(?!#if 0\n|#endif).)*?)#endif\nINCLUDE_ASM\((\w+)\);\n", re.S)


def run(cmd):
    return subprocess.run(cmd, capture_output=True, text=True)


def main():
    exe = sys.argv[1]
    only = set(sys.argv[2:])
    os.chdir(REPO)
    for f in sorted(os.listdir("src")):
        if not f.endswith(".c"):
            continue
        path = "src/" + f
        orig = open(path).read()
        for m in PAT.finditer(orig):
            name = m.group(2)
            if only and name not in only:
                continue
            res = []
            for cc in ("4.4", "4.3", "4.6", "4.6n"):
                open(path, "w").write(orig[:m.start()] + m.group(1) + orig[m.end():])
                open("config/cc43.txt", "w").write((f[:-2] + " " + cc if cc != "4.4" else "") + "\n")
                if run([sys.executable, "build.py"]).returncode:
                    res.append(cc + ":build-fail")
                    continue
                out = run([sys.executable, "scripts/check_match.py", exe, name]).stdout
                line = [l for l in out.splitlines() if l.startswith(name + " ")]
                res.append(cc + ":" + (line[0].split(" ", 1)[1] if line else "?"))
            open(path, "w").write(orig)
            print(f, name, " ".join(res), flush=True)
    open("config/cc43.txt", "w").write("")
    run(["git", "checkout", "src"])


main()
