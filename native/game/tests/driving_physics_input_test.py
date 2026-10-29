#!/usr/bin/env python3
"""Verify driving, steering, manual shifts, neutral launches and TC using real input."""
import argparse,json,subprocess,time
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__)
for name in ['game','assets','xdotool','output']:p.add_argument('--'+name,type=Path,required=True)
a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False);data=a.output/'data';data.mkdir();captures=a.output/'captures';checks={};states={}
def check(name,value):
 checks[name]=bool(value)
 if not value:raise RuntimeError(name)
def xdo(*args):return subprocess.check_output([str(a.xdotool),*map(str,args)],text=True,stderr=subprocess.DEVNULL).strip()
def key(k):xdo('keydown',k);time.sleep(.05);xdo('keyup',k);time.sleep(.12)
def capture(name):
 key('F12');p=max(captures.glob('capture-*.png.state'),key=lambda f:f.stat().st_mtime_ns)
 state=dict(line.split('=',1) for line in p.read_text().splitlines() if '=' in line);states[name]=state;return state
def start():
 global proc,window,log
 log=(a.output/'application.log').open('a');proc=subprocess.Popen([str(a.game),'--assets-dir',str(a.assets),'--data-dir',str(data),'--capture-dir',str(captures),'--no-audio'],stdout=log,stderr=log)
 for _ in range(160):
  if proc.poll() is not None:raise RuntimeError('Game exited at startup')
  try:window=xdo('search','--onlyvisible','--pid',proc.pid,'--name','Pixel Car Racer').splitlines()[0];xdo('windowfocus','--sync',window);break
  except (subprocess.CalledProcessError,IndexError):time.sleep(.04)
 else:raise RuntimeError('No native window')
 for _ in range(40):
  before=len(list(captures.glob('*.png')));key('F12')
  if len(list(captures.glob('*.png')))>before:break
 xdo('mousemove','--window',window,220,272);xdo('mousedown',1);time.sleep(.08);xdo('mouseup',1);time.sleep(.25)
 check('entered_free_drive_'+str(len(checks)),capture('start_'+str(len(checks)))['screen']=='2')
def close():
 xdo('keyup','z','s','v');xdo('keydown','ctrl');key('q');xdo('keyup','ctrl');proc.wait(timeout=15);log.close();check('clean_exit_'+str(len(checks)),proc.returncode==0)
settings='width=960\nheight=540\nfps=120\nvsync=0\nsound=0\ntraffic=0\nabs=1\ntraction_control={tc}\n'
(data/'settings.ini').write_text(settings.format(tc=0))
(data/'profile.ini').write_text('version=8\ncar=20\ncontent_source=0\nfactory_drive=0\ndrive=1\nautomatic=0\npart_engine=1014\npart_turbo=3026\npart_ecu=4008\npart_tires=10017\n')
try:
 start();xdo('keydown','z');time.sleep(2);s=capture('powered');check('power_moves_car_and_physically_spins_wheels',float(s['player_speed_mps'])>0 and float(s['player_wheel_omega'])*float(s['player_wheel_radius'])>float(s['player_speed_mps'])*1.05);check('spinning_engine_rpm_exceeds_ground_speed_rpm',float(s['player_rpm'])>float(s['player_road_rpm'])*1.05)
 key('d');time.sleep(.15);s=capture('steering');check('steering_is_progressive_while_moving',1<float(s['player_lane'])<2 and float(s['player_lateral_speed'])>0)
 key('e');time.sleep(.45);s=capture('second_gear');check('rolling_wheelspin_survives_manual_second_gear_power',s['player_gear']=='2' and float(s['player_wheel_omega'])*float(s['player_wheel_radius'])>float(s['player_speed_mps']))
 xdo('keyup','z');xdo('keydown','s');time.sleep(4);xdo('keyup','s');s=capture('stopped');check('service_brake_stops_native_car',float(s['player_speed_mps'])==0)
 before=float(s['player_lane']);key('a');time.sleep(.4);s=capture('stationary_steering');check('steering_cannot_move_stationary_car_sideways',abs(float(s['player_lane'])-before)<.001)
 xdo('keydown','v','z');time.sleep(1.3);s=capture('neutral');check('neutral_revs_without_driving',float(s['player_speed_mps'])==0 and float(s['player_rpm'])>8000)
 xdo('keyup','v');time.sleep(.6);s=capture('rev_release');check('neutral_release_delivers_stored_rotation',float(s['player_wheel_omega'])*float(s['player_wheel_radius'])>float(s['player_speed_mps']) and float(s['player_speed_mps'])>0);close()
 (data/'settings.ini').write_text(settings.format(tc=1));start();xdo('keydown','z');time.sleep(1.3);s=capture('tc');check('enabled_tc_controls_powered_wheelspin',s['player_tc']=='1' and float(s['player_wheel_slip'])<.01 and float(s['player_wheel_omega'])<0 and float(s['player_speed_mps'])>0);close()
 (a.output/'report.json').write_text(json.dumps({'checks':checks,'states':states},indent=2)+'\n');print('PASS:',len(checks),'actual driving physics input checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
