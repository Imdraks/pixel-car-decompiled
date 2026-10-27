#!/usr/bin/env python3
"""Locate source drag/traction code in pinned Android ELF files without executing them.
This is a static coverage report, not an executable physics extraction.
"""
import argparse,hashlib,json,re,subprocess
from pathlib import Path
from recover_yyc_fields import recover
repo=Path(__file__).resolve().parents[2]
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--root',type=Path,default=Path('/workspace/windows-port'));p.add_argument('--output',type=Path,required=True);a=p.parse_args();a.output.mkdir(parents=True,exist_ok=True)
banks={}
wanted=['current_wieght','weight_to_power','wind_friction','xspeed','max_xspeed','run_acc','no_traction','tire_heat','wheel_spin','RPM','currentgear','gear_final']
for bank,folder,expected in [('original','original-recovered','af1f9adc9a3a0a4ec1547d051fe41a89974045cb3d7666fbbb94715ce2872a18'),('unbound','recovered','fb3726e175e7d1c643e0ddac1ec1a365901c4d52a16ded97e89fd672f6a9e9cc')]:
 binary=a.root/folder/'lib/x86/libyoyo.so';digest=hashlib.sha256(binary.read_bytes()).hexdigest()
 if digest!=expected:raise SystemExit('Unrecognized source library: '+bank)
 fields={f['id']:f['name'] for f in recover(binary)['fields'] if f['id'] is not None}
 inv=json.loads((repo/'native/evidence'/bank/'native-inventory.json').read_text())['x86']['game_functions']
 fn=next(v for v in inv if v['demangled'].startswith('gml_Object_ob_car_Step_0('));start=int(fn['address'],16)
 asm=subprocess.check_output(['objdump','-d','-C',f'--start-address={start}',f'--stop-address={start+fn["size"]}',str(binary)],text=True)
 lines=asm.splitlines();hits={k:[] for k in wanted};annotated=[]
 for line in lines:
  m=re.search(r'^\s*([0-9a-f]+):.*movl\s+\$0x([0-9a-f]+),0x4\(%esp\)',line)
  if m and (name:=fields.get(int(m[2],16))) in hits:
   hits[name].append('0x'+m[1]);line+=' # verified field ID: '+name
  annotated.append(line)
 # Small evidence windows preserve argument loads, operators and branch guards.
 indices=[i for i,line in enumerate(annotated) if 'verified field ID:' in line and any('ID: '+k in line for k in ['wind_friction','tire_heat','no_traction'])]
 selected=set()
 for i in indices:
  if len(selected)>18000:break
  selected.update(range(max(0,i-24),min(len(lines),i+85)))
 snippet='\n'.join(line for i,line in enumerate(annotated) if i in selected)+'\n'
 (a.output/(bank+'-traction-fragments.asm')).write_text(snippet)
 banks[bank]={'binary_sha256':digest,'function':fn['demangled'],'address':fn['address'],'bytes':fn['size'],'field_access_addresses':hits,'fragment_sha256':hashlib.sha256(snippet.encode()).hexdigest()}
report={'banks':banks,'import_status':'Existing source driving logic located; complete executable equations have not been reconstructed.','already_imported':['191 stock masses, power, redlines, chassis grip stats and drive layouts','part catalog values and gearbox ratios'], 'not_yet_imported':['complete tyre heat and traction equations','complete RPM, clutch and run_acc control flow','original timing and unit conversion across drag modes'],'limitations':['Field access addresses prove code coverage, not the meaning of every branch or unit.','YYRValue runtime, CInstance methods and room state prevent loading Android code directly into the Windows executable.','Native spring, damper and wheelie parameters are not established original-game parameters.','No Android-vs-Windows launch trace comparison has been performed.']}
(a.output/'drag-physics-source.json').write_text(json.dumps(report,indent=2)+'\n');print('Verified source driving code in both libraries; complete physics import remains unresolved.')
