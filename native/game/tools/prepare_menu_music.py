#!/usr/bin/env python3
"""Prepare a supplied song and a garage-speaker variant without replacing source audio."""
import argparse,array,datetime,hashlib,json,math,re,shutil,subprocess
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__);p.add_argument('source',type=Path);p.add_argument('--work-dir',type=Path,required=True);p.add_argument('--assets',type=Path,required=True);a=p.parse_args();a.work_dir.mkdir(parents=True,exist_ok=True);a.assets.mkdir(parents=True,exist_ok=True)
def run(cmd):
 result=subprocess.run(cmd,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
 if result.returncode:raise RuntimeError(result.stderr.decode(errors='replace'))
 return result
def probe(path):return json.loads(run(['ffprobe','-v','error','-show_entries','format=duration:stream=codec_name,sample_rate,channels','-of','json',str(path)]).stdout)
def backup(path):
 if path.exists():
  dest=a.work_dir/'backups'/datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%S%f');dest.mkdir(parents=True,exist_ok=True);shutil.copy2(path,dest/path.name)
duration=float(probe(a.source)['format']['duration']);frames=round(duration*44100);source_hash=hashlib.file_digest(a.source.open('rb'),'sha256').hexdigest();clips=[]
for name,effects in [('menu-underground',''),('menu-underground-garage','highpass=f=60,lowpass=f=6500,equalizer=f=180:t=q:w=1:g=2,extrastereo=m=0.65,aecho=0.8:0.8:17|37|61|89:0.18|0.12|0.09|0.06,')]:
 prefix=effects+f'atrim=duration={duration},asetpts=PTS-STARTPTS,'
 meter=run(['ffmpeg','-hide_banner','-nostats','-i',str(a.source),'-af',prefix+'loudnorm=I=-18:TP=-2:LRA=11:print_format=json','-f','null','-']).stderr.decode()
 measured=json.loads(re.search(r'\{\s*"input_i".*?\}',meter,re.S)[0]);normal='loudnorm=I=-18:TP=-2:LRA=11:linear=true:'+':'.join(k+'='+measured[v] for k,v in [('measured_I','input_i'),('measured_TP','input_tp'),('measured_LRA','input_lra'),('measured_thresh','input_thresh'),('offset','target_offset')])
 wav=a.work_dir/(name+'.wav');ogg=a.assets/(name+'.ogg');assert a.source.resolve() not in {wav.resolve(),ogg.resolve()};backup(wav);backup(ogg)
 filters=prefix+normal+f',aresample=44100,asetpts=PTS-STARTPTS,apad=whole_len={frames},afade=t=in:st=0:d=0.08,afade=t=out:st={duration-.18}:d=0.18,atrim=end_sample={frames},asetpts=PTS-STARTPTS'
 run(['ffmpeg','-y','-v','error','-i',str(a.source),'-af',filters,'-ar','44100','-ac','2','-c:a','pcm_s16le',str(wav)])
 run(['ffmpeg','-y','-v','error','-i',str(wav),'-c:a','libvorbis','-q:a','5','-ar','44100','-ac','2','-metadata','title='+('Underground - garage speaker' if effects else 'Underground - menu'),str(ogg)])
 info=probe(ogg);samples=array.array('f');samples.frombytes(run(['ffmpeg','-v','error','-i',str(ogg),'-f','f32le','-ac','2','-ar','44100','-']).stdout)
 peak=max(abs(min(samples)),max(samples));rms=math.sqrt(sum(v*v for v in samples)/len(samples));jump=max(abs(samples[c]-samples[-2+c]) for c in [0,1])
 assert info['streams'][0]['codec_name']=='vorbis' and int(info['streams'][0]['sample_rate'])==44100 and info['streams'][0]['channels']==2
 assert abs(float(info['format']['duration'])-duration)<.025 and peak<.99 and rms>.001 and jump<.003, {'file':str(ogg),'source_duration':duration,'duration':info['format']['duration'],'peak':peak,'rms':rms,'endpoint_jump':jump}
 clips.append({'file':ogg.name,'duration_s':float(info['format']['duration']),'sample_rate':44100,'channels':2,'decoded_frames':len(samples)//2,'decoded_peak':peak,'decoded_rms':rms,'loop_endpoint_jump':jump,'sha256':hashlib.file_digest(ogg.open('rb'),'sha256').hexdigest(),'effects':effects or 'unfiltered music, loudness normalization only','normalization_lufs':-18,'normalization_true_peak_db':-2})
report={'title':'Underground — fichier fourni','source_filename':a.source.name,'source_sha256':source_hash,'source_original_preserved':hashlib.file_digest(a.source.open('rb'),'sha256').hexdigest()==source_hash,'duration_s':duration,'clips':clips,'menu_gain':.55,'garage_gain':.55,'customization_gain':.22,'customization_uses_garage_variant':True,'driving_music':False,'passed':True}
backup(a.assets/'manifest.json');(a.assets/'manifest.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n');(a.work_dir/'validation.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n');print(json.dumps(report,ensure_ascii=False))
