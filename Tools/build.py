import os
import subprocess
from genLinkerScript import genLDScript
from colorama import Fore, Style
import sys
import shutil
from settings import *

def status(msg: str):
    print(Style.BRIGHT + Fore.CYAN + msg + Fore.RESET + Style.RESET_ALL)

if len(sys.argv) >= 2 and sys.argv[1] == 'clean':
    shutil.rmtree(getBuildPath())
    exit()

if not os.path.exists(getBuildPath()):
    os.mkdir(getBuildPath())

status("Generating Linker Script")
genLDScript()

result = subprocess.run(f'python Tools/gen-build.py', shell=True)
if result.returncode != 0:
    exit()

result = subprocess.run(f'ninja -C build', shell=True)
if result.returncode != 0:
    exit()

def fromelf():
    status("Generating code.bin")
    subprocess.run("\"" + os.environ.get('ARMCC_PATH') + f"/bin/fromelf.exe\" --bincombined {getElfPath()} --output {getBuildPath()}/code.bin", shell=True)

fromelf()