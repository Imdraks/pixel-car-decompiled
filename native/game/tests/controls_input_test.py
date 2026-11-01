#!/usr/bin/env python3
"""Drive the real commands page with keyboard and mouse; check persistence and gameplay."""
import argparse,json,subprocess,time
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__)
for n in ['game','assets','xdotool','output']:p.add_argument('--'+n,type=Path,required=True)
a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False);data=a.output/'data';data.mkdir();caps=a.output/'captures';checks={}
(data/'settings.ini').write_text('width=960\nheight=540\nfps=120\nvsync=0\nsound=0\ntraffic=0\n')
def xdo(*args):return subprocess.check_output([str(a.xdotool),*map(str,args)],text=True,stderr=subprocess.DEVNULL).strip()
def key(k):xdo('keydown',k);time.sleep(.06);xdo('keyup',k);time.sleep(.12)
def click(x,y):xdo('mousemove','--window',window,round(x*.75),round(y*.75));xdo('mousedown',1);time.sleep(.07);xdo('mouseup',1);time.sleep(.18)
def check(n,v):
 checks[n]=bool(v)
 if not v:raise RuntimeError(n)
def state():
 key('F12');f=max(caps.glob('capture-*.png.state'),key=lambda x:x.stat().st_mtime_ns);return dict(x.split('=',1) for x in f.read_text().splitlines() if '=' in x)
def start():
 global proc,window,log
 log=(a.output/'application.log').open('a');proc=subprocess.Popen([str(a.game),'--assets-dir',str(a.assets),'--data-dir',str(data),'--capture-dir',str(caps),'--no-audio'],stdout=log,stderr=log)
 for _ in range(150):
  try:window=xdo('search','--onlyvisible','--pid',proc.pid,'--name','Pixel Car Racer').splitlines()[0];xdo('windowfocus','--sync',window);break
  except (subprocess.CalledProcessError,IndexError):time.sleep(.05)
 else:raise RuntimeError('Window missing')
 time.sleep(1)
def close():
 xdo('keydown','ctrl');key('q');xdo('keyup','ctrl');proc.wait(timeout=15);log.close();check('clean_exit_'+str(len(checks)),proc.returncode==0)
try:
 start();click(300,565);click(925,107);check('commands_page_accessible',state()['controls_page']=='1')
 click(515,153);key('x');click(900,635)
 check('binding_saved_to_disk','key_0=88\n' in (data/'settings.ini').read_text());key('Escape');click(300,360)
 xdo('keydown','x');time.sleep(.6);xdo('keyup','x');check('new_throttle_accelerates',float(state()['player_speed_mps'])>0)
 close()
 start();check('binding_survives_restart',state()['throttle_key']=='88')
 click(300,565);click(925,107);click(515,153);key('g');click(900,635)
 s=state();check('duplicate_assignment_swaps_actions',s['throttle_key']=='71' and s['engine_key']=='88')
 click(925,107);click(515,153);key('z');click(270,635)
 check('cancel_preserves_previous_binding',state()['throttle_key']=='71')
 click(925,107);click(535,635);click(900,635)
 check('defaults_restore',state()['throttle_key']=='90');close()
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=10)
(a.output/'controls-input.json').write_text(json.dumps({'checks_passed':len(checks),'checks':checks,'physical_gamepad_tested':False},indent=2)+'\n');print('PASS:',len(checks),'actual command-page input checks')
