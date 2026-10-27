#!/usr/bin/env python3
"""Recover replacement-engine audio assignments from both pinned YYC libraries.

Read-only disassembly and literal extraction. Never loads or executes Android code.
"""
import argparse
import hashlib
import json
import re
import struct
import subprocess
from pathlib import Path
from recover_yyc_fields import recover

repo = Path(__file__).resolve().parents[2]
p = argparse.ArgumentParser(description=__doc__)
p.add_argument('--root', type=Path, default=Path('/workspace/windows-port'))
p.add_argument('--output', type=Path, required=True)
p.add_argument('--header', type=Path)
a = p.parse_args()
stock = json.loads((repo/'native/evidence/merged/stock-vehicles.json').read_text())
sounds = json.loads((repo/'native/evidence/unbound/parts/sounds.json').read_text())
parts = [r for r in json.loads((repo/'native/evidence/merged/performance.json').read_text())['parts'] if r['category'] == 'engine']
banks = {}
for bank, folder in [('original', 'original-recovered'), ('unbound', 'recovered')]:
    binary = a.root/folder/'lib/x86/libyoyo.so'
    data = binary.read_bytes()
    digest = hashlib.sha256(data).hexdigest()
    assert digest == stock['banks'][bank]['binary_sha256']
    elf = struct.unpack_from('<16sHHIIIIIHHHHHH', data)
    sections = [struct.unpack_from('<10I', data, elf[6]+i*elf[11]) for i in range(elf[12])]
    def offset(address):
        return next(s[4]+address-s[3] for s in sections if s[1] != 8 and s[3] <= address < s[3]+s[5])
    fn = stock['banks'][bank]['function']
    text = subprocess.check_output(['objdump', '-d', '-C', '--start-address='+fn['address'], '--stop-address='+hex(int(fn['address'], 16)+fn['size']), str(binary)], text=True)
    pic = re.search(r'call\s+([0-9a-f]+).*\n.*pop\s+%ebx\n.*add\s+\$0x([0-9a-f]+),%ebx', text)
    base = int(pic[1], 16)+int(pic[2], 16)
    fields = {f['name']: f['id'] for f in recover(binary)['fields']}
    instructions = {}
    for line in text.splitlines():
        m = re.match(r'\s*([0-9a-f]+):\s+(?:[0-9a-f]{2}\s+)+\s*([a-z0-9]+)\s*(.*)', line)
        if m:
            instructions[int(m[1], 16)] = (m[2], m[3])
    addresses = list(instructions)
    following = dict(zip(addresses, addresses[1:]))
    # Original YYC compares against initialized {RValue, case ordinal} rows;
    # the case ordinal is not the profile ID (notably 1/2 and 15).
    static_words = {}
    for m in re.finditer(r'movl\s+\$0x([a-f0-9]+),0x([a-f0-9]+)\(%ebx\)', text):
        key = int(m[2], 16)
        assert key not in static_words or static_words[key] == int(m[1], 16)
        static_words[key] = int(m[1], 16)
    dispatch = {}
    for channel, table, count, default, literals in [
        ('on', -0x13e1178 if bank == 'original' else -0x43ea00, 12 if bank == 'original' else 16, 0x11abdb9 if bank == 'original' else 0x61e546, 0x32a948),
        ('off', -0x13e1148 if bank == 'original' else -0x43e9c0, 8 if bank == 'original' else 16, 0x11ac3e2 if bank == 'original' else 0x61ea8d, 0x32aa40),
    ]:
        mapping = {}
        for ordinal in [*range(count), -1]:
            profile = ordinal
            if bank == 'original' and ordinal >= 0:
                ptr = literals+ordinal*20
                assert static_words[ptr+12] == 0 and static_words[ptr+16] == ordinal
                profile = int(struct.unpack('<d', struct.pack('<II', static_words[ptr], static_words[ptr+4]))[0])
            pc = default if ordinal < 0 else base+struct.unpack_from('<i', data, offset(base+table+ordinal*4))[0]
            entry = pc
            for _ in range(200):
                op, rest = instructions[pc]
                m = re.search(r'(-?0x[0-9a-f]+)\(%ebx\),%xmm0', rest)
                if op == 'movsd' and m:
                    value = struct.unpack_from('<d', data, offset(base+int(m[1], 16)))[0]
                    assert value == int(value) and 'engine' in sounds[int(value)]['name']
                    mapping[profile] = {'sample_id': int(value), 'sample_name': sounds[int(value)]['name'], 'case_address': hex(entry), 'literal_address': hex(pc)}
                    break
                pc = int(rest.split()[0], 16) if op == 'jmp' and not rest.startswith('*') else following[pc]
            else:
                raise ValueError('Unresolved dispatch path')
        dispatch[channel] = mapping
    assignments = []
    for engine in stock['banks'][bank]['replacement_engines']:
        # Independently verify the HP guard against the ELF, not just the prior report.
        begin = text.index(engine['guard_address'].removeprefix('0x')+':')
        revpos = text.index(engine['write_addresses']['redline_rpm']+':')
        guard = text[begin:revpos]
        if bank == 'original':
            hi = re.search(r'movl\s+\$0x([a-f0-9]+),0xa24\(%esp\)', guard)
            lo = re.search(r'movl\s+\$0x([a-f0-9]+),0xa20\(%esp\)', guard)
            hp = struct.unpack('<d', struct.pack('<II', int(lo[1], 16), int(hi[1], 16)))[0]
            assert 'YYCompareVal' in guard and re.search(r'jne\s+', guard)
        else:
            literal = re.search(r'addsd\s+(-?0x[a-f0-9]+)\(%ebx\)', guard)
            hp = -struct.unpack_from('<d', data, offset(base+int(literal[1], 16)))[0]
        assert hp == engine['engine_hp']
        row = {'engine_hp_guard': hp, 'guard_address': engine['guard_address']}
        for channel, field in [('on', 'e_s'), ('off', 'e_s2')]:
            access = re.search(r'^\s*([a-f0-9]+):.*movl\s+\$0x'+format(fields[field], 'x')+r',0x4\(%esp\)', text[revpos:], re.M)
            assert access
            tail = text[revpos+access.end():revpos+access.end()+2000]
            hi = re.search(r'movl\s+\$0x([a-f0-9]+),0x4\(%(eax|ebp|esi|edi|ecx|edx)\)', tail)
            lo = re.search(r'movl\s+\$0x([a-f0-9]+),(?:0x0)?\(%'+hi[2]+r'\)', tail[hi.end():hi.end()+180])
            profile = struct.unpack('<d', struct.pack('<II', int(lo[1], 16), int(hi[1], 16)))[0]
            assert profile == int(profile) and -1 <= profile <= 15
            row[channel] = {'profile': int(profile), 'field_write_address': '0x'+access[1], **dispatch[channel].get(int(profile), dispatch[channel][-1])}
        assignments.append(row)
    assert len(assignments) == 15
    banks[bank] = {'binary_sha256': digest, 'dispatch': dispatch, 'assignments': assignments}
rows = []
for part in sorted(parts, key=lambda r: r['subimage']):
    matches = [next(r for r in banks[bank]['assignments'] if r['engine_hp_guard'] == part['stat']) for bank in ['original', 'unbound']]
    assert all(matches[0][channel]['sample_id'] == matches[1][channel]['sample_id'] and matches[0][channel]['profile'] == matches[1][channel]['profile'] for channel in ['on', 'off'])
    rows.append({'id': part['id'], 'name': part['name'], 'subimage': part['subimage'], 'hp': part['stat'], 'on': matches[0]['on'], 'off': matches[0]['off']})
assert len(rows) == 16 and [r['subimage'] for r in rows] == list(range(1, 17))
report = {'method': 'Static engine_hp equality guards -> e_s/e_s2 literal assignments -> profile dispatch -> sample IDs; independently checked in both pinned Android libraries', 'replacement_engine_count': 16, 'same_assignments_in_both_banks': True, 'engines': rows, 'banks': banks, 'limitations': ['Stock-car audio selection is not established by this replacement-engine extraction.', 'Manual PC audio overrides remain available.', 'Sample selection is recovered; complete original pitch, gain and playback timing are not imported.']}
a.output.parent.mkdir(parents=True, exist_ok=True)
a.output.write_text(json.dumps(report, indent=2)+'\n')
if a.header:
    lines = ['// Generated by native/tools/recover_engine_assignments.py; verified in both source banks.', '#pragma once', 'namespace pcr {', 'inline constexpr int ReplacementEngineSamples[17][2] = {', '{21,20}, // Unequipped: native fallback, stock selection not recovered here.']
    lines += ['{'+str(r['on']['sample_id'])+','+str(r['off']['sample_id'])+'}, // '+r['name'] for r in rows]
    a.header.write_text('\n'.join(lines+['};', '}'])+'\n')
for r in rows:
    print(r['name'], r['on']['sample_name'], r['off']['sample_name'])
