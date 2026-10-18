import os
import subprocess
from genLinkerScript import genLDScript
from colorama import Fore, Style
import sys
import shutil
from settings import *

def find_cmake():
    # The MSYS2 cmake that ships with devkitPro (C:\devkitPro\msys2\usr\bin) mangles Windows
    # paths such as ARMCC_PATH ("The CMAKE_C_COMPILER: C is not a full path"), so skip it.
    # Set CMAKE=<path to cmake.exe> to force a specific one.
    if os.environ.get('CMAKE'):
        return os.environ['CMAKE']
    for d in os.environ.get('PATH', '').split(os.pathsep):
        exe = os.path.join(d, 'cmake.exe' if os.name == 'nt' else 'cmake')
        if os.path.isfile(exe) and 'msys' not in exe.lower():
            return exe
    return 'cmake'

CMAKE = find_cmake()

def status(msg: str):
    print(Style.BRIGHT + Fore.CYAN + msg + Fore.RESET + Style.RESET_ALL)

if len(sys.argv) >= 2 and sys.argv[1] == 'clean':
    shutil.rmtree(getBuildPath())
    exit()

if not os.path.exists(getBuildPath()):
    os.mkdir(getBuildPath())

status("Generating Linker Script")
genLDScript()

result = subprocess.run(f'"{CMAKE}" -S . -B {getBuildPath()} -G Ninja', shell=True)
if result.returncode != 0:
    exit()

result = subprocess.run(f'"{CMAKE}" --build {getBuildPath()}', shell=True)
if result.returncode != 0:
    exit()

def fromelf():
    status("Generating code.bin")
    subprocess.run("\"" + os.environ.get('ARMCC_PATH') + f"/bin/fromelf.exe\" --bincombined {getElfPath()} --output {getBuildPath()}/code.bin", shell=True)

    # The SDK's crt0 emits .module_id at 0x04000000 (MODULE_INFO in Linker.ld). --bincombined pads
    # up to it, which makes code.bin ~64MB; the game's code.bin ends with the last real segment.
    import struct
    BASE, MODULE_INFO = 0x00100000, 0x04000000
    with open(getElfPath(), 'rb') as f:
        elf = f.read()
    phoff, = struct.unpack_from('<I', elf, 0x1c)
    phentsize, phnum = struct.unpack_from('<HH', elf, 0x2a)
    end = BASE
    for i in range(phnum):
        p_type, _, p_vaddr, _, p_filesz = struct.unpack_from('<5I', elf, phoff + i * phentsize)
        if p_type == 1 and p_vaddr < MODULE_INFO:
            end = max(end, p_vaddr + p_filesz)
    with open(f"{getBuildPath()}/code.bin", 'r+b') as f:
        f.truncate(end - BASE)

fromelf()