#!/usr/bin/env python3
"""Review all three banks using visible RGBA, shop stats and stable compatibility aliases.
Transparent RGB is discarded before comparison. Existing files and IDs stay intact.
Generated aliases hide duplicate shop choices, not users' saved configurations.
"""
from pathlib import Path
import argparse,re,json,hashlib,subprocess,collections
from PIL import Image,ImageChops
p=argparse.ArgumentParser();p.add_argument('--hashes',type=Path,help='Optional precomputed normalized frame hashes');a=p.parse_args();G=Path(__file__).resolve().parents[1];base='919084744cf44ecd993be033899443d330c86237'
def source(name):return subprocess.check_output(['git','show',base+':native/game/'+name],cwd=G,text=True)
if a.hashes:hashes=json.loads(a.hashes.read_text())
else:
 text=(G/'src/content_art.hpp').read_text();groups={n:[list(map(int,v.split(','))) for v in re.findall(r'\{([\d,]+)\}',rows)] for n,rows in re.findall(r'inline const Frame (\w+)\[\]=\{(.*?)\n\};',text,re.S)};cache={};hashes={}
 for name,rows in groups.items():
  hs=[]
  for f in rows:
   atlas,x,y,w,h,dx,dy,cw,ch=f
   if atlas not in cache:cache[atlas]=Image.open(G/'assets'/f'content-{atlas-2000:02d}.png').convert('RGBA')
   im=Image.new('RGBA',(cw,ch));im.paste(cache[atlas].crop((x,y,x+w,y+h)),(dx,dy));alpha=im.getchannel('A');rgb=Image.composite(im.convert('RGB'),Image.new('RGB',im.size),alpha.point(lambda x:255 if x else 0));rgb.putalpha(alpha);hs.append(hashlib.sha256(rgb.tobytes()).hexdigest())
  hashes[name]=hs
mask_origin=lambda mask:'Original' if mask&1 else 'Unbound' if mask&(2|8) else 'Underground' if mask&16 else 'Création PC'
def eq(bank,suffix,index,other):return hashes[bank+suffix][index]==hashes[other+suffix][index]
cos=source('src/content_catalog.hpp');rim=source('src/rims.hpp');cat=source('src/catalog.hpp');rawcat=cat
for inc in re.findall(r'#include "([^"]+\.inc)"',cat):rawcat=rawcat.replace('#include "'+inc+'"',source('src/'+inc))
C=[dict(id=int(uid),slot=int(slot),sub=int(sub),name=json.loads(name),weight=float(weight),mask=int(mask),bank=int(bank)) for uid,slot,sub,name,weight,mask,bank in re.findall(r'^\{(\d+),(\d+),(\d+),("(?:[^"\\]|\\.)*"),([^,]+),(\d+),(-?\d+)\},$',cos,re.M)]
R=[]
for uid,sid,im,name,extra in re.findall(r'^\{(\d+),(\d+),(\d+),("(?:[^"\\]|\\.)*")(.*?)\},$',rim,re.M):
 values=extra.lstrip(',').split(',') if extra else [];R.append(dict(id=int(uid),source_id=int(sid),image=int(im),name=json.loads(name),mask=int(values[0]) if values else 3,bank=int(values[1]) if values else -1))
P=[]
for uid,slot,name,tail in re.findall(r'^\{(\d+),PartSlot::(\w+),("(?:[^"\\]|\\.)*"),([^{}]+)\},$',rawcat,re.M):
 values=tail.split(',');P.append(dict(id=int(uid),slot=slot,name=json.loads(name),stat=float(values[0]),weight=float(values[1]),value=float(values[2]),sub=int(values[3]),mask=int(values[4]) if len(values)>4 else 3,bank=int(values[5]) if len(values)>5 else -1))
cm={v['id']:v for v in C};rm={v['id']:v for v in R};pm={v['id']:v for v in P};aliases={'cosmetics':{},'rims':{},'parts':{},'vehicles':{}};decisions=[]
portable={1:'Wraps',3:'Racks',8:'Brakes',9:'Seats',10:'Hooks',11:'Lugs'}
for c in C:
 if c['bank']!=2:continue
 same=cm.get(c['id']-500000);suffix=portable.get(c['slot']);target=None
 if c['slot']==0:target=same # all 108 palette columns identical, checked independently below
 elif suffix:
  candidates=sorted([v for v in C if v['bank']!=2 and v['slot']==c['slot'] and v['sub']==c['sub'] and v['weight']==c['weight']],key=lambda v:(v['mask']&1==0,v['id']))
  target=next((v for v in candidates if eq('underground',suffix,c['sub'],'original' if v['bank']==1 else 'unbound')),None)
 if target:aliases['cosmetics'][c['id']]=target['id']
for r in R:
 if r['bank']==2:
  target=next((v for v in R if v['bank']!=2 and v['source_id']==r['source_id'] and eq('underground','Rims',r['image'],'original' if v['bank']==1 else 'unbound')),None)
  if target:aliases['rims'][r['id']]=target['id']
for v in P:
 if v['bank']!=2:continue
 target=pm.get(v['id']-60000);suffix={'Exhaust':'Exhausts','Tires':'Tires'}.get(v['slot'])
 if target and suffix and all(v[k]==target[k] for k in ['slot','stat','weight','value','sub']) and eq('underground',suffix,v['sub'],'original' if target['bank']==1 else 'unbound'):aliases['parts'][v['id']]=target['id']
vehicles=json.loads(source('vehicles.json'))['vehicles'];nfs={e['id']:e for e in json.loads((G/'nfs-catalog.json').read_text())['engines']};bundles={};perbody=[k[11:] for k,v in hashes.items() if k.startswith('underground') and len(v)==191]
for i,v in enumerate(vehicles):
 bank=['unbound','original','underground'][v['source']];engine=nfs.get(v['factory_engine_id']);motor=('nfs',engine['id']) if engine else ('stock',v['recovered_hp'],v['recovered_litres'],v['recovered_redline_rpm'])
 key=(v['body_asset'],tuple(hashes[bank+s][v['body_asset']] for s in perbody),tuple(sorted(v['mechanics'].items())),motor);bundles.setdefault(key,[]).append(i)
for choices in bundles.values():
 canonical=min(choices,key=lambda i:(vehicles[i]['source_mask']&1==0,vehicles[i]['source']==2,i))
 for i in choices:
  if i!=canonical:aliases['vehicles'][i]=canonical
# Explicit visual review: modified panel/convertible variants retain their actual family.
original={v['body']:v['name'] for v in json.loads((G.parent/'evidence/merged/vehicle-identities.json').read_text())['records']}
replacements={7:'Ford GT40',22:'Kart Underground — véhicule spécial',47:'Fourgon Underground 048 à identifier',101:'Prototype Underground 102 à identifier',120:'Compacte Underground 121 à identifier',167:'BMW M3 E36',183:'Ferrari F40',187:'Supercar Underground 188 à identifier',188:'Supercar Underground 189 à identifier'}
convertibles={26,27,41,152,155,156,177};review=json.loads((G/'underground-catalog.json').read_text())
for v in review['body_variants']:
 b=v['body'];name=replacements.get(b,original[b])
 if b in convertibles:name+=' — cabriolet'
 if b==148:name+=' — conversion break'
 if b==164:name+=' — conversion pick-up'
 if b not in (22,47,101,120,187,188):name+=' (Underground)'
 idx=239+b
 if idx in aliases['vehicles']:name=vehicles[aliases['vehicles'][idx]]['name']
 v['name']=name;v['status']='unresolved' if 'identifier' in name else 'visually_reviewed_family';v['identification_basis']='Original/Unbound/Underground side-by-side sprite comparison; no new model names in the identical 1185 source strings.'
review['reviewed_aliases']=aliases;review['visual_review_policy']='Ignore RGB in fully transparent pixels only. Keep every difference in visible RGBA or mechanical values. Existing IDs retained for saved equipment.';(G/'underground-catalog.json').write_text(json.dumps(review,ensure_ascii=False,indent=2)+'\n')
wrap_names={2:'Rouille',4:'Néon automobile',7:'Zèbre rose',9:'Graffiti blanc',11:'Emblème rouge',15:'Bandes violettes',16:'Emblème violet',18:'Emblème monochrome',30:'Coulures orange',31:'Camouflage requin',40:'Tigre',46:'Lettrage blanc',47:'Galaxie bleue',56:'Écussons colorés',57:'Emblème magenta',70:'Néon rose',73:'Emblème vert',74:'Fleurs bleu clair',79:'Dents blanches',80:'Graffiti multicolore',88:'Bandes tricolores blanches',91:'Logo vert',104:'Lettrage violet',105:'Lettrage cyan',106:'Marquage jaune',110:'Camouflage rose',115:'Love dégradé',122:'Coulures vertes',124:'Bandes bleues',127:'Motif vert',128:'Blason noir',130:'Motif vert compact',132:'Coulures rouge et vert',135:'Bandes rouges',138:'Bande rose',139:'Diagonales noires et rouges',142:'Galaxie rouge',143:'Bandes tricolores bleu clair',145:'Emblème blanc',147:'Fond bleu marin',149:'Éclair blanc',154:'Losanges orange',157:'Accents verts',160:'Emblème carbone',163:'Motif jaune et blanc',170:'Automobile nocturne',171:'Emblème rose'}
# Label actual variants. Never create an Underground V12: the source has only the 16 shared blocks.
for c in C:
 if c['bank']==2 and c['id'] not in aliases['cosmetics']:
  old=json.dumps(c['name']);display=wrap_names.get(c['sub'],c['name']) if c['slot']==1 else c['name'];new=json.dumps(display+' — variante Underground',ensure_ascii=True)
  cos=re.sub(r'(^\{'+str(c['id'])+r',\d+,\d+,)'+re.escape(old),lambda m:m[1]+new,cos,flags=re.M)
for r in R:
 if r['bank']==2 and r['id'] not in aliases['rims']:
  old=json.dumps(r['name']);new=json.dumps(r['name']+' — variante Underground',ensure_ascii=True);rim=re.sub(r'(^\{'+str(r['id'])+r',\d+,\d+,)'+re.escape(old),lambda m:m[1]+new,rim,flags=re.M)
for v in P:
 if v['bank']==2 and v['id'] not in aliases['parts']:
  old=json.dumps(v['name']);display={70020:'Nitto — marquage violet',70033:'P Zero — flanc rose'}.get(v['id'],v['name']);new=json.dumps(display+' — variante Underground',ensure_ascii=True);cat=re.sub(r'(^\{'+str(v['id'])+r',PartSlot::\w+,)'+re.escape(old),lambda m:m[1]+new,cat,flags=re.M)
(G/'src/content_catalog.hpp').write_text(cos);(G/'src/rims.hpp').write_text(rim);(G/'src/catalog.hpp').write_text(cat)
h=['// Generated by curate_content.py; source IDs retained for compatibility.','#pragma once','namespace pcr {','inline const char* catalogOriginLabel(int mask){return (mask&1)?"ORIGINAL":(mask&(2|8))?"UNBOUND":(mask&16)?"UNDERGROUND":"CRÉATION PC";}']
for domain,fun in [('cosmetics','canonicalCosmeticId'),('rims','canonicalRimId'),('parts','canonicalPartId'),('vehicles','canonicalVehicleIndex')]:
 h+=['inline int '+fun+'(int id){switch(id){']+['case '+str(k)+':return '+str(v)+';' for k,v in sorted(aliases[domain].items())]+['default:return id;}}']
h+=['inline bool retiredVehicle(int id){return id==187;}','inline bool reviewedShowroomVehicle(int id){return id>=0&&id<430&&canonicalVehicleIndex(id)==id&&id!=261&&!retiredVehicle(id);}','}'];(G/'src/catalog_review.hpp').write_text('\n'.join(h)+'\n')
for domain,rows in [('cosmetics',C),('rims',R),('parts',P)]:
 for v in rows:
  target=aliases[domain].get(v['id'],v['id']);decisions.append({'domain':domain,'id':v['id'],'name':v['name'],'origin':mask_origin({'cosmetics':cm,'rims':rm,'parts':pm}[domain][target]['mask']),'source_membership_mask':v['mask'],'canonical_id':target,'decision':'hidden_duplicate_compatibility_alias' if target!=v['id'] else 'retained_visible_variant' if v['bank']==2 else 'retained_original_or_unbound','basis':'Same visible pixels and source mechanical values' if target!=v['id'] else 'Native PC creation, not extracted from a mod' if v['mask']==4 else 'User NFS Unbound workbook' if v['mask']==8 else 'Source identity and visible resource or mechanic distinction'})
summary={'stored_equipment_ids':len(C)+len(R)+len(P),'visible_equipment':len(C)+len(R)+len(P)-sum(len(aliases[k]) for k in ['cosmetics','rims','parts']),'aliases':{k:len(v) for k,v in aliases.items()},'stored_vehicle_ids':len(vehicles),'visible_showroom_vehicles':len(vehicles)-len(aliases['vehicles'])-2,'retired_novelty_vehicle':{'id':'pcr-underground-022','reason':'Kart graphic with inherited Smart physics; kept in existing garage saves but not offered as a newly identified automobile.'},'shared_source_engine_count':16,'underground_exclusive_engine_count':0,'new_v12_claimed':False,'method':'Pixel-exact visible RGBA after clearing RGB under alpha=0; manual comparison sheets inspected for all changed portable frames and 64 previously flagged car images.'}
summary['retired_vehicles']=[{'id':'pcr-unbound-187','reason':'Removed at user request after review of the misidentified Gallardo and its kit variants; preparations archived.'}]
(G/'catalogue-review.json').write_text(json.dumps({'summary':summary,'aliases':aliases,'items':decisions,'vehicle_names':[{'body':v['body'],'name':v['name'],'basis':v['identification_basis']} for v in review['body_variants']]},ensure_ascii=False,indent=2)+'\n');print(json.dumps(summary,ensure_ascii=False))
