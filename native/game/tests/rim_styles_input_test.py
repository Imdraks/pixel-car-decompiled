#!/usr/bin/env python3
"""Verify six rim style filters, equipment changes and persistence with real input."""
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
 start();key('Down');key('Return');key('Down');key('Return');key('Down');key('Return');before=ini(data/'profile.ini');s=state();check('all_reviewed_rims_available',s['visible_choice_count']=='530' and s['rim_style_filter']=='0')
 counts={}
 for i,label in enumerate(['Offroad','Tuner','Muscle','Drag','Luxury','Hyper'],1):
  key(str(i));s=state();counts[label]=int(s['visible_choice_count']);check('filter_'+label,s['rim_style_filter']==str(i) and counts[label]>0 and counts[label]<530 and s['custom_group']=='1' and ini(data/'profile.ini')==before)
 check('six_disjoint_categories_cover_visible_rims',sum(counts.values())==530)
 click(38+5*172+82,515);check('mouse_selects_luxury',state()['rim_style_filter']=='5');key('Return');equipped=ini(data/'profile.ini');check('equip_from_filtered_category',equipped['rim']!=before['rim'] and state()['rim_style_filter']=='5')
 key('Tab');check('tire_tab_does_not_inherit_rim_style_filter',state()['custom_slot']=='10' and state()['visible_choice_count']=='74');key('Tab');check('return_to_rims_retains_category',state()['rim_style_filter']=='5')
 key('0');check('all_button_restores_every_visible_rim',state()['visible_choice_count']=='530');key('Escape');check('back_returns_to_wheel_parent',page(8,8) and state()['rides_selection']=='1');close();start();check('selected_rim_survives_restart',ini(data/'profile.ini')['rim']==equipped['rim']);close()
 (a.output/'report.json').write_text(json.dumps({'checks':checks,'category_counts':counts},indent=2)+'\n');print('PASS:',len(checks),'actual rim category input checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
