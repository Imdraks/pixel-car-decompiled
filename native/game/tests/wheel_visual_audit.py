#!/usr/bin/env python3
"""Capture every body using the real garage UI on an isolated XTest display."""
import argparse
import json
from pathlib import Path
import subprocess
import time

parser=argparse.ArgumentParser(description=__doc__)
for name in ['game','assets','xdotool','output']:parser.add_argument('--'+name,type=Path,required=True)
args=parser.parse_args();args.output.mkdir(parents=True,exist_ok=False)
data=args.output/'data';data.mkdir();captures=args.output/'captures'
(data/'profile.ini').write_text('version=1\ncar=0\nrim=8\nautomatic=1\ndrive=1\n')
log=(args.output/'application.log').open('w')
process=subprocess.Popen([str(args.game),'--assets-dir',str(args.assets),'--data-dir',str(data),
    '--capture-dir',str(captures),'--safe-mode','--no-audio'],stdout=log,stderr=log)
def xdo(*p):return subprocess.check_output([str(args.xdotool),*map(str,p)],text=True).strip()
def ini(path):return dict(line.split('=',1) for line in path.read_text().splitlines() if '=' in line)
try:
    window=None
    for _ in range(100):
        if process.poll() is not None:raise RuntimeError('Game exited before opening its window')
        try:window=xdo('search','--pid',process.pid,'--name','Pixel Car Racer').splitlines()[0];break
        except subprocess.CalledProcessError:time.sleep(.05)
    if not window:raise RuntimeError('Native game window not found')
    xdo('windowfocus','--sync',window);time.sleep(.15)
    geometry=dict(line.split('=',1) for line in xdo('getwindowgeometry','--shell',window).splitlines())
    width,height=int(geometry['WIDTH']),int(geometry['HEIGHT']);scale=min(width/1280,height/720)
    def click(x,y):
        px=(width-1280*scale)/2+x*scale;py=(height-720*scale)/2+y*scale
        xdo('mousemove','--window',window,round(px),round(py));xdo('mousedown',1)
        time.sleep(.06);xdo('mouseup',1);time.sleep(.10)
    def key(name):
        xdo('keydown',name);time.sleep(.05);xdo('keyup',name);time.sleep(.04)
    def screenshot(name):
        key('F12')
        for _ in range(100):
            found=list(captures.glob('capture-*.png'))
            if found and found[0].read_bytes().endswith(b'IEND\xaeB`\x82'):
                found[0].rename(captures/name);return
            time.sleep(.02)
        raise RuntimeError('Missing complete native screenshot: '+name)
    click(280,435) # Menu -> actual garage.
    for index in range(191):
        assert ini(data/'profile.ini')['car']==str(index),'Garage input did not select the expected body'
        screenshot(f'car-{index+1:03d}.png')
        if index<190:click(400,609)
        if (index+1)%32==0:print('Captured',index+1,'bodies',flush=True)
    click(1015,605);xdo('keydown','w');time.sleep(1);xdo('keyup','w');time.sleep(.1)
    screenshot('free-drive.png')
    xdo('keydown','ctrl');key('q');xdo('keyup','ctrl');process.wait(timeout=10)
    session=ini(data/'last-session.txt')
    result={'platform':'Linux XTest, actual native renderer','body_count':191,'rim_style':9,
        'all_body_screenshots_present':all((captures/f'car-{i:03d}.png').exists() for i in range(1,192)),
        'free_drive_moves':float(session['distance_m'])>0,'normal_exit':process.returncode==0,
        'reported_case':'captures/car-021.png','note':'Captured pixels require visual review; capture count alone does not establish alignment.'}
    (args.output/'report.json').write_text(json.dumps(result,indent=2)+'\n')
    assert result['all_body_screenshots_present'] and result['free_drive_moves'] and result['normal_exit']
    print(json.dumps(result),flush=True)
finally:
    if process.poll() is None:process.terminate();process.wait(timeout=10)
    log.close()
