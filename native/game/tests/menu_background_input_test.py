#!/usr/bin/env python3
"""Verify menu backgrounds fill resized tall and wide windows while menu navigation stays aligned."""
import argparse,json,subprocess,time
from PIL import Image
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
 before={p:p.stat().st_mtime_ns for p in captures.glob('capture-*.png.state')};key('F12')
 for _ in range(100):
  files=[p for p in captures.glob('capture-*.png.state') if p not in before or p.stat().st_mtime_ns>before[p]]
  if files:
   latest=max(files,key=lambda p:p.stat().st_mtime_ns);result=ini(latest)
   if 'garage_engine_rpm' in result:return result
  time.sleep(.05)
 raise RuntimeError('No completed fresh screenshot state')
def page(screen,node=None):
 s=state();return s['screen']==str(screen) and (node is None or s['rides_page']==str(node))
(data/'settings.ini').write_text('width=960\nheight=540\nfps=60\nvsync=0\nsound=0\n')
(data/'profile.ini').write_text('version=8\ncar=20\ncontent_source=0\n')
measurements={}
def filled(name):
 s=state();p=max(captures.glob('capture-*.png'),key=lambda p:p.stat().st_mtime_ns);im=Image.open(p).convert('RGB');w,h=im.size
 if w/h<16/9:
  points=[(x,y) for y in [8,h-9] for x in range(8,w-8,4)]
 else:
  points=[(x,y) for x in [8,w-9] for y in range(8,h-8,4)]
 screen=int(s['screen']);native=screen in [3,4,5]
 source=Image.open(a.assets/('original-ui-00.png' if native else 'texture-047.png')).convert('RGB');origin=1 if native else 2
 tint,shade={0:((145,154,172),.74),3:((118,122,133),.45),4:((255,255,255),0),5:((255,255,255),0),7:((108,116,129),.47),8:((112,120,132),.35)}[screen]
 scale=max(w/940,h/480);alpha=int(shade*255)/255;ink=(10,15,23);matched=0
 for x,y in points:
  sx=(940-w/scale)/2+(x+.5)/scale;sy=(480-h/scale)/2+(y+.5)/scale;actual=im.getpixel((x,y));errors=[]
  for dy in [-1,0,1]:
   for dx in [-1,0,1]:
    pixel=source.getpixel((origin+max(0,min(939,int(sx)+dx)),origin+max(0,min(479,int(sy)+dy))))
    expected=[pixel[c]*tint[c]/255*(1-alpha)+ink[c]*alpha for c in range(3)]
    errors.append(max(abs(actual[c]-expected[c]) for c in range(3)))
  matched+=min(errors)<=4
 coverage=matched/len(points);measurements[name]={'width':w,'height':h,'source_pixel_matches':coverage,'screen':s['screen']}
 check(name+'_fills_window_margins',coverage>.99);return s
def resize(w,h):xdo('windowmove',window,0,0);xdo('windowsize','--sync',window,w,h);time.sleep(.35)
try:
 start();resize(1200,900);filled('custom_home_tall');key('F1');check('keyboard_opens_engine_leaf_after_resize',filled('engine_tall')['screen']=='3');key('Escape');key('F9');filled('suspension_tall');key('Escape')
 key('Down');key('Return');key('Down');key('Down');key('Down');key('Return');check('transmission_reached_after_resize',filled('transmission_tall')['screen']=='4');key('Escape');key('Escape');key('Home');key('Down');key('Down');key('Return');filled('showroom_tall');key('Escape');key('Escape');check('home_back_returns_main_menu',filled('main_tall')['screen']=='0')
 resize(1600,700);filled('main_wide');xdo('mousemove','--window',window,450,489);xdo('mousedown',1);time.sleep(.08);xdo('mouseup',1);time.sleep(.2);check('mouse_coordinates_still_open_customization',filled('custom_home_wide')['screen']=='8');key('F9');filled('suspension_wide');close()
 (a.output/'report.json').write_text(json.dumps({'checks':checks,'measurements':measurements},indent=2)+'\n');print('PASS:',len(checks),'actual menu backdrop input checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
