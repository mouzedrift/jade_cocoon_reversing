from ninja import ninja_syntax
import os
import subprocess
import sys

c_files = ["main.c", "funcs.c", "globals.c", "sound.c"]

CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
BUILD_DIR = f"{CURRENT_DIR}\\build_psyq"

def generate_ninja():
    psyq_path = f"{CURRENT_DIR}\\libs\\psyq_sdk\\psyq_4.4"
    with open("build.ninja", "w") as ninja_file:
        ninja = ninja_syntax.Writer(ninja_file)

        ninja.variable("cpppsx", f"{psyq_path}\\bin\\CPPPSX.EXE")
        ninja.variable("cc1psx", f"{psyq_path}\\bin\\CC1PSX.EXE")
        ninja.variable("aspsx", f"{CURRENT_DIR}\\libs\\psyq_sdk\\ASPSX\\2.81\\ASPSX.EXE")
        ninja.variable("psylink", f"{psyq_path}\\bin\\psylink.exe")
        ninja.variable("cpe2exe", f"{psyq_path}\\bin\\cpe2exe.exe")
        includes = f"-I {psyq_path}\\INCLUDE -I {CURRENT_DIR}\\src"
        pysq_lib = f"/l {psyq_path}\\LIB"

        ninja.rule("pre_process", f"$cpppsx -undef -D__GNUC__=2 -v -D__OPTIMIZE__ {includes} -lang-c -Dmips -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D__CHAR_UNSIGNED__ -D_LANGUAGE_C -DLANGUAGE_C $in $out", "Preprocess $in -> $out")
        ninja.rule("compile", "$cc1psx -quiet -G0 -O2 $in -o $out", "Compile $in -> $out")
        ninja.rule("assemble", "$aspsx -G0 -q $in -o $out", "Assemble $in -> $out")
        ninja.rule("link", f"$psylink {pysq_lib} /c /n 4000 /q /gp .sdata /m @linker_command_file.txt,{BUILD_DIR}\\jade_cocoon.cpe,{BUILD_DIR}\\jade_cocoon.sym,{BUILD_DIR}\\jade_cocoon.map", "Linking $out")
        ninja.rule("convert_cpe_to_exe", "$cpe2exe -CA $in", "$in -> $out")

        linker_deps = list()
        for c_file in c_files:
            file_name = c_file.split(".")[0]
            ninja.build(f"{BUILD_DIR}\\{file_name}.preproc", "pre_process", f"{CURRENT_DIR}\\src\\{c_file}")
            ninja.build(f"{BUILD_DIR}\\{file_name}.o", "compile", f"{BUILD_DIR}\\{file_name}.preproc")
            ninja.build(f"{BUILD_DIR}\\{file_name}.obj", "assemble", f"{BUILD_DIR}\\{file_name}.o")
            linker_deps.append(f"{BUILD_DIR}\\{file_name}.obj")

        ninja.build(f"{BUILD_DIR}\\jade_cocoon.cpe", "link", implicit=linker_deps)
        ninja.build(f"{BUILD_DIR}\\jade_cocoon.exe", "convert_cpe_to_exe", f"{BUILD_DIR}\\jade_cocoon.cpe")

def build():
    return subprocess.call(f"ninja")

def main():
    os.makedirs(BUILD_DIR, exist_ok=True)
    generate_ninja()
    retcode = build()
    if retcode != 0:
        print(f"Build failed with return code {retcode}")
    else:
        print("Build finished successfully!")
        
    sys.exit(retcode)

if __name__ == "__main__":
    main()
