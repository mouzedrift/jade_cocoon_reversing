#!/usr/bin/env python3
"""
Hash check of everything that is built: the linked image of the executable and every overlay.

usage: verify.py SLUS_008.54 ISO.bin [--update]
  * runs build.py and scripts/overlays.py for each overlay that has overlays/<name>.sym
  * compares the SHA-1 of each built image with the original (executable image without header and
    without the bss/garbage behind the linked image; overlays as stored on the disc)
  * config/hashes.txt keeps the expected hashes (only hashes, no game data); --update rewrites it from the
    originals, otherwise the built hashes are also checked against the file
Exit status 0 only if everything matches.
"""
import glob
import hashlib
import os
import subprocess
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import overlays  # noqa: E402


def sha(b):
    return hashlib.sha1(b).hexdigest()


def main(argv):
    exe_path, iso = argv[0], argv[1]
    update = "--update" in argv
    if subprocess.call([sys.executable, os.path.join(REPO, "build.py")], cwd=REPO) != 0:
        print("exe: BUILD FAILED")
        return 1
    orig = open(exe_path, "rb").read()[0x800:]
    built = open(os.path.join(REPO, "build_psyq", "jade_cocoon.exe"), "rb").read()[0x800:]
    results = {"exe-image": (sha(orig[:len(built)]), sha(built))}
    for sym in sorted(glob.glob(os.path.join(REPO, "overlays", "*.sym"))):
        name = os.path.basename(sym)[:-4].upper()
        out_bin = os.path.join(REPO, "build_psyq", name + ".BIN")
        if os.path.exists(out_bin):
            os.remove(out_bin)  # a failed build must not leave the previous image behind
        if subprocess.call([sys.executable, os.path.join(REPO, "scripts", "overlays.py"), name, iso, exe_path],
                           cwd=REPO, stdout=subprocess.DEVNULL) not in (0, 1):
            results["overlay-" + name] = ("", "BUILD FAILED")
            continue
        if not os.path.exists(out_bin):
            results["overlay-" + name] = ("", "BUILD FAILED")
            continue
        data = open(os.path.join(REPO, "build_psyq", name + ".orig"), "rb").read()
        results["overlay-" + name] = (sha(data), sha(open(out_bin, "rb").read()))
    path = os.path.join(REPO, "config", "hashes.txt")
    if update:
        with open(path, "w") as f:
            f.write("# SHA-1 of the original images (see scripts/verify.py)\n")
            for k, (o, _) in results.items():
                f.write("%s %s\n" % (k, o))
    expected = {}
    if os.path.exists(path):
        for line in open(path):
            if line.strip() and not line.startswith("#"):
                k, h = line.split()
                expected[k] = h
    ok = True
    for k, (o, b) in results.items():
        good = o == b and expected.get(k, o) == b
        ok &= good
        print("%-18s %s  %s" % (k, "OK  " if good else "FAIL", b))
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
