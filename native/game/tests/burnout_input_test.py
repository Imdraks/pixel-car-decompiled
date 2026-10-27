#!/usr/bin/env python3
"""Check burnout and held neutral through actual PC keyboard input."""
import argparse
import json
import subprocess
import time
from pathlib import Path

p = argparse.ArgumentParser(description=__doc__)
for name in ['game', 'assets', 'xdotool', 'output']:
    p.add_argument('--' + name, type=Path, required=True)
a = p.parse_args()
a.output.mkdir(parents=True, exist_ok=False)
checks, sessions = {}, {}


def check(name, value):
    checks[name] = bool(value)
    if not value:
        raise RuntimeError('Failed: ' + name)


def scenario(name, actions, automatic=True):
    root = a.output / name
    root.mkdir()
    (root / 'profile.ini').write_text('car=20\ndrive=1\nautomatic=' + str(int(automatic)) + '\npart_tires=10009\npart_nos=5007\n')
    (root / 'settings.ini').write_text('width=960\nheight=540\nfps=60\nvsync=0\nsound=0\ntraffic=0\n')
    def xdo(*args):
        return subprocess.check_output([str(a.xdotool), *map(str, args)], text=True, stderr=subprocess.DEVNULL).strip()
    held = set()
    with (root / 'application.log').open('w') as log:
        proc = subprocess.Popen([str(a.game), '--assets-dir', str(a.assets), '--data-dir', str(root),
                                 '--capture-dir', str(root / 'captures'), '--free-drive', '--no-audio'], stdout=log, stderr=log)
        try:
            window = None
            for _ in range(150):
                if proc.poll() is not None:
                    raise RuntimeError('Game exited during startup')
                try:
                    window = xdo('search', '--onlyvisible', '--pid', proc.pid, '--name', 'Pixel Car Racer').splitlines()[0]
                    xdo('windowfocus', '--sync', window)
                    break
                except (subprocess.CalledProcessError, IndexError):
                    time.sleep(.04)
            if window is None:
                raise RuntimeError('Game window unavailable')
            for _ in range(50):
                xdo('keydown', 'F12'); time.sleep(.06); xdo('keyup', 'F12'); time.sleep(.1)
                if list((root / 'captures').glob('*.png')):
                    break
            else:
                raise RuntimeError('Game did not render its first frame')
            for key, down, duration in actions:
                xdo('keydown' if down else 'keyup', key)
                if down: held.add(key)
                else: held.discard(key)
                time.sleep(duration)
            xdo('keydown', 'F12'); time.sleep(.08); xdo('keyup', 'F12'); time.sleep(.1)
            xdo('keydown', 'ctrl'); xdo('keydown', 'q'); time.sleep(.08); xdo('keyup', 'q'); xdo('keyup', 'ctrl')
            proc.wait(timeout=15)
            check(name + '_clean_exit', proc.returncode == 0)
            state = dict(line.split('=', 1) for line in (root / 'last-session.txt').read_text().splitlines() if '=' in line)
            sessions[name] = state
            return state
        finally:
            for key in held | {'ctrl', 'q', 'F12'}:
                subprocess.run([str(a.xdotool), 'keyup', key], capture_output=True)
            if proc.poll() is None:
                proc.terminate(); proc.wait(timeout=15)


b = scenario('burnout', [('s', True, .1), ('w', True, 1.2), ('n', True, .2)])
check('brake_and_throttle_trigger_first_gear_burnout', b['burnout'] == '1' and b['gear'] == '1' and float(b['rpm']) > 5000)
check('burnout_keeps_ground_stopped', float(b['distance_m']) == 0 and float(b['speed_mps']) == 0)
check('burnout_spins_only_rear_drive_wheels', float(b['rear_roll_m']) > 5 and float(b['front_roll_m']) == 0)
check('burnout_does_not_consume_nos', b['nitro_active'] == '0' and float(b['nitro_remaining']) == 10)
n = scenario('neutral', [('v', True, .1), ('w', True, 1.1), ('n', True, .1), ('e', True, .1), ('e', False, .1)])
check('v_holds_neutral_while_revving', n['neutral'] == '1' and float(n['rpm']) > 7000)
check('neutral_disconnects_both_axles', float(n['distance_m']) == 0 and float(n['rear_roll_m']) == 0 and float(n['front_roll_m']) == 0)
check('neutral_blocks_shift_and_nos', n['gear'] == '1' and n['nitro_active'] == '0' and float(n['nitro_remaining']) == 10 and float(n['current_hp']) == 0)
r = scenario('neutral_release', [('v', True, .1), ('w', True, .8), ('v', False, 1.2)])
check('releasing_v_reconnects_and_accelerates', r['neutral'] == '0' and float(r['distance_m']) > 1 and float(r['speed_mps']) > 1)
r = scenario('brake_release', [('s', True, .1), ('w', True, 1), ('s', False, 1.2)])
check('releasing_brake_ends_burnout_and_accelerates', r['burnout'] == '0' and float(r['distance_m']) > 1 and float(r['speed_mps']) > 1)
h = scenario('handbrake_priority', [('s', True, .1), ('w', True, .8), ('space', True, .3)])
check('space_overrides_burnout', h['handbraking'] == '1' and h['burnout'] == '0' and float(h['current_hp']) == 0)
hrev = scenario('handbrake_rev', [('space', True, .1), ('w', True, 1.2), ('n', True, .1)])
check('handbrake_allows_free_engine_revs',hrev['handbraking']=='1' and float(hrev['rpm'])>7000)
check('revving_handbrake_keeps_car_stationary',float(hrev['distance_m'])==0 and float(hrev['rear_roll_m'])==0 and float(hrev['front_roll_m'])==0 and hrev['nitro_active']=='0')
hlaunch = scenario('handbrake_release', [('space',True,.1),('w',True,.8),('space',False,1.2)])
check('releasing_handbrake_launches_with_throttle',hlaunch['handbraking']=='0' and float(hlaunch['distance_m'])>1)
(a.output / 'report.json').write_text(json.dumps({'checks': checks, 'sessions': sessions}, indent=2) + '\n')
print('PASS:', len(checks), 'actual keyboard burnout/neutral checks')
