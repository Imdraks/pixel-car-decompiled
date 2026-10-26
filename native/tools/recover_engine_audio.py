#!/usr/bin/env python3
"""Read the two 16-entry original engine-sound dispatch tables, without execution."""
import argparse,hashlib,json,re,struct,subprocess
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--binary',type=Path,required=True);p.add_argument('--sounds',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args()
b=a.binary.read_bytes()
if hashlib.sha256(b).hexdigest()!='fb3726e175e7d1c643e0ddac1ec1a365901c4d52a16ded97e89fd672f6a9e9cc':raise ValueError('Unsupported binary')
h=struct.unpack_from('<16sHHIIIIIHHHHHH',b);sections=[struct.unpack_from('<10I',b,h[6]+i*h[11]) for i in range(h[12])]
def offset(v,size):return next(s[4]+v-s[3] for s in sections if s[1]!=8 and s[3]<=v and v+size<=s[3]+s[5])
text=subprocess.check_output(['objdump','-d', '--start-address=0x61e37c','--stop-address=0x61ee51',str(a.binary)],text=True)
instructions={}
for line in text.splitlines():
 m=re.match(r'\s*([0-9a-f]+):\s+(?:[0-9a-f]{2}\s+)+\s*([a-z0-9]+)\s*(.*)',line)
 if m:instructions[int(m[1],16)]=(m[2],m[3])
addresses=sorted(instructions);nextAddress=dict(zip(addresses,addresses[1:]));base=0x13b5000
sounds=json.loads(a.sounds.read_text());rows=[]
for profile in range(16):
 result={'profile':profile};paths=[]
 for key,table,field in [('on',base-0x43ea00,0x34f0),('off',base-0x43e9c0,0x3510)]:
  case=base+struct.unpack_from('<i',b,offset(table+profile*4,4))[0];pc=case;value=None;seenField=False;path=[]
  for _ in range(150):
   op,rest=instructions[pc];path.append(hex(pc))
   if re.search(r'\$0x'+format(field,'x')+r',%esi',rest):seenField=True
   m=re.search(r'(-?0x[0-9a-f]+)\(%ebx\),%xmm0',rest)
   if op=='movsd' and m:value=struct.unpack_from('<d',b,offset(base+int(m[1],16),8))[0]
   if op=='movsd' and rest=='%xmm0,(%esi)':
    if value is None or not seenField:raise ValueError('Incomplete literal path')
    sound=int(value)
    if sound<0 or sound>=len(sounds) or not ('engine' in sounds[sound]['name']):raise ValueError('Invalid sound index')
    result[key]={'id':sound,'name':sounds[sound]['name'],'file':sounds[sound]['file'],'case_address':hex(case)};paths.append(path);break
   pc=int(rest.split()[0],16) if op=='jmp' and not rest.startswith('*') else nextAddress[pc]
  else:raise ValueError('Unresolved engine sound case')
 result['instruction_paths']=paths;rows.append(result)
report={'binary_sha256':hashlib.sha256(b).hexdigest(),'profiles':rows,
 'source_fields':['e_s','e_s2'],'limitations':['Dispatch from the original sound profile indices to sample IDs is recovered.', 'Assignment of each engine item to a profile is not proven; native automatic assignment is an approximation and can be overridden.']}
a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_text(json.dumps(report,indent=2)+'\n')
for row in rows:print(row['profile'],row['on']['name'],row['off']['name'])
