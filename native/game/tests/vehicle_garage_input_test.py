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
 start();initial=ini(data/'profile.ini');check('untouched_legacy_gets_factory_engine',initial['part_engine']=='30000' and initial['factory_initialized']=='1' and initial['vehicle_id']=='pcr-shared-000')
 check('immutable_pre_migration_backup', (data/'profile.ini.pre-vehicles-v1.bak').read_text()==legacy)
 key('F1');equip_search('AMG GT63');key('F8');first_config=ini(data/'profile.ini');check('first_vehicle_customized',first_config['part_engine']=='1501' and first_config['roll_cage']=='1')
 choose_vehicle('pcr-shared-001');b=ini(data/'profile.ini');check('different_vehicle_keeps_factory_not_previous_tune',b['vehicle_id']=='pcr-shared-001' and b['part_engine']=='30001' and b['roll_cage']=='0')
 key('F1');equip_search('Unbound I6 2.6L 276');check('nfs_engine_universal_on_other_model',ini(data/'profile.ini')['part_engine']=='20049')
 choose_vehicle('pcr-shared-000');check('first_preparation_restored',ini(data/'profile.ini')==first_config)
 key('F11');name('Independent A');key('Return');named=ini(data/'cars/car-1.ini');key('Escape');choose_vehicle('pcr-shared-001');second=ini(data/'profile.ini');check('second_preparation_restored',second['part_engine']=='20049' and second['roll_cage']=='0');key('F12');close()
 start();check('active_vehicle_survives_restart',ini(data/'profile.ini')==second);choose_vehicle('pcr-shared-000');check('other_vehicle_survives_restart',ini(data/'profile.ini')==named)
 choose_vehicle('pcr-shared-001');key('F11');click(300,245);click(220,620);check('named_profile_load_restores_its_vehicle',ini(data/'profile.ini')==named)
 choose_vehicle('pcr-shared-001');check('named_load_does_not_pollute_other_vehicle',ini(data/'profile.ini')==second)
 key('b');click(1220,140);key('F12');key('Escape');close()
 check('separate_automatic_files',len(list((data/'vehicles').glob('*.ini')))==2)
 check('original_migration_backup_preserved', (data/'profile.ini.pre-vehicles-v1.bak').read_text()==legacy)
 (a.output/'report.json').write_text(json.dumps({'checks':checks,'legacy':legacy,'first_vehicle':first_config,'second_vehicle':second,'named':named},indent=2)+'\n');print('PASS:',len(checks),'actual independent vehicle input checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
