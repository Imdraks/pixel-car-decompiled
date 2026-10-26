#!/usr/bin/env python3
"""Drive the real Linux window through XTest; requires an isolated X display."""
import argparse
import json
import os
from pathlib import Path
import subprocess
import time

parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--game',type=Path,required=True)
parser.add_argument('--assets',type=Path,required=True)
parser.add_argument('--xdotool',type=Path,required=True)
parser.add_argument('--output',type=Path,required=True)
args=parser.parse_args();args.output.mkdir(parents=True,exist_ok=True)
if (args.output/'data').exists():raise SystemExit('Use a fresh output directory')
log=(args.output/'application.log').open('w')
process=subprocess.Popen([str(args.game),'--assets-dir',str(args.assets),'--data-dir',str(args.output/'data'),
 '--capture-dir',str(args.output/'captures'),'--safe-mode','--no-audio'],stdout=log,stderr=log)
def xdo(*parameters):return subprocess.check_output([str(args.xdotool),*map(str,parameters)],text=True).strip()
def pause():time.sleep(.15)
try:
    window=None
    for _ in range(80):
        if process.poll() is not None:raise RuntimeError('Game exited during initialization')
        try:window=xdo('search','--pid',process.pid,'--name','Pixel Car Racer').splitlines()[0];break
        except subprocess.CalledProcessError:time.sleep(.1)
    if not window:raise RuntimeError('Native window not found')
    xdo('windowfocus','--sync',window);pause()
    def click(x,y):
        geometry=dict(line.split('=',1) for line in xdo('getwindowgeometry','--shell',window).splitlines())
        width,height=int(geometry['WIDTH']),int(geometry['HEIGHT'])
        scale=min(width/1280,height/720)
        px=(width-1280*scale)/2+x*scale;py=(height-720*scale)/2+y*scale
        xdo('mousemove','--window',window,round(px),round(py));xdo('mousedown',1);time.sleep(.08);xdo('mouseup',1);pause()
    def key(name):
        xdo('keydown',name);time.sleep(.08);xdo('keyup',name);pause()
    click(280,435)  # Menu -> garage.
    click(400,609)  # Select next real Unbound body.
    click(750,609)  # Select next rim.
    click(1100,189) # Propulsion reference -> all wheel drive reference.
    key('F12')
    click(1015,605) # Garage -> free drive.
    xdo('keydown','w');time.sleep(2);key('Right');key('t');key('e');xdo('keyup','w')
    key('F12')
    click(920,42) # Free drive -> settings.
    click(1040,168) # Bordered -> borderless.
    click(1040,262) # FPS 60 -> 120.
    click(1040,314) # VSync off -> on.
    click(1040,366) # Quality high -> low.
    click(1040,418) # FPS display on.
    click(1040,522) # Disable traffic.
    key('F12')
    click(910,624) # Apply.
    time.sleep(.4)
    click(490,398) # Keep the new display settings.
    time.sleep(.3)
    key('F12');key('Escape')
    xdo('keydown','w');time.sleep(1);xdo('keyup','w')
    xdo('keydown','ctrl');key('q');xdo('keyup','ctrl');process.wait(timeout=10)
    def ini(path):return dict(line.split('=',1) for line in path.read_text().splitlines() if '=' in line)
    settings=ini(args.output/'data/settings.ini');profile=ini(args.output/'data/profile.ini');session=ini(args.output/'data/last-session.txt')
    checks={
      'normal_exit':process.returncode==0,'garage_car_click':profile['car']=='1','garage_rim_click':profile['rim']=='1',
      'actual_keyboard_acceleration':float(session['distance_m'])>1,'actual_lane_input':session['target_lane']=='2',
      'actual_gearbox_toggle':profile['automatic']=='0',
      'actual_drive_selection_saved':profile['drive']=='2','actual_drive_selection_applied':session['drive_layout']=='2','actual_settings_apply':settings['mode']=='borderless',
      'actual_fps_choice':settings['fps']=='120','actual_vsync_choice':settings['vsync']=='1',
      'actual_quality_choice':settings['quality']=='0','actual_fps_overlay_choice':settings['show_fps']=='1',
      'traffic_preference_saved':settings['traffic']=='0','traffic_removed_from_active_session':session['traffic_enabled']=='0' and session['traffic_count']=='0'}
    process=subprocess.Popen([str(args.game),'--assets-dir',str(args.assets),'--data-dir',str(args.output/'data'),'--free-drive','--no-audio'],stdout=log,stderr=log)
    for _ in range(100):
        if process.poll() is not None:raise RuntimeError('Restart failed')
        try:window=xdo('search','--pid',process.pid,'--name','Pixel Car Racer').splitlines()[0];break
        except subprocess.CalledProcessError:time.sleep(.05)
    xdo('windowfocus','--sync',window);time.sleep(.3)
    xdo('keydown','ctrl');key('q');xdo('keyup','ctrl');process.wait(timeout=10)
    resumed=ini(args.output/'data/last-session.txt')
    checks['traffic_remains_disabled_after_restart']=resumed['traffic_enabled']=='0' and resumed['traffic_count']=='0'
    (args.output/'report.json').write_text(json.dumps({'checks':checks,'settings':settings,'profile':profile,'session':session},indent=2))
    print(json.dumps(checks,indent=2))
    if not all(checks.values()):raise SystemExit(1)
finally:
    if process.poll() is None:process.terminate();process.wait(timeout=10)
    log.close()
