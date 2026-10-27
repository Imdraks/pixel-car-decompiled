#!/usr/bin/env python3
"""Verify the read-only audio export, stage original bytes and generate sample metadata."""
import argparse,hashlib,json,shutil
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--source',type=Path,default=Path('/workspace/native-runtime/game-audio'));a=p.parse_args()
game=Path(__file__).resolve().parents[1];sounds=json.loads((a.source/'sounds.json').read_text())
if len(sounds)!=94 or [s['id'] for s in sounds]!=list(range(94)):raise ValueError('Expected the 94 original sound IDs')
profile=json.loads((game.parent/'evidence/unbound/parts/engine-audio.json').read_text())['profiles']
out=game/'assets/audio';out.mkdir(parents=True,exist_ok=True)
for sound in sounds:
 source=a.source/sound['file']
 if hashlib.file_digest(source.open('rb'),'sha256').hexdigest()!=sound['sha256']:raise ValueError('Sound digest mismatch: '+sound['name'])
 shutil.copy2(source,out/sound['file'])
shutil.copy2(a.source/'sounds.json',out/'sounds.json')
lines=['// Original Unbound sound metadata and verified sound-profile dispatch.','#pragma once','namespace pcr {','struct OriginalSound { const char* name; const char* file; float volume=1; };','inline constexpr OriginalSound OriginalSounds[] = {']
for sound in sounds:lines.append('{'+json.dumps(sound['name'])+','+json.dumps('audio/'+sound['file'])+','+format(float(sound['volume']),'.8f')+'f},')
lines+=['};','inline constexpr int EngineSoundProfiles[16][2] = {']
for row in profile:lines.append('{'+str(row['on']['id'])+','+str(row['off']['id'])+'},')
lines+=['};','}'];(game/'src/original_audio.hpp').write_text('\n'.join(lines)+'\n')
p=game/'assets/provenance.json';provenance=json.loads(p.read_text())
provenance['files']=[f for f in provenance['files'] if not f['file'].startswith('audio/')]
provenance['files'] += [{'file':'audio/'+s['file'],'sha256':s['sha256']} for s in sounds]
provenance['original_audio']={'count':94,'manifest':'audio/sounds.json','sound_profile_dispatch':'Recovered from original e_s/e_s2 switches','engine_item_automatic_assignment':'16 replacement-engine assignments verified in both ELF banks; stock selection unresolved; manual override available'}
p.write_text(json.dumps(provenance,indent=2)+'\n')
print('Verified and staged',len(sounds),'original sounds; generated sound profile metadata')
