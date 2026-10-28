#!/usr/bin/env python3
"""Verify simulation manifests and install a separate, reproducible native audio bank."""
import argparse,hashlib,json,re,shutil
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--packs-root',type=Path,required=True);p.add_argument('--assets',type=Path,required=True);p.add_argument('--header',type=Path,required=True);a=p.parse_args()
names=['ls-v8-v1','amg-gt63s-v1','huracan-v10-v1','aventador-svj-v1','f1-v6-v1','ford-coyote-v1'];packs=[]
for name in names:
 root=a.packs_root/name;manifest=json.loads((root/'manifest.json').read_text());report=json.loads((root/'validation.json').read_text());vehicle=json.loads((root/'vehicle.json').read_text());slug=vehicle['slug']
 if not report.get('passed') or not re.fullmatch('[a-z0-9_]+',slug):raise ValueError('Invalid validated pack')
 for row in report['files']:
  for kind in ['wav','ogg']:
   file=row[kind]
   if Path(file).name!=file or hashlib.sha256((root/file).read_bytes()).hexdigest()!=row[kind+'_sha256']:raise ValueError('Audio digest mismatch')
 target=a.assets/'engine-packs'/slug;target.mkdir(parents=True,exist_ok=True)
 # Idempotent reuse; refuse to overwrite any changed asset, including metadata.
 files=[r[k] for r in report['files'] for k in ['wav','ogg']]+['manifest.json','vehicle.json','validation.json','ENGINE-SIM-LICENSE.txt']
 for name in files:
  source=root/name;dest=target/name
  if dest.exists() and dest.read_bytes()!=source.read_bytes():raise FileExistsError('Changed audio asset requires backup: '+str(dest))
  if not dest.exists():shutil.copy2(source,dest)
 packs.append((slug,manifest))
lines=['// Generated from the validated simulation manifests. Do not edit by hand.','#pragma once','#include <cstddef>','namespace pcr {','struct SimulatedClip {const char* file;double rpm,load;};','struct SimulatedPack {int engineId;const char* name;const SimulatedClip* clips;std::size_t count;const char* startup;const char* shutdown;double startupSeconds;};']
quote=lambda text:json.dumps(text,ensure_ascii=True)
for slug,m in packs:
 loops=[r for r in m['clips'] if r['type']=='rpm_loop'];events={r['type']:r for r in m['clips'] if not r['loop']};base='engine-packs/'+slug+'/'
 lines.append('inline constexpr SimulatedClip Clips_'+slug+'[]={')
 for clip in loops:lines.append('{'+quote(base+clip['ogg'])+','+str(clip['rpm'])+','+str(clip['load'])+'},')
 lines.append('};')
lines.append('inline constexpr SimulatedPack SimulatedPacks[]={')
for slug,m in packs:
 events={r['type']:r for r in m['clips'] if not r['loop']};base='engine-packs/'+slug+'/'
 for id in m['game_engine_ids']:lines.append('{'+str(id)+','+quote(m['model'])+',Clips_'+slug+',std::size(Clips_'+slug+'),'+quote(base+events['startup']['ogg'])+','+quote(base+events['ignition_off']['ogg'])+','+str(events['startup']['duration_s'])+'},')
lines+=['};','inline const SimulatedPack* simulatedPack(int engineId){for(const auto& p:SimulatedPacks)if(p.engineId==engineId)return &p;return nullptr;}','}']
a.header.parent.mkdir(parents=True,exist_ok=True);a.header.write_text('\n'.join(lines)+'\n');print('Installed',len(packs),'verified simulation banks; source audio untouched')
