from ninja import ninja_syntax
import glob
import os
import subprocess
import sys
import argparse
import time
import re
import platform

def read_tus():
    """translation units of the game code in link order (config/tus.txt): src/<name>.c each, or
    "obj NAME" for a PSY-Q object linked as is from libs/psyq4.4/LIB/NAME (e.g. the SN start-up 2MBYTE.OBJ)"""
    tus = []
    for line in open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "config", "tus.txt")):
        f = line.split("#")[0].split()
        if f:
            tus.append(("obj " + f[1]) if f[0] == "obj" else f[0])
    return tus


c_files = [tu if tu.startswith("obj ") else tu + ".c" for tu in read_tus()]

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "scripts"))


def read_lib_objs():
    """config/lib_objs.txt: the PSY-Q modules in link order, ("obj", LIB, MODULE), ("src", FILE) for src/lib/FILE,
    ("bsshead", SIZE) / ("bsstail", SIZE)"""
    out = []
    for line in open(os.path.join(CURRENT_DIR, "config", "lib_objs.txt")):
        f = line.split("#")[0].split()
        if not f:
            continue
        if f[0] in ("bsshead", "bsstail"):
            out.append((f[0], int(f[1], 16)))
        elif f[0] == "src":
            out.append(("src", f[1]))
        else:
            out.append(("obj", f[0], f[1]))
    return out


def read_lib_commons():
    """config/lib_commons.txt: {(LIB, MODULE): [(name, size, addr)]} by address.
    psylink aligns every .bss contribution to 8 bytes once there are common symbols, which the original link
    didn't (the game's .bss is packed); defining the commons ourselves (behind their module, where psylink
    would put them) keeps them out of the link."""
    out = {}
    for line in open(os.path.join(CURRENT_DIR, "config", "lib_commons.txt")):
        f = line.split("#")[0].split()
        if f:
            out.setdefault((f[0], f[1]), []).append((f[2], int(f[3], 16), int(f[4], 16)))
    return {k: sorted(v, key=lambda c: c[2]) for k, v in out.items()}


def game_bss_end():
    """end of the game's .bss (the PSY-Q modules' .bss follows); the game's variables are all C"""
    import layout
    return layout.BSS_GAME_END


def read_aliases(image="EXE"):
    """config/aliases.txt: names of places inside C objects of the executable (or of an overlay),
    [(name, base symbol, offset)]"""
    out = []
    for line in open(os.path.join(CURRENT_DIR, "config", "aliases.txt")):
        f = line.split("#")[0].split()
        if f and f[0] == image:
            out.append((f[1], f[2], int(f[3], 16)))
    return out


def read_map_symbols():
    """{name: address} of the last link (build_psyq/jade_cocoon.map), {} before the first one"""
    path = os.path.join(BUILD_DIR, f"{EXE_NAME}.map")
    if not os.path.exists(path):
        return {}
    return {m.group(2): int(m.group(1), 16) for m in re.finditer(r"^ ([0-9A-F]{8})  (\w+)$", open(path).read(), re.M)}


def aliases_resolved():
    """True if the aliases of the last link sit at BASE + OFFSET (the equates are from the link before when
    something moved; nothing else depends on their values, so linking once more fixes them)"""
    syms = read_map_symbols()
    return all(n in syms and b in syms and syms[n] == syms[b] + off for n, b, off in read_aliases())


def external_symbols(src_dir):
    """[(name, address)] of the names in the executable's C sources (src/*.c, *.h, not src/overlays) that are
    outside of its image: from overlays/*.sym, or by the name's _XXXXXXXX suffix (buffers behind the image)"""
    ovl = {}
    for path in glob.glob(os.path.join(CURRENT_DIR, "overlays", "*.sym")):
        for line in open(path):
            m = re.match(r"(\w+)=0x([0-9a-fA-F]+);", line)
            if m:
                ovl[m.group(1)] = int(m.group(2), 16)
    names = set()
    for path in glob.glob(os.path.join(src_dir, "*.[ch]")):
        names |= set(re.findall(r"\b[A-Za-z_]\w*\b", open(path).read()))
    out = {}
    for n in names:
        if n in ovl:
            out[n] = ovl[n]
        else:
            m = re.match(r"\w+_([0-9A-F]{8})$", n)
            if m and int(m.group(1), 16) >= IMAGE_END:
                out[n] = int(m.group(1), 16)
    return sorted(out.items(), key=lambda x: (x[1], x[0]))


def write_if_changed(path, text):
    if not os.path.exists(path) or open(path, newline="").read() != text:
        with open(path, "w", newline="") as f:
            f.write(text)


def extract_lib_objs(psyq_lib, out_dir, wanted):
    """writes the wanted (LIB, MODULE) of the PSY-Q .LIB files to out_dir/LIB/MODULE.OBJ, returns their paths"""
    from lib_match import lib_modules
    paths = {}
    for lib in sorted({l for l, _ in wanted}):
        mods = {m: data for m, data in lib_modules(os.path.join(psyq_lib, lib))}
        d = os.path.join(out_dir, lib.split(".")[0])
        os.makedirs(d, exist_ok=True)
        for l, m in wanted:
            if l != lib:
                continue
            path = os.path.join(d, m + ".OBJ")
            if not os.path.exists(path) or open(path, "rb").read() != mods[m]:
                open(path, "wb").write(mods[m])
            paths[(l, m)] = path
    return paths

CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
BUILD_DIR = os.path.join(CURRENT_DIR, "build_psyq")

EXE_NAME = "jade_cocoon"
IMAGE_END = 0x800A05A0  # end of the executable's image (.bss included), where GAME/TITLE/... are loaded

def read_cc43():
    """TUs built with another compiler than psyq 4.4: "tu [4.3|4.6|4.6n]" (4.6n: with -mno-check-zero-division)"""
    path = os.path.join(CURRENT_DIR, "config", "cc43.txt")
    if not os.path.exists(path):
        return {}
    out = {}
    for l in open(path):
        f = l.split("#")[0].split()
        if f:
            out[f[0]] = f[1] if len(f) > 1 else "4.3"
    return out


cc43 = read_cc43()


def generate_ninja():
    psyq_path = os.path.join(CURRENT_DIR, "libs", "psyq4.4")
    with open("build.ninja", "w") as ninja_file:
        ninja = ninja_syntax.Writer(ninja_file)

        bin_dir = os.path.join(psyq_path, "bin")

        ninja.variable("cpppsx", os.path.join(bin_dir, "CPPPSX.EXE"))
        ninja.variable("cc1psx", os.path.join(bin_dir, "CC1PSX.EXE"))
        ninja.variable("cc1psx43", os.environ.get("CC1PSX43", os.path.join(CURRENT_DIR, "..", "psyq_sdk", "psyq_4.3", "bin", "cc1psx.exe")))
        ninja.variable("cc1psx46", os.environ.get("CC1PSX46", os.path.join(CURRENT_DIR, "..", "psyq_sdk", "psyq_4.6", "bin", "CC1PSX.EXE")))
        ninja.variable("aspsx", os.environ.get("ASPSX_EXE", os.path.join(bin_dir, "ASPSX.EXE")))
        ninja.variable("psylink", os.path.join(bin_dir, "psylink.exe"))
        ninja.variable("cpe2exe", os.path.join(bin_dir, "cpe2exe.exe"))

        psyq_include = os.path.join(psyq_path, "INCLUDE")
        project_src = os.path.join(CURRENT_DIR, "src")
        includes = f"-I {psyq_include} -I {project_src}"
        # extra defines for experiments, e.g. JC_DEFINES=DEBUG_TTY (see docs/testing_in_emulator.md); unset = matching build
        includes += "".join(f" -D{d}" for d in os.environ.get("JC_DEFINES", "").split())

        psyq_lib = os.path.join(psyq_path, "LIB")
        pysq_lib = f"/l {psyq_lib}"

        cpe_path = os.path.join(BUILD_DIR, f"{EXE_NAME}.cpe")
        sym_path = os.path.join(BUILD_DIR, f"{EXE_NAME}.sym")
        map_path = os.path.join(BUILD_DIR, f"{EXE_NAME}.map")
        exe_path = os.path.join(BUILD_DIR, f"{EXE_NAME}.exe")

        link_path = os.path.join(BUILD_DIR, "link.txt")
        rules = {
            "pre_process": (f"$cpppsx -undef -D__GNUC__=2 -v -D__OPTIMIZE__ {includes} -lang-c -Dmips -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D__CHAR_UNSIGNED__ -D_LANGUAGE_C -DLANGUAGE_C $in $out", "Preprocess $in -> $out"),
            "compile": ("$cc1psx -quiet -G0 -O2 $in -o $out", "Compile $in -> $out"),
            "compile4.3": ("$cc1psx43 -quiet -G0 -O2 $in -o $out", "Compile (psyq 4.3) $in -> $out"),
            "compile4.6": ("$cc1psx46 -quiet -G0 -O2 $in -o $out", "Compile (psyq 4.6) $in -> $out"),
            "compile4.6n": ("$cc1psx46 -quiet -G0 -O2 -mno-check-zero-division $in -o $out", "Compile (psyq 4.6, no zero check) $in -> $out"),
            "assemble": ("$aspsx -G0 -q -0 $in -o $out", "Assemble $in -> $out"),
            "link": (f"$psylink {pysq_lib} /c /n 4000 /q /m @{link_path},{cpe_path},{sym_path},{map_path}", "Linking $out"),
            "convert_cpe_to_exe": ("$cpe2exe -CA $in", "$in -> $out")
        }

        on_linux = platform.system() == "Linux"
        for name, (cmd, desc) in rules.items():
            ninja.rule(name, f"wine {cmd}" if on_linux else cmd, desc)

        linker_deps = list()
        bss_tail = None
        objs = []
        headers = [os.path.join(project_src, f) for f in sorted(os.listdir(project_src)) if f.endswith(".h")]
        for c_file in c_files:
            if c_file.startswith("obj "):
                linker_deps.append(os.path.join(CURRENT_DIR, "libs", "psyq4.4", "LIB", c_file[4:]))
                continue
            file_name = c_file.split(".")[0]
            out_path = os.path.join(BUILD_DIR, file_name)

            # headers are not tracked by the preprocessor, so rebuild everything when any of them change
            ninja.build(f"{out_path}.preproc", "pre_process", os.path.join(project_src, c_file), implicit=headers)
            ninja.build(f"{out_path}.o", "compile" + cc43[file_name] if file_name in cc43 else "compile", f"{out_path}.preproc")
            ninja.build(f"{out_path}.obj", "assemble", f"{out_path}.o")
            linker_deps.append(f"{out_path}.obj")

        lib_objs = read_lib_objs()
        # the PSY-Q modules themselves, from the .LIB files; the code that is no 4.4 module is src/lib/*.s
        from objlib.sections import parse_obj_sections
        commons = read_lib_commons()
        bss_pos = game_bss_end()
        paths = extract_lib_objs(psyq_lib, os.path.join(BUILD_DIR, "libobj"),
                                 [(o[1], o[2]) for o in lib_objs if o[0] == "obj"])
        for o in lib_objs:
            if o[0] in ("bsshead", "bsstail"):
                # bsshead: linked in front of the game so that it starts the bss group (the original's
                # commons made psylink 8-align the .bss); bsstail: padding behind everything (the original's
                # .bss group ends on 8 bytes, and the start-up clears the bss up to that end)
                out_path = os.path.join(BUILD_DIR, "lib_" + o[0])
                write_if_changed(out_path + ".s", "\t.section\t.bss\r\n\t.space\t%d\r\n\t.text\r\n" % o[1])
                ninja.build(f"{out_path}.obj", "assemble", out_path + ".s")
                if o[0] == "bsshead":
                    linker_deps.insert(0, f"{out_path}.obj")
                else:
                    bss_tail = f"{out_path}.obj"
            elif o[0] == "src":
                src = os.path.join(CURRENT_DIR, "src", "lib", o[1])
                out_path = os.path.join(BUILD_DIR, "lib_" + o[1][:-2])
                # ASPSX wants CRLF
                write_if_changed(out_path + ".s", open(src).read().replace("\r\n", "\n").replace("\n", "\r\n"))
                ninja.build(f"{out_path}.obj", "assemble", out_path + ".s", implicit=[src])
                linker_deps.append(f"{out_path}.obj")
            else:
                secs = parse_obj_sections(paths[(o[1], o[2])])
                if ".bss" in secs and secs[".bss"].size and bss_pos % 8:
                    # the .bss of the PSY-Q modules is on 8 bytes (psylink does that itself only with commons)
                    name = "libpad_%08X" % bss_pos
                    src = os.path.join(BUILD_DIR, name + ".s")
                    write_if_changed(src, "\t.section\t.bss\r\n\t.space\t%d\r\n\t.text\r\n" % (8 - bss_pos % 8))
                    ninja.build(os.path.join(BUILD_DIR, name + ".obj"), "assemble", src)
                    linker_deps.append(os.path.join(BUILD_DIR, name + ".obj"))
                    bss_pos += 8 - bss_pos % 8
                linker_deps.append(paths[(o[1], o[2])])
                bss_pos += secs[".bss"].size if ".bss" in secs else 0
                own = commons.get((o[1], o[2]))
                if own:
                    # its common symbols, defined right behind it (see read_lib_commons)
                    name = "libcom_%s_%s" % (o[1].split(".")[0], o[2])
                    src = os.path.join(BUILD_DIR, name + ".s")
                    lines = ["\t.section\t.bss"]
                    for n, size, a in own:
                        if not 0 <= a - bss_pos < 8:
                            print("lib_commons: %s at %08X, but the .bss is at %08X there" % (n, a, bss_pos))
                        if a > bss_pos:
                            lines.append("\t.space\t%d" % (a - bss_pos))
                        lines += ["\t.globl\t%s" % n, "%s:" % n, "\t.space\t%d" % size]
                        bss_pos = a + size
                    lines.append("\t.text")
                    write_if_changed(src, "\r\n".join(lines) + "\r\n")
                    ninja.build(os.path.join(BUILD_DIR, name + ".obj"), "assemble", src)
                    linker_deps.append(os.path.join(BUILD_DIR, name + ".obj"))
        # the 3 words of padding behind the library code
        out_path = os.path.join(BUILD_DIR, "lib_pad")
        write_if_changed(out_path + ".s", "\t.text\r\n\t.word\t0,0,0\r\n")
        ninja.build(f"{out_path}.obj", "assemble", out_path + ".s")
        linker_deps.append(f"{out_path}.obj")

        if bss_tail:
            linker_deps.append(bss_tail)
        with open(link_path, "w") as f:
            f.write("\torg\t$80010000\n")
            for g, kw in (("text", ""), ("rdata", ""), ("data", ""), ("bss", "\tbss")):
                f.write("%s\tgroup%s\n" % (g, kw))
            for sec, g in ((".text", "text"), (".rdata", "rdata"), (".data", "data"), (".sdata", "data"),
                           (".sbss", "data"), (".bss", "bss")):
                f.write("\tsection\t%s,%s\n" % (sec, g))
            for o in linker_deps:
                f.write('\tinclude "%s"\n' % o)
            # what the executable uses outside of its image: overlay code/data (at the overlays' fixed load
            # addresses) and buffers behind the image
            for name, a in external_symbols(project_src):
                f.write("%s\tequ\t$%08X\n" % (name, a))
            # names the code has for a place inside a C object (playerYan_8008B594 == saveData_8008B570.inv_24),
            # from where the last link put the object (see aliases_resolved)
            syms = read_map_symbols()
            for name, base, off in read_aliases():
                f.write("%s\tequ\t$%08X\n" % (name, syms.get(base, 0) + off))
            f.write("\tregs\tpc=__SN_ENTRY_POINT\n")

        ninja.build(cpe_path, "link", implicit=linker_deps + [link_path])
        ninja.build(exe_path, "convert_cpe_to_exe", cpe_path)

def build():
    start = time.time()
    retcode = subprocess.call("ninja")
    build_time = time.time() - start
    if retcode != 0:
        print(f"Build failed with return code {retcode}!")
    else:
        print(f"Build finished in {build_time:.2f} seconds!")

    return retcode

def read_hashes():
    path = os.path.join(CURRENT_DIR, "config", "hashes.txt")
    return {k: h for k, h in (l.split() for l in open(path) if l.strip() and not l.startswith("#"))}


def verify_hashes(iso):
    """SHA-1 of the linked exe image and of every overlay (scripts/overlays.py, built from build_psyq/NAME.orig
    or from the disc image with --iso) against config/hashes.txt. Returns True if everything matches."""
    import concurrent.futures
    import hashlib
    expected = read_hashes()
    results = {}
    exe = open(os.path.join(BUILD_DIR, f"{EXE_NAME}.exe"), "rb").read()[0x800:]
    results["exe-image"] = hashlib.sha1(exe).hexdigest()

    def one(name):
        out_bin = os.path.join(BUILD_DIR, name + ".BIN")
        if os.path.exists(out_bin):
            os.remove(out_bin)  # a failed build must not leave the previous image behind
        src = iso if iso else "orig"
        r = subprocess.run([sys.executable, os.path.join(CURRENT_DIR, "scripts", "overlays.py"), name, src,
                            os.path.join(BUILD_DIR, f"{EXE_NAME}.exe")], cwd=CURRENT_DIR, capture_output=True, text=True)
        if not os.path.exists(out_bin):
            tail = (r.stdout + r.stderr).strip().split("\n")[-1:]
            return name, "BUILD FAILED: " + " ".join(tail)
        return name, hashlib.sha1(open(out_bin, "rb").read()).hexdigest()

    names = sorted(os.path.basename(p)[:-4].upper() for p in glob.glob(os.path.join(CURRENT_DIR, "overlays", "*.sym")))
    with concurrent.futures.ThreadPoolExecutor(8) as pool:
        for name, h in pool.map(one, names):
            results["overlay-" + name] = h
    bad = 0
    for k, h in results.items():
        want = expected.get(k)
        if want != h:
            bad += 1
            print(f"HASH MISMATCH {k}: built {h}, expected {want}")
    missing = [k for k in expected if k not in results]
    for k in missing:
        print(f"HASH NOT CHECKED {k}")
    if bad or missing:
        print(f"Hash check FAILED ({bad} mismatching, {len(missing)} not checked of {len(expected)})")
        return False
    print(f"Hash check OK: exe + {len(results) - 1} overlays identical to the originals")
    return True


def is_build_file(file):
    for suffix in [".preproc", ".o", ".obj", ".cpe", ".sym", ".map", ".exe"]:
        if file.endswith(suffix):
            return True
    return False

def clean(log):
    deleted_files_count = 0
    for file in os.listdir(BUILD_DIR):
        if is_build_file(file):
            file_to_remove = os.path.join(BUILD_DIR, file)
            os.remove(file_to_remove)
            deleted_files_count += 1

    if not log:
        return

    if deleted_files_count > 0:
        print(f"Cleaned up {deleted_files_count} files!")
    else:
        print("Nothing to clean")

def find_iso():
    for file in os.listdir(BUILD_DIR):
        if file.endswith(".bin"):
            print(f"Found game iso: {file}")
            return os.path.join(BUILD_DIR, file)
    return ""

def exec_pcsx(iso_path):
    pcsx_path = os.environ.get("PCSX")
    if not pcsx_path:
        print("Could not find PCSX environment variable")
        sys.exit(1)

    game_iso = ""
    if iso_path is not None and os.path.exists(iso_path) and iso_path.endswith(".bin"):
        game_iso = iso_path
    else:
        # look in the build folder
        game_iso = find_iso()

    if game_iso == "":
        print(f"Could not find game iso in {BUILD_DIR}")
        sys.exit(1)

    pcsx_exe = os.path.join(pcsx_path, "pcsx-redux.exe")
    game_exe = os.path.join(BUILD_DIR, "jade_cocoon.exe")
    pcsx_command = f"{pcsx_exe} -iso {game_iso} -exe {game_exe} -run"
    print(pcsx_command)

    # set cwd to pcsx_path to avoid writing all the files in the repository root
    subprocess.call(pcsx_command, cwd=pcsx_path)

def main():
    parser = argparse.ArgumentParser()
    #parser.add_argument("-b", "--build", action="store_true", help="Builds the project with psyq 4.4")
    parser.add_argument("-c", "--clean", action="store_true", help="cleans up all the build objects")
    parser.add_argument("-r", "--rebuild", action="store_true", help="rebuild the project")
    parser.add_argument("-e", "--exec", action="store_true", help="executes the built exe with pcsx-redux")
    parser.add_argument("-i", "--iso", help="the path to the original game iso (for --exec, and to build the overlays "
                        "for the hash check when build_psyq/*.orig do not exist yet)")
    parser.add_argument("--no-verify", action="store_true",
                        help="skip the hash check of the exe and all overlays (quick experiments only)")

    args = parser.parse_args()

    #if len(sys.argv) == 1:
    #    parser.print_help()
    #    sys.exit(0)
    
    os.makedirs(BUILD_DIR, exist_ok=True)
    generate_ninja()

    if args.clean:
        clean(log=True)
        sys.exit(0)
    elif args.rebuild:
        clean(log=False)

    build_retcode = build()
    if build_retcode == 0 and not aliases_resolved():
        generate_ninja()
        build_retcode = build()
    if build_retcode != 0:
        sys.exit(build_retcode)
    if not aliases_resolved():
        sys.exit("aliases (config/aliases.txt) still not at BASE + OFFSET after relinking")

    if not args.no_verify and not verify_hashes(args.iso):
        sys.exit(1)

    if args.exec:
        exec_pcsx(args.iso)

    sys.exit(0)

if __name__ == "__main__":
    main()
