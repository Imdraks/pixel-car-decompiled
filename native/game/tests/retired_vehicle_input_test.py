#!/usr/bin/env python3
"""Verify retirement of Unbound 188, preserved backups and an empty-garage restart."""
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
def state():
 key('F12');files=list(captures.glob('capture-*.png.state'))
 if not files:raise RuntimeError('Missing capture state')
 return ini(max(files,key=lambda path:path.stat().st_mtime_ns))
def page(screen,node=None):
 s=state();return s['screen']==str(screen) and (node is None or s['rides_page']==str(node))
legacy='version=8\ncar=187\ncontent_source=0\naudio_source=0\npart_engine=1504\nrim=10100\n'
(data/'settings.ini').write_text('width=960\nheight=540\nfps=60\nvsync=0\nsound=0\n')
(data/'vehicles').mkdir();(data/'cars').mkdir()
(data/'profile.ini').write_text(legacy)
(data/'vehicles/pcr-unbound-085.ini').write_text('version=8\nvehicle_id=pcr-unbound-085\ncar=85\ncontent_source=0\npart_engine=1501\n')
old_inventory='version=1\nvehicle=pcr-unbound-187\nvehicle=pcr-unbound-085\n'
(data/'garage-inventory.ini').write_text(old_inventory)
(data/'cars/car-1.ini').write_text(legacy)
try:
 start();s=state();check('active_retired_vehicle_replaced_by_owned_086',s['vehicle_id']=='pcr-unbound-085' and s['garage_count']=='1')
 check('removed_car_frees_a_place','pcr-unbound-187' not in (data/'garage-inventory.ini').read_text())
 archived=ini(data/'vehicles/pcr-unbound-187.ini');check('retired_tune_preserved',archived['part_engine']=='1504' and archived['rim']=='10100')
 check('original_active_profile_backed_up_exactly',(data/'profile.ini.pre-retired-188.bak').read_text()==legacy)
 check('original_inventory_backed_up_exactly',(data/'garage-inventory.ini.pre-retired-188.bak').read_text()==old_inventory)
 key('b');key('Tab');xdo('keydown','ctrl');key('f');xdo('keyup','ctrl');xdo('type','--clearmodifiers','pcr-unbound-187');key('Return');key('Return');key('Return')
 check('showroom_cannot_reacquire_removed_model','pcr-unbound-187' not in (data/'garage-inventory.ini').read_text() and ini(data/'profile.ini')['vehicle_id']=='pcr-unbound-085');key('F12');key('Escape')
 key('F11');key('Return');check('archived_named_config_cannot_restore_retired_car',ini(data/'profile.ini')['vehicle_id']=='pcr-unbound-085' and (data/'cars/car-1.ini').read_text()==legacy);key('Escape');close()
 start();check('restart_keeps_086_and_exact_backups',state()['vehicle_id']=='pcr-unbound-085' and (data/'profile.ini.pre-retired-188.bak').read_text()==legacy and (data/'garage-inventory.ini.pre-retired-188.bak').read_text()==old_inventory);close()
 (data/'profile.ini').write_text(legacy);(data/'garage-inventory.ini').write_text('version=1\nvehicle=pcr-unbound-187\n')
 start();s=state();check('only_retired_car_leaves_empty_garage',s['garage_count']=='0' and 'vehicle=' not in (data/'garage-inventory.ini').read_text())
 check('removed_vehicle_not_active_in_empty_garage',s['vehicle_id']!='pcr-unbound-187');key('F12');close()
 (a.output/'report.json').write_text(json.dumps({'checks':checks},indent=2)+'\n');print('PASS:',len(checks),'actual vehicle-retirement input checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
