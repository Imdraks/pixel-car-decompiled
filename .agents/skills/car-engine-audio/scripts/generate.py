#!/usr/bin/env python3
"""Generate physically simulated car audio using the pinned upstream exporter."""
import argparse,csv,hashlib,json,math,re,shutil,subprocess,sys,wave
from pathlib import Path
import numpy as np
TEMPLATES={
 'V12':'assets/engines/atg-video-2/12_ferrari_412_t2.mr',
 'V10':'assets/engines/atg-video-2/10_lfa_v10.mr',
 'V8':'assets/engines/atg-video-2/07_gm_ls.mr',
 'V6':'assets/engines/atg-video-2/06_even_fire_v6.mr',
 'I6':'assets/engines/atg-video-2/03_2jz.mr',
 'I5':'assets/engines/atg-video-1/07_audi_i5.mr',
 'I4':'assets/engines/atg-video-1/05_honda_vtec.mr',
 'H4':'assets/engines/atg-video-2/01_subaru_ej25_eh.mr'}
def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def adapt(spec,source,job):
    layout=spec['layout']
    if layout not in TEMPLATES:raise ValueError('No compatible bundled physical configuration for '+layout+'; supply a reviewed .mr template, do not substitute a different cylinder layout.')
    template=source/TEMPLATES[layout];s=template.read_text();notes=[]
    if layout=='V12':
        # Same rod-journal/firing order pattern, with 60-degree bank and cam offsets.
        s=re.sub(r'\b75\b','60',s);s=s.replace('50 * units.g','500 * units.g').replace('(50) * units.g','(480) * units.g')
        s=s.replace('15.95 * units.mm','13 * units.mm');notes.append('V12 bank, crank TDC, cam/ignition offsets adapted from 75 to 60 degrees; road-sized moving masses and valve lift estimated.')
    for key in ['bore','stroke']:
        value=spec.get(key+'_mm')
        if value is not None:
            s,count=re.subn(r'(label\s+'+key+r'\s*\()[^\n)]*(\))',lambda m:m[1]+str(float(value))+' * units.mm'+m[2],s,count=1)
            if count!=1:raise ValueError('Template does not expose '+key+'; manual compatible adapter required')
    if 'bore_mm' in spec and 'stroke_mm' in spec:
        displacement=math.pi/4*spec['bore_mm']**2*spec['stroke_mm']*spec['cylinders']/1e6
        if abs(displacement-spec['litres'])/spec['litres']>.01:raise ValueError('Description displacement disagrees with bore/stroke/cylinders')
    s,n=re.subn(r'(redline:\s*)[\d.]+\s*\*\s*units.rpm',lambda m:m[1]+str(spec['redline_rpm'])+' * units.rpm',s,count=1)
    if n!=1:raise ValueError('Cannot locate template redline')
    s=re.sub(r'(rev_limit:\s*)[\d.]+\s*\*\s*units.rpm',lambda m:m[1]+str(spec['redline_rpm']+100)+' * units.rpm',s)
    if spec.get('exhaust'):
        if spec['exhaust'] not in {'minimal_muffling_01','minimal_muffling_02','minimal_muffling_03','mild_exhaust_0','mild_exhaust_0_reverb'}:raise ValueError('Unsupported bundled exhaust impulse response')
        s=re.sub(r'(impulse_response:\s*ir_lib\.)\w+',lambda m:m[1]+spec['exhaust'],s)
    s=re.sub(r'(name:\s*)"[^"]+"',lambda m:m[1]+json.dumps(spec['model']+' [simulated approximation]',ensure_ascii=True),s,count=1)
    # Engine files define main but require a wrapper to execute it.
    (job/'engine.mr').write_text(s);(job/'main.mr').write_text('import "engine_sim.mr"\nimport "engine.mr"\nmain()\n')
    for name in ['es','assets']:(job/name).symlink_to(source/name,target_is_directory=True)
    return {'template':str(template.relative_to(source)),'template_sha256':digest(template),'adapted_sha256':digest(job/'engine.mr'),'notes':notes}
def read_wav(p):
    with wave.open(str(p),'rb') as w:
        if w.getnchannels()!=1 or w.getsampwidth()!=2 or w.getframerate()!=44100:raise ValueError('Expected mono PCM16/44100: '+str(p))
        return np.frombuffer(w.readframes(w.getnframes()),dtype='<i2').astype(np.float64)/32768

def metrics(data):
    if data.size==0 or not np.isfinite(data).all():raise ValueError('Empty or non-finite PCM')
    return {'frames':len(data),'duration_s':len(data)/44100,'peak':float(np.max(np.abs(data))),'rms':float(np.sqrt(np.mean(data*data))),'dc':float(np.mean(data)),'seam_jump':float(abs(data[0]-data[-1])),'rail_samples':int(np.count_nonzero(np.abs(data)>=32767/32768))}
def write_wav(p,a):
    with wave.open(str(p),'wb') as w:w.setnchannels(1);w.setsampwidth(2);w.setframerate(44100);w.writeframes(np.rint(a*32767).astype('<i2').tobytes())
def process(job,output,spec,ffmpeg,duration):
    rows=list(csv.DictReader((job/'raw/unity_audio_manifest.csv').open()));reports=[];manifest=[]
    for row in rows:
        raw=job/'raw'/row['filename'];data=read_wav(raw);before=metrics(data);loop=row['loop']=='true'
        if before['rail_samples']:raise ValueError('Source clipped before postprocessing: '+raw.name)
        if before['rms']<1e-5:raise ValueError('Silent/invalid source: '+raw.name)
        if abs(before['duration_s']-duration)>.01:raise ValueError('Incorrect source duration: '+raw.name)
        data-=np.mean(data)
        if loop:
            n=min(int(.03*44100),len(data)//16);length=len(data)-n
            conditioned=data[n:].copy();weight=.5-.5*np.cos(np.linspace(0,np.pi,n))
            conditioned[-n:]=conditioned[-n:]*(1-weight)+data[:n]*weight;data=conditioned
            # Locate a quiet low-slope circular seam, then smooth 3ms at both ends.
            slopes=np.abs(data-np.roll(data,1));offset=int(np.argmin(slopes+.1*np.abs(data)));data=np.roll(data,-offset)
            n=132;fade=.5-.5*np.cos(np.linspace(0,np.pi,n));data[:n]*=fade;data[-n:]*=fade[::-1]
        else:
            n=min(220,len(data)//8);fade=np.linspace(0,1,n);data[:n]*=fade;data[-n:]*=fade[::-1]
        # Constant gain only: no saturation limiter and no invented combustion signal.
        measured=metrics(data);gain=min(.80/measured['peak'],.12/measured['rms']);data*=gain
        kind=row['type'];name=f"{spec['slug']}_{kind}"+(f"_rpm_{row['rpm']}_load_{row['throttle_percent']}" if loop else '')
        wav=output/(name+'.wav');ogg=output/(name+'.ogg');write_wav(wav,data)
        subprocess.run([ffmpeg,'-v','error','-n','-i',str(wav),'-c:a','libvorbis','-q:a','6',str(ogg)],check=True)
        decoded=subprocess.check_output([ffmpeg,'-v','error','-i',str(ogg),'-f','f32le','-ac','1','-ar','44100','-'])
        after=metrics(read_wav(wav));compressed=metrics(np.frombuffer(decoded,dtype='<f4'))
        if after['peak']>=.99 or compressed['peak']>=.99:raise ValueError('Output peak exceeds headroom: '+name)
        if abs(compressed['duration_s']-after['duration_s'])>.02:raise ValueError('OGG duration mismatch')
        if loop and (after['seam_jump']>.01 or compressed['seam_jump']>.04):raise ValueError('Loop seam exceeds numerical threshold: '+name)
        reports.append({'wav':wav.name,'ogg':ogg.name,'raw':before,'wav_metrics':after,'ogg_metrics':compressed,'gain':gain,'wav_sha256':digest(wav),'ogg_sha256':digest(ogg)})
        manifest.append({'wav':wav.name,'ogg':ogg.name,'type':kind,'rpm':int(row['rpm']),'load':int(row['throttle_percent'])/100 if row['throttle_percent'] else None,'loop':loop,'duration_s':after['duration_s']})
    required={'startup','rpm_loop','ignition_off','acceleration','deceleration'}
    if not required.issubset({x['type'] for x in manifest}):raise ValueError('Missing engine event types')
    return manifest,reports

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--description',type=Path,required=True);p.add_argument('--exporter-root',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--duration',type=float,default=3);p.add_argument('--warmup',type=float,default=3);p.add_argument('--ffmpeg',default='ffmpeg');p.add_argument('--timeout',type=int,default=1800);a=p.parse_args()
    spec=json.loads(a.description.read_text());slug=spec['slug']
    if not re.fullmatch('[a-z0-9_]+',slug):raise ValueError('Invalid output slug')
    rpm=spec['rpm_anchors'];throttle=spec.get('throttle_layers',[0,30,100])
    if not 0.5<=a.duration<=30 or not 0.5<=a.warmup<=30:raise ValueError('Duration/warmup outside supported range')
    if not rpm or any(not isinstance(x,int) or x<500 or x>spec['redline_rpm'] for x in rpm):raise ValueError('RPM anchors outside engine range')
    if 0 not in throttle or 100 not in throttle:raise ValueError('Include coast (0) and full-load (100) layers')
    a.output=a.output.resolve();a.output.mkdir(parents=True,exist_ok=False);job=a.output/'simulation';job.mkdir();source=a.exporter_root.resolve()/'source';exe=a.exporter_root.resolve()/'build/engine-sim-exporter'
    if not exe.is_file():raise FileNotFoundError('Exporter not built: '+str(exe))
    (a.output/'vehicle.json').write_text(json.dumps(spec,indent=2)+'\n');provenance=adapt(spec,source,job)
    command=[str(exe),'--script',str(job/'main.mr'),'--out',str(job/'raw'),'--rpm',','.join(map(str,rpm)),'--throttle',','.join(map(str,throttle)),'--duration',str(a.duration),'--warmup',str(a.warmup),'--loop-crossfade','30']
    with (job/'export.log').open('w') as log:subprocess.run(command,cwd=job,stdout=log,stderr=log,timeout=a.timeout,check=True)
    manifest,reports=process(job,a.output,spec,a.ffmpeg,a.duration)
    shutil.copy2(source/'LICENSE',a.output/'ENGINE-SIM-LICENSE.txt')
    (a.output/'manifest.json').write_text(json.dumps({'schema':1,'model':spec['model'],'sample_rate':44100,'channels':1,'simulated':True,'manufacturer_recording':False,'game_engine_ids':spec.get('game_engine_ids',[]),'clips':manifest},indent=2)+'\n')
    (a.output/'validation.json').write_text(json.dumps({'passed':True,'provenance':provenance,'exporter_source':json.loads((a.exporter_root/'source-provenance.json').read_text()),'commands':[command],'turbo_generated':False,'backfire_generated':False,'limits':['Simulation approximates a physical engine; not an authentic vehicle recording.','No turbo compressor, turbine or backfire source added.','Numerical loop/peak checks do not replace listening.'],'files':reports},indent=2)+'\n')
    print(json.dumps({'output':str(a.output),'wav':len(reports),'ogg':len(reports),'validation':'passed'}))
if __name__=='__main__':
    try:main()
    except Exception as e:print('Generation failed: '+str(e),file=sys.stderr);raise
