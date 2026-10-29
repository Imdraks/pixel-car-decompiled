#!/usr/bin/env python3
"""Append hash-checked Underground resources without changing existing atlas bytes.
Input: extracted sprite map/textures from the supplied APK. No APK code is run.
The matching YYC SHA establishes unchanged shop stats/anchor tables, not identities.
"""
from pathlib import Path
import argparse,json,re,hashlib,statistics,shutil,subprocess
from PIL import Image
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--root',type=Path,required=True);a=p.parse_args();G=Path(__file__).resolve().parents[1];r=a.root
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
assert sha(r/'lib/x86/libyoyo.so')=='fb3726e175e7d1c643e0ddac1ec1a365901c4d52a16ded97e89fd672f6a9e9cc','Unknown shop/anchor binary'
backup=G/'build/pre-underground';backup.mkdir(parents=True,exist_ok=True)
def baseline(name):
 q=G/name;b=backup/name
 if not b.exists():
  b.parent.mkdir(parents=True,exist_ok=True)
  if name.startswith('src/'):
   b.write_bytes(subprocess.check_output(['git','show','6b1f7ff38c54d02545ef1be27990a41e2b18c718:native/game/'+name],cwd=G))
  else:
   data=json.loads(q.read_text());data['files']=[v for v in data['files'] if not v['file'].startswith('audio-underground/') and not (re.fullmatch(r'content-\d+\.png',v['file']) and int(v['file'][8:10])>=6)];b.write_text(json.dumps(data,indent=2)+'\n')
 return b.read_text()
ss={s['name']:s for s in json.loads((r/'textures/sprites.json').read_text())['sprites']};tex={};issues=[]
for row in json.loads((r/'textures/textures.json').read_text()):assert sha(r/'textures'/row['file'])==row['sha256']
def sprite(name,i):
 s=ss[name];im=Image.new('RGBA',(s['width'],s['height']));f=s['frames'][i]
 if f:
  if f['file'] not in tex:tex[f['file']]=Image.open(r/'textures'/f['file']).convert('RGBA')
  src=tex[f['file']];x,y,w,h=f['source_rect']
  if x+w>src.width or y+h>src.height:issues.append({'sprite':name,'frame':i,'rect':[x,y,w,h],'atlas':list(src.size),'handling':'transparent padding outside atlas'})
  im.paste(src.crop((x,y,x+w,y+h)),tuple(f['target_offset']))
 return im
palette=sprite('sp_color_pal',0);custom=baseline('src/customization_data.hpp');palette_rows=['{'+','.join('0x'+''.join(f'{c:02x}' for c in palette.getpixel((x,y)))+'u' for y in range(11))+'},' for x in range(108)];custom=custom.rsplit('}',1)[0]+'inline constexpr unsigned undergroundPaint[108][11]={\n'+'\n'.join(palette_rows)+'\n};\n}\n';(G/'src/customization_data.hpp').write_text(custom)
base=baseline('src/content_art.hpp');groups={n:[list(map(int,v.split(','))) for v in re.findall(r'\{([\d,]+)\}',rows)] for n,rows in re.findall(r'inline const Frame (\w+)\[\]=\{(.*?)\n\};',base,re.S)}
cache={};dedup={}
def signature(im):return (im.size,hashlib.sha256(im.tobytes()).hexdigest())
for rows in groups.values():
 for f in rows:
  atlas,x,y,w,h,dx,dy,cw,ch=f
  if atlas not in cache:cache[atlas]=Image.open(G/'assets'/f'content-{atlas-2000:02d}.png').convert('RGBA')
  im=Image.new('RGBA',(cw,ch));im.paste(cache[atlas].crop((x,y,x+w,y+h)),(dx,dy));dedup[signature(im)]=f
start=int(re.search(r'AtlasCount=(\d+)',base)[1]);pages=[Image.new('RGBA',(2048,2048))];x=y=rowh=0
new={};changed={}
def pack(im):
 global x,y,rowh
 k=signature(im)
 if k in dedup:return dedup[k]
 dx,dy,xx,yy=im.getbbox() or (0,0,1,1);crop=im.crop((dx,dy,xx,yy));w,h=crop.size
 assert w<=2046 and h<=2046
 if x+w+2>2048:x=0;y+=rowh+2;rowh=0
 if y+h+2>2048:pages.append(Image.new('RGBA',(2048,2048)));x=y=rowh=0
 pages[-1].paste(crop,(x+1,y+1));f=[2000+start+len(pages)-1,x+1,y+1,w,h,dx,dy,*im.size];dedup[k]=f;x+=w+2;rowh=max(rowh,h);return f
maps=dict(Cars='sp_car',Wraps='sp_tex_wraps',Brakes='sp_brakes',Seats='sp_seats',Racks='sp_bike',Hooks='sp_towhook_part',Lugs='sp_lug',Headlights='sp_car_headlight',Taillights='sp_car_brakelight',Front='sp_car_front',Rear='sp_car_rear',Tires='sp_tire_0',Exhausts='sp_car_exhaust',Rollcages='sp_rollcage',HeadlightsNeo='sp_car_headlight_neo',HeadlightsFortune='sp_headlight_fortune',HeadlightsTuner='sp_headlight_tuner',HeadlightsDrag='sp_headlight_drag2',TaillightsFortune='sp_car_brakelight_fortune',TaillightsTuner='sp_car_brakelight_tuner')
kitnames={1:'rocketbunny',3:'bn',4:'stickerbomb',5:'drag',6:'pandem',7:'fortune',8:'vxlip',9:'bashbar',10:'heavybashbar',11:'drag2',12:'tuner'}
recipes=json.loads((G.parent/'evidence/merged/rims.json').read_text())['rims']
for n,old in groups.items():
 if not n.startswith('unbound'):continue
 suffix=n[7:]
 if suffix=='Rims':
  images=[]
  for recipe in recipes:
   fields=recipe['fields'];im=sprite('sp_adv_lip',fields['lip']);spoke=sprite('sp_adv_rims',fields['spoke'])
   for j in range(fields['count']):im.alpha_composite(spoke.rotate(360*j/fields['count'],resample=Image.Resampling.NEAREST,center=(31,31)))
   images.append(im)
 else:
  name=maps.get(suffix,suffix if suffix.startswith('sp_') else 'sp_spoiler_'+suffix[8:] if suffix.startswith('Spoiler_') else '')
  if suffix.startswith('Kit_'):
   _,kid,side=suffix.split('_');name='sp_'+kitnames[int(kid)]+'_'+side
  assert name in ss,(suffix,name)
  assert len(ss[name]['frames'])>=len(old),(name,len(old))
  images=[sprite(name,i) for i in range(len(old))]
 new[suffix]=[pack(im) for im in images];changed[suffix]=[i for i,f in enumerate(new[suffix]) if f!=old[i]]
# Native garage preview and driving scenery use the new bank's actual images.
for suffix,name in [('GarageScenery','sp_garage')]:
 new[suffix]=[pack(sprite(name,i)) for i in range(5)]
background_file=r/'backgrounds.json'
if background_file.exists():
 backgrounds={v['name']:v for v in json.loads(background_file.read_text())}
 for suffix,name in [('SceneSky','bg_sky'),('SceneMountains','bg_fuji'),('SceneCity','bg_city_l3')]:
  v=backgrounds[name];src=Image.open(r/'textures'/f"texture-{v['texture_id']:03d}.png").convert('RGBA');im=Image.new('RGBA',(v['width'],v['height']));im.paste(src.crop((v['x'],v['y'],v['x']+v['w'],v['y']+v['h'])),(v['dx'],v['dy']));new[suffix]=[pack(im)]
# Extend every rendering accessor to source=2. Existing 0/1 calls keep their behavior.
insert=[]
for suffix,rows in new.items():insert+=['inline const Frame underground'+suffix+'[]={',*['{'+','.join(map(str,f))+'},' for f in rows],'};']
base=re.sub(r'inline const Frame\* (\w+)\(bool original\)\{return original\?original\1:unbound\1;\}',lambda m:'inline const Frame* '+m[1]+'(int source){return source==2?underground'+m[1]+':source==1?original'+m[1]+':unbound'+m[1]+';}',base)
pos=base.index('inline const Frame* ');base=base[:pos]+'\n'.join(insert)+'\n'+base[pos:]
# Derive wheel arches using the same alpha rule as the existing importer.
anchors=[];anchorFallback=[]
oldanchors=[list(map(float,v.replace('f','').split(','))) for v in re.findall(r'\{([^{}]+)\}',re.search(r'unboundAnchors\[\]\[5\]=\{(.*?)\n\};',base,re.S)[1])]
for i in range(191):
 im=sprite('sp_car',i);px=im.load();rear,cy=ss['sp_car']['origin'];candidates=[]
 for yy in range(cy-14,cy+1):
  begin=None
  for xx in range(im.width):
   if px[xx,yy][3]<128:
    if begin is None:begin=xx
   elif begin is not None:
    mid=(begin+xx)/2
    if begin>0 and 5<=xx-begin<=44 and rear+30<=mid<=im.width-10:candidates.append((mid,yy))
    begin=None
 clusters=[]
 for mid,yy in candidates:
  group=next((g for g in clusters if abs(statistics.median(v[0] for v in g)-mid)<=2.5),None)
  if group is None:clusters.append([(mid,yy)])
  else:group.append((mid,yy))
 best=max(clusters,key=lambda g:len(set(v[1] for v in g))) if clusters else []
 if len(set(v[1] for v in best))>=3:front=statistics.median(v[0] for v in best);radius=12.5
 else:front=oldanchors[i][1];radius=oldanchors[i][3];anchorFallback.append(i)
 roof=min((yy for yy in range(50) for xx in range(55,145) if px[xx,yy][3]>128),default=30);anchors.append([rear,front,cy,radius,roof])
base=base.replace('inline constexpr int AtlasCount=', 'inline constexpr float undergroundAnchors[][5]={\n'+'\n'.join('{'+','.join(str(float(v))+'f' for v in row)+'},' for row in anchors)+'\n};\ninline constexpr int AtlasCount=');base=base.replace('AtlasCount='+str(start)+';','AtlasCount='+str(start+len(pages))+';');(G/'src/content_art.hpp').write_text(base)
# Complete-bundle deduplication, not only body silhouettes. Append IDs, never renumber old ones.
bc=baseline('src/body_choices.hpp');choices=[list(map(int,v)) for v in re.findall(r'\{(\d+),(\d+),(\d+)\}',bc)];names={v['body']:v['name'] for v in json.loads((G.parent/'evidence/merged/vehicle-identities.json').read_text())['records']};variants=[]
for i in range(191):
 match=None
 for choice in choices:
  body,source,mask=choice
  if body!=i:continue
  bank='original' if source==1 else 'unbound'
  if all(rows[i]==groups[bank+suffix][i] for suffix,rows in new.items() if len(rows)==191):match=choice;break
 if match is not None:match[2]|=16
 else:
  choices.append([i,2,16]);same= new['Cars'][i]==groups['originalCars'][i];variants.append({'body':i,'name':names[i]+' (Underground)' if same else f'Underground — véhicule {i+1:03d} à identifier','status':'shared_original_silhouette' if same else 'unresolved'})
bc=bc[:bc.index('inline constexpr BodyChoice BodyChoices[]=')]+ 'inline constexpr BodyChoice BodyChoices[]={\n'+'\n'.join('{'+','.join(map(str,c))+'},' for c in choices)+'\n};\n}\n';(G/'src/body_choices.hpp').write_text(bc)
# Cosmetics whose portable artwork differs get selectable source-specific IDs.
cos=baseline('src/content_catalog.hpp');rows=re.findall(r'^\{(\d+),(\d+),(\d+),("(?:[^"\\]|\\.)*"),([^,]+),(\d+),(-?\d+)\},$',cos,re.M);extra=[];cosvariants=[]
portable={1:'Wraps',3:'Racks',8:'Brakes',9:'Seats',10:'Hooks',11:'Lugs'}
for uid,slot,sub,name,weight,mask,source in rows:
 uid,slot,sub,mask,source=map(int,(uid,slot,sub,mask,source));suffix=portable.get(slot)
 if slot==0 or (suffix and sub<len(new[suffix]) and new[suffix][sub]!=groups[('original' if source==1 else 'unbound')+suffix][sub]):
  if source==1:continue
  if source<0:cos=cos.replace('{'+f'{uid},{slot},{sub},{name},{weight},{mask},{source}'+'},','{'+f'{uid},{slot},{sub},{name},{weight},{mask},0'+'},')
  if suffix and new[suffix][sub]==groups['original'+suffix][sub] and any(int(other[1])==slot and int(other[2])==sub and int(other[6])==1 for other in rows):continue
  extra.append('{'+f'{500000+uid},{slot},{sub},{name},{weight},16,2'+'},');cosvariants.append(500000+uid)
 else:
  cos=cos.replace('{'+f'{uid},{slot},{sub},{name},{weight},{mask},{source}'+'},','{'+f'{uid},{slot},{sub},{name},{weight},{mask|16},{source}'+'},')
pos=cos.index('\n};',cos.index('CosmeticCatalog'));cos=cos[:pos]+'\n'+'\n'.join(extra)+cos[pos:];(G/'src/content_catalog.hpp').write_text(cos)
rims=baseline('src/rims.hpp').replace('const char* name;','const char* name;int sourceMask=3,imageSource=-1;');extra=[];rimids=[]
for uid,sid,i,name in re.findall(r'^\{(\d+),(\d+),(\d+),("[^"\n]*")\},$',rims,re.M):
 uid,sid,i=map(int,(uid,sid,i))
 if new['Rims'][i]!=groups['unboundRims'][i]:
  rims=rims.replace('{'+f'{uid},{sid},{i},{name}'+'},','{'+f'{uid},{sid},{i},{name},3,0'+'},')
  extra.append('{'+f'{200000+sid},{sid},{i},{name},16,2'+'},');rimids.append(200000+sid)
 else:rims=rims.replace('{'+f'{uid},{sid},{i},{name}'+'},','{'+f'{uid},{sid},{i},{name},19,-1'+'},')
pos=rims.index('\n};',rims.index('RimCatalog'));rims=rims[:pos]+'\n'+'\n'.join(extra)+rims[pos:]
m=re.search(r'inline constexpr std::array<int,(\d+)> RimFrames\{([^}]+)\}',rims);rims=rims[:m.start()]+f'inline constexpr std::array<int,{int(m[1])+len(rimids)}> RimFrames'+'{'+m[2]+','+','.join(map(str,rimids))+'}'+rims[m.end():];(G/'src/rims.hpp').write_text(rims)
# Identical binary means every mechanical item keeps the existing balance/stat values.
# Portable changed exhaust/tyre assets get separate equip IDs with identical mechanics.
cat=baseline('src/catalog.hpp');extra=[];partids=[]
for line in cat.splitlines():
 m=re.fullmatch(r'\{(\d+),PartSlot::(\w+),("(?:[^"\\]|\\.)*"),([^{}]+)\},',line)
 if not m:continue
 uid,slot=int(m[1]),m[2];args=m[4].split(',')
 if uid>=11000 or uid in (3027,3028) or len(args)!=6:continue
 stat,weight,value,sub,mask,src=args;sub=int(sub);mask=int(mask);suffix={'Exhaust':'Exhausts','Tires':'Tires'}.get(slot)
 if suffix and sub<len(new[suffix]) and new[suffix][sub]!=groups['unbound'+suffix][sub]:
  if int(src)<0:cat=cat.replace(line,'{'+f'{uid},PartSlot::{slot},{m[3]},{stat},{weight},{value},{sub},{mask},0'+'},')
  extra.append('{'+f'{60000+uid},PartSlot::{slot},{m[3]},{stat},{weight},{value},{sub},16,2'+'},');partids.append(60000+uid)
 else:cat=cat.replace(line,'{'+f'{uid},PartSlot::{slot},{m[3]},{stat},{weight},{value},{sub},{mask|16},{src}'+'},')
pos=cat.index('\n};',cat.index('PartCatalog'));cat=cat[:pos]+'\n'+'\n'.join(extra)+cat[pos:];(G/'src/catalog.hpp').write_text(cat)
files=[]
for i,im in enumerate(pages):
 path=G/'assets'/f'content-{start+i:02d}.png';im.save(path,optimize=True);files.append({'file':path.name,'sha256':sha(path)})
prov=json.loads(baseline('assets/provenance.json'));prov['files']+=files;
current=json.loads((G/'assets/provenance.json').read_text());prov['files'] += [v for v in current['files'] if v['file'].startswith('audio-underground/')];(G/'assets/provenance.json').write_text(json.dumps(prov,indent=2)+'\n')
report={'archive_sha256':sha(r/'Underground.zip'),'game_droid_sha256':sha(r/'assets/game.droid'),'binary_sha256':sha(r/'lib/x86/libyoyo.so'),'binary_identical_to_unbound':True,'new_atlas_files':files,'body_variants':variants,'total_vehicles':len(choices),'changed_frames_vs_unbound':changed,'cosmetic_variant_ids':cosvariants,'rim_variant_ids':rimids,'performance_variant_ids':partids,'wheel_anchor_fallbacks':anchorFallback,'source_frame_issues':issues,'balance':'Identical source mechanics and rarity calculations; source label never multiplies stats. Turbo/supercharger exclusion and powertrain compatibility stay enforced.','limitations':['No new gameplay is inferred from resource differences.','Changed car silhouettes without confirmed identity are explicitly unnamed.','Source anchor literals are shared with Unbound; wheel arches recovered from Underground alpha.']}
audiofile=r/'audio/sounds.json'
if audiofile.exists():
 audio=json.loads(audiofile.read_text());report['audio_changed']=[v for v in audio if (G/'assets/audio-underground'/v['file']).exists()];report['audio_shared_count']=94-len(report['audio_changed'])
(G/'underground-catalog.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n');print(json.dumps({k:len(v) if isinstance(v,list) else v for k,v in report.items() if k in ['body_variants','total_vehicles','cosmetic_variant_ids','rim_variant_ids','performance_variant_ids','wheel_anchor_fallbacks','source_frame_issues','new_atlas_files']},ensure_ascii=False))
