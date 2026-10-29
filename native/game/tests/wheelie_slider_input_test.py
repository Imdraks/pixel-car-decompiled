#!/usr/bin/env python3
"""Verify the single wheelie slider, removed toggle, persistence and cancellation with real input."""
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
(data/'profile.ini').write_text('version=8\ncar=20\ncontent_source=0\nallow_wheelie=0\nwheelie_tune=1\n')
def handling():
 key('Down');key('Return');key('Down');key('Down');key('Return');check('handling_menu_open_'+str(len(checks)),page(5))
try:
 start();handling();before=ini(data/'profile.ini');click(990,514);s=state();check('former_enable_button_has_no_action',s['draft_wheelie_tune']=='1' and s['draft_allows_wheelie']=='0' and ini(data/'profile.ini')==before)
 click(276,477);s=state();check('slider_alone_enables_draft_wheelie',abs(float(s['draft_wheelie_tune'])-.35)<.011 and s['draft_allows_wheelie']=='1');check('draft_does_not_change_saved_vehicle',ini(data/'profile.ini')['wheelie_tune']=='1')
 click(630,667);s=state();saved=ini(data/'profile.ini');check('saving_slider_enables_physics_without_switch',abs(float(saved['wheelie_tune'])-.35)<.011 and s['vehicle_allows_wheelie']=='1' and saved['allow_wheelie']=='1')
 click(590,443);click(990,514);click(630,667);s=state();check('balanced_endpoint_disables_lift_without_separate_toggle',ini(data/'profile.ini')['wheelie_tune']=='1' and s['vehicle_allows_wheelie']=='0')
 click(100,443);check('wheelie_label_selects_free_endpoint',state()['draft_wheelie_tune']=='0' and state()['draft_allows_wheelie']=='1');click(100,667);check('cancel_preserves_balanced_saved_setup',page(8,7) and ini(data/'profile.ini')['wheelie_tune']=='1')
 key('Return');click(181,477);click(630,667);saved=ini(data/'profile.ini');check('intermediate_position_is_saved',abs(float(saved['wheelie_tune'])-.2)<.011);close()
 start();check('single_slider_setting_survives_restart',abs(float(ini(data/'profile.ini')['wheelie_tune'])-.2)<.011 and state()['vehicle_allows_wheelie']=='1');close()
 (a.output/'report.json').write_text(json.dumps({'checks':checks},indent=2)+'\n');print('PASS:',len(checks),'actual single wheelie slider input checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
