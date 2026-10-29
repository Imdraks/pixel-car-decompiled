#!/usr/bin/env python3
"""Fit native hood-pipe feet to the imported Underground body/front-kit silhouettes."""
from pathlib import Path
import argparse,json,re
from PIL import Image,ImageChops
p=argparse.ArgumentParser();p.add_argument('--textures',type=Path,required=True);a=p.parse_args();G=Path(__file__).resolve().parents[1];ss={s['name']:s for s in json.loads((a.textures/'sprites.json').read_text())['sprites']};cache={}
def image(name,i):
 s=ss[name];im=Image.new('RGBA',(220,70));f=s['frames'][i]
 if f:
  if f['file'] not in cache:cache[f['file']]=Image.open(a.textures/f['file']).convert('RGBA')
  x,y,w,h=f['source_rect'];im.paste(cache[f['file']].crop((x,y,x+w,y+h)),tuple(f['target_offset']))
 return im
text=(G/'src/content_art.hpp').read_text();anchors=[list(map(float,v.replace('f','').split(','))) for v in re.findall(r'\{([^{}]+)\}',re.search(r'undergroundAnchors\[\]\[5\]=\{(.*?)\n\};',text,re.S)[1])]
kitnames={1:'rocketbunny',3:'bn',4:'stickerbomb',5:'drag',6:'pandem',7:'fortune',8:'vxlip',9:'bashbar',10:'heavybashbar',11:'drag2',12:'tuner'};rows=[]
for body in range(191):
 base=image('sp_car',body);mask=image('sp_car_front',body).getchannel('A');hints=anchors[body];hx=round(hints[1]-12);bodyrows=[]
 for kit in range(13):
  im=base.copy();name='sp_'+str(kitnames.get(kit))+'_front';replacement=image(name,body) if name in ss else None;compatible=kit in (0,2) or replacement is not None and replacement.getbbox() is not None
  if kit and compatible:
   im.putalpha(ImageChops.subtract(im.getchannel('A'),mask))
   if replacement is not None:im.alpha_composite(replacement)
  choices=[]
  for x in range(max(0,hx-8),min(220,hx+9)):
   ys=[y for y in range(18,54) if im.getpixel((x,y))[3]>=250 and y+1<54 and im.getpixel((x,y+1))[3]>=250]
   if ys:
    y=min(ys);nearby=[]
    for nx in range(max(0,x-2),min(220,x+3)):
     q=[ny for ny in range(10,54) if im.getpixel((nx,ny))[3]>=250]
     if q:nearby.append(min(q))
    slope=max(nearby)-min(nearby) if nearby else 99;choices.append((slope*3+abs(x-hx),x,y))
  if choices:_,x,y=min(choices);fallback=kit==2 or not compatible
  else:x,y=hx,36;fallback=True
  bodyrows.append([x,y+1,int(compatible),int(fallback)])
 rows.append(bodyrows)
p=G/'src/customization_data.hpp';s=p.read_text();s=re.sub(r'inline constexpr HoodMount undergroundHoods\[191\]\[13\]=\{.*?\n\};\n','',s,flags=re.S);insert='inline constexpr HoodMount undergroundHoods[191][13]={\n'+'\n'.join('{'+','.join('{'+','.join(map(str,v))+'}' for v in row)+'},' for row in rows)+'\n};\n';pos=s.index('inline const HoodMount& hoodMount');s=s[:pos]+insert+s[pos:];s=s.replace('int kit,bool original','int kit,int original').replace('(original?originalHoods:unboundHoods)','(original==2?undergroundHoods:original==1?originalHoods:unboundHoods)');p.write_text(s)
(G/'validation/underground-hoods.json').write_text(json.dumps({'body_front_kit_cases':191*13,'mounts':rows,'method':'Native alpha silhouette fit; shared compiled anchors for rear and side pipes remain source literals.'},indent=2)+'\n');print('Fitted 2483 Underground hood/front-kit combinations.')
