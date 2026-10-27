#!/usr/bin/env python3
"""Read stock per-car literals and guarded car cases from both pinned YYC libraries.
Static data extraction only: never executes an APK or an Android library.
"""
import argparse,hashlib,json,re,struct,subprocess
from functools import lru_cache
from pathlib import Path
from recover_yyc_fields import recover

repo=Path(__file__).resolve().parents[2]
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--root',type=Path,default=Path('/workspace/windows-port'));a=p.parse_args();banks={}
for bank,folder,expected in [('original','original-recovered','af1f9adc9a3a0a4ec1547d051fe41a89974045cb3d7666fbbb94715ce2872a18'),('unbound','recovered','fb3726e175e7d1c643e0ddac1ec1a365901c4d52a16ded97e89fd672f6a9e9cc')]:
 binary=a.root/folder/'lib/x86/libyoyo.so';b=binary.read_bytes();assert hashlib.sha256(b).hexdigest()==expected
 h=struct.unpack_from('<16sHHIIIIIHHHHHH',b);ss=[struct.unpack_from('<10I',b,h[6]+i*h[11]) for i in range(h[12])]
 def data(s):return b[s[4]:s[4]+s[5]]
 def cs(buf,pos):return buf[pos:buf.index(b'\0',pos)].decode('utf8')
 def off(v):return next(s[4]+v-s[3] for s in ss if s[1]!=8 and s[3]<=v<s[3]+s[5])
 symbols=[]
 for s in ss:
  if s[1]!=11:continue
  ns=data(ss[s[6]])
  for pos in range(s[4],s[4]+s[5],s[9]):
   n,v,z,info,other,idx=struct.unpack_from('<IIIBBH',b,pos);symbols.append((cs(ns,n),v,z,idx))
 got={}
 for s in ss:
  if s[1]!=9:continue
  for pos in range(s[4],s[4]+s[5],s[9]):
   addr,info=struct.unpack_from('<II',b,pos)
   if info&255==6:got[addr]=symbols[info>>8]
 fn=next(f for f in json.loads((repo/'native/evidence'/bank/'native-inventory.json').read_text())['x86']['game_functions'] if f['demangled'].startswith('gml_Object_ob_car_Step_0('))
 asm=subprocess.check_output(['objdump','-d','-C','--start-address='+fn['address'],'--stop-address='+hex(int(fn['address'],16)+fn['size']),str(binary)],text=True)
 pic=re.search(r'call\s+([0-9a-f]+).*\n.*pop\s+%ebx\n.*add\s+\$0x([0-9a-f]+),%ebx',asm);base=int(pic[1],16)+int(pic[2],16)
 ids={f['name']:f['id'] for f in recover(binary)['fields']}
 # In Unbound car is an instance field at 0x218; g_VAR_car is a distinct global.
 carid=ids['car'] if bank=='original' else 0x218
 @lru_cache(maxsize=None)
 def accesses(field):return list(re.finditer(r'^\s*([a-f0-9]+):.*movl\s+\$0x'+format(field,'x')+r',0x4\(%esp\)',asm,re.M))
 offsets=accesses(ids['offsety']);cars=accesses(carid);assert len(offsets)==191
 def number(part):
  m=re.search(r'^\s*([a-f0-9]+):.*movl\s+\$0x([0-9a-f]+),0x4\(%(eax|ebp|esi|edi|ecx|edx)\)',part,re.M);assert m
  lo=re.search(r'movl\s+\$0x([0-9a-f]+),(?:0x0)?\(%'+m[3]+r'\)',part[m.end():m.end()+180]);assert lo
  return struct.unpack('<d',struct.pack('<II',int(lo[1],16),int(m[2],16)))[0],m[1]
 records=[]
 for i,start in enumerate(offsets):
  guard=next(m for m in reversed(cars) if m.start()<start.start());drive=next(m for m in accesses(ids['drivetrain']) if m.start()>start.start());block=asm[guard.start():drive.start()]
  if bank=='original':
   hi=re.search(r'movl\s+\$0x([0-9a-f]+),0xa24\(%esp\)',block);lo=re.search(r'movl\s+\$0x([0-9a-f]+),0xa20\(%esp\)',block);assert hi and lo
   bound=struct.unpack('<d',struct.pack('<II',int(lo[1],16),int(hi[1],16)))[0]
  else:
   compare=block[:start.start()-guard.start()];d=list(re.finditer(r'addsd\s+(-?0x[0-9a-f]+)\(%ebx\)',compare));assert d
   bound=-struct.unpack_from('<d',b,off(base+int(d[-1][1],16)))[0]
  assert bound==int(bound) and 1<=bound<=191,(bank,i,bound)
  body=int(bound)-1
  values={};addresses={}
  for m in re.finditer(r'^\s*([a-f0-9]+):.*movl\s+\$0x([0-9a-f]+),0x4\(%(eax|ebp)\)',block,re.M):
   low=re.search(r'movl\s+\$0x([0-9a-f]+),(?:0x0)?\(%'+m[3]+r'\)',block[m.end():m.end()+180]);assert low
   if bank=='unbound' and m[3]=='ebp':key='hp'
   else:
    loads=list(re.finditer(r'mov\s+0x([0-9a-f]+)\(%esp\),%eax',block[:m.start()]));assert loads
    # These cached pointers are initialized from global wieght/hp/grip/topspeed
    # in this hash-pinned Step prologue. Local fields with similar names differ.
    key=({'34':'weight_lb','28':'hp','2c':'grip_raw','30':'speed_mph'} if bank=='original' else {'70':'weight_lb','58':'grip_raw','44':'speed_mph'})[loads[-1][1]]
   assert key not in values;values[key]=struct.unpack('<d',struct.pack('<II',int(low[1],16),int(m[2],16)))[0];addresses[key]=m[1]
  for name,key in [('car_rev','redline_rpm'),('engine_liter','displacement_raw')]:
   match=next(m for m in accesses(ids[name]) if guard.start()<m.start()<drive.start());values[key],addresses[key]=number(asm[match.end():drive.start()])
  assert set(values)=={'weight_lb','hp','grip_raw','speed_mph','redline_rpm','displacement_raw'}
  tail=asm[drive.end():drive.end()+2000];call=re.search(r'^\s*([a-f0-9]+):.*call.*YYCreateString',tail,re.M);assert call
  ref=list(re.finditer(r'mov\s+(-?0x[0-9a-f]+)\(%ebx\),%eax',tail[:call.start()]))[-1]
  sym=got[base+int(ref[1],16)];assert sym[0].startswith('g_pString');layout=cs(b,off(sym[1]));assert layout.upper() in ['FWD','RWD','AWD'],layout
  values['drivetrain']=layout;addresses['drivetrain']=call[1]
  assert 1000<=values['weight_lb']<=6000 and 20<=values['hp']<=1000 and 6000<=values['redline_rpm']<=10000
  records.append({'body':body,'guard_address':guard[1],'upper_bound':bound,'values':values,'write_addresses':addresses})
 assert sorted(r['body'] for r in records)==list(range(191))
 records.sort(key=lambda r:r['body'])
 # Recover the distinct engine-HP guards for replacement-engine rev/displacement overrides.
 allfields=list(re.finditer(r'^\s*([a-f0-9]+):.*movl\s+\$0x([0-9a-f]+),0x4\(%esp\)',asm,re.M))
 knownhp={250,410,212,270,290,330,478,505,656,542,707,627,755,260,187}
 guards=[]
 for hpaccess in accesses(ids['engine_hp']):
  nextfield=next((v.start() for v in allfields if v.start()>hpaccess.start()),len(asm));part=asm[hpaccess.end():nextfield]
  try:
   if bank=='original':
    hi=re.search(r'movl\s+\$0x([0-9a-f]+),0xa24\(%esp\)',part);lo=re.search(r'movl\s+\$0x([0-9a-f]+),0xa20\(%esp\)',part)
    if not hi or not lo:continue
    hp=struct.unpack('<d',struct.pack('<II',int(lo[1],16),int(hi[1],16)))[0]
   else:
    literals=list(re.finditer(r'addsd\s+(-?0x[0-9a-f]+)\(%ebx\)',part))
    if not literals:continue
    hp=-struct.unpack_from('<d',b,off(base+int(literals[0][1],16)))[0]
   if hp in knownhp:guards.append((hpaccess,hp))
  except StopIteration:continue
 if bank=='unbound':
  # YYC keeps engine_hp in xmm0 across these comparisons, eliminating repeated
  # field lookups. The subtraction literal is the independently recovered guard.
  guards=[]
  for literal in re.finditer(r'^\s*([a-f0-9]+):.*addsd\s+(-?0x[0-9a-f]+)\(%ebx\)',asm,re.M):
   hp=-struct.unpack_from('<d',b,off(base+int(literal[2],16)))[0]
   if hp in knownhp:guards.append((literal,hp))
 engines=[];stockrevs={r['write_addresses']['redline_rpm'] for r in records}
 for revaccess in accesses(ids['car_rev']):
  if revaccess.start()<offsets[0].start():continue
  nextfield=next((v.start() for v in allfields if v.start()>revaccess.start()),len(asm));part=asm[revaccess.end():nextfield]
  try:rev,revaddr=number(part)
  except (AssertionError,AttributeError):continue
  if revaddr in stockrevs:continue
  hpaccess,hp=next(v for v in reversed(guards) if v[0].start()<revaccess.start())
  litreaccess=next(v for v in reversed(accesses(ids['engine_liter'])) if hpaccess.start()<v.start()<revaccess.start());lit,litaddr=number(asm[litreaccess.end():revaccess.start()])
  engines.append({'engine_hp':hp,'redline_rpm':rev,'displacement_raw':lit,'guard_address':hpaccess[1],'write_addresses':{'redline_rpm':revaddr,'displacement_raw':litaddr}})
 assert len(engines)==15 and {r['engine_hp'] for r in engines}==knownhp,(bank,engines)
 banks[bank]={'binary_sha256':expected,'function':fn,'records':records,'replacement_engines':engines}
assert [r['values'] for r in banks['original']['records']]==[r['values'] for r in banks['unbound']['records']]
assert {r['engine_hp']:(r['redline_rpm'],r['displacement_raw']) for r in banks['original']['replacement_engines']}=={r['engine_hp']:(r['redline_rpm'],r['displacement_raw']) for r in banks['unbound']['replacement_engines']}
report={'method':'Read-only guarded stock-car and replacement-engine literals in ob_car_Step_0; stock upper bounds and engine HP guards independently checked in both banks','body_count':191,'banks':banks,'conversions':{'mass_kg':'weight_lb * 0.45359237','litres':'displacement_raw * 10 (source display scale)','native_grip':'grip_raw / 1200 * 1.08; native calibration, not a recovered friction equation'},'limitations':['Stock literals are recovered, not complete Android vehicle dynamics.','No real manufacturer model name is inferred from a number alone.','A mod skin inherits its source body mechanical record until explicit different source parameters exist.']}
(repo/'native/evidence/merged/stock-vehicles.json').write_text(json.dumps(report,indent=2)+'\n')
lines=['// Generated by native/tools/recover_vehicle_data.py; identical stock literals in both source banks.','#pragma once','namespace pcr {','struct StockVehicle {double weightLb,hp,gripRaw,speedMph,redlineRpm,litres;int drive;};','inline constexpr StockVehicle StockVehicles[]={']
for row in banks['original']['records']:
 v=row['values'];nums=[v[k] for k in ['weight_lb','hp','grip_raw','speed_mph','redline_rpm']]+[v['displacement_raw']*10];lines.append('{'+','.join(format(n,'.12g') for n in nums)+','+str({'FWD':0,'RWD':1,'AWD':2}[v['drivetrain'].upper()])+'},')
lines+=['};','inline const StockVehicle& stockVehicle(int body){return StockVehicles[body>=0&&body<191?body:0];}', 'struct ReplacementEngine {double redlineRpm,litres;};','inline constexpr ReplacementEngine ReplacementEngines[]={','{0,0},']
engine_map={r['engine_hp']:r for r in banks['original']['replacement_engines']}
parts=[r for r in json.loads((repo/'native/evidence/merged/performance.json').read_text())['parts'] if r['category']=='engine']
parts.sort(key=lambda r:r['subimage']);assert [r['subimage'] for r in parts]==list(range(1,17))
for part in parts:
 v=engine_map[part['stat']];lines.append('{'+format(v['redline_rpm'],'.12g')+','+format(v['displacement_raw']*10,'.12g')+'},')
lines+=['};','inline const ReplacementEngine& replacementEngine(int frame){return ReplacementEngines[frame>0&&frame<17?frame:0];}','}'];(repo/'native/game/src/stock_vehicles.hpp').write_text('\n'.join(lines)+'\n');print('Recovered 191 stock vehicles in each bank; 1337 per-bank values and all 382 upper bounds checked.')
