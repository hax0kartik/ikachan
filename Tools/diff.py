from io import StringIO
import subprocess
import csv
import os
import sys
import threading
from settings import *

def fail(msg: str):
    print(msg)
    sys.exit(1)

elf_exists = os.path.exists(getElfPath())
if elf_exists:
    readelf_data = str(subprocess.check_output(f"arm-none-eabi-readelf {getElfPath()} -sw -W", shell=True))
    if sys.platform == 'win32':
        readelf_data = readelf_data.replace(r'\r\n', '\n')
    else:
        readelf_data = readelf_data.replace(r'\n', '\n')
# Built once and shared by every lookup (check.py calls these from several threads)
_cache_lock = threading.Lock()
_stub_names = None
_elf_funcs = None
_images = {}


def _load_symbol_tables():
    global _stub_names, _elf_funcs
    with _cache_lock:
        if _elf_funcs is not None:
            return
        # symbols that live in Stubs.c (placeholders, not decompiled code)
        stubs = set()
        with open(f"{getBuildPath()}/ikachan3.axf.map") as f:
            for line in f:
                parts = line.split()
                if len(parts) == 6 and parts[5] == 'Stubs.o(stubs)':
                    stubs.add(parts[0])
        funcs = {}
        for line in StringIO(readelf_data):
            if "FUNC" in line:
                arr = line.split()
                if arr[7] not in funcs:  # first occurrence wins, as before
                    funcs[arr[7]] = (int(arr[1], 16), int(arr[2]))
        _stub_names, _elf_funcs = stubs, funcs


def get_elf_symbol(sym_name: str):
    if not elf_exists:
        fail(f"{getElfPath()} not found")
    _load_symbol_tables()
    if sym_name in _stub_names:
        return None
    return _elf_funcs.get(sym_name)


def _image(path: str):
    with _cache_lock:
        if path not in _images:
            _images[path] = open(path, 'rb').read() if os.path.exists(path) else None
        return _images[path]

def read_sym_file(file: str):
    with open(file, newline='') as f:
        syms = []
        reader = csv.reader(f, delimiter=',',quotechar='"')
        for row in reader:
            if len(row) == 5:
                syms.append((row[0], int(row[1], 16), row[3], row[2], row[4]))
            else:
                syms.append((row[0], int(row[1], 16), row[3], row[2], ''))
        return syms

def get_symbol(symbol: str):
    for subdir, dirs, files in os.walk('Symbols'):
        for file in files:
            syms = read_sym_file(os.path.join(subdir, file))
            for sym in syms:
                if sym[0] == symbol:
                    return sym
    return None

def rank_symbol(sym, decomp_sym):
    sym_size = int(sym[3])
    decomp_size = int(decomp_sym[1])

    if decomp_size == 0:
        decomp_size = sym_size

    # Identical bytes can only diff as OK, so skip launching asm-differ for them
    if decomp_size == sym_size:
        base, mine = _image('orig/code.bin'), _image(f'{getBuildPath()}/code.bin')
        o, d = sym[1] - 0x00100000, decomp_sym[0] - 0x00100000
        if (base is not None and mine is not None
                and 0 <= o and o + sym_size <= len(base) and 0 <= d and d + sym_size <= len(mine)
                and base[o:o + sym_size] == mine[d:d + sym_size]):
            return 'O'

    out = str(subprocess.check_output(f"\"{sys.executable}\" Tools/asm-differ/diff.py --format json {sym[1] - 0x00100000} {decomp_sym[0] - 0x00100000} {str(sym_size)} {str(decomp_size)}", shell=True))

    rank = 'O'
    if "diff_change" in out:
        rank = 'm'
    if "diff_add" in out or "diff_remove" in out:
        if out.count('diff_add') == out.count('diff_remove'):
            rank = 'm'
        else:
            rank = 'M'
    
    return rank


def main() -> None:
    if len(sys.argv) != 2:
        fail("diff.py <symbol>")
    symbolname = sys.argv[1]

    symbol = get_symbol(symbolname)
    decomp_symbol = get_elf_symbol(symbolname)

    if (symbol is None):
        fail("Couldn't find symbol")
    if (decomp_symbol is None):
        fail("Couldn't find decomp symbol")

    sym_size = int(symbol[3])
    decomp_size = int(decomp_symbol[1])

    if decomp_size == 0:
        print("Warning: decomp symbol size is 0. using original size instead")
        decomp_size = sym_size

    subprocess.run(f"\"{sys.executable}\" Tools/asm-differ/diff.py {symbol[1] - 0x00100000} {decomp_symbol[0] - 0x00100000} {str(sym_size)} {str(decomp_size)}", shell=True)

if __name__ == "__main__":
    main()