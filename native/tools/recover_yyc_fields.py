#!/usr/bin/env python3
"""Export named YYC fields from ELF32 metadata without executing the binary.

The two words in g_VAR_* are the name pointer and field ID. Pointer/string
agreement and non-sentinel ID uniqueness are checked; no native vehicle behaviour is inferred.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct


def recover(binary):
    data=binary.read_bytes()
    if data[:6]!=b'\x7fELF\x01\x01':raise ValueError('Expected little-endian ELF32')
    h=struct.unpack_from('<16sHHIIIIIHHHHHH',data)
    sections=[struct.unpack_from('<10I',data,h[6]+i*h[11]) for i in range(h[12])]
    def at(address,size):
        for s in sections:
            if s[1]!=8 and s[3]<=address and address+size<=s[3]+s[5]:
                return s[4]+address-s[3]
        raise ValueError(f'Unmapped address {address:x}')
    def string(buffer,offset):return buffer[offset:buffer.index(b'\0',offset)].decode('utf8')
    fields=[]
    for s in sections:
        if s[1]!=11:continue
        table=sections[s[6]];strings=data[table[4]:table[4]+table[5]]
        for pos in range(s[4],s[4]+s[5],s[9]):
            name,address,size,info,other,index=struct.unpack_from('<IIIBBH',data,pos)
            symbol=string(strings,name)
            if not symbol.startswith('g_VAR_'):continue
            if size!=8 or index==0:raise ValueError('Unexpected field metadata layout')
            pointer,field_id=struct.unpack_from('<II',data,at(address,8))
            literal=string(data,at(pointer,1))
            if literal!=symbol[6:]:raise ValueError('Field name/pointer mismatch: '+symbol)
            fields.append({'name':literal,'id':field_id if field_id!=0xffffffff else None,'instance_offset':field_id*16 if field_id!=0xffffffff else None,
                           'symbol_address':hex(address),'string_address':hex(pointer)})
    indexed=[f for f in fields if f['id'] is not None]
    if not fields or len({f['id'] for f in indexed})!=len(indexed):raise ValueError('Missing/duplicate non-sentinel field IDs')
    return {'binary_sha256':hashlib.sha256(data).hexdigest(),'field_count':len(fields),
            'layout':'ELF32 g_VAR_name = { char* name; uint32 field_id; }; YYRValue stride 16 inferred from existing disassembly',
            'fields':sorted(fields,key=lambda f:(f['id'] is None,f['id'] or 0,f['name'])),
            'limitations':['Field names and IDs only; values and vehicle equations are not recovered by this export.']}

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--binary',type=Path,required=True)
    parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args();report=recover(args.binary)
    args.output.parent.mkdir(exist_ok=True,parents=True)
    args.output.write_text(json.dumps(report,indent=2)+'\n')
    print(f"Verified {report['field_count']} YYC field names and IDs; binary SHA256 {report['binary_sha256']}")
