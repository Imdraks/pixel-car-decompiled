#!/usr/bin/env python3
"""Exercise eight-slot ownership, showroom, deletion, archives and all loading limits in the actual UI."""
import argparse,json,subprocess,time
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__)
for name in ['game','assets','xdotool','output']:p.add_argument('--'+name,type=Path,required=True)
a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False);data=a.output/'data';data.mkdir();captures=a.output/'captures';checks={}
def ini(path):return dict(line.split('=',1) for line in path.read_text().splitlines() if '=' in line)
def owned():return [line.split('=',1)[1] for line in (data/'garage-inventory.ini').read_text().splitlines() if line.startswith('vehicle=')]
def check(name,value):
 checks[name]=bool(value)
 if not value:raise RuntimeError(name)
def xdo(*args):return subprocess.check_output([str(a.xdotool),*map(str,args)],text=True,stderr=subprocess.DEVNULL).strip()
def key(k):xdo('keydown',k);time.sleep(.08);xdo('keyup',k);time.sleep(.12)
def click(x,y):xdo('mousemove','--window',window,round(x*.75),round(y*.75));time.sleep(.04);xdo('mousedown',1);time.sleep(.08);xdo('mouseup',1);time.sleep(.16)
def search(value):
 xdo('keydown','ctrl');key('f');key('a');xdo('keyup','ctrl');xdo('type','--clearmodifiers','--delay','1',value);time.sleep(.12);key('Return')
def start(free=False):
 global proc,window,log
 log=(a.output/'application.log').open('a');proc=subprocess.Popen([str(a.game),'--assets-dir',str(a.assets),'--data-dir',str(data),'--capture-dir',str(captures),'--no-audio']+(['--free-drive'] if free else []),stdout=log,stderr=log)
 for _ in range(150):
  if proc.poll() is not None:raise RuntimeError('Game exited at startup')
  try:window=xdo('search','--onlyvisible','--pid',proc.pid,'--name','Pixel Car Racer').splitlines()[0];xdo('windowfocus','--sync',window);break
  except (subprocess.CalledProcessError,IndexError):time.sleep(.04)
 else:raise RuntimeError('No window')
 for _ in range(30):
  before=len(list(captures.glob('*.png')));key('F12')
  if len(list(captures.glob('*.png')))>before:break
 time.sleep(.1)
def close():
 xdo('keydown','ctrl');key('q');xdo('keyup','ctrl');proc.wait(timeout=15);log.close();check('clean_exit_'+str(len(checks)),proc.returncode==0)
keys=['pcr-shared-000','pcr-shared-001','pcr-shared-002','pcr-unbound-003','pcr-shared-004','pcr-shared-005','pcr-unbound-006','pcr-shared-007','pcr-shared-008']
(data/'settings.ini').write_text('width=960\nheight=540\nfps=60\nvsync=0\nsound=0\n')
legacy='version=8\ncar=0\ncontent_source=0\npart_engine=1501\nrim=10100\nroll_cage=1\nfactory_initialized=1\nfactory_engine_id=-1\n'
(data/'profile.ini').write_text(legacy)
try:
 start();check('migration_owns_active_car',owned()==keys[:1]);original=ini(data/'profile.ini');check('legacy_tune_untouched',original['part_engine']=='1501' and original['rim']=='10100' and original['roll_cage']=='1')
 click(280,435);key('Tab')
 for identifier in keys[1:8]:search(identifier);key('Return')
 check('eight_cars_acquired',set(owned())==set(keys[:8]));check('acquisition_keeps_active_preparation',ini(data/'profile.ini')==original);key('F12')
 search(keys[8]);key('Return');click(1000,650);check('ninth_car_blocked_keyboard_and_mouse',len(owned())==8 and keys[8] not in owned());key('F12')
 key('Tab');search(keys[1]);key('Delete');key('F12');key('Escape');check('cancel_removal_preserves_inventory',len(owned())==8)
 # A named preparation is an alternate acquisition path, never a capacity bypass.
 imported=dict(original,vehicle_id=keys[8],car='8',part_engine='30008',factory_engine_id='30008',saved_name='Import neuvieme')
 (data/'cars').mkdir();(data/'cars/car-1.ini').write_text(''.join(k+'='+v+'\n' for k,v in imported.items()))
 key('Escape');click(280,500);key('F11');click(300,245);click(220,620)
 check('named_load_cannot_bypass_eight_slots',len(owned())==8 and ini(data/'profile.ini')==original)
 key('Escape');key('b');search(keys[1]);key('Delete');key('Return');check('remove_non_active_frees_one_slot',len(owned())==7 and keys[1] not in owned() and ini(data/'profile.ini')==original)
 key('Escape');key('F11');click(300,245);click(220,620);check('named_load_acquires_when_space_available',len(owned())==8 and keys[8] in owned() and ini(data/'profile.ini')['vehicle_id']==keys[8])
 key('b');search(keys[0]);key('Return');check('owned_selection_restores_configuration',ini(data/'profile.ini')==original)
 key('Right');check('customization_arrows_only_cycle_owned',ini(data/'profile.ini')['vehicle_id'] in owned() and ini(data/'profile.ini')['vehicle_id']!=keys[0] and len(owned())==8);key('Left');check('customization_cycle_restores_previous_tune',ini(data/'profile.ini')==original)
 key('b');search(keys[0]);key('Delete');key('Return');check('remove_active_switches_to_remaining_car',len(owned())==7 and keys[0] not in owned() and ini(data/'profile.ini')['vehicle_id'] in owned());check('removed_tune_archived',ini(data/'vehicles'/f'{keys[0]}.ini')==original)
 key('Tab');search(keys[0]);key('Return');key('Return');check('reacquisition_restores_archived_tune',len(owned())==8 and ini(data/'profile.ini')==original)
 key('b');key('F12');close();start();check('owned_inventory_survives_restart',len(owned())==8 and ini(data/'profile.ini')==original)
 click(280,435)
 for identifier in list(owned()):search(identifier);key('Delete');key('Return')
 check('all_cars_can_be_removed',owned()==[]);key('F12');check('archives_not_deleted',len(list((data/'vehicles').glob('*.ini')))>=9)
 key('Escape');click(280,355);close();check('empty_garage_blocks_driving',ini(data/'last-session.txt')['screen']=='7')
 start(free=True);check('empty_inventory_not_repopulated_on_restart',owned()==[]);key('F12');close();check('free_drive_shortcut_cannot_use_unowned_car',ini(data/'last-session.txt')['screen']=='7')
 start();click(280,435);key('Tab');search(keys[0]);key('Return');key('Return');check('showroom_recovers_from_empty_garage',owned()==keys[:1] and ini(data/'profile.ini')==original);close()
 check('inventory_backup_exists',(data/'garage-inventory.ini.bak').is_file())
 (a.output/'report.json').write_text(json.dumps({'checks':checks,'owned':owned(),'original_preparation':original},indent=2)+'\n');print('PASS:',len(checks),'actual showroom/ownership checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
