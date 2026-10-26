#!/usr/bin/env python3
"""Exercise the original-art PC garage with real mouse/keyboard input and saved profiles."""
import argparse,json,subprocess,time
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__)
for name in ['game','assets','xdotool','output']:p.add_argument('--'+name,type=Path,required=True)
p.add_argument('--with-audio',action='store_true');a=p.parse_args();a.output.mkdir(exist_ok=False,parents=True);data=a.output/'data';data.mkdir()
(data/'profile.ini').write_text('car=20\nrim=8\nautomatic=1\ndrive=1\n')
(data/'settings.ini').write_text('width=960\nheight=540\nfps=60\nvsync=0\nsound=0\ntraffic=0\n')
log=(a.output/'application.log').open('w');checks={};proc=None;window=None

def xdo(*v):return subprocess.check_output([str(a.xdotool),*map(str,v)],text=True,stderr=subprocess.DEVNULL).strip()
def ini(path):return dict(line.split('=',1) for line in path.read_text().splitlines() if '=' in line)
def check(name,value):
 checks[name]=bool(value)
 if not value:raise RuntimeError('Failed: '+name)
def start(free=False):
 global proc,window
 proc=subprocess.Popen([str(a.game),'--assets-dir',str(a.assets),'--data-dir',str(data),'--capture-dir',str(a.output/'captures')]+([] if a.with_audio else ['--no-audio'])+(['--free-drive'] if free else []),stdout=log,stderr=log)
 for _ in range(150):
  if proc.poll() is not None:raise RuntimeError('Application exited during startup')
  try:window=xdo('search','--onlyvisible','--pid',proc.pid,'--name','Pixel Car Racer').splitlines()[0]
  except subprocess.CalledProcessError:time.sleep(.04);continue
  result=subprocess.run([str(a.xdotool),'windowfocus','--sync',window],capture_output=True)
  if result.returncode==0:
   ready_after=time.time_ns()
   for _ in range(40):
    xdo('keydown','F12');time.sleep(.07);xdo('keyup','F12');time.sleep(.12)
    if any(path.stat().st_mtime_ns>=ready_after for path in (a.output/'captures').glob('capture-*.png')):return
    if proc.poll() is not None:raise RuntimeError('Application exited before its first frame')
   raise RuntimeError('No first rendered frame')
  time.sleep(.04)
 raise RuntimeError('Window never became ready')
def coordinates(x,y):
 geo=dict(line.split('=',1) for line in xdo('getwindowgeometry','--shell',window).splitlines());w,h=int(geo['WIDTH']),int(geo['HEIGHT']);scale=min(w/1280,h/720)
 return round((w-1280*scale)/2+x*scale),round((h-720*scale)/2+y*scale)
def move(x,y):x,y=coordinates(x,y);xdo('mousemove','--window',window,x,y);time.sleep(.06)
def click(x,y):move(x,y);xdo('mousedown',1);time.sleep(.07);xdo('mouseup',1);time.sleep(.14)
def key(k):xdo('keydown',k);time.sleep(.07);xdo('keyup',k);time.sleep(.10)
def search(value):
 xdo('keydown','ctrl');key('f');xdo('keyup','ctrl');xdo('type','--clearmodifiers','--delay','12',value);time.sleep(.2)
def close():
 xdo('keydown','ctrl');key('q');xdo('keyup','ctrl');proc.wait(timeout=15)
 return ini(data/'last-session.txt')
def profile():return ini(data/'profile.ini')
slots={'engine':('F1',881,0),'ecu':('F1',1126,4),'tires':('F2',1126,10),'suspension':('F5',881,1),'turbo':('F4',840,2),'supercharger':('F4',1003,3),'intercooler':('F4',1167,7),'nos':('F3',1003,5),'intake':('F6',840,6),'pistons':('F6',1003,8),'exhaust':('F6',1167,9)}
def equip(slot,name,id,index=0):
 f,x,_=slots[slot];key(f);click(x,250);search(name)
 if index:click(879+(index%2)*246,314+(index//2)*74)
 key('Return');check('equip_'+slot,profile()['part_'+slot]==str(id))
try:
 start();click(280,435);key('F12');key('Right');check('keyboard_changes_body',profile()['car']=='21');key('Left')
 equip('engine','2JZ',1002)
 key('F1');search('LT5');check('preview_does_not_equip',profile()['part_engine']=='1002');key('F12');search('SR20');key('Return');check('ctrl_f_replaces_existing_query',profile()['part_engine']=='1001')
 xdo('keydown','ctrl');key('f');key('a');xdo('keyup','ctrl');key('BackSpace');xdo('type','--clearmodifiers','2JZ');time.sleep(.2);key('Return');check('ctrl_a_and_backspace_edit_search',profile()['part_engine']=='1002');key('Escape')
 equip('suspension','VX Slams',2015,2)
 equip('turbo','Reddy T60E (Black Gem)',3026);equip('supercharger','WIPPLE (BLACK)',3020)
 check('compressor_removes_turbo',profile()['part_turbo']=='0')
 equip('ecu','SF Type R +VX FLUX',4008);equip('nos','Demon 250',5007);equip('intake','Carbon Pro X',6021);equip('intercooler','PR X Black',7013);equip('pistons','VX Concept X',8008);equip('exhaust','Short Pipe (Hood)',9048);equip('tires','NITTO SLICKS LARGE',10017)
 equip('turbo','Reddy T60E (Black Gem)',3026);check('turbo_removes_compressor',profile()['part_supercharger']=='0')
 key('F6');click(1167,250);key('Home');key('Next');key('Return');check('page_down_selects_next_page',profile()['part_exhaust']=='9003')
 move(1000,400);xdo('click',5);time.sleep(.2);key('Return');check('mouse_wheel_pages_inventory',profile()['part_exhaust']!='9003')
 equip('exhaust','Short Pipe (Hood)',9048)
 key('F2');key('End');key('Return');check('last_real_rim_equips',profile()['rim']=='42');key('F2');search('38');key('Return');check('effect_frame_cannot_equip',profile()['rim']=='42');search('09');key('Return');check('rims_equip_through_original_category',profile()['rim']=='8')
 key('F3');search('VX 50 Shot');move(879,314)
 for _ in range(2):xdo('mousedown',1);time.sleep(.06);xdo('mouseup',1);time.sleep(.08)
 check('double_click_equips',profile()['part_nos']=='5001');equip('nos','Demon 250',5007)
 key('F1');click(1050,578);key('Home');key('Right');key('Return');check('descending_sort_exposes_best_engine',profile()['part_engine']=='1014')
 click(77,670);maximum=profile();check('maximum_preparation_still_works',maximum['part_engine']=='1014' and maximum['part_turbo']=='3026' and maximum['part_nos']=='5007')
 key('F12');key('Escape');key('F12');click(245,518);click(930,281);click(930,335);click(930,390);key('F12')
 prefs=profile();check('sound_choices_save',prefs['sound_on']=='0' and prefs['sound_off']=='0' and prefs['bov']=='0');click(830,557)
 click(175,518);key('F12');click(910,615)
 click(111,518);click(150,489);check('gearbox_draft_does_not_save',profile()['gear_count']=='6');click(250,577);click(717,203);click(850,674)
 box=profile();check('ten_speed_and_ratio_buttons_save',box['gear_count']=='10' and float(box['gear_1'])>4.70)
 old=float(box['gear_1']);click(500,203);click(760,582);click(850,674);box=profile();check('ratio_and_final_drive_sliders_work',float(box['gear_1'])!=old and abs(float(box['final_drive'])-3.15)>.1)
 click(53,577);click(850,674);check('gear_count_selector',profile()['gear_count']=='9');click(150,489);click(850,674);click(150,269);click(400,674)
 check('gearbox_cancel_discards_draft',profile()['gear_count']=='10');click(111,518);click(615,674);click(850,674);check('gearbox_reset_restores_six',profile()['gear_count']=='6')
 click(150,489);click(850,674);key('F12');click(1140,45)
 # Use a 4:3 window and then Full HD. Hit testing must follow letterboxing/scaling.
 xdo('windowsize','--sync',window,1200,900);xdo('windowmove','--sync',window,0,0);time.sleep(.4);key('F1');click(1126,250);search('VX Speed +2STEP');key('Return');check('letterboxed_mouse_and_keyboard_work',profile()['part_ecu']=='4002');equip('ecu','SF Type R +VX FLUX',4008);key('F12');key('Escape')
 xdo('windowsize','--sync',window,1920,1080);xdo('windowmove','--sync',window,0,0);time.sleep(.4);key('F2');click(1126,250);search('Low Pro 17');click(879,314);key('Return');check('full_hd_category_hit_testing',profile()['part_tires']=='10002');equip('tires','NITTO SLICKS LARGE',10017);key('F12');key('Escape')
 click(1215,105);xdo('keydown','space');time.sleep(1);stationary=close();xdo('keyup','space')
 check('space_does_not_accelerate',float(stationary['distance_m'])==0 and float(stationary['speed_mps'])==0)
 check('space_activates_handbrake',stationary['handbraking']=='1')
 start(True);xdo('keydown','w');time.sleep(2);baseline=close();xdo('keyup','w');check('ten_speed_reaches_driving',baseline['gear_count']=='10')
 start(True);xdo('keydown','w');time.sleep(2);xdo('keydown','space');xdo('keydown','n');time.sleep(.5);key('F12');time.sleep(.5);braked=close();xdo('keyup','n');xdo('keyup','space');xdo('keyup','w')
 check('handbrake_slows_actual_vehicle',float(braked['speed_mps'])<float(baseline['speed_mps'])-1)
 check('handbrake_overrides_throttle_and_nos',braked['handbraking']=='1' and braked['nitro_active']=='0' and float(braked['nitro_remaining'])==10 and float(braked['current_hp'])==0)
 check('rear_wheels_lock_while_vehicle_moves',float(braked['rear_roll_m'])<float(braked['distance_m']))
 check('equipment_and_gearbox_survive_restart',braked['engine_part']=='1014' and braked['tire_part']=='10017' and braked['gear_count']=='10')
 (a.output/'report.json').write_text(json.dumps({'checks':checks,'maximum':maximum,'gearbox':profile(),'stationary':stationary,'baseline':baseline,'handbrake':braked},indent=2)+'\n');print(json.dumps(checks,indent=2))
finally:
 for k in ['w','space','n','ctrl']:subprocess.run([str(a.xdotool),'keyup',k],capture_output=True)
 if proc is not None and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
 log.close()
