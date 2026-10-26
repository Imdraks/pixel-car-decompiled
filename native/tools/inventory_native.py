#!/usr/bin/env python3
"""Read-only ELF32/64 and APK evidence for native Windows feasibility."""
import collections
import argparse
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess
import zipfile

ROOT = Path('/workspace/native-investigation')
INPUTS = {
    'unbound': Path('/workspace/game-input/Unboundtester.apk'),
    'original': Path('/workspace/game-input/original/Pixel+Car+Racer_1.2.5_APKPure.apk'),
}

def elf32_inventory(data):
    if data[:6] != b'\x7fELF\x01\x01':
        raise ValueError('Expected ELF32 little endian')
    h = struct.unpack_from('<16sHHIIIIIHHHHHH', data)
    shoff, shsize, shcount, shstr = h[6], h[11], h[12], h[13]
    sections = [struct.unpack_from('<10I', data, shoff+i*shsize) for i in range(shcount)]
    def payload(s): return data[s[4]:s[4]+s[5]]
    def string(tab, p): return tab[p:tab.index(b'\0',p)].decode('utf-8',errors='replace')
    names = payload(sections[shstr])
    symbols, imports = [], []
    for s in sections:
        if s[1] != 11: continue
        strs = payload(sections[s[6]])
        for pos in range(s[4], s[4]+s[5], s[9]):
            name, value, size, info, other, index = struct.unpack_from('<IIIBBH',data,pos)
            if not name: continue
            row = {'name':string(strs,name),'address':f'0x{value:08x}','size':size,'kind':info&15}
            if index == 0: imports.append(row)
            else: symbols.append(row)
    mangled = [s['name'] for s in symbols]
    demangled = subprocess.run(['c++filt'],input='\n'.join(mangled)+'\n',text=True,capture_output=True,check=True).stdout.splitlines()
    for s,d in zip(symbols,demangled): s['demangled']=d
    functions = [s for s in symbols if s['kind']==2]
    game = [s for s in functions if re.search(r'\bgml_(Script|Object|GlobalScript)_',s['demangled'])]
    relocations = collections.Counter()
    for s in sections:
        if s[1] != 9: continue
        for pos in range(s[4],s[4]+s[5],s[9]):
            _,info=struct.unpack_from('<II',data,pos);relocations[str(info&255)]+=1
    needed=[]
    for s in sections:
        if s[1]!=6:continue
        strs=payload(sections[s[6]])
        for pos in range(s[4],s[4]+s[5],s[9]):
            tag,value=struct.unpack_from('<II',data,pos)
            if tag==1:needed.append(string(strs,value))
    return {'sha256':hashlib.sha256(data).hexdigest(),'size':len(data),'elf_machine':h[2],
            'debug_sections':[string(names,s[0]) for s in sections if string(names,s[0]).startswith('.debug')],
            'needed':needed,'defined_function_count':len(functions),'game_function_count':len(game),
            'game_function_symbol_bytes':sum(s['size'] for s in game),
            'largest_game_functions':sorted(game,key=lambda s:s['size'],reverse=True)[:15],
            'relocation_type_counts':dict(relocations),'import_count':len(imports),
            'imports':imports,'game_functions':game}

def main():
    global ROOT, INPUTS
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--unbound',type=Path,default=INPUTS['unbound'])
    parser.add_argument('--original',type=Path,default=INPUTS['original'])
    parser.add_argument('--output',type=Path,default=ROOT)
    args=parser.parse_args()
    ROOT=args.output;INPUTS={'unbound':args.unbound,'original':args.original}
    for label,apk in INPUTS.items():
        with zipfile.ZipFile(apk) as z:
            names=z.namelist()
            report={'apk_sha256':hashlib.file_digest(apk.open('rb'),'sha256').hexdigest(),
                    'native_libraries':[n for n in names if n.startswith('lib/') and n.endswith('.so')],
                    'source_candidates':[n for n in names if Path(n).suffix.lower() in {'.gml','.yy','.yyp','.gmx','.cpp','.cc','.c','.h'}]}
            b=z.read('assets/game.droid');offset=8; chunks=[]
            while offset<len(b):
                tag=b[offset:offset+4].decode('ascii');size=struct.unpack_from('<I',b,offset+4)[0]
                chunks.append({'tag':tag,'size':size});offset+=8+size
            if offset!=len(b):raise ValueError('Invalid GameMaker chunks')
            report['gamemaker_chunks']=chunks
            report['x86']=elf32_inventory(z.read('lib/x86/libyoyo.so'))
        folder=ROOT/label;folder.mkdir(exist_ok=True,parents=True)
        (folder/'native-inventory.json').write_text(json.dumps(report,indent=2)+'\n')
        x=report['x86']
        print(json.dumps({'label':label,'native_libraries':report['native_libraries'],'source_candidates':report['source_candidates'],
                          'defined_functions':x['defined_function_count'],'game_functions':x['game_function_count'],
                          'game_bytes':x['game_function_symbol_bytes'],'imports':x['import_count'],'needed':x['needed'],
                          'largest_game_functions':[{k:s[k] for k in ['demangled','size']} for s in x['largest_game_functions'][:4]]}))

if __name__=='__main__':main()
