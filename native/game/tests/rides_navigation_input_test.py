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
def state():
 key('F12');files=list(captures.glob('capture-*.png.state'))
 if not files:raise RuntimeError('Missing capture state')
 return ini(max(files,key=lambda path:path.stat().st_mtime_ns))
def page(screen,node=None):
 s=state();return s['screen']==str(screen) and (node is None or s['rides_page']==str(node))
(data/'settings.ini').write_text('width=960\nheight=540\nfps=60\nvsync=0\nsound=0\n')
(data/'profile.ini').write_text('version=8\ncar=0\ncontent_source=0\n')
try:
 start();initial=ini(data/'profile.ini');s=state();check('customization_opens_home_first',s['screen']=='8' and s['rides_page']=='0' and s['rides_depth']=='0' and s['entry_count']=='4' and s['rides_selection']=='0')
 key('Return');check('single_enter_opens_only_style_menu',page(8,1) and state()['rides_depth']=='1')
 key('Return');check('style_body_has_own_menu',page(8,2) and state()['entry_count']=='3')
 key('Return');s=state();check('body_kits_opens_actual_kit_catalogue',s['screen']=='3' and s['inventory_open']=='1' and s['cosmetic_slot']=='4' and s['cosmetic_picker']=='1')
 check('entering_leaf_does_not_change_preparation',ini(data/'profile.ini')==initial)
 key('Escape');check('escape_leaf_restores_body_parent',page(8,2) and state()['rides_selection']=='0')
 key('Down');key('Down');key('Return');check('stance_is_reached_through_body_menu',page(9))
 click(447,173);s=state();check('stance_adjustment_is_only_a_draft',float(s['draft_ride_height_mm'])==5 and ini(data/'profile.ini')['ride_height_mm']=='0')
 key('Escape');check('stance_cancel_returns_to_body_without_save',page(8,2) and ini(data/'profile.ini')['ride_height_mm']=='0')
 key('Return');click(447,173);click(330,668);check('stance_save_updates_real_vehicle_height',page(8,2) and ini(data/'profile.ini')['ride_height_mm']=='5')
 key('Escape');check('escape_body_restores_style',page(8,1));key('Down');key('Return');check('paint_has_own_two_entry_menu',page(8,4) and state()['entry_count']=='2')
 key('Return');check('paint_entry_opens_paint_catalogue',state()['cosmetic_slot']=='0' and page(3));key('Escape');key('Down');key('Return');check('wrap_entry_opens_existing_wraps',state()['cosmetic_slot']=='1' and page(3))
 key('Escape');key('Escape');key('End');key('Return');s=state();check('style_exhaust_sound_opens_working_audio_popup',s['screen']=='8' and s['rides_page']=='1' and s['audio_popup']=='1');key('Escape');check('audio_close_stays_in_style',page(8,1) and state()['audio_popup']=='0')
 key('Home');key('Down');key('Down');key('Return');check('driving_effects_has_own_menu',page(8,5));key('Return');s=state();check('tire_smoke_entry_opens_tires',s['screen']=='3' and s['custom_slot']=='10')
 key('Escape');key('Escape');key('Down');key('Return');check('vanity_has_own_menu',page(8,6));key('End');key('Return');check('vanity_cage_action_is_real',ini(data/'profile.ini')['roll_cage']=='1')
 key('Escape');key('Escape');key('Down');key('Return');check('performance_has_own_menu',page(8,7));key('Down');key('Return');check('performance_parts_has_own_eight_families',page(8,8) and state()['entry_count']=='8')
 key('Home');key('Return');s=state();check('performance_engine_family_opens_engine_catalogue',s['screen']=='3' and s['custom_slot']=='0');key('Escape');key('Escape');key('Home');key('Down');key('Down');key('Return');check('performance_handling_opens_suspension',page(5));key('Escape');check('suspension_returns_to_performance_parent',page(8,7))
 key('Down');key('Return');check('performance_transmission_opens_gearbox',page(4));key('Escape');check('gearbox_returns_to_performance_parent',page(8,7));key('Down');key('Return');check('performance_dyno_popup_works',state()['power_popup']=='1');key('Escape');key('Escape')
 key('Down');key('Return');check('home_buy_sell_opens_showroom',page(7));key('Escape');check('showroom_returns_to_home_selection',page(8,0) and state()['rides_selection']=='2');key('Down');key('Return');check('home_all_rides_opens_owned_inventory',page(7));key('Escape')
 key('g');check('ignition_works_from_home',state()['garage_engine_running']=='1');xdo('keydown','z');time.sleep(.6);xdo('keyup','z');check('revving_works_from_home',float(state()['garage_engine_rpm'])>1000);key('g')
 key('h');check('hide_ui_keeps_current_menu',state()['hide_ui']=='1' and page(8,0));key('h');key('Escape');check('home_back_returns_to_main_menu',page(0));close()
 start();check('new_session_starts_at_home_and_keeps_config',page(8,0) and ini(data/'profile.ini')['ride_height_mm']=='5' and ini(data/'profile.ini')['roll_cage']=='1' and ini(data/'profile.ini')['part_engine']==initial['part_engine'])
 click(180,423);check('mouse_selects_style_from_home',page(8,1));click(180,372);check('mouse_selects_body_from_style',page(8,2));close()
 (a.output/'report.json').write_text(json.dumps({'checks':checks},indent=2)+'\n');print('PASS:',len(checks),'actual hierarchical rides navigation input checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
