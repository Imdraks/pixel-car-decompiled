#!/usr/bin/env python3
"""Verify music routing in actual menus, owned garage, custom editors and paused driving."""
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
(data/'settings.ini').write_text('width=960\nheight=540\nfps=60\nvsync=0\nsound=0\ntraffic=0\n')
(data/'profile.ini').write_text('version=8\ncar=20\ncontent_source=0\n')
def context(name,expected):check(name,state()['menu_music_context']==expected)
try:
 start();context('custom_home_uses_reduced_garage_context','CUSTOMISATION');key('Escape');context('main_menu_uses_normal_song','MENU')
 click(280,435);context('owned_garage_uses_resonant_song','GARAGE');key('Tab');context('showroom_uses_normal_song','MENU');key('Tab');context('return_to_owned_garage_restores_resonance','GARAGE');key('Escape')
 click(280,500);key('F1');context('engine_editor_uses_reduced_song','CUSTOMISATION');key('Escape');key('F9');context('suspension_editor_uses_reduced_song','CUSTOMISATION');key('Escape');key('Escape')
 click(280,360);context('free_drive_has_no_music','SILENCE');key('Escape');context('paused_driving_still_has_no_music','SILENCE');click(920,42);context('driving_settings_still_have_no_music','SILENCE');close()
 (a.output/'report.json').write_text(json.dumps({'checks':checks,'scope':'Actual application menu routing; PCM playback verified separately with music_audio_test.cpp.'},indent=2)+'\n');print('PASS:',len(checks),'actual music context input checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
