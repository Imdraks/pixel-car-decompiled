#!/usr/bin/env python3
"""Verify single source badges, duplicate migrations and genuine Underground variants."""
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
(data/'settings.ini').write_text('width=960\nheight=540\nfps=60\nvsync=0\nsound=0\n')
(data/'profile.ini').write_text('version=8\ncar=0\ncontent_source=0\n')
(data/'profile.ini').write_text('version=8\ncar=0\ncontent_source=0\npart_engine=1002\npart_exhaust=69026\nrim=200109\ncosmetic_0=600001\n')
def search(value):
 xdo('keydown','ctrl');key('f');xdo('keyup','ctrl');xdo('type','--clearmodifiers','--delay','15',value);time.sleep(.2);key('Return')
try:
 start();p=ini(data/'profile.ini');check('legacy_duplicate_paint_canonicalized',p['cosmetic_0']=='100001');check('legacy_duplicate_rim_canonicalized',p['rim']=='10109');check('legacy_duplicate_exhaust_canonicalized',p['part_exhaust']=='9026')
 key('Down');key('Return');key('Down');key('Return');key('Return');s=state();check('shared_engine_has_only_original_badge',s['preview_origin']=='ORIGINAL')
 search('Unbound V12 6.5L 759');s=state();check('spreadsheet_engine_has_only_unbound_badge',s['preview_origin']=='UNBOUND' and ini(data/'profile.ini')['part_engine']=='20139')
 search('AMG GT63');s=state();check('native_engine_creation_is_labelled_honestly',s['preview_origin']=='CRÉATION PC' and ini(data/'profile.ini')['part_engine']=='1501')
 search('Underground V12');s=state();check('no_invented_underground_v12',s['visible_choice_count']=='0' and ini(data/'profile.ini')['part_engine']=='1501');key('Escape')
 key('Down');key('Return');search('Underground');s=state();check('only_real_underground_rim_variants_remain',s['preview_origin']=='UNDERGROUND' and s['visible_choice_count']=='9' and 'variante' in s['preview_name']);check('duplicate_rim_not_offered',ini(data/'profile.ini')['rim']!='200109');key('Escape');key('Escape');key('Escape');key('Home');key('Return');key('Down');key('Return');key('Return')
 check('canonical_paint_keeps_original_provenance',state()['preview_origin']=='ORIGINAL');search('Underground');check('identical_palette_has_no_fake_variants',state()['visible_choice_count']=='0');key('Escape');close()
 (a.output/'report.json').write_text(json.dumps({'checks':checks},indent=2)+'\n');print('PASS:',len(checks),'actual reviewed provenance input checks')
finally:
 if 'proc' in globals() and proc.poll() is None:proc.terminate();proc.wait(timeout=15)
