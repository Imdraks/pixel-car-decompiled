#!/usr/bin/env python3
"""Import the user's NFS workbook as data; calibrations are native, not NFS physics."""
import csv
import argparse,hashlib,json,re,unicodedata
from pathlib import Path
import openpyxl
G=Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser(description=__doc__);p.add_argument('workbook',type=Path);a=p.parse_args()
w=openpyxl.load_workbook(a.workbook,read_only=True,data_only=True)
def rows(sheet):return list(w[sheet].values)[1:]
def q(x):return json.dumps(x,ensure_ascii=True)
def num(x,fallback=0):
 try:return float(x)
 except (TypeError,ValueError):return fallback
grades=['Basic','Sport','Pro','Super','Elite','Contrebande']
# Explicit generation/model bridges; year/trim differences remain labelled in the report.
bridges={2:'Subaru Impreza WRX STI (2006)',53:'Nissan GT-R R35 (2017)',3:'Nissan 350Z (2008)',6:'Nissan Skyline GT-R R34 (1999)',11:'Honda NSX-R (1992)',14:'BMW M3 (2006)',15:'Nissan 180SX Type X (1996)',16:'Honda Integra Type R (1998)',19:'Mazda RX-8 Spirit R (2011)',20:'Nissan Skyline GT-R R32 (1993)',24:'Nissan 370Z Heritage Edition (2019)',25:'Nissan Silvia S15 (2002)',26:'Subaru BRZ Premium (2014)',27:'Honda S2000 (2009)',28:'Nissan Silvia S14 (1998)',29:'Nissan Silvia S14 (1998)',32:'Mazda MX-5 (1996)',36:'Mazda RX-7 Spirit R (2002)',38:'Mitsubishi Lancer Evolution X (2008)',42:'BMW M3 Evolution II (1988)',45:'Subaru Impreza WRX STI (2010)',60:'Dodge Charger SRT Hellcat (2019)',61:'Dodge Challenger SRT8 (2014)',62:'Ford Mustang Foxbody (1990)',63:'Volkswagen Golf GTI (1976)',66:'Mazda MX-5 (2015)',67:'Acura NSX (2017)',74:'Volkswagen Beetle (1963)',78:'Dodge Charger R/T (1969)',79:'BMW M4 Coupé (2018)',87:'Mitsubishi Eclipse GSX (1999)',90:'Nissan Fairlady 240ZG (1971)',95:'Nissan GT-R R35 Nismo (2017)',102:'Mercedes-AMG A 45 (2016)',104:'Audi RS 6 Avant (2020)',105:'Honda Civic Type R (2015)',112:'Ford Focus RS (2016)',114:'Dodge Charger SRT Hellcat (2019)',115:'Jaguar F-Type R Coupé (2016)',120:'Alfa Romeo Giulia Quadrifoglio (2016)',121:'BMW M5 (2018)',148:'Buick Grand National GNX (1987)',156:'Chevrolet Corvette ZR1 (2019)',164:'Mercedes-Benz 190E 2.5-16 (1988)',167:'BMW M1 (1981)',183:'DMC DeLorean (1981)',184:'Chevrolet Bel Air (1955)',185:'Pontiac Firebird (1977)',187:'Audi R8 Coupé V10 (2019)',189:'Mercedes-AMG GT S (2019)'}
# Generic/uncertain generation identities are not silently resolved (e.g. Porsche 911).
engines=[];pc=[];parts=[];meta=[]
for index,r in enumerate(rows('145 moteurs')):
 layout,hp,litres,grade,potential,price,_,url,donor,*_=r;id=20000+index
 maxima=[float(x) for x in re.findall(r'\d+(?:\.\d+)?',str(potential))];maximum=max(hp,min(maxima)) if maxima else hp
 electric=layout=='Électrique';hybrid='hybride' in layout;family=layout.split()[0]
 cylinders={'F4':4,'F6':6,'F12':12,'I3':3,'I4':4,'I6':6,'V6':6,'V8':8,'V10':10,'V12':12,'W16':16}.get(family,0)
 rpm={'Électrique':16000,'F4':7500,'F6':8000,'F12':7200,'I3':6500,'I4':7800,'I6':7500,'Wankel':8500,'V6':7500,'V8':7200,'V10':8500,'V12':8500,'W16':6700}.get(family,7500)
 if family=='I4' and hp<150:rpm=6500
 if family=='I4' and 'S2000' in donor:rpm=9000
 if family=='V8' and hp<350:rpm=6000
 if 'SVJ' in donor:rpm=8700
 slug={'I4':'nfs_i4','I6':'nfs_i6','F4':'nfs_h4','V6':'nfs_v6','V8':'gm_ls_v8','V10':'huracan_v10','V12':'aventador_svj_v12'}.get(family,'')
 if family=='V8':
  if any(x in donor for x in ['Ferrari','McLaren','Koenigsegg']):slug='nfs_v8_flat'
  elif 'Mercedes-AMG' in donor:slug='amg_gt63s_2021'
  elif 'Mustang' in donor and litres=='5.0':slug='ford_coyote_v8'
 on,off={'F4':(23,21),'F6':(47,20),'F12':(78,24),'I3':(21,20),'I4':(21,20),'I6':(71,23),'V6':(47,20),'V8':(24,20),'V10':(73,24),'V12':(78,24),'Wankel':(80,20),'W16':(24,20)}.get(family,(20,20))
 litres=num(litres);g=grades.index(grade);weight=150+cylinders*13 if not electric else (1200 if hp<1000 else 1500)
 row={'id':id,'sheet_row':index+2,'family':layout,'hp':hp,'litres':litres,'grade':grade,'potential_raw':potential,'potential_hp':maximum,'potential_ambiguous':len(maxima)!=1,'price':price,'donor':donor,'source':url,'donor_status':r[11],'redline_rpm':rpm,'redline_is_estimate':True,'audio_family':slug or ('silent_electric' if electric else 'legacy_approximation'),'audio_exact_vehicle':False}
 engines.append(row);name=f"Unbound {layout} {litres:g}L {hp} HP" if not electric else f"Unbound Electrique {hp} HP"
 parts.append('{'+f'{id},PartSlot::Engine,{q(name)},{hp},{weight},{num(price)},{max(1,min(cylinders,16))},8,-1'+'},')
 peak={'F4':.64,'F6':.72,'F12':.69,'I3':.62,'I4':.72,'I6':.64,'Wankel':.78,'V6':.65,'V8':.60 if hp<400 else .67,'V10':.76,'V12':.72,'W16':.60}.get(family,.65)
 low={'I4':.42,'I6':.52,'V6':.52,'V8':.65,'V10':.38,'V12':.40,'Wankel':.30}.get(family,.5)
 inertia=round(min(.55,max(.10,.08+litres*.025+cylinders*.007)),4)
 blower=any(x in donor for x in ['Hellcat','Challenger SRT8']) and 'Hellcat' in donor
 factory_boost=11.6 if blower else 16 if any(x in donor for x in ['GT-R','Mercedes-AMG','BMW M5 (2018)','BMW M4','Lancer Evolution','Focus RS','Civic Type R (2015)','RX-7 Spirit R']) else 0
 row['native_inertia']=inertia;row['native_weight_lb']=weight;row['factory_boost_audio_psi_estimate']=factory_boost
 pc.append('{'+f'{id},{rpm},{litres},{cylinders},{rpm*peak},{rpm*.40},{low},{inertia},{on},{off},{factory_boost},{str(blower).lower()}'+'},')
 meta.append('{'+f'{id},{q(layout)},{q(donor)},{hp},{maximum},{litres},{g},{rpm},{str(electric).lower()},{str(hybrid).lower()},{q(slug)}'+'},')
# New categories append indices, preserving every legacy save slot.
slots={'Admission':('Intake',6),'ECU':('Ecu',4),'Alimentation carburant':('Fuel',11),'Échappement':('Exhaust',9),'Nitro':('Nos',5),'Suralimentation':('Turbo',2),'Refroidissement batterie':('BatteryCooling',16),'Système électrique':('Electrical',17),'Composants moteurs':('MotorComponents',18),'Surcharge':('Overcharge',19),'Suspension':('Suspension',1),'Freins':('Brakes',12),'Pneus':('Tires',10),'Embrayage':('Clutch',13),'Différentiel':('Differential',14),'Boîte':('Gearbox',15)}
upgrades=[];umeta=[]
for index,r in enumerate(rows('Pièces perf')):
 family,kind,variant,grade,price,effect,note,url=r;id=21000+index;g=grades.index(grade);strength=[.04,.15,.35,.65,1][g];slot,slotno=slots[kind];vi=0
 if kind=='Suralimentation':
  if 'Compresseur' in variant:slot='Supercharger'
  vi={'Atmosphérique':0,'Turbo simple':1,'Double turbo':2,'Compresseur centrifuge':3,'Compresseur Roots':4,'Compresseur à vis':5}[variant]
 if kind=='Pneus':vi=['Neutres','Grip','Drift','Route','Tout-terrain','Drift Pro'].index(variant)
 if kind=='Suspension':vi=['Neutre','Route','Tout-terrain'].index(variant)
 stat={'Intake':5+27*strength,'Ecu':300*strength,'Fuel':strength,'Exhaust':10+80*strength,'Nos':25+175*strength,'Turbo':0 if vi==0 else 8+26*strength,'Supercharger':8+26*strength,'Suspension':strength,'Brakes':13+3*strength,'Tires':120+200*strength,'Clutch':.15-.10*strength,'Differential':strength,'Gearbox':int(re.search(r'\d+',variant)[0]) if kind=='Boîte' else 0,'BatteryCooling':strength,'Electrical':strength,'MotorComponents':strength,'Overcharge':30+220*strength}[slot]
 sub={'Engine':1,'Intake':2,'Ecu':1,'Exhaust':1,'Nos':1,'Turbo':2,'Supercharger':1,'Suspension':1,'Tires':1}.get(slot,0)
 weight={'Suspension':130-30*strength,'Intake':10,'Exhaust':80,'Turbo':45,'Supercharger':60}.get(slot,0)
 name=f'Unbound {kind} {variant} {grade}'
 parts.append('{'+f'{id},PartSlot::{slot},{q(name)},{stat},{weight},{num(price)},{sub},8,-1'+'},')
 upgrades.append({'id':id,'sheet_row':index+2,'family':family,'kind':kind,'variant':variant,'grade':grade,'price':price,'effect':effect,'note':note,'source':url,'slot':slot,'strength':strength,'native_stat':stat})
 umeta.append('{'+f'{id},{g},{slotno},{vi},{strength}'+'},')
# Contraband additions for appended categories have native values above their Elite versions.
for slot,slotno,stat in [('Fuel',11,1.3),('Brakes',12,17),('Clutch',13,.04),('Differential',14,1.3),('Gearbox',15,10),('BatteryCooling',16,1.3),('Electrical',17,1.3),('MotorComponents',18,1.3),('Overcharge',19,300)]:
 id=22000+slotno;parts.append('{'+f'{id},PartSlot::{slot},{q("PC "+slot+" Contrebande")},{stat},0,100000,0,4,-1'+'},');umeta.append('{'+f'{id},5,{slotno},0,1.3'+'},')
# Normalize unique workbook identities; compatibility cells occasionally leave grade unspecified.
def engine_key(layout,hp,litres):return (layout,int(hp),num(litres))
lookup={engine_key(e['family'],e['hp'],e['litres']):e['id'] for e in engines}
compat=[];unresolved=[]
for i,r in enumerate(rows('Compatibilités détaillées'),2):
 car,role,layout,hp,litres,grade,donor,source,note=r;id=lookup.get(engine_key(layout,hp,litres))
 if not id:unresolved.append({'sheet_row':i,'car':car,'family':layout,'hp':hp,'litres':litres});continue
 compat.append({'car':car,'origin':role=='Origine','engine_id':id,'donor':donor,'sheet_row':i,'source':source})
identities=json.loads((G.parent/'evidence/merged/vehicle-identities.json').read_text());replaced={r['body'] for r in identities['unbound_visual_replacements']};matches=[]
for body,car in bridges.items():
 assert any(r['car']==car for r in compat),car
 for bank in [0,1]:
  if bank==0 and body in replaced:continue
  rel=[r for r in compat if r['car']==car]
  for row in rel:matches.append({**row,'body':body,'source':bank,'table_source':row['source'],'mapping':'explicit_model_generation_bridge; trim/year may differ','game_name':identities['records'][body]['name']})
header=['// Generated from the supplied workbook. Grades/prices are data; physics/RPM/audio are native approximations.','#pragma once','namespace pcr {','struct NfsEngine {int id;const char* family;const char* donor;double hp,potentialHp,litres;int grade;double redline;bool electric,hybrid;const char* audioFamily;};','inline constexpr NfsEngine NfsEngines[]={',*meta,'};','inline const NfsEngine* nfsEngine(int id){return id>=20000&&id<20145?&NfsEngines[id-20000]:nullptr;}','struct NfsUpgrade {int id,grade,kind,variant;double strength;};','inline constexpr NfsUpgrade NfsUpgrades[]={',*umeta,'};','inline const NfsUpgrade* nfsUpgrade(int id){if(id>=21000&&id<21113)return &NfsUpgrades[id-21000];if(id>=22011&&id<=22019)return &NfsUpgrades[113+id-22011];return nullptr;}','inline int nfsGrade(int id){if(auto e=nfsEngine(id))return e->grade;if(auto p=nfsUpgrade(id))return p->grade;return -1;}','struct NfsCompatibility {int body,source,engineId;bool origin;};','inline constexpr NfsCompatibility NfsCompatibilities[]={']
header+=['{'+f'{r["body"]},{r["source"]},{r["engine_id"]},{str(r["origin"]).lower()}'+'},' for r in matches]
header+=['};','inline int nfsCompatibility(int body,int source,int engineId){for(const auto& r:NfsCompatibilities)if(r.body==body&&r.source==source&&r.engineId==engineId)return r.origin?2:1;return 0;}','inline int nfsFactoryEngine(int body,int source){for(const auto& r:NfsCompatibilities)if(r.body==body&&r.source==source&&r.origin)return r.engineId;return 0;}','}']
(G/'src/nfs_catalog.hpp').write_text('\n'.join(header)+'\n');(G/'src/nfs_engine_parts.inc').write_text('\n'.join(parts)+'\n');(G/'src/nfs_pc_engines.inc').write_text('\n'.join(pc)+'\n')
report={'workbook_name':a.workbook.name,'workbook_sha256':hashlib.sha256(a.workbook.read_bytes()).hexdigest(),'grades':grades,'engines':engines,'performance_parts':upgrades,'compatibilities':compat,'body_matches':matches,'unresolved_compatibilities':unresolved,'auxiliary_rows_not_implemented':rows('Auxiliaires'),'pursuit_rows_not_implemented':rows('Poursuite tech'),'limitations':['Workbook values are NFS Unbound data, not recovered Pixel Car Racer physics.','Body bridges may differ by trim/year; unknown bodies and visual replacements remain unmapped.','Audio is shared physical-family approximation or explicitly labelled legacy fallback; no NFS audio is supplied.','Police/pursuit and damage/repair auxiliary game modes do not exist in native free drive.','Potential power ranges use their lower bound; unknown potential stays at base power.','Missing prices remain null in evidence, displayed as zero in the prototype without purchases.']}
(G/'nfs-catalog.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n')
print(json.dumps({'engines':len(engines),'parts':len(upgrades),'new_contraband':9,'car_models':len(bridges),'body_source_pairs':len({(r['body'],r['source']) for r in matches}),'compatible_links':len(matches),'unresolved_compatibilities':len(unresolved)},indent=2))

with (G/'nfs-correspondances.csv').open('w') as f:
 writer=csv.writer(f,lineterminator="\n");writer.writerow(['body','source','game_name','nfs_car','role','engine_id','family','hp','litres','grade','donor','mapping'])
 by_id={e['id']:e for e in engines}
 for row in matches:
  e=by_id[row['engine_id']];writer.writerow([row['body'],row['source'],row['game_name'],row['car'],'origin' if row['origin'] else 'swap',e['id'],e['family'],e['hp'],e['litres'],e['grade'],e['donor'],row['mapping']])
