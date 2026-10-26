#!/usr/bin/env python3
"""Exercise real customization controls, equipment persistence and free drive via XTest."""
import argparse,json,subprocess,time
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__)
for name in ['game','assets','xdotool','output']:p.add_argument('--'+name,type=Path,required=True)
p.add_argument('--with-audio',action='store_true')
a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False);data=a.output/'data';data.mkdir()
(data/'profile.ini').write_text('car=20\nrim=8\nautomatic=1\ndrive=1\n')
log=(a.output/'application.log').open('w');checks={}
def xdo(*v):return subprocess.check_output([str(a.xdotool),*map(str,v)],text=True).strip()
def ini(path):return dict(line.split('=',1) for line in path.read_text().splitlines() if '=' in line)
def start(free=False):
 proc=subprocess.Popen([str(a.game),'--assets-dir',str(a.assets),'--data-dir',str(data),'--capture-dir',str(a.output/'captures'),'--safe-mode']+([] if a.with_audio else ['--no-audio'])+(['--free-drive'] if free else []),stdout=log,stderr=log)
 for _ in range(100):
  if proc.poll() is not None:raise RuntimeError('Application exited during startup')
  try:window=xdo('search','--pid',proc.pid,'--name','Pixel Car Racer').splitlines()[0];break
  except subprocess.CalledProcessError:time.sleep(.05)
 else:raise RuntimeError('Window not found')
 xdo('windowfocus','--sync',window);time.sleep(.2)
 return proc,window
proc,window=start()
def click(x,y):
 geo=dict(line.split('=',1) for line in xdo('getwindowgeometry','--shell',window).splitlines());w,h=int(geo['WIDTH']),int(geo['HEIGHT']);scale=min(w/1280,h/720)
 xdo('mousemove','--window',window,round((w-1280*scale)/2+x*scale),round((h-720*scale)/2+y*scale));xdo('mousedown',1);time.sleep(.06);xdo('mouseup',1);time.sleep(.12)
def key(k):xdo('keydown',k);time.sleep(.06);xdo('keyup',k);time.sleep(.08)
def quit_game():xdo('keydown','ctrl');key('q');xdo('keyup','ctrl');proc.wait(timeout=10)
def equip(slot,name,id,row=0):
 click(140,124+slot*43);xdo('type','--clearmodifiers','--delay','15',name);time.sleep(.2)
 click(500,177+row*53);click(1050,460)
 profile=ini(data/'profile.ini');key=['engine','suspension','turbo','supercharger','ecu','nos','intake','intercooler','pistons','exhaust','tires'][slot]
 checks['equip_'+key]=profile['part_'+key]==str(id)
 if not checks['equip_'+key]:raise RuntimeError('Equipment was not applied: '+name+' '+str(profile))
try:
 click(280,503)
 equip(0,'2JZ',1002);key('F12')
 equip(1,'VX Slams',2015,2)
 equip(2,'Reddy T60E (Black Gem)',3026)
 equip(3,'WIPPLE (BLACK)',3020)
 checks['supercharger_replaces_turbo']=ini(data/'profile.ini')['part_turbo']=='0'
 equip(4,'SF Type R +VX FLUX',4008)
 equip(5,'Demon 250',5007)
 equip(6,'Carbon Pro X',6021)
 equip(7,'PR X Black',7013)
 equip(8,'VX Concept X',8008)
 click(140,124+9*43);click(814,615);click(500,177);click(1050,460)
 checks['exhaust_pagination']=ini(data/'profile.ini')['part_exhaust']=='9008'
 equip(9,'Short Pipe (Hood)',9048)
 equip(10,'NITTO SLICKS LARGE',10017);key('F12')
 equip(2,'Reddy T60E (Black Gem)',3026)
 checks['turbo_replaces_supercharger']=ini(data/'profile.ini')['part_supercharger']=='0'
 click(1050,674);click(930,281);click(930,335);click(930,390);key('F12')
 
 if a.with_audio:
  click(400,455);time.sleep(.25);click(620,455);time.sleep(.25);click(840,455);time.sleep(.1)
 prefs=ini(data/'profile.ini');checks['audio_choices_saved']=prefs['sound_on']=='0' and prefs['sound_off']=='0' and prefs['bov']=='0'
 click(830,557);click(1140,45);key('F12')
 click(1015,605);xdo('keydown','w');xdo('keydown','n');time.sleep(3);key('F12');xdo('keyup','n');xdo('keyup','w')
 quit_game();session=ini(data/'last-session.txt');profile=ini(data/'profile.ini')
 checks['drives_with_equipment']=float(session['distance_m'])>10 and session['engine_part']=='1002' and session['tire_part']=='10017'
 checks['equipment_changes_native_torque']=float(session['native_torque_nm'])>500
 if a.with_audio:checks['original_audio_backend_ready']=session['audio_ready']=='1' and session['audio_failures']=='0'
 proc,window=start(True);xdo('keydown','w');time.sleep(.5);xdo('keyup','w');quit_game()
 resumed=ini(data/'last-session.txt')
 checks['equipment_survives_restart']=resumed['engine_part']=='1002' and resumed['tire_part']=='10017' and resumed['native_torque_nm']==session['native_torque_nm']
 (a.output/'report.json').write_text(json.dumps({'audio_requested':a.with_audio,'checks':checks,'profile':profile,'session':session,'resumed':resumed},indent=2)+'\n')
 print(json.dumps(checks,indent=2))
 if not all(checks.values()):raise SystemExit(1)
finally:
 if proc.poll() is None:proc.terminate();proc.wait(timeout=10)
 log.close()
