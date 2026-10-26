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
 checks['exhaust_pagination']=ini(data/'profile.ini')['part_exhaust']=='9001'
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
 proc,window=start();click(280,503)
 click(450,660) # strongest-first sorting; base entry remains first
 click(500,230);click(1050,460)
 checks['descending_sort_exposes_strongest_engine']=ini(data/'profile.ini')['part_engine']=='1014'
 click(140,600);maximum=ini(data/'profile.ini')
 checks['maximum_preparation_equips_all_slots']=maximum['part_engine']=='1014' and maximum['part_turbo']=='3026' and maximum['part_supercharger']=='0' and maximum['part_nos']=='5007' and all(maximum['part_'+k]!='0' for k in ['suspension','ecu','intake','intercooler','pistons','exhaust','tires'])
 key('F12');click(630,659);key('F12');key('Escape')
 click(1050,617);xdo('keydown','w');xdo('keydown','n');time.sleep(2);xdo('keyup','n');xdo('keyup','w');quit_game()
 max_session=ini(data/'last-session.txt')
 checks['maximum_power_is_used_in_free_drive']=float(max_session['native_hp'])>4200 and float(max_session['native_nos_hp'])>4500 and max_session['engine_part']=='1014'
 proc,window=start();click(280,503);click(780,659);click(150,489)
 checks['gearbox_draft_does_not_save_early']=ini(data/'profile.ini')['gear_count']=='6'
 click(250,577);click(717,203);click(850,674)
 gearbox=ini(data/'profile.ini');checks['ten_gears_and_ratio_buttons_save']=gearbox['gear_count']=='10' and float(gearbox['gear_1'])>4.70
 old_ratio=float(gearbox['gear_1']);click(500,203);click(760,582);click(850,674)
 gearbox=ini(data/'profile.ini');checks['gear_and_final_drive_sliders_save']=float(gearbox['gear_1'])!=old_ratio and abs(float(gearbox['final_drive'])-3.15)>.1
 click(53,577);click(850,674);checks['gear_count_selector_changes_box']=ini(data/'profile.ini')['gear_count']=='9'
 click(150,489);click(850,674);click(150,269);click(400,674)
 checks['cancel_discards_unsaved_gearbox']=ini(data/'profile.ini')['gear_count']=='10'
 click(780,659);click(615,674);click(850,674);checks['gearbox_reset_restores_six_gears']=ini(data/'profile.ini')['gear_count']=='6'
 click(150,489);click(850,674);key('F12');click(1100,674);xdo('keydown','w');time.sleep(.5);xdo('keyup','w');quit_game()
 transmission_session=ini(data/'last-session.txt');checks['ten_speed_reaches_actual_driving']=transmission_session['gear_count']=='10' and abs(float(transmission_session['final_drive'])-3.15)<.001
 proc,window=start(True);time.sleep(.3);quit_game();transmission_resumed=ini(data/'last-session.txt')
 checks['ten_speed_survives_restart']=transmission_resumed['gear_count']=='10' and transmission_resumed['final_drive']==transmission_session['final_drive']
 (a.output/'report.json').write_text(json.dumps({'audio_requested':a.with_audio,'checks':checks,'profile':profile,'session':session,'resumed':resumed,'maximum':maximum,'maximum_session':max_session,'gearbox':gearbox,'transmission_session':transmission_session,'transmission_resumed':transmission_resumed},indent=2)+'\n')
 print(json.dumps(checks,indent=2))
 if not all(checks.values()):raise SystemExit(1)
finally:
 if proc.poll() is None:proc.terminate();proc.wait(timeout=10)
 log.close()
