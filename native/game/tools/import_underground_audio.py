#!/usr/bin/env python3
"""Import the 94 exported Underground sound IDs, deduplicate, and give decoded peaks headroom.
Source bytes stay in --audio; game copies only are normalized. No existing other bank is replaced.
Run after import_underground.py and export_audio.csx.
"""
from pathlib import Path
import argparse,json,hashlib,subprocess,array,math,shutil
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--audio',type=Path,required=True);a=p.parse_args();G=Path(__file__).resolve().parents[1]
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
rows=json.loads((a.audio/'sounds.json').read_text());assert len(rows)==94
h=['#pragma once','#include "original_audio.hpp"','namespace pcr {','inline constexpr OriginalSound UndergroundSounds[]={'];files=[];audit=[]
for v in rows:
 source=a.audio/v['file'];assert sha(source)==v['sha256'];old=G/'assets/audio'/v['file'];file='audio/'+v['file']
 if not old.exists() or sha(old)!=sha(source):
  raw=subprocess.check_output(['ffmpeg','-v','error','-i',str(source),'-f','f32le','-acodec','pcm_f32le','-']);samples=array.array('f');samples.frombytes(raw);peak=max(map(abs,samples));assert peak>0 and all(math.isfinite(x) for x in samples)
  file='audio-underground/'+v['file'];dest=G/'assets'/file;dest.parent.mkdir(exist_ok=True)
  gain=min(1.,.86/peak)
  if gain<1:subprocess.run(['ffmpeg','-y','-v','error','-i',str(source),'-af',f'volume={gain:.12f}',*(['-c:a','libvorbis','-q:a','6'] if dest.suffix=='.ogg' else ['-c:a','pcm_s16le']),str(dest)],check=True)
  else:shutil.copy2(source,dest)
  raw=subprocess.check_output(['ffmpeg','-v','error','-i',str(dest),'-f','f32le','-acodec','pcm_f32le','-']);samples=array.array('f');samples.frombytes(raw);final=max(map(abs,samples));assert final<.99 and final>0,(file,final)
  meta=json.loads(subprocess.check_output(['ffprobe','-v','error','-show_entries','stream=codec_name,sample_rate,channels,duration','-of','json',str(dest)],text=True))['streams'][0]
  audit.append({**v,'game_file':file,'game_sha256':sha(dest),'source_peak':peak,'gain':gain,'game_peak':final,'samples':len(samples),'format':meta,'verified':True});files.append({'file':file,'sha256':sha(dest)})
 h.append('{'+json.dumps(v['name'])+','+json.dumps(file)+','+str(float(v['volume']))+'f},')
h+=['};','}'];(G/'src/underground_audio.hpp').write_text('\n'.join(h)+'\n')
prov=json.loads((G/'assets/provenance.json').read_text());prov['files']=[v for v in prov['files'] if not v['file'].startswith('audio-underground/')]+files;(G/'assets/provenance.json').write_text(json.dumps(prov,indent=2)+'\n')
report=json.loads((G/'underground-catalog.json').read_text());report['audio_changed']=audit;report['audio_shared_count']=94-len(audit);(G/'underground-catalog.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n')
(G/'validation/underground-audio.json').write_text(json.dumps({'passed':True,'changed':audit,'shared':94-len(audit),'source_backups':str(a.audio),'policy':'Source files retained. Decoded source peaks above 0.86 are attenuated in separate game copies.'},indent=2)+'\n');print('Verified',len(audit),'new sounds with peak < 0.99; original banks unchanged.')
