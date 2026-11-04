#!/usr/bin/env python3
"""
Turn C data definitions back into INCLUDE_DATA lines (to generate them again with gendata.py, e.g. after their
type changed).

  python scripts/regendata.py SLUS_008.54 TU NAME... [--gen]

Each NAME's definition in src/TU.c is replaced by the INCLUDE_DATA lines of the asm/d symbols it covers (up to the
next data definition of the executable); --gen runs gendata.py on them (--write).
"""
import bisect
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gendata  # noqa: E402
import data_owners  # noqa: E402
import split  # noqa: E402

REPO = gendata.REPO


def statement_span(text, name):
    """(start, end) of the top-level definition of name"""
    m = re.search(r"^(?!extern|typedef|return)[A-Za-z_][^\n;{}=]*[\s*(]%s\b[^\n;]*?(=|BSS)" % re.escape(name),
                  text, re.M)
    if not m:
        raise SystemExit("no definition of %s" % name)
    i, depth = m.start(), 0
    while True:
        c = text[i]
        if c in "\"'":
            i = gendata._skip_quoted(text, i)
            continue
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
        elif c == ";" and depth == 0:
            break
        i += 1
    end = text.index("\n", i) + 1
    return m.start(), end


def main(argv):
    args = [a for a in argv if not a.startswith("--")]
    exe = open(args[0], "rb").read()[0x800:]
    tu, names = args[1], args[2:]
    syms = gendata.Syms(exe)
    # every data symbol that is defined somewhere (C or INCLUDE_DATA): the ends of the objects
    starts = set()
    for t, _ in split.load_tus():
        for n in data_owners.c_definitions(t) + gendata.tu_data(t):
            if n in syms.addr:
                starts.add(syms.addr[n])
    starts = sorted(starts)
    path = os.path.join(REPO, "src", tu + ".c")
    text = open(path).read()
    restored = []
    for name in names:
        a = syms.addr[name]
        b = starts[bisect.bisect_right(starts, a)] if bisect.bisect_right(starts, a) < len(starts) else a + 4
        s, e = statement_span(text, name)
        inc = []
        for x in syms.sorted:
            if a <= x < b:
                ns = [n for n in syms.by_addr[x] if os.path.exists(os.path.join(REPO, "asm", "d", n + ".s"))]
                if ns:
                    inc.append(ns[0])
        text = text[:s] + "".join("INCLUDE_DATA(%s);\n" % n for n in inc) + text[e:]
        restored += inc
        print("%s -> %s" % (name, " ".join(inc)))
    open(path, "w").write(text)
    if "--gen" in argv:
        subprocess.check_call([sys.executable, os.path.join(REPO, "scripts", "gendata.py"), args[0], tu] + restored +
                              ["--write"])


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
