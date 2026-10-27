#!/usr/bin/env python3
"""Exercise split rims, source materials, lights and compatibility through real input."""
import argparse
import json
import subprocess
import time
from pathlib import Path

p = argparse.ArgumentParser(description=__doc__)
for key in ['game', 'assets', 'xdotool', 'output']:
    p.add_argument('--' + key, type=Path, required=True)
a = p.parse_args()
a.output.mkdir(parents=True, exist_ok=False)
data = a.output / 'data'; data.mkdir()
(data / 'profile.ini').write_text('car=20\ndrive=1\nrim=10101\n')
(data / 'settings.ini').write_text('width=960\nheight=540\nfps=60\nvsync=0\nsound=0\ntraffic=0\n')
log = (a.output / 'application.log').open('w')
checks, sessions = {}, {}
proc, window = None, None


def xdo(*args):
    return subprocess.check_output([str(a.xdotool), *map(str, args)], text=True, stderr=subprocess.DEVNULL).strip()


def key(name):
    xdo('keydown', name); time.sleep(.07); xdo('keyup', name); time.sleep(.12)


def click(x, y):
    geo = dict(line.split('=', 1) for line in xdo('getwindowgeometry', '--shell', window).splitlines())
    w, h = int(geo['WIDTH']), int(geo['HEIGHT']); scale = min(w / 1280, h / 720)
    xdo('mousemove', '--window', window, round((w - 1280 * scale) / 2 + x * scale), round((h - 720 * scale) / 2 + y * scale))
    xdo('mousedown', 1); time.sleep(.07); xdo('mouseup', 1); time.sleep(.15)


def ini(name):
    return dict(line.split('=', 1) for line in (data / name).read_text().splitlines() if '=' in line)


def check(name, value):
    checks[name] = bool(value)
    if not value:
        key('F12')
        raise RuntimeError('Failed: ' + name)


def start(free=False):
    global proc, window
    proc = subprocess.Popen([str(a.game), '--assets-dir', str(a.assets), '--data-dir', str(data),
                             '--capture-dir', str(a.output / 'captures'), '--no-audio'] + (['--free-drive'] if free else []), stdout=log, stderr=log)
    for _ in range(150):
        if proc.poll() is not None:
            raise RuntimeError('Game exited during startup')
        try:
            window = xdo('search', '--onlyvisible', '--pid', proc.pid, '--name', 'Pixel Car Racer').splitlines()[0]
            xdo('windowfocus', '--sync', window); break
        except (subprocess.CalledProcessError, IndexError):
            time.sleep(.05)
    else:
        raise RuntimeError('Window never became focusable')
    ready = time.time_ns()
    for _ in range(40):
        key('F12')
        if any(f.stat().st_mtime_ns >= ready for f in (a.output / 'captures').glob('*.png')):
            return
    raise RuntimeError('No first rendered frame')


def close(name):
    xdo('keydown', 'ctrl'); key('q'); xdo('keyup', 'ctrl'); proc.wait(timeout=15)
    check(name + '_clean_exit', proc.returncode == 0)
    sessions[name] = ini('last-session.txt')
    return sessions[name]


def search(value):
    xdo('keydown','ctrl'); key('f'); xdo('keyup','ctrl'); xdo('type','--clearmodifiers','--delay','10',value); time.sleep(.2)

def choose_rim(axle,name):
    click(947+98*axle,174); search(name); key('Return')

try:
    start(); click(280,435); key('F2')
    choose_rim(1,'Four Racing')
    check('front_only_rim_retains_rear',ini('profile.ini')['rim']=='10100' and ini('profile.ini')['rear_rim']=='10101')
    choose_rim(2,'Four Racing'); check('rear_only_rim_changes',ini('profile.ini')['rear_rim']=='10100')
    choose_rim(0,'Sleepers'); check('both_axle_rims_relink',ini('profile.ini')['rim']=='10101' and ini('profile.ini')['rear_rim']=='-1')
    choose_rim(1,'Four Racing'); choose_rim(2,'Sleepers'); key('F12')
    key('F7'); search('Matte White'); key('Return'); check('matte_paint_equips',ini('profile.ini')['cosmetic_0']=='100085'); key('F12')
    search('Premium Blue Chrome'); key('Return'); check('chrome_paint_equips',ini('profile.ini')['cosmetic_0']=='100086'); key('F12')
    for _ in range(12): key('Tab')
    search('Midnight blue'); key('Return'); check('source_glass_tint_equips',ini('profile.ini')['cosmetic_12']=='112002')
    key('Tab'); search('red headlight tint'); key('Return'); check('red_headlight_tint_equips',ini('profile.ini')['cosmetic_13']=='113007'); key('k'); key('F12')
    search('sky headlight tint'); key('Return'); check('sky_headlight_tint_equips',ini('profile.ini')['cosmetic_13']=='113005')
    key('Tab'); search('70% taillight tint'); key('Return'); check('tail_tint_equips',ini('profile.ini')['cosmetic_14']=='114003')
    key('Tab'); search('HID 8000k'); key('Return'); check('bulb_equips',ini('profile.ini')['cosmetic_15']=='115002')
    key('F6'); click(1167,250); search('Short Triple'); key('Return'); check('triple_hood_pipe_equips',ini('profile.ini')['part_exhaust']=='9050'); key('Escape'); key('F12')
    close('styled'); saved=ini('profile.ini')
    start(True); resumed=close('restarted')
    check('split_rims_reach_driving_after_restart',resumed['front_rim']=='10100' and resumed['rear_rim']=='10101')
    check('material_and_lighting_survive_restart',ini('profile.ini')['cosmetic_0']=='100086' and ini('profile.ini')['headlights']=='1')
    report_path=Path(__file__).resolve().parents[2]/'evidence/merged/customization-render.json'
    report=json.loads(report_path.read_text()); bad=next(v for v in report['banks']['unbound']['compatibility'] if v['unsupported_cosmetic_ids']); cid=bad['unsupported_cosmetic_ids'][0]
    import re
    catalog=(Path(__file__).resolve().parents[1]/'src/content_catalog.hpp').read_text(); match=re.search(r'\{'+str(cid)+r',(\d+),\d+,"([^"\n]+)"',catalog); slot=int(match[1]); name=match[2]
    saved['car']=str(bad['body']);saved['content_source']='0';saved['cosmetic_'+str(slot)]='0'
    (data/'profile.ini').write_text(''.join(k+'='+v+'\n' for k,v in saved.items()))
    start(); click(280,435); key('F7')
    for _ in range(slot): key('Tab')
    search(name); key('Return'); key('F12')
    check('keyboard_rejects_incompatible_variant',ini('profile.ini')['cosmetic_'+str(slot)]=='0')
    click(1171,535); check('mouse_cannot_equip_missing_variant',ini('profile.ini')['cosmetic_'+str(slot)]=='0')
    close('compatibility')
    (a.output/'report.json').write_text(json.dumps({'checks':checks,'sessions':sessions,'profile':ini('profile.ini')},indent=2)+'\n')
    print('PASS:',len(checks),'actual customization input checks')
finally:
    for name in ['ctrl','q','F12']:
        subprocess.run([str(a.xdotool),'keyup',name],capture_output=True)
    if proc is not None and proc.poll() is None:
        proc.terminate();proc.wait(timeout=15)
    log.close()
