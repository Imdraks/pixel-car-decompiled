#!/usr/bin/env python3
"""Verify distinct Lamborghini models and recovery of the previously removed Huracan."""
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
(data/'settings.ini').write_text('width=960\nheight=540\nfps=60\nvsync=0\nsound=0\n')
(data/'vehicles').mkdir();(data/'cars').mkdir()
aventador='version=8\nvehicle_id=pcr-unbound-085\ncar=85\ncontent_source=0\naudio_source=0\npart_engine=1501\n'
huracan='version=8\nvehicle_id=pcr-unbound-187\ncar=187\ncontent_source=0\naudio_source=0\npart_engine=1504\nrim=10100\nsaved_name=Ancienne configuration 188\n'
(data/'profile.ini').write_text(aventador);(data/'garage-inventory.ini').write_text('version=1\nvehicle=pcr-unbound-085\n')
(data/'vehicles/pcr-unbound-085.ini').write_text(aventador);(data/'vehicles/pcr-unbound-187.ini').write_text(huracan);(data/'cars/car-1.ini').write_text(huracan)
backup='version=1\nvehicle=pcr-unbound-187\nvehicle=pcr-unbound-085\n';(data/'garage-inventory.ini.pre-retired-188.bak').write_text(backup);(data/'profile.ini.pre-retired-188.bak').write_text(huracan)
def choose_vehicle(identifier,showroom=False):
 key('b')
 if showroom:key('Tab')
 xdo('keydown','ctrl');key('f');xdo('keyup','ctrl');xdo('type','--clearmodifiers','--delay','15',identifier);key('Return');key('Return')
 if showroom:key('Return')
try:
 start();s=state();check('post_retirement_garage_does_not_auto_add_cars',s['vehicle_id']=='pcr-unbound-085' and s['garage_count']=='1')
 choose_vehicle('pcr-unbound-187',True);s=state();check('huracan_available_in_showroom_and_selectable',s['vehicle_id']=='pcr-unbound-187' and s['garage_count']=='2')
 current=ini(data/'profile.ini');check('huracan_restores_archived_v12_and_rims',current['part_engine']=='1504' and current['rim']=='10100');key('F1');key('F12');key('Escape')
 choose_vehicle('pcr-unbound-085');check('aventador_remains_a_separate_owned_model',state()['vehicle_id']=='pcr-unbound-085' and ini(data/'profile.ini')['part_engine']=='1501');key('F1');key('F12');key('Escape')
 check('backups_preserved_exactly',(data/'garage-inventory.ini.pre-retired-188.bak').read_text()==backup and (data/'profile.ini.pre-retired-188.bak').read_text()==huracan);close()
 start();s=state();check('both_models_persist_after_restart',s['vehicle_id']=='pcr-unbound-085' and s['garage_count']=='2')
 key('F11');click(300,245);click(220,620);s=state();check('old_named_huracan_config_loads_again',s['vehicle_id']=='pcr-unbound-187' and ini(data/'profile.ini')['part_engine']=='1504');key('F12')
 choose_vehicle('pcr-unbound-186-ford-gt-2017',True);s=state();current=ini(data/'profile.ini');check('ford_gt_2017_is_a_third_distinct_model',s['vehicle_id']=='pcr-unbound-186-ford-gt-2017' and s['garage_count']=='3')
 check('ford_visual_variant_and_stock_v6_are_active',current['visual_variant']=='1' and current['part_engine']=='20077' and s['vehicle_base_kit']=='7' and s['vehicle_audio_engine']=='20077');key('F1');key('F12');key('Escape')
 key('F11');name('GT 2017 personnelle');key('Return');check('named_ford_save_preserves_independent_variant',ini(data/'cars/car-2.ini')['visual_variant']=='1' and ini(data/'cars/car-2.ini')['vehicle_id']=='pcr-unbound-186-ford-gt-2017');key('Escape');close()
 start();s=state();check('ford_variant_and_three_car_inventory_survive_restart',s['vehicle_id']=='pcr-unbound-186-ford-gt-2017' and s['vehicle_variant']=='1' and s['garage_count']=='3');close()
 check('both_stable_per_vehicle_files_preserved',(data/'vehicles/pcr-unbound-085.ini').exists() and (data/'vehicles/pcr-unbound-187.ini').exists())
 (a.output/'report.json').write_text(json.dumps({'checks':checks},indent=2)+'\n');print('PASS:',len(checks),'actual Lamborghini identity/recovery input checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
