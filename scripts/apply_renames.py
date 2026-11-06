#!/usr/bin/env python3
"""Apply config/renames.txt to the sources (the file format is documented at its top).

Every rename is a whole-word replacement in the files that hold symbol names: src/ (all .c/.h, overlays
included), include/, config/*.txt and overlays/*.sym (docs/ is left alone: it uses
address names as examples): a name is shared by the C of every image that uses it and by the symbol
lists (overlays/*.sym, config/aliases.txt, config/fixed_symbols.txt).

Files belong to a unit: an overlay's files are src/overlays/<name>.c, <name>_<n>.c, <name>.h and
overlays/<name>.sym; everything else is EXE. A pair applies to the files of the units its section names
(`[GAME BATTLE EXE]`), or to every file in an `[ALL]` section (the default at the top of the file).
Overlays loaded at the same address reuse addresses for different things, so a pair whose address is in
the overlay area (0x800A05A0 and up) must be in a section that names its units.

Chains (A B, then B C) are resolved per file among the pairs that apply to it, so the result does not
depend on match order. Running the script again is a no-op: once OldName is gone nothing matches.
Usage: python3 scripts/apply_renames.py [--check]
(--check only lists the files that would change and exits 1 if there are any).
"""
import glob
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
ADDR = re.compile(r"_([0-9A-F]{8})$")
OVERLAY_AREA = 0x800A05A0  # lowest overlay load address (TITLE, GAME, ...); the executable's .bss ends below


def overlay_units():
    return {os.path.basename(p)[:-4].upper() for p in glob.glob(os.path.join(REPO, "overlays", "*.sym"))}


def unit_of(rel):
    rel = rel.replace(os.sep, "/")
    m = re.match(r"src/overlays/([a-z0-9]+?)(?:_\d+)?\.[ch]$", rel) or re.match(r"overlays/([a-z0-9]+)\.sym$", rel)
    return m.group(1).upper() if m else "EXE"


def addr_of(name):
    m = ADDR.search(name)
    return int(m.group(1), 16) if m else None


def load_renames(path):
    """-> list of (old, new, scope) in file order; scope is None ([ALL]) or a frozenset of unit names."""
    units = overlay_units() | {"EXE"}
    renames = []
    seen = {}
    scope = None
    for n, line in enumerate(open(path), 1):
        line = line.split("#", 1)[0].strip()
        if not line:
            continue
        if line.startswith("["):
            if not line.endswith("]"):
                sys.exit("%s:%d: expected `[UNIT ...]`: %r" % (path, n, line))
            names = line[1:-1].split()
            if names == ["ALL"]:
                scope = None
                continue
            bad = [u for u in names if u not in units]
            if not names or bad:
                sys.exit("%s:%d: unknown unit(s) %s (overlays/*.sym names, EXE or ALL)" % (path, n, " ".join(bad)))
            scope = frozenset(names)
            continue
        parts = line.split()
        if len(parts) != 2 or not all(IDENT.match(p) for p in parts):
            sys.exit("%s:%d: expected `OldName NewName`: %r" % (path, n, line))
        old, new = parts
        if old == new:
            sys.exit("%s:%d: %s renamed to itself" % (path, n, old))
        if scope is None:
            for x in (old, new):
                a = addr_of(x)
                if a is not None and OVERLAY_AREA <= a < 0x80200000:
                    sys.exit("%s:%d: %s is an overlay address: put the pair in a [UNIT ...] section" % (path, n, x))
        for m, s in seen.get(old, []):
            if s is None or scope is None or s & scope:
                sys.exit("%s:%d: %s renamed twice for the same files (line %d)" % (path, n, old, m))
        seen.setdefault(old, []).append((n, scope))
        renames.append((old, new, scope))
    return renames


def target_files():
    pats = ["src/**/*.c", "src/**/*.h", "include/**/*.c", "include/**/*.h", "include/**/*.inc",
            "config/*.txt", "overlays/*.sym"]
    files = set()
    for p in pats:
        files.update(glob.glob(os.path.join(REPO, p), recursive=True))
    files.discard(os.path.join(REPO, "config", "renames.txt"))
    return sorted(files)


def build_pattern(renames, unit):
    final = {}
    for old, new, scope in renames:
        if scope is None or unit in scope:
            final[old] = new
    for old in list(final):
        n, hops = final[old], 0
        while n in final and hops < len(final):
            n, hops = final[n], hops + 1
        if n in final:
            sys.exit("rename cycle through %s" % old)
        final[old] = n
    if not final:
        return None, final
    pat = re.compile(r"\b(" + "|".join(sorted(map(re.escape, final), key=len, reverse=True)) + r")\b")
    return pat, final


def main():
    check = "--check" in sys.argv
    renames = load_renames(os.path.join(REPO, "config", "renames.txt"))
    if not renames:
        return 0
    cache = {}
    changed = []
    for path in target_files():
        unit = unit_of(os.path.relpath(path, REPO))
        if unit not in cache:
            cache[unit] = build_pattern(renames, unit)
        pat, final = cache[unit]
        if pat is None:
            continue
        try:
            text = open(path, encoding="latin-1", newline="").read()
        except OSError:
            continue
        if os.path.basename(path) == "aliases.txt":
            # each line belongs to the image in its first column
            def line_sub(line):
                f = line.split()
                u = f[0] if f and not line.startswith("#") else "EXE"
                if u not in cache:
                    cache[u] = build_pattern(renames, u)
                p, fin = cache[u]
                return p.sub(lambda m: fin[m.group(1)], line) if p is not None else line
            new = "".join(line_sub(l) for l in text.splitlines(True))
        else:
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
