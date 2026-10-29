#!/usr/bin/env python3
"""Verify leaf-only customization navigation using real keyboard and mouse input."""
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
 start();key('Down');key('Return');key('Down');key('Return');key('Return');s=state();before=ini(data/'profile.ini')
 check('engine_editor_scoped_to_parts_parent',s['screen']=='3' and s['scoped_editor']=='1' and s['custom_group']=='0')
 for k in ['F1','F2','F3','F4','F5','F6','F7','F8','F9','F11','b','k']:
  key(k);s=state();check('blocked_cross_category_'+k,s['screen']=='3' and s['custom_group']=='0' and s['cosmetic_picker']=='0' and ini(data/'profile.ini')==before)
 for x in [280,480,680,880,1080]:click(x,515)
 check('old_category_buttons_are_inactive',state()['custom_group']=='0' and page(3))
 key('Tab');check('tab_selects_local_ecu',state()['custom_slot']=='4' and state()['custom_group']=='0');key('Tab');check('tab_wraps_back_to_engine',state()['custom_slot']=='0')
 click(100,686);check('global_max_preparation_absent',ini(data/'profile.ini')==before and page(3));key('F12')
 click(925,686);check('return_button_restores_exact_parts_parent',page(8,8) and state()['rides_selection']=='0')
 key('Down');key('Return');key('Tab');check('wheel_editor_keeps_tires_in_its_family',state()['custom_slot']=='10' and state()['custom_group']=='1');key('Escape')
 key('Down');key('Return');key('Tab');check('nos_editor_tab_cannot_escape_family',state()['custom_group']=='2' and state()['custom_slot']=='5');key('Escape');key('Escape');key('Escape');key('Home');key('Return');key('Down');key('Return');key('Return')
 check('paint_catalogue_has_own_scope',state()['editor_cosmetic']=='0' and state()['cosmetic_picker']=='1')
 click(50,127);click(916,127);key('Tab');key('F2');check('cosmetic_arrows_and_shortcuts_cannot_change_slot',state()['cosmetic_slot']=='0' and page(3))
 click(930,41);check('top_return_restores_paint_parent',page(8,4));key('Down');key('Return');check('wraps_require_parent_selection',state()['cosmetic_slot']=='1');key('Escape');close()
 (a.output/'report.json').write_text(json.dumps({'checks':checks},indent=2)+'\n');print('PASS:',len(checks),'actual scoped customization input checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
