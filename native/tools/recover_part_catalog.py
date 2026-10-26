#!/usr/bin/env python3
"""Recover the Unbound item literals by static ELF/SSE pointer propagation.
No game code, Android runtime or CPU emulation is executed. Unsupported data
remains unresolved and must pass the strict catalog validation below.
"""
import argparse,hashlib,math
from pathlib import Path
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--binary',type=Path,required=True)
parser.add_argument('--output',type=Path,required=True)
parser.add_argument('--raw-output',type=Path)
parser.add_argument('--source',choices=['unbound','original'],default='unbound')
options=parser.parse_args()
import struct,json,subprocess,re
from pathlib import Path
b=options.binary.read_bytes()
expected={'unbound':'fb3726e175e7d1c643e0ddac1ec1a365901c4d52a16ded97e89fd672f6a9e9cc','original':'af1f9adc9a3a0a4ec1547d051fe41a89974045cb3d7666fbbb94715ce2872a18'}[options.source]
if hashlib.sha256(b).hexdigest()!=expected:raise ValueError('Unreviewed source binary')
h=struct.unpack_from('<16sHHIIIIIHHHHHH',b);ss=[struct.unpack_from('<10I',b,h[6]+i*h[11]) for i in range(h[12])]
def data(s):return b[s[4]:s[4]+s[5]]
def cs(buf,p):return buf[p:buf.index(b'\0',p)].decode('utf8','replace')
def off(v):return next(s[4]+v-s[3] for s in ss if s[1]!=8 and s[3]<=v<s[3]+s[5])
symbols=[]
for s in ss:
 if s[1]!=11:continue
 ns=data(ss[s[6]])
 for p in range(s[4],s[4]+s[5],s[9]):
  n,v,z,info,other,idx=struct.unpack_from('<IIIBBH',b,p);symbols.append((cs(ns,n),v,z,idx))
got={}
for s in ss:
 if s[1]!=9:continue
 for p in range(s[4],s[4]+s[5],s[9]):
  addr,info=struct.unpack_from('<II',b,p)
  if info&255==6:got[addr]=symbols[info>>8]
f=next(s for s in symbols if 'gml_Script_db_shop_items' in s[0] and s[3]);start=f[1];end=start+f[2]
text=subprocess.check_output(['objdump','-d','-C',f'--start-address={start}',f'--stop-address={end}',str(options.binary)],text=True)

from collections import Counter
pic=re.search(r'([0-9a-f]+):\s+(?:[0-9a-f]{2} )+\s+pop\s+%ebx\n\s*[0-9a-f]+:\s+(?:[0-9a-f]{2} )+\s+add\s+\$0x([0-9a-f]+),%ebx',text)
if not pic:raise ValueError('Unsupported PIC prologue')
base=int(pic[1],16)+int(pic[2],16)
registers={'%ebx':base};memory={};values={};records=[]
byname={s[0]:s for s in symbols}
def stackaddr(s):
 m=re.fullmatch(r'(0x[0-9a-f]+)?\(%esp\)',s)
 return int(m[1] or '0',16) if m else None
def read(s):
 s=s.strip()
 if s.startswith('$'):return int(s[1:],0)
 if s.startswith('%'):return registers.get(s)
 p=stackaddr(s)
 if p is not None:return memory.get(p)
 m=re.fullmatch(r'(-?0x[0-9a-f]+)\(%ebx\)',s)
 if m:
  sym=got.get(base+int(m[1],16))
  if sym:return ('symbol',sym[0])
 return None
def write(dst,value):
 if dst.startswith('%'):registers[dst]=value;return
 p=stackaddr(dst)
 if p is not None:
  memory[p]=value
  for k in list(values):
   if k<=p<k+16:del values[k]
def vector(s):
 p=stackaddr(s)
 if p is not None:return [memory.get(p+i*4) for i in range(4)]
 r=read(s);return r if isinstance(r,list) else [r,None,None,None]
def rval(p):
 if not isinstance(p,tuple):return None
 if p[0]=='address':
  try:return cs(b,off(p[1]))
  except (StopIteration,ValueError):return None
 if p[0]=='symbol':
  sym=byname[p[1]];v=sym[1]
  if p[1].startswith('g_pString'):
   try:return cs(b,off(v))
   except StopIteration:return ''
  if p[1].startswith('gs_constArg'):
   section=next(s for s in ss if s[3]<=v and v+16<=s[3]+s[5])
   raw=bytes(16) if section[1]==8 else b[off(v):off(v)+16]
   n,flags,kind=struct.unpack('<dII',raw)
   return n if kind==0 else None
 if p[0]=='stack':
  n=p[1]
  if n in values:return values[n]
  low,high,kind=memory.get(n),memory.get(n+4),memory.get(n+12)
  if kind==0 and isinstance(low,int) and isinstance(high,int):return struct.unpack('<d',struct.pack('<II',low&0xffffffff,high&0xffffffff))[0]
 return None
for line in text.splitlines():
 m=re.match(r'\s*([0-9a-f]+):\s+(?:[0-9a-f]{2}\s+)+\s*([a-z0-9]+)\s*(.*)',line)
 if not m:continue
 address,op,rest=int(m[1],16),m[2],m[3].split(' #')[0].strip()
 parts=re.split(r',(?![^\(]*\))',rest)
 if op=='call':
  if 'YYSetString' in rest:
   dest=memory.get(0);src=rval(memory.get(4))
   if isinstance(dest,tuple) and dest[0]=='stack':values[dest[1]]=src
  elif 'YYRValue::operator=(int)' in rest:
   dest=memory.get(0);value=memory.get(4)
   if isinstance(dest,tuple) and dest[0]=='stack':values[dest[1]]=value
  elif 'YYRValue::operator=(double)' in rest:
   dest=memory.get(0);low,high=memory.get(4),memory.get(8)
   if isinstance(dest,tuple) and dest[0]=='stack' and isinstance(low,int) and isinstance(high,int):values[dest[1]]=struct.unpack('<d',struct.pack('<II',low&0xffffffff,high&0xffffffff))[0]
  elif 'YYRValue::operator=' in rest:
   dest=memory.get(0);value=rval(memory.get(4))
   if isinstance(dest,tuple) and dest[0]=='stack':values[dest[1]]=value
  elif 'gml_Script_db_query_insert(' in rest:
   ptr=memory.get(16);argc=memory.get(12)
   if argc==9 and isinstance(ptr,tuple) and ptr[0]=='stack':
    args=[rval(memory.get(ptr[1]+4*i)) for i in range(9)]
    if (options.source=='original' or address>=0x3abbd3) and args[0]=='items':records.append({'address':hex(address),'args':args})
  continue
 if op=='pshufd' and len(parts)==3:
  imm=int(parts[0].strip()[1:],0);v=vector(parts[1].strip());write(parts[2].strip(),[v[(imm>>(2*i))&3] for i in range(4)]);continue
 if len(parts)!=2:continue
 src,dst=map(str.strip,parts)
 if op=='lea':
  p=stackaddr(src);m=re.fullmatch(r'(-?0x[0-9a-f]+)\(%ebx\)',src);write(dst,('stack',p) if p is not None else ('address',base+int(m[1],16)) if m else None)
 elif op in ['mov','movl']:write(dst,read(src))
 elif op=='movd':write(dst,[read(src),0,0,0] if dst.startswith('%xmm') else vector(src)[0])
 elif op=='movq':
  v=vector(src)[:2]+[0,0]
  if dst.startswith('%'):write(dst,v)
  else:
   p=stackaddr(dst)
   if p is not None:
    for i,value in enumerate(v[:2]):write(hex(p+4*i)+'(%esp)',value)
 elif op in ['movdqa','movdqu','movaps','movups','movapd','movupd']:
  v=vector(src)
  if dst.startswith('%'):write(dst,v.copy())
  else:
   p=stackaddr(dst)
   if p is not None:
    for i,value in enumerate(v):write(hex(p+4*i)+'(%esp)',value)
 elif op=='punpcklqdq':
  a,c=vector(src),vector(dst);write(dst,[c[0],c[1],a[0],a[1]])
 elif op=='punpckldq':
  a,c=vector(src),vector(dst);write(dst,[c[0],a[0],c[1],a[1]])
 elif dst.startswith('%') and op not in ['cmp','test','ucomisd','ucomiss']:
  write(dst,None)

if options.raw_output:
 options.raw_output.parent.mkdir(parents=True,exist_ok=True);options.raw_output.write_text(json.dumps(records,indent=2)+'\n')

schema='type|string,name|string,float|real,hp|real,weight|real,value|real,subimage|real,equiped|real'
if schema.encode()+b'\0' not in b:raise ValueError('Item schema not found')
kinds=['engine','suspension','turbo','ecu','nos','intake','intercooler','pistons','exhaust','tires']
selected=[r for r in records if r['args'][1] in kinds]
if len(records)!=(1197 if options.source=='original' else 1195) or len(selected)!=(197 if options.source=='original' else 195):raise ValueError('Unexpected item insertion coverage')
result=[];keys=set()
for row in selected:
 a=row['args']
 if a[0]!='items' or any(v is None for v in a):raise ValueError('Unresolved catalog row: '+str(row))
 if any(not isinstance(v,(int,float)) or not math.isfinite(v) for v in a[3:]):raise ValueError('Invalid numeric literal')
 category,name=a[1:3];subimage=int(a[7]);key=(category,subimage)
 if key in keys:raise ValueError('Duplicate category/subimage')
 keys.add(key)
 if name=='None':continue
 slot='supercharger' if category=='turbo' and ('SC' in name or 'WIPPLE' in name or 'BLOWER' in name) else category
 uid=(kinds.index(category)+1)*1000+subimage
 result.append({'id':uid,'category':slot,'source_type':category,'name':name,'stat':a[4],'weight':a[5],'value':a[6],
                'subimage':subimage,'source_call_address':row['address']})
result.sort(key=lambda p:p['id'])
report={'binary_sha256':expected,'method':'Read-only ELF/GOT and SSE literal-pointer propagation over db_shop_items',
 'schema':schema,'item_insertions_covered':len(records),'requested_rows_including_none':len(selected),
 'part_count':len(result),'parts':result,
 'limitations':['Generic hp field has category-specific semantics; full original runtime formulas are not reconstructed.',
 'Weight units and dynamic purchase/unlock rules are not established by this export.','None is represented by the native unequipped option.']}
options.output.parent.mkdir(parents=True,exist_ok=True);options.output.write_text(json.dumps(report,indent=2)+'\n')
print('Recovered',len(result),'parts:',dict(Counter(r['category'] for r in result)))
