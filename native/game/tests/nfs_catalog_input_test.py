#!/usr/bin/env python3
"""Exercise workbook engines, new parts, powertrain compatibility and named saves with real input."""
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
(data/'settings.ini').write_text('width=960\nheight=540\nfps=60\nvsync=0\nsound=0\n')
(data/'profile.ini').write_text('version=6\ncar=6\ncontent_source=0\naudio_source=0\n')
try:
 start();key('F1');equip_search('NFS I6 2.6L 276');check('workbook_engine_search_and_equip',ini(data/'profile.ini')['part_engine']=='20049')
 key('F6');click(1185,253);equip_search('Elite');check('fuel_category_equips_elite',ini(data/'profile.ini')['part_fuel']=='21014')
 key('F5');click(1185,253);equip_search('Contrebande');before=ini(data/'profile.ini');check('gearbox_category_equips_ten_speed',before['part_gearbox']=='22015' and before['gear_count']=='10')
 key('F5');click(942,253);equip_search('Contrebande');check('brakes_category_equips_contraband',ini(data/'profile.ini')['part_brakes']=='22012')
 key('F11');name('NFS R34');key('Return');ice=ini(data/'cars/car-1.ini');check('expanded_parts_saved_with_named_car',ice['part_fuel']=='21014' and ice['part_gearbox']=='22015' and ice['part_brakes']=='22012');key('Escape')
 key('F1');equip_search('NFS Electrique 751');ev=ini(data/'profile.ini');check('electric_swap_removes_thermal_parts',ev['part_engine']=='20000' and ev['part_fuel']=='0')
 key('F1');click(1167,253);click(942,253);equip_search('Elite');check('electric_system_equips_elite',ini(data/'profile.ini')['part_electrical']=='21047')
 key('F11');name('EV 751');key('Return');electric=ini(data/'cars/car-2.ini');check('electric_named_save_preserves_combustion_car',ini(data/'cars/car-1.ini')==ice and electric['part_engine']=='20000' and electric['part_electrical']=='21047');key('F12');close()
 start();check('new_categories_persist_after_restart',ini(data/'profile.ini')['part_electrical']=='21047');key('F11');click(300,245);click(220,620);check('named_load_restores_thermal_build',ini(data/'profile.ini')==ice);key('F12');close()
 (a.output/'report.json').write_text(json.dumps({'checks':checks,'combustion_car':ice,'electric_car':electric},indent=2)+'\n');print('PASS:',len(checks),'actual spreadsheet customization checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
