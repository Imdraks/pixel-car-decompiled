#!/usr/bin/env python3
"""Exercise real mouse volume sliders, cancellation, persistence and old display settings."""
import argparse,json,subprocess,time
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__)
for k in ['game','assets','xdotool','output']:p.add_argument('--'+k,type=Path,required=True)
a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False);data=a.output/'data';data.mkdir();captures=a.output/'captures';checks={}
def ini(path):return dict(line.split('=',1) for line in path.read_text().splitlines() if '=' in line)
def check(k,v):
 checks[k]=bool(v)
 if not v:raise RuntimeError(k)
def xdo(*args):return subprocess.check_output([str(a.xdotool),*map(str,args)],text=True,stderr=subprocess.DEVNULL).strip()
def key(k):xdo('keydown',k);time.sleep(.08);xdo('keyup',k);time.sleep(.12)
def click(x,y):
 xdo('mousemove','--window',window,round(x*.75),round(y*.75));time.sleep(.06);xdo('mousedown',1);time.sleep(.09);xdo('mouseup',1);time.sleep(.14)
def drag(index,value):
 y=183+index*62;xdo('mousemove','--window',window,round(750*.75),round(y*.75));xdo('mousedown',1);time.sleep(.07)
 xdo('mousemove','--window',window,round((540+436*value)*.75),round(y*.75));time.sleep(.15);xdo('mouseup',1);time.sleep(.1)
def start():
 global proc,window,log
 log=(a.output/'application.log').open('a');proc=subprocess.Popen([str(a.game),'--assets-dir',str(a.assets),'--data-dir',str(data),'--capture-dir',str(captures),'--no-audio'],stdout=log,stderr=log)
 for _ in range(150):
  if proc.poll() is not None:raise RuntimeError('Game exited before startup')
  try:window=xdo('search','--onlyvisible','--pid',proc.pid,'--name','Pixel Car Racer').splitlines()[0];xdo('windowfocus','--sync',window);break
  except (subprocess.CalledProcessError,IndexError):time.sleep(.04)
 else:raise RuntimeError('No window')
 for _ in range(40):
  before=len(list(captures.glob('*.png')));key('F12')
  if len(list(captures.glob('*.png')))>before:break
 click(280,565);click(468,468)
def close():
 xdo('keydown','ctrl');key('q');xdo('keyup','ctrl');proc.wait(timeout=15);log.close();check('clean_exit_'+str(len(checks)),proc.returncode==0)
(data/'settings.ini').write_text('width=960\nheight=540\nfps=60\nvsync=0\nsound=1\ntraffic=0\nabs=0\ntraction_control=0\n')
values=[.73,.24,.61,.55,.35,.19];keys=['master','engine','turbo','effects','ambience','interface']
try:
 start()
 for i,v in enumerate(values):drag(i,v)
 key('F12');click(890,620);saved=ini(data/'settings.ini')
 for k,v in zip(keys,values):check('saved_'+k,abs(float(saved['volume_'+k])-v)<.011)
 check('display_and_driving_preserved',saved['width']=='960' and saved['height']=='540' and saved['traffic']=='0' and saved['abs']=='0' and saved['traction_control']=='0')
 click(468,468);drag(0,0);click(330,620);check('cancel_does_not_save_preview',ini(data/'settings.ini')==saved)
 click(468,468);drag(1,1);key('Escape');check('escape_does_not_save_preview',ini(data/'settings.ini')==saved)
 close();start();key('F12');click(890,620);check('levels_survive_restart',ini(data/'settings.ini')==saved)
 click(468,468);click(585,620);click(890,620);reset=ini(data/'settings.ini');check('reset_all_channels',all(float(reset['volume_'+k])==1 for k in keys));close()
 (a.output/'report.json').write_text(json.dumps({'checks':checks,'saved_settings':saved},indent=2)+'\n');print('PASS:',len(checks),'actual volume-slider input checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
