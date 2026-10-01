from diff import *
from colorama import Fore
import multiprocessing
import threading
import time
import shutil
from concurrent.futures import ThreadPoolExecutor

def getRankName(rank: str):
    match rank:
        case 'O':
            return Fore.GREEN + "OK" + Fore.RESET
        case 'm':
            return Fore.YELLOW + "Minor problems" + Fore.RESET
        case 'M':
            return Fore.RED + "Major problems" + Fore.RESET
        case 'U':
            return "Undecompiled"
    return '?'

def clear_line():
    print(' ' * shutil.get_terminal_size((80, 20)).columns, end='\r')

print_lock = threading.Lock()


def check_symbol(sym):
    decomp_symbol = get_elf_symbol(sym[0])
    if decomp_symbol is None:
        rank = 'U'
    else:
        with print_lock:
            clear_line()
            print("Checking " + sym[0], end='\r')
        rank = rank_symbol(sym, decomp_symbol)
    if sym[2] != rank:
        with print_lock:
            clear_line()
            print(sym[0] + ' ' + getRankName(sym[2]) + ' -> ' + getRankName(rank))
    return (sym[0], sym[1], rank, sym[3], sym[4])


def write_sym_file(filepath: str, newsyms: list):
    with open(filepath, 'w') as f:
        for sym in newsyms:
            f.write(sym[0] + ',' + "{:08x}".format(sym[1]) + ',' + sym[3] + ',' + sym[2])
            if sym[4] != '':
                f.write(',' + sym[4] + '\n')
            else:
                f.write('\n')

def main():
    start = time.time()

    checkdir = 'Symbols'
    if len(sys.argv) == 2:
        checkdir = 'Symbols/' + sys.argv[1]
    print('Checking ' + checkdir + '/')

    sym_files = []
    for subdir, dirs, files in os.walk(checkdir):
        for file in files:
            if "Unnamed.sym" in file:
                continue
            sym_files.append(os.path.join(subdir, file))

    # Rank every symbol of every file on one shared pool, so slow asm-differ runs
    # are spread over all cores instead of piling up in whichever file has them
    with ThreadPoolExecutor(max_workers=multiprocessing.cpu_count()) as pool:
        pending = [(path, [pool.submit(check_symbol, sym) for sym in read_sym_file(path)])
                   for path in sym_files]
        for path, futures in pending:
            write_sym_file(path, [fut.result() for fut in futures])

    clear_line()
    print(f"{int(time.time() - start)}s elapsed")


if __name__ == "__main__":
    main()