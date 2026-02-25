#!/usr/bin/env python3
import os
from pathlib import Path

# ---------------------------
# User configuration
# ---------------------------
ARMCC_PATH = os.environ.get("ARMCC_PATH")
if not ARMCC_PATH:
    raise RuntimeError("Please set ARMCC_PATH environment variable")

BUILD_DIR = Path("build")
SRC_DIRS = [Path("Source"), Path("External/zlib-1.1.4"), Path("External/libpng"), Path("External/nnsdk")]
INCLUDE_DIRS = [Path("Include"),
                Path("External/libpng"),
                Path("External/nnsdk/include"),
                Path("External/zlib-1.1.4")]

EXE_NAME = "ikachan3.axf"
LINKER_SCRIPT = "Linker.ld"

# Compiler binaries
ARMCC = Path(ARMCC_PATH)/"bin/armcc.exe"
ARMASM = Path(ARMCC_PATH)/"bin/armasm.exe"
ARMAR = Path(ARMCC_PATH)/"bin/armar.exe"
ARMLINK = Path(ARMCC_PATH)/"bin/armlink.exe"

ARMINC = Path(ARMCC_PATH)/"include"

def include_flags(dirs):
    includes = " ".join([f'-I..\\{Path(d)}' for d in dirs])
    includes = includes + f" -I{ARMINC}"
    return includes

# Flags
CFLAGS = "--apcs=//interwork --cpu=MPCore --fpmode=fast --c99 --arm " \
         "--signed_chars --multibyte-chars --locale=japanese -Otime -O3 " \
         "--data-reorder --split_sections --diag_suppress=1294 " + include_flags(INCLUDE_DIRS) + " -DNON_MATCHING="

CXXFLAGS = "--apcs=//interwork --cpu=MPCore --fpmode=fast --cpp --arm " \
           "--force_new_nothrow --signed_chars --multibyte-chars --locale=japanese " \
           "--no_vfe --no_rtti_data --no_rtti --no_exceptions -Otime -O3 " \
           "--data-reorder --split_sections --forceinline " + include_flags(INCLUDE_DIRS) + " -DNON_MATCHING="

LDFLAGS = "--cpu=MPCore --entry=__ctr_start --startup=__ctr_start " \
          "--library_type=standardlib --ref_cpp_init --scanlib --legacyalign " \
          "--tailreorder --no_remove --datacompressor=off --arm_only --inline " \
          "--verbose --mangled --symbols --paged --scatter=" + LINKER_SCRIPT

# ---------------------------
# Scan sources
# ---------------------------
sources_c = []
sources_cpp = []
sources_asm = []

for src_dir in SRC_DIRS:
    for path in src_dir.rglob("*"):
        if path.suffix == ".c":
            sources_c.append(path)
        elif path.suffix == ".cpp":
            sources_cpp.append(path)
        elif path.suffix in [".s", ".S", ".asm"]:
            sources_asm.append(path)

# ---------------------------
# Start writing build.ninja
# ---------------------------
BUILD_DIR.mkdir(exist_ok=True)
with open(BUILD_DIR/"build.ninja", "w") as f:
    f.write("# Auto-generated Ninja build file for ARMCC\n\n")
    
    # Rules
    f.write(f"rule cc\n")
    f.write(f"  command = \"{ARMCC}\" {CFLAGS} -c $in -o $out\n")
    f.write(f"  description = CC $out\n\n")
    
    f.write(f"rule cxx\n")
    f.write(f"  command = \"{ARMCC}\" {CXXFLAGS} -c $in -o $out\n")
    f.write(f"  description = CXX $out\n\n")
    
    f.write(f"rule asm\n")
    f.write(f"  command = \"{ARMASM}\" $in -o $out\n")
    f.write(f"  description = ASM $out\n\n")
    
    f.write(f"rule link\n")
    f.write(f"  command = \"{ARMLINK}\" {LDFLAGS} $in -o $out --list $out.map\n")
    f.write(f"  description = LINK $out\n\n")
    
    # Build object files
    all_objects = []
    for src in sources_c:
        obj = BUILD_DIR / (src.stem + ".o")
        f.write(f"build {obj}: cc ../{src}\n")
        all_objects.append(str(obj))
    for src in sources_cpp:
        obj = BUILD_DIR / (src.stem + ".o")
        f.write(f"build {obj}: cxx ../{src}\n")
        all_objects.append(str(obj))
    for src in sources_asm:
        obj = BUILD_DIR / (src.stem + ".o")
        f.write(f"build {obj}: asm ../{src}\n")
        all_objects.append(str(obj))
    
    # Link final executable
    f.write(f"\nbuild {EXE_NAME}: link {' '.join(all_objects)}\n")
    f.write(f"default {EXE_NAME}\n")

print("Generated build.ninja successfully!")
