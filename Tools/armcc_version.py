#!/usr/bin/env python3
"""Estimate which armcc (RVCT 4.x) toolchain build a code.bin was linked with.

Usage: python Tools/armcc_version.py [orig/code.bin] [--base 0x100000] [--patterns Tools/patterns.json]

Searches the binary for library routines whose code differs between toolchain
builds, using the byte patterns in patterns.json (made by Tools/build_patterns.py),
and intersects the builds that ship each routine that is found. Build labels follow
https://github.com/RE-Pepper/data/releases ("b894-local" is a separate local install).
"""
import argparse
import json
import os
import re

HERE = os.path.dirname(os.path.abspath(__file__))


def compile_pattern(p):
    """Regex for a stored pattern: '??' bytes are wildcards; in ARM code a
    bx<c> lr word also matches mov<c> pc, lr (armlink rewrites one to the other)."""
    hexs = p['bytes']
    nbytes = len(hexs) // 2
    out = []
    i = 0
    while i < nbytes:
        word = hexs[i * 2:i * 2 + 8]
        if not p['thumb'] and i % 4 == 0 and len(word) == 8 and '?' not in word:
            w = int.from_bytes(bytes.fromhex(word), 'little')
            if w & 0x0fffffff in (0x012fff1e, 0x01a0f00e):
                cond = w & 0xf0000000
                bx = (cond | 0x012fff1e).to_bytes(4, 'little')
                mov = (cond | 0x01a0f00e).to_bytes(4, 'little')
                out.append(b'(?:' + re.escape(bx) + b'|' + re.escape(mov) + b')')
                i += 4
                continue
        h = hexs[i * 2:i * 2 + 2]
        out.append(b'.' if h == '??' else re.escape(bytes.fromhex(h)))
        i += 1
    return re.compile(b''.join(out), re.S)


def sort_key(b):
    return (0, int(b)) if b.isdigit() else (1, 0)


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument('code', nargs='?', default='orig/code.bin')
    ap.add_argument('--base', default='0x100000', help='load address of the binary (default 0x100000)')
    ap.add_argument('--patterns', default=os.path.join(HERE, 'patterns.json'))
    args = ap.parse_args()
    base = int(args.base, 0)
    db = json.load(open(args.patterns))
    data = open(args.code, 'rb').read()
    builds = set(db['builds'])

    # func -> list of (address, set of builds, set of libraries)
    found = {}
    for p in db['patterns']:
        align = 2 if p['thumb'] else 4
        for m in compile_pattern(p).finditer(data):
            if m.start() % align:
                continue
            where = p['found_in']
            found.setdefault(p['func'], []).append(
                (m.start(), {w.split(':')[0] for w in where}, sorted({w.split(':')[1] for w in where})))

    print(f'Scanning {args.code} ({len(data):,} bytes) with {len(db["patterns"])} patterns '
          f'from {len(builds)} builds\n')
    funcs = sorted({p['func'] for p in db['patterns']})
    candidates = set(builds)
    for func in funcs:
        hits = found.get(func)
        if not hits:
            print(f'  {func:24} not found')
            continue
        ok = set()
        for addr, bset, libs in sorted(hits):
            ok |= bset
            print(f'  {func:24} at {base + addr:#010x}  [{", ".join(libs[:4])}{" ..." if len(libs) > 4 else ""}]'
                  f'  -> {", ".join(sorted(bset, key=sort_key))}')
        candidates &= ok

    print()
    if not found:
        print('No marker routine found, so no conclusion.')
        return
    if not candidates:
        print('No single build ships every marker found (mixed or unknown toolchain).')
        return
    numbered = sorted(int(b) for b in candidates if b.isdigit())
    print(f'Candidate builds: {", ".join(sorted(candidates, key=sort_key))}')
    if numbered:
        print(f'Rough range:      {numbered[0]} - {numbered[-1]}')


if __name__ == '__main__':
    main()
