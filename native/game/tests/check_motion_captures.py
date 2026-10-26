#!/usr/bin/env python3
"""Check actual road displacement in the controlled native smoke captures."""
import argparse,json
from pathlib import Path
from PIL import Image,ImageChops
p=argparse.ArgumentParser(description=__doc__);p.add_argument('captures',type=Path);p.add_argument('--report',type=Path,required=True);a=p.parse_args()
def load(name):return Image.open(a.captures/(name+'.png')).convert('RGB')
checks={}
checks['stationary_scene_and_wheels_are_frozen']=ImageChops.difference(load('motion-stationary-a'),load('motion-stationary-b')).getbbox() is None
checks["paused_at_speed_scene_and_wheels_are_frozen"]=ImageChops.difference(load("motion-paused-a"),load("motion-paused-b")).getbbox() is None
measurements={}
for speed in [100,200]:
 first=load(f'motion-{speed}-a');second=load(f'motion-{speed}-b');assert first.size==second.size
 width,height=first.size
 # The lower dashed line is outside the car, HUD and traffic in these captures.
 row=round(517*height/720)
 def mask(image):return [image.getpixel((x,row))==(171,173,181) for x in range(width)]
 before,after=mask(first),mask(second)
 assert any(before) and not all(before) and any(after)
 scores=[]
 for shift in range(round(12*48*width/1280)):
  score=sum(before[x+shift]==after[x] for x in range(width-shift))/(width-shift)
  scores.append(score)
 actual=max(range(len(scores)),key=scores.__getitem__)
 expected=speed/3.6*.1*48*width/1280
 checks[f'road_{speed}_kmh_matches_distance']=abs(actual-expected)<=1 and scores[actual]>.98
 measurements[str(speed)]={'pixels_in_0.1_seconds':actual,'expected_pixels':expected,'match':scores[actual]}
# Each measured shift is quantised to one screen pixel; allow the combined error.
checks['doubling_speed_doubles_ground_travel']=abs(measurements['200']['pixels_in_0.1_seconds']-2*measurements['100']['pixels_in_0.1_seconds'])<=3
report={'checks':checks,'measurements':measurements};a.report.parent.mkdir(parents=True,exist_ok=True);a.report.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
if not all(checks.values()):raise SystemExit('Rendered road motion validation failed')
