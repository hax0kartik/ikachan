from io import StringIO
import subprocess
import csv
import os
import re
import sys
from settings import *

branch_regex = re.compile(r'\b(b(?:l|x)?(?:eq|ne|ge|lt|gt|le|cs|cc|mi|pl|vs|vc|hi|ls)?)\s+0x([0-9a-fA-F]+)')
addr_regex = re.compile(r'^\s*([0-9a-fA-F]+):\s+(.*)')

def process(lines):
    targets = set()
    parsed = []
    # First pass: collect branch targets
    for line in lines:
        m = branch_regex.search(line)
        if m:
            targets.add(m.group(2).lower())

    # Second pass: rewrite lines
    for line in lines:
        m = addr_regex.match(line)
        if not m:
            continue

        addr = m.group(1).lower()
        instr = m.group(2)

        # Insert label if this address is a branch target
        if addr in targets:
            print(f"loc_{addr}:")

        # Replace branch address with label
        def repl(match):
            mnemonic = match.group(1)
            target = match.group(2).lower()
            return f"{mnemonic} loc_{target}"

        instr = branch_regex.sub(repl, instr)

        print(f"    {instr}")

def fail(msg: str):
    print(msg)
    sys.exit(1)

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


def main() -> None:
    if len(sys.argv) != 2:
        fail("dump.py <symbol>")
    symbolname = sys.argv[1]

    symbol = get_symbol(symbolname)

    if (symbol is None):
        fail("Couldn't find symbol")

    sym_size = int(symbol[3])

    start_addr = symbol[1] 
    end_addr = symbol[1] + sym_size

    cmd = f"arm-none-eabi-objdump -D -EL -b binary -m arm --adjust-vma=0x100000 --start-address={start_addr} --stop-address={end_addr} --no-show-raw-insn code.bin"

    ret = subprocess.run(cmd, shell=True, capture_output=True)
    process(ret.stdout.decode("utf-8").splitlines())

if __name__ == "__main__":
    main()