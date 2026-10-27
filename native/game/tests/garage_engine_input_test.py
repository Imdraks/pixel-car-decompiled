#!/usr/bin/env python3
"""Exercise garage ignition/revving and text-focus protection with real keys."""
import argparse,json,subprocess,time
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__)
for name in ['game','assets','xdotool','output']:p.add_argument('--'+name,type=Path,required=True)
p.add_argument('--with-audio',action='store_true');a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False)
checks={};sessions={}
def check(name,value):
 checks[name]=bool(value)
 if not value:raise RuntimeError('Failed: '+name)
def scenario(name,actions):
 root=a.output/name;root.mkdir()
 (root/'profile.ini').write_text('car=20\npart_engine=1002\nsound_on=-1\nsound_off=-1\n')
 (root/'settings.ini').write_text('width=960\nheight=540\nfps=60\nvsync=0\nsound=1\ntraffic=0\n')
 def xdo(*args):return subprocess.check_output([str(a.xdotool),*map(str,args)],text=True,stderr=subprocess.DEVNULL).strip()
 def key(k):xdo('keydown',k);time.sleep(.07);xdo('keyup',k);time.sleep(.1)
 held=set()
 with (root/'application.log').open('w') as log:
  proc=subprocess.Popen([str(a.game),'--assets-dir',str(a.assets),'--data-dir',str(root),'--capture-dir',str(root/'captures')]+([] if a.with_audio else ['--no-audio']),stdout=log,stderr=log)
  try:
   for _ in range(150):
    if proc.poll() is not None:raise RuntimeError('Game exited before startup')
    try:window=xdo('search','--onlyvisible','--pid',proc.pid,'--name','Pixel Car Racer').splitlines()[0];xdo('windowfocus','--sync',window);break
    except (subprocess.CalledProcessError,IndexError):time.sleep(.04)
   else:raise RuntimeError('No window')
   for _ in range(40):
    key('F12')
    if list((root/'captures').glob('*.png')):break
   else:raise RuntimeError('No rendered frame')
   xdo('mousemove','--window',window,210,326);time.sleep(.06);xdo('mousedown',1);time.sleep(.08);xdo('mouseup',1);time.sleep(.25)
   for keyname,down,duration in actions:
    xdo('keydown' if down else 'keyup',keyname)
    if down:held.add(keyname)
    else:held.discard(keyname)
    time.sleep(duration)
   key('F12');xdo('keydown','ctrl');key('q');xdo('keyup','ctrl');proc.wait(timeout=15)
   check(name+'_clean_exit',proc.returncode==0)
   state=dict(line.split('=',1) for line in (root/'last-session.txt').read_text().splitlines() if '=' in line);sessions[name]=state
   if name!='leave_garage':check(name+'_entered_garage',state['screen'] in {'1','3'})
   check(name+'_no_vehicle_motion',float(state['distance_m'])==0 and float(state['front_roll_m'])==0 and float(state['rear_roll_m'])==0)
   if a.with_audio:check(name+'_audio_backend_valid',state['audio_ready']=='1' and state['audio_failures']=='0')
   return state
  finally:
   for keyname in held|{'ctrl','q','F12'}:subprocess.run([str(a.xdotool),'keyup',keyname],capture_output=True)
   if proc.poll() is None:proc.terminate();proc.wait(timeout=15)
g=[('g',True,.08),('g',False,.2)]
s=scenario('off_throttle',[('z',True,1.2)]);check('z_does_not_start_engine',s['garage_engine_running']=='0' and float(s['garage_engine_rpm'])==0)
s=scenario('ignition_idle',g);check('g_starts_idle',s['garage_engine_running']=='1' and 500<float(s['garage_engine_rpm'])<1500)
s=scenario('held_rev',g+[('z',True,1.5)]);check('z_reaches_limiter',s['garage_engine_limiter']=='1' and float(s['garage_engine_rpm'])>7000)
s=scenario('released_rev',g+[('z',True,1.5),('z',False,1.6)]);check('release_returns_to_idle',s['garage_engine_running']=='1' and s['garage_engine_limiter']=='0' and float(s['garage_engine_rpm'])<1500)
s=scenario('ignition_off',g+[('z',True,1.2)]+g);check('g_stops_even_with_z_held',s['garage_engine_running']=='0' and float(s['garage_engine_rpm'])==0)
focus=[('ctrl',True,.05),('f',True,.07),('f',False,.1),('ctrl',False,.1)]
s=scenario('search_off',focus+g+[('z',True,.8)]);check('typing_g_z_does_not_start_engine',s['garage_engine_running']=='0')
s=scenario('search_running',g+focus+g+[('z',True,1.1)]);check('search_suppresses_ignition_and_throttle',s['garage_engine_running']=='1' and float(s['garage_engine_rpm'])<1500)
s=scenario('leave_garage',g+[('Escape',True,.08),('Escape',False,.3)]);check('leaving_garage_stops_engine',s['garage_engine_running']=='0' and float(s['garage_engine_rpm'])==0)
(a.output/'report.json').write_text(json.dumps({'checks':checks,'sessions':sessions},indent=2)+'\n')
print('PASS:',len(checks),'actual garage ignition/revving input checks')
