#!/usr/bin/env python3
"""Apply config/renames.txt (one `OldName NewName` per line, # comments) to the sources.

Every rename is a whole-word replacement in the files that hold symbol names: src/ (all .c/.h, overlays
included), include/, symbol_addrs.txt, config/*.txt and overlays/*.sym (docs/ is left alone: it uses address names as examples). The overlays pick up
main-executable names from symbol_addrs.txt (scripts/overlays.py writes them as equates), so a rename has
to reach both the symbol list and every C source that uses the name.

Renames are applied in file order, so chains (A B, then B C) work. Running the script again is a no-op:
once OldName is gone nothing matches. Usage: python3 scripts/apply_renames.py [--check]
(--check only lists the files that would change and exits 1 if there are any).
"""
import glob
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")


def load_renames(path):
    renames = []
    seen = {}
    for n, line in enumerate(open(path), 1):
        line = line.split("#", 1)[0].strip()
        if not line:
            continue
        parts = line.split()
        if len(parts) != 2 or not all(IDENT.match(p) for p in parts):
            sys.exit("%s:%d: expected `OldName NewName`: %r" % (path, n, line))
        old, new = parts
        if old == new:
            sys.exit("%s:%d: %s renamed to itself" % (path, n, old))
        if old in seen:
            sys.exit("%s:%d: %s renamed twice (line %d)" % (path, n, old, seen[old]))
        seen[old] = n
        renames.append((old, new))
    return renames


def target_files():
    pats = ["src/**/*.c", "src/**/*.h", "include/**/*.c", "include/**/*.h", "include/**/*.inc",
            "symbol_addrs.txt", "config/*.txt", "overlays/*.sym"]
    files = set()
    for p in pats:
        files.update(glob.glob(os.path.join(REPO, p), recursive=True))
    files.discard(os.path.join(REPO, "config", "renames.txt"))
    return sorted(files)


def main():
    check = "--check" in sys.argv
    renames = load_renames(os.path.join(REPO, "config", "renames.txt"))
    if not renames:
        return 0
    # one pass per file: chains are resolved first so the result does not depend on match order
    final = {}
    for old, new in renames:
        final[old] = new
    for old in list(final):
        n, hops = final[old], 0
        while n in final and hops < len(final):
            n, hops = final[n], hops + 1
        if n in final:
            sys.exit("rename cycle through %s" % old)
        final[old] = n
    pat = re.compile(r"\b(" + "|".join(sorted(map(re.escape, final), key=len, reverse=True)) + r")\b")
    changed = []
    for path in target_files():
        try:
            text = open(path, encoding="latin-1", newline="").read()
        except OSError:
            continue
        new = pat.sub(lambda m: final[m.group(1)], text)
        if new != text:
            changed.append(os.path.relpath(path, REPO))
            if not check:
                with open(path, "w", encoding="latin-1", newline="") as f:
                    f.write(new)
    for c in changed:
        print(("would change " if check else "renamed in ") + c)
    return 1 if (check and changed) else 0


if __name__ == "__main__":
    sys.exit(main())
