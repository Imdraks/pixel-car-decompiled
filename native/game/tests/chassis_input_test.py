#!/usr/bin/env python3
"""Exercise suspension tuning, wheelie and driving-aid settings with real input."""
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
(data / 'profile.ini').write_text('car=20\ndrive=1\n')
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


try:
    start(); click(280, 435); click(75, 670); key('F9')
    click(150, 578)  # Route preset, then independent plus buttons.
    for y in [188, 274, 360, 446]: click(1205, y)
    click(990, 514); click(630, 667)
    saved = ini('profile.ini')
    check('independent_suspension_controls_save', float(saved['ride_height_mm']) == 5 and float(saved['spring_stiffness']) == 1.1 and float(saved['damping_ratio']) == .7 and float(saved['front_bias']) == .01 and saved['allow_wheelie'] == '1')
    click(365, 578); click(1010, 667)  # Drag preset and save + drive.
    saved = ini('profile.ini')
    check('drag_preset_persists', float(saved['ride_height_mm']) == 120 and float(saved['spring_stiffness']) == .5 and float(saved['damping_ratio']) == .3 and float(saved['front_bias']) == -.15 and saved['allow_wheelie'] == '1')
    xdo('keydown', 'w'); xdo('keydown', 'n'); time.sleep(6); key('F12')
    wheelie = close('wheelie'); xdo('keyup', 'w'); xdo('keyup', 'n')
    check('actual_drag_launch_lifts_front_axle', float(wheelie['peak_front_lift_m']) > .1)
    check('default_aids_reach_live_vehicle', wheelie['abs_enabled'] == '1' and wheelie['tc_enabled'] == '1')
    start(True); click(920, 42); click(410, 566); click(850, 566); click(910, 624); time.sleep(.3); click(490, 398); key('Escape')
    off = close('aids_off')
    check('actual_aid_buttons_save_off', ini('settings.ini')['abs'] == '0' and ini('settings.ini')['traction_control'] == '0')
    check('disabled_aids_apply_to_live_vehicle', off['abs_enabled'] == '0' and off['tc_enabled'] == '0')
    start(True); click(920, 42); click(410, 566); click(850, 566); click(910, 624); time.sleep(.3); key('Escape'); key('Escape')
    restored = close('preview_reverted')
    check('aid_preview_reverts_without_confirmation', restored['abs_enabled'] == '0' and restored['tc_enabled'] == '0' and ini('settings.ini')['abs'] == '0')
    start(); click(280, 435); key('F9'); click(150, 578); click(150, 667)
    check('cancel_keeps_saved_suspension', ini('profile.ini')['ride_height_mm'] == '120' and ini('profile.ini')['allow_wheelie'] == '1')
    key('F9'); click(590, 578); click(1010, 667)
    saved = ini('profile.ini')
    check('track_preset_saves_grounded_stiff_setup', saved['ride_height_mm'] == '-40' and saved['spring_stiffness'] == '2' and saved['damping_ratio'] == '0.9' and saved['allow_wheelie'] == '0')
    xdo('keydown', 'w'); time.sleep(2); grounded = close('grounded'); xdo('keyup', 'w')
    check('grounded_setup_cannot_lift_wheels', float(grounded['peak_front_lift_m']) == 0 and float(grounded['distance_m']) > 1)
    check('aid_choices_survive_restart', grounded['abs_enabled'] == '0' and grounded['tc_enabled'] == '0')
    (a.output / 'report.json').write_text(json.dumps({'checks': checks, 'sessions': sessions, 'profile': saved}, indent=2) + '\n')
    print('PASS:', len(checks), 'actual chassis and driving-aid input checks')
finally:
    for name in ['w', 'n', 'ctrl', 'q', 'F12']:
        subprocess.run([str(a.xdotool), 'keyup', name], capture_output=True)
    if proc is not None and proc.poll() is None:
        proc.terminate(); proc.wait(timeout=15)
    log.close()
