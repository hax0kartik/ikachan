#!/usr/bin/env python3
"""Add byte patterns for version-marker library routines to Tools/patterns.json.

Usage: python Tools/build_patterns.py <label> <toolchain.zip | lib directory>

Reads armlib/cpplib archives (in a zip or a folder containing armlib/ and cpplib/)
without extracting them, and records the code of each marker routine from every
library variant. Relocated bytes are stored as wildcards. Identical patterns are
merged, so each pattern lists every (build, library) that ships it.
"""
import json
import os
import re
import struct
import sys
import zipfile

HERE = os.path.dirname(os.path.abspath(__file__))
DB = os.path.join(HERE, 'patterns.json')

# marker routines: archive member (or None = any member) and section name
MARKERS = [
    ('memcmp', 'memcmp.o', None),
    ('strcmp', 'strcmpfast.o', None),
    ('rand', 'rand.o', None),
    ('std::string::_C_unlink', None, 't._ZNSs9_C_unlinkEv'),
]
R_ARM_NONE, R_ARM_V4BX = 0, 40


def ar_members(data):
    """Yield (name, body) for each member of a SysV/GNU ar archive."""
    if data[:8] != b'!<arch>\n':
        return
    p, longnames = 8, b''
    while p + 60 <= len(data):
        h = data[p:p + 60]
        name = h[:16].decode('latin1').rstrip()
        try:
            size = int(h[48:58].decode().strip())
        except ValueError:
            return
        body = data[p + 60:p + 60 + size]
        if name == '//':
            longnames = body
        elif name.startswith('/') and name[1:].strip().isdigit():
            o = int(name[1:])
            name = longnames[o:longnames.index(b'/', o)].decode('latin1')
        yield name.rstrip('/'), body
        p += 60 + size + (size & 1)


def code_sections(elf):
    """Yield (section name, bytes, wildcard byte offsets, is_thumb) for executable sections."""
    if elf[:4] != b'\x7fELF':
        return
    shoff, = struct.unpack_from('<I', elf, 0x20)
    es, n, shstrndx = struct.unpack_from('<HHH', elf, 0x2e)
    secs = [struct.unpack_from('<IIIIIIIIII', elf, shoff + i * es) for i in range(n)]
    strtab = secs[shstrndx]

    def sname(s):
        o = strtab[4] + s[0]
        return elf[o:elf.index(b'\0', o)].decode('latin1')

    wild, thumb_secs = {}, set()
    for i, s in enumerate(secs):
        if s[1] in (9, 4):  # SHT_REL / SHT_RELA: sh_info is the section they patch
            ent = 8 if s[1] == 9 else 12
            for off in range(s[4], s[4] + s[5], ent):
                r_off, r_info = struct.unpack_from('<II', elf, off)
                if r_info & 0xff in (R_ARM_NONE, R_ARM_V4BX):
                    continue  # no bytes change (V4BX only marks a bx)
                wild.setdefault(s[7], set()).update(range(r_off, r_off + 4))
        if s[1] == 2:  # symbol table: $t mapping symbols mark Thumb code
            st = secs[s[6]]
            for off in range(s[4], s[4] + s[5], 16):
                st_name, _, _, _, _, shndx = struct.unpack_from('<IIIBBH', elf, off)
                o = st[4] + st_name
                if elf[o:o + 2] == b'$t':
                    thumb_secs.add(shndx)
    for i, s in enumerate(secs):
        if s[1] == 1 and s[2] & 4 and s[5]:
            yield sname(s), elf[s[4]:s[4] + s[5]], wild.get(i, set()), i in thumb_secs


def archives(src):
    if src.lower().endswith('.zip'):
        z = zipfile.ZipFile(src)
        for n in sorted(z.namelist()):
            if re.search(r'(armlib|cpplib)/[^/]+\.l$', n, re.I):
                yield os.path.basename(n), lambda n=n: z.read(n)
    else:
        for sub in ('armlib', 'cpplib'):
            d = os.path.join(src, sub)
            if os.path.isdir(d):
                for f in sorted(os.listdir(d)):
                    if f.endswith('.l'):
                        yield f, lambda p=os.path.join(d, f): open(p, 'rb').read()


def to_pattern(raw, wild):
    return ''.join('??' if i in wild else f'{b:02x}' for i, b in enumerate(raw))


def main():
    label, src = sys.argv[1], sys.argv[2]
    db = json.load(open(DB)) if os.path.exists(DB) else {'builds': [], 'patterns': []}
    index = {(p['func'], p['thumb'], p['bytes']): p for p in db['patterns']}
    # re-running a label replaces its previous entries
    for p in db['patterns']:
        p['found_in'] = [w for w in p['found_in'] if w.split(':')[0] != label]
    added = 0
    for lib, read in archives(src):
        for mname, body in ar_members(read()):
            for func, member, section in MARKERS:
                if member and mname != member:
                    continue
                try:
                    secs = list(code_sections(body))
                except (struct.error, ValueError):
                    continue
                for sname, raw, wild, thumb in secs:
                    if section and sname != section:
                        continue
                    if len(raw) < 16:
                        continue
                    key = (func, thumb, to_pattern(raw, wild))
                    p = index.get(key)
                    if p is None:
                        p = index[key] = {'func': func, 'thumb': thumb, 'bytes': key[2], 'found_in': []}
                        db['patterns'].append(p)
                        added += 1
                    where = f'{label}:{lib}'
                    if where not in p['found_in']:
                        p['found_in'].append(where)
    db['patterns'] = [p for p in db['patterns'] if p['found_in']]
    if label not in db['builds']:
        db['builds'].append(label)
    json.dump(db, open(DB, 'w'), indent=1)
    mine = [p for p in db['patterns'] if any(w.startswith(label + ':') for w in p['found_in'])]
    by_func = {}
    for p in mine:
        by_func[p['func']] = by_func.get(p['func'], 0) + 1
    print(f'{label}: {len(mine)} patterns ({added} new) ' + ', '.join(f'{f}={n}' for f, n in by_func.items()))


if __name__ == '__main__':
    main()
