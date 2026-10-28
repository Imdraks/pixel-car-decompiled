#!/usr/bin/env python3
"""Exercise named car storage, loading, updates and restart with real mouse/keys."""
import argparse,json,subprocess,time
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__)
for key in ['game','assets','xdotool','output']:p.add_argument('--'+key,type=Path,required=True)
a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False);data=a.output/'data';data.mkdir();captures=a.output/'captures';checks={}
def ini(path):return dict(line.split('=',1) for line in path.read_text().splitlines() if '=' in line)
def check(name,value):
 checks[name]=bool(value)
 if not value:raise RuntimeError(name)
def xdo(*args):return subprocess.check_output([str(a.xdotool),*map(str,args)],text=True,stderr=subprocess.DEVNULL).strip()
def key(k):xdo('keydown',k);time.sleep(.08);xdo('keyup',k);time.sleep(.12)
def click(x,y):xdo('mousemove','--window',window,round(x*.75),round(y*.75));time.sleep(.05);xdo('mousedown',1);time.sleep(.08);xdo('mouseup',1);time.sleep(.15)
def name(value):click(300,155);xdo('keydown','ctrl');key('a');xdo('keyup','ctrl');xdo('type','--clearmodifiers','--delay','100',value);time.sleep(.1)
def start():
 global proc,window,log
 log=(a.output/'application.log').open('a');proc=subprocess.Popen([str(a.game),'--assets-dir',str(a.assets),'--data-dir',str(data),'--capture-dir',str(captures),'--no-audio'],stdout=log,stderr=log)
 for _ in range(150):
  if proc.poll() is not None:raise RuntimeError('Game exited at startup')
  try:window=xdo('search','--onlyvisible','--pid',proc.pid,'--name','Pixel Car Racer').splitlines()[0];xdo('windowfocus','--sync',window);break
  except (subprocess.CalledProcessError,IndexError):time.sleep(.04)
 else:raise RuntimeError('No window')
 for _ in range(30):
  before=len(list(captures.glob('*.png')));key('F12')
  if len(list(captures.glob('*.png')))>before:break
 click(280,500)
def close():
 xdo('keydown','ctrl');key('q');xdo('keyup','ctrl');proc.wait(timeout=15);log.close();check('clean_exit_'+str(len(checks)),proc.returncode==0)
def amg():
 key('F1');xdo('keydown','ctrl');key('f');xdo('keyup','ctrl');xdo('type','--clearmodifiers','AMG GT63');time.sleep(.2);key('Return');key('Escape')
 check('amg_equipped_'+str(len(checks)),ini(data/'profile.ini')['part_engine']=='1501')
(data/'settings.ini').write_text('width=960\nheight=540\nfps=60\nvsync=0\nsound=0\n')
(data/'profile.ini').write_text('version=6\ncar=20\nrim=10100\nrear_rim=10101\npart_engine=1008\npart_turbo=3026\npart_ecu=4008\npart_nos=5007\ncosmetic_6=106011\ncontent_source=1\naudio_source=1\nroll_cage=1\nheadlights=1\nsound_on=-1\nsound_off=-1\nbov=3\nfactory_drive=0\ndrive=1\ngear_count=10\ngear_1=4.7\ngear_2=2.99\ngear_3=2.15\ngear_4=1.8\ngear_5=1.52\ngear_6=1.28\ngear_7=1\ngear_8=0.85\ngear_9=0.69\ngear_10=0.64\nfinal_drive=3.15\nshift_seconds=0.12\nride_height_mm=-20\nspring_stiffness=1.6\ndamping_ratio=0.9\nfront_bias=-0.1\nallow_wheelie=1\nwheelie_tune=0.2\n')
try:
 start();key('F12');key('F11');key('F12');name('Drag été ZG');key('F12');key('Return');key('F12');first=ini(data/'cars/car-1.ini');baseline=ini(data/'profile.ini');check('named_car_saved',first==baseline and first['saved_name']=='Drag été ZG');key('F12')
 key('Escape');amg();key('b');key('Tab');xdo('keydown','ctrl');key('f');xdo('keyup','ctrl');xdo('type','--clearmodifiers','pcr-shared-001');key('Return');key('Return');key('Return');key('F11');name('AMG Cruise');key('Return');second=ini(data/'cars/car-2.ini');check('second_car_keeps_first',len(list((data/'cars').glob('*.ini')))==2 and ini(data/'cars/car-1.ini')==first and second['car']!=first['car'])
 click(300,245);click(220,620);check('full_first_config_restored',ini(data/'profile.ini')==first)
 amg();key('F11');click(300,245);name('Drag Updated');click(530,620);updated=ini(data/'cars/car-1.ini');check('update_targets_selected_slot',updated['part_engine']=='1501' and updated['saved_name']=='Drag Updated');check('update_keeps_previous_config',ini(data/'cars/car-1.ini.bak')==first)
 key('F12');close();start();key('F11');key('F12');click(890,245);click(220,620);check('cars_persist_after_restart',ini(data/'profile.ini')==second);close()
 (a.output/'report.json').write_text(json.dumps({'checks':checks,'full_configuration':first,'second_configuration':second,'updated_configuration':updated},indent=2)+'\n');print('PASS:',len(checks),'actual saved-car input checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
