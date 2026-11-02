from ninja import ninja_syntax
import os
import subprocess
import sys
import argparse
import time
import re
import platform

def read_tus():
    """translation units of the game code in link order (config/tus.txt), one src/<name>.c each"""
    tus = []
    for line in open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "config", "tus.txt")):
        line = line.split("#")[0].strip()
        if line:
            tus.append(line.split()[0])
    return tus


c_files = [tu + ".c" for tu in read_tus()]

# the PSY-Q library part of the executable, as raw blobs (see scripts/split.py)
lib_files = ["text", "lib_pad", "lib_rdata", "lib_data", "lib_sbss", "lib_bss"]

CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
BUILD_DIR = os.path.join(CURRENT_DIR, "build_psyq")

EXE_NAME = "jade_cocoon"

def read_cc43():
    """TUs built with the psyq 4.3 compiler (GCC 2.7.2) instead of 4.4 (config/cc43.txt)"""
    path = os.path.join(CURRENT_DIR, "config", "cc43.txt")
    if not os.path.exists(path):
        return set()
    return {l.split("#")[0].strip() for l in open(path) if l.split("#")[0].strip()}


cc43 = read_cc43()


def generate_ninja():
    psyq_path = os.path.join(CURRENT_DIR, "libs", "psyq4.4")
    with open("build.ninja", "w") as ninja_file:
        ninja = ninja_syntax.Writer(ninja_file)

        bin_dir = os.path.join(psyq_path, "bin")

        ninja.variable("cpppsx", os.path.join(bin_dir, "CPPPSX.EXE"))
        ninja.variable("cc1psx", os.path.join(bin_dir, "CC1PSX.EXE"))
        ninja.variable("cc1psx43", os.environ.get("CC1PSX43", os.path.join(CURRENT_DIR, "..", "psyq_sdk", "psyq_4.3", "bin", "cc1psx.exe")))
        ninja.variable("aspsx", os.path.join(bin_dir, "ASPSX.EXE"))
        ninja.variable("psylink", os.path.join(bin_dir, "psylink.exe"))
        ninja.variable("cpe2exe", os.path.join(bin_dir, "cpe2exe.exe"))

        psyq_include = os.path.join(psyq_path, "INCLUDE")
        project_src = os.path.join(CURRENT_DIR, "src")
        includes = f"-I {psyq_include} -I {project_src}"

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
            "compile43": ("$cc1psx43 -quiet -G0 -O2 $in -o $out", "Compile (psyq 4.3) $in -> $out"),
            "assemble": ("$aspsx -G0 -q -0 $in -o $out", "Assemble $in -> $out"),
            "link": (f"$psylink {pysq_lib} /c /n 4000 /q /m @{link_path},{cpe_path},{sym_path},{map_path}", "Linking $out"),
            "convert_cpe_to_exe": ("$cpe2exe -CA $in", "$in -> $out")
        }

        on_linux = platform.system() == "Linux"
        for name, (cmd, desc) in rules.items():
            ninja.rule(name, f"wine {cmd}" if on_linux else cmd, desc)

        linker_deps = list()
        objs = []
        headers = [os.path.join(project_src, f) for f in sorted(os.listdir(project_src)) if f.endswith(".h")]
        for c_file in c_files:
            file_name = c_file.split(".")[0]
            out_path = os.path.join(BUILD_DIR, file_name)

            # headers are not tracked by the preprocessor, so rebuild everything when any of them change
            # INCLUDE_ASM / INCLUDE_DATA pull in generated assembly, rebuild when it changes
            text = open(os.path.join(project_src, c_file)).read()
            inc = [os.path.join(CURRENT_DIR, "asm", "f" if k == "ASM" else "d", n + ".s")
                   for k, n in re.findall(r"INCLUDE_(ASM|DATA)\((\w+)\)", text)]
            ninja.build(f"{out_path}.preproc", "pre_process", os.path.join(project_src, c_file), implicit=headers + inc)
            ninja.build(f"{out_path}.o", "compile43" if file_name in cc43 else "compile", f"{out_path}.preproc")
            ninja.build(f"{out_path}.obj", "assemble", f"{out_path}.o")
            linker_deps.append(f"{out_path}.obj")

        for lib in lib_files:
            out_path = os.path.join(BUILD_DIR, "lib_" + lib if not lib.startswith("lib_") else lib)
            ninja.build(f"{out_path}.obj", "assemble", os.path.join(CURRENT_DIR, "asm", "lib", lib + ".s"))
            linker_deps.append(f"{out_path}.obj")

        with open(link_path, "w") as f:
            f.write("\torg\t$80010000\n")
            for g, kw in (("text", ""), ("rdata", ""), ("data", ""), ("bss", "\tbss")):
                f.write("%s\tgroup%s\n" % (g, kw))
            for sec, g in ((".text", "text"), (".rdata", "rdata"), (".data", "data"), (".sdata", "data"),
                           (".sbss", "bss"), (".bss", "bss")):
                f.write("\tsection\t%s,%s\n" % (sec, g))
            for o in linker_deps:
                f.write('\tinclude "%s"\n' % o)
            # symbols outside of the image (overlays, buffers behind the executable)
            for line in open(os.path.join(CURRENT_DIR, "symbol_addrs.txt")):
                m = re.match(r"(\w+)=0x([0-9a-fA-F]+);", line)
                if m and int(m.group(2), 16) >= 0x800A05A0:
                    f.write("%s\tequ\t$%s\n" % (m.group(1), m.group(2)))
            f.write("\tregs\tpc=start\n")

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
    parser.add_argument("-i", "--iso", help="the path to the original game iso (for use with --exec)")

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
    if build_retcode != 0:
        sys.exit(build_retcode)
        
    if args.exec:
        exec_pcsx(args.iso)

    sys.exit(0)

if __name__ == "__main__":
    main()
