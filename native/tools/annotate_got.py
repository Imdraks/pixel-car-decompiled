#!/usr/bin/env python3
"""Annotate objdump text using observed ELF32 GOT relocations, never guesses."""
import json
import argparse
from pathlib import Path
import re
import struct
import subprocess

parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--root',type=Path,default=Path('/workspace/native-investigation/unbound'))
parser.add_argument('--binary',type=Path,default=Path('/workspace/windows-port/recovered/lib/x86/libyoyo.so'))
args=parser.parse_args();root=args.root;binary=args.binary
b=binary.read_bytes();h=struct.unpack_from('<16sHHIIIIIHHHHHH',b)
sections=[struct.unpack_from('<10I',b,h[6]+i*h[11]) for i in range(h[12])]
def data(s):return b[s[4]:s[4]+s[5]]
def cstr(buf,p):return buf[p:buf.index(b'\0',p)].decode('utf8',errors='replace')
symbols=[]
for s in sections:
    if s[1]!=11:continue
    strs=data(sections[s[6]])
    for p in range(s[4],s[4]+s[5],s[9]):
        name,value,size,info,other,index=struct.unpack_from('<IIIBBH',b,p)
        symbols.append({'name':cstr(strs,name),'value':value,'size':size})
got={}
for s in sections:
    if s[1]!=9:continue
    for p in range(s[4],s[4]+s[5],s[9]):
        addr,info=struct.unpack_from('<II',b,p)
        if info&255==6:got[addr]=symbols[info>>8]
inventory=json.loads((root/'native-inventory.json').read_text())['x86']
selected=['gml_Script_ease_linear(', 'gml_Script_scr_car_var(',
          'gml_Object_ob_car_Step_1(', 'gml_Object_ob_car_Step_2(']
for prefix in selected:
    fn=next(s for s in inventory['game_functions'] if s['demangled'].startswith(prefix))
    start=int(fn['address'],16);end=start+fn['size']
    text=subprocess.check_output(['objdump','-d','-C',f'--start-address={start}',f'--stop-address={end}',str(binary)],text=True)
    # Observe this function's call/pop PIC base rather than assuming a global base.
    pic=re.search(r'([0-9a-f]+):\s+(?:[0-9a-f]{2} )+\s+pop\s+%ebx\n\s*[0-9a-f]+:\s+(?:[0-9a-f]{2} )+\s+add\s+\$0x([0-9a-f]+),%ebx',text)
    if pic is None:raise ValueError('Unsupported PIC prologue: '+fn['demangled'])
    base=int(pic[1],16)+int(pic[2],16)
    lines=[]
    for line in text.splitlines():
        match=re.search(r'(-?0x[0-9a-f]+)\(%ebx\)',line)
        if match:
            addr=base+int(match[1],16)
            if addr in got:
                sym=got[addr]
                line+='  # ELF GOT -> '+sym['name']+f" @ 0x{sym['value']:08x}"
        lines.append(line)
    name=prefix.split('(')[0]
    (root/(name+'.annotated-asm.txt')).write_text('\n'.join(lines)+'\n')
    print(name,'PIC base',hex(base),'annotated GOT references',sum('# ELF GOT' in l for l in lines))
