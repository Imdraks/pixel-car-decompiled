#!/usr/bin/env python3
"""Verify and retain the original 1.2.5 sound bank alongside Unbound's bank."""
import argparse,hashlib,json,shutil
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--source',type=Path,default=Path('/workspace/native-runtime/original-audio-08'));a=p.parse_args();game=Path(__file__).resolve().parents[1];sounds=json.loads((a.source/'sounds.json').read_text());mod=json.loads((game/'assets/audio/sounds.json').read_text());assert len(sounds)==94 and all(x['id']==y['id'] and x['name']==y['name'] for x,y in zip(sounds,mod))
out=game/'assets/audio-original';out.mkdir(exist_ok=True);files=[]
for s in sounds:
 path=a.source/s['file'];assert hashlib.file_digest(path.open('rb'),'sha256').hexdigest()==s['sha256'];shutil.copy2(path,out/s['file']);files.append({'file':'audio-original/'+s['file'],'sha256':s['sha256']})
shutil.copy2(a.source/'sounds.json',out/'sounds.json')
h=['// Verified original 1.2.5 samples; stable names/indices match the Unbound bank.','#pragma once','#include "original_audio.hpp"','namespace pcr {','inline constexpr OriginalSound BaseGameSounds[]={']
h+=['{'+json.dumps(s['name'])+','+json.dumps('audio-original/'+s['file'])+','+format(float(s['volume']),'.8f')+'f},' for s in sounds];h+=['};','inline const OriginalSound& sourceSound(int id,int source){return source==1?BaseGameSounds[id]:OriginalSounds[id];}','}'];(game/'src/base_audio.hpp').write_text('\n'.join(h)+'\n')
j=json.loads((game/'assets/provenance.json').read_text());j['files']=[s for s in j['files'] if not s['file'].startswith('audio-original/')]+files;j['merged_audio']={'original':94,'unbound':94,'equal_names_and_indices':True,'byte_identical':sum(x['sha256']==y['sha256'] for x,y in zip(sounds,mod)),'original_source_binary':'af1f9adc9a3a0a4ec1547d051fe41a89974045cb3d7666fbbb94715ce2872a18'};(game/'assets/provenance.json').write_text(json.dumps(j,indent=2)+'\n');(game/'validation/merged-audio.json').write_text(json.dumps(j['merged_audio'],indent=2)+'\n');print('Preserved and verified original/Unbound banks:',len(sounds)+len(mod),'samples')
