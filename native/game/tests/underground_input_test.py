#!/usr/bin/env python3
"""Exercise per-vehicle identities, factory migration, universal swaps and independent automatic storage."""
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
def name(value):click(300,155);xdo('keydown','ctrl');key('a');xdo('keyup','ctrl');xdo('type','--clearmodifiers','--delay','25',value);time.sleep(.1)
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
def equip_search(value):
 xdo('keydown','ctrl');key('f');xdo('keyup','ctrl');xdo('type','--clearmodifiers','--delay','25',value);time.sleep(.2);key('Return');key('Escape')
def choose_vehicle(identifier):
 already=identifier in (data/'garage-inventory.ini').read_text()
 key('b');key('Tab');xdo('keydown','ctrl');key('f');xdo('keyup','ctrl');xdo('type','--clearmodifiers','--delay','60',identifier);time.sleep(.2);key('Return');key('Return')
 if not already:key('Return')
(data/'settings.ini').write_text('width=960\nheight=540\nfps=60\nvsync=0\nsound=0\n')
legacy='version=7\ncar=0\ncontent_source=0\naudio_source=0\n'
(data/'profile.ini').write_text(legacy)
try:
 start();original=ini(data/'profile.ini')
 choose_vehicle('pcr-underground-007');u=ini(data/'profile.ini');check('underground_vehicle_acquired',u['vehicle_id']=='pcr-underground-007' and u['content_source']=='2' and u['audio_source']=='2')
 key('F1');equip_search('Unbound I6 2.6L 276');check('unbound_engine_universal_on_underground',ini(data/'profile.ini')['part_engine']=='20049')
 key('F7');equip_search('Underground');check('underground_paint_selected',int(ini(data/'profile.ini')['cosmetic_0'])>=600000)
 key('F2');equip_search('Drag Steelie Underground');check('underground_rim_selected',int(ini(data/'profile.ini')['rim'])>=200000);key('F12')
 prepared=ini(data/'profile.ini');close();start();check('underground_preparation_survives_restart',ini(data/'profile.ini')==prepared)
 choose_vehicle('pcr-shared-000');check('original_preparation_unchanged',ini(data/'profile.ini')==original)
 choose_vehicle('pcr-underground-007');check('underground_preparation_restored',ini(data/'profile.ini')==prepared);close()
 (a.output/'report.json').write_text(json.dumps({'checks':checks,'underground':prepared},indent=2)+'\n');print('PASS:',len(checks),'actual Underground import input checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
