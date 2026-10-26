#!/usr/bin/env python3
"""Recover every shop rim's count/lip/spoke recipe from literal YYC assignments.
Static ELF reads only. Each constant comparison and field write is retained.
"""
import argparse,hashlib,json,re,struct,subprocess
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--binary',type=Path,required=True);p.add_argument('--items',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args();b=a.binary.read_bytes()
assert hashlib.sha256(b).hexdigest()=='fb3726e175e7d1c643e0ddac1ec1a365901c4d52a16ded97e89fd672f6a9e9cc'
h=struct.unpack_from('<16sHHIIIIIHHHHHH',b);ss=[struct.unpack_from('<10I',b,h[6]+i*h[11]) for i in range(h[12])]
def off(v):return next(s[4]+v-s[3] for s in ss if s[1]!=8 and s[3]<=v<s[3]+s[5])
text=subprocess.check_output(['objdump','-d','-C','--start-address=0x189150','--stop-address=0x1d9c2c',str(a.binary)],text=True)
ms=list(re.finditer(r'^\s*([a-f0-9]+):.*addsd\s+(-?0x[0-9a-f]+)\(%ebx\),%xmm0',text,re.M));rows={}
fields={1644:'count',1468:'lip',1486:'spoke',1482:'shadow',1484:'shine'}
for i,m in enumerate(ms):
 case=-struct.unpack_from('<d',b,off(0x13b5000+int(m[2],16)))[0]
 if not case.is_integer():continue
 case=int(case);block=text[m.start():ms[i+1].start() if i+1<len(ms) else len(text)];values={};writes={}
 for x in re.finditer(r'^\s*([a-f0-9]+):.*add\s+\$0x([0-9a-f]+),%edi',block,re.M):
  field=int(x[2],16)//16
  if field not in fields:continue
  tail=block[x.end():];high=re.search(r'movl\s+\$0x([0-9a-f]+),0x4\(%edi\)',tail);low=re.search(r'movl\s+\$0x([0-9a-f]+),\(%edi\)',tail)
  if high and low:
   n=struct.unpack('<d',struct.pack('<II',int(low[1],16),int(high[1],16)))[0]
   if not n.is_integer():raise ValueError('Noninteger rim recipe')
   values[fields[field]]=int(n);writes[fields[field]]=x[1]
 if set(values)==set(fields.values()):rows.setdefault(case,{'source_id':case,'comparison_address':m[1],'fields':values,'write_addresses':writes})
items=json.loads(a.items.read_text());rims=[]
for row in items:
 v=row['args']
 if v[1]!='rims':continue
 recipe=rows[int(v[7])];n=recipe['fields'];assert 1<=n['count']<=24 and 0<=n['lip']<325 and 0<=n['spoke']<403 and 0<=n['shadow']<4 and 0<=n['shine']<54
 rims.append({**recipe,'name':v[2],'shop_call_address':row['address']})
assert len(rims)==521 and len({r['source_id'] for r in rims})==521
report={'binary_sha256':hashlib.sha256(b).hexdigest(),'method':'Static scr_rim_setup literal comparisons and five field assignments; radial count confirmed by draw_adv_rim 360/count loop','rims':sorted(rims,key=lambda r:r['source_id'])}
a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_text(json.dumps(report,indent=2)+'\n');print('Recovered',len(rims),'complete rim recipes')
