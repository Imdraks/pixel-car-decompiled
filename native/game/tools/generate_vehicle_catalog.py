#!/usr/bin/env python3
"""Build named, categorized vehicle definitions with stable IDs and factory engines."""
from pathlib import Path
import json,re,collections
G=Path(__file__).resolve().parents[1]
identities=json.loads((G.parent/'evidence/merged/vehicle-identities.json').read_text())
choices=[tuple(map(int,r)) for r in re.findall(r'\{(\d+),(\d+),(\d+)\}',(G/'src/body_choices.hpp').read_text())]
variant_data=json.loads((G/'vehicle-variants.json').read_text());variants=variant_data['variants']
variant_rows={(v['body'],v['source'],v['visual_variant']):v for v in variants}
choices += [(v['body'],v['source'],v['source_mask'],v['visual_variant']) for v in variants]
stocks=[list(map(float,r.split(','))) for r in re.findall(r'^\{([^{}]+)\},', (G/'src/stock_vehicles.hpp').read_text(),re.M)]
original={r['body']:r['name'] for r in identities['records']};alternate={r['body']:r['name'] for r in identities['unbound_visual_replacements']}
nfs=json.loads((G/'nfs-catalog.json').read_text());origins={(r['body'],r['source']):r['engine_id'] for r in nfs['body_matches'] if r['origin']}
compact={0,1,4,5,12,16,22,39,40,48,55,58,63,65,69,72,73,74,82,84,102,105,108,110,111,113,135,137,139,140,144,146,147,154,157,160,168,169,179}
sedans={18,21,37,43,44,45,51,54,60,64,80,81,85,92,94,97,99,104,106,114,118,119,120,121,122,125,129,132,138,141,165,166,167,170,171,172,176,178,181}
muscle={7,52,61,62,68,71,75,78,89,98,124,126,145,149,150,151,152,175,185}
supercar={11,53,67,70,88,95,96,101,115,123,155,156,177,186,187,188,189}
utility={23,47,123,174,180}
categories=['COMPACTES','BERLINES / BREAKS','SPORTIVES','MUSCLE CARS','GT / SUPERCARS','UTILITAIRES','CLASSIQUES','À IDENTIFIER']
def category(body,name):
 if 'identifier' in name or 'confirmer' in name:return 7
 if name.startswith(('Porsche 911','Lamborghini ','Ford GT40','Ferrari F40')):return 4
 if body in utility:return 5
 if body in muscle:return 3
 if body in compact:return 0
 if body in supercar:return 4
 if body in sedans:return 1
 year=re.match(r'^(\d{4})',name)
 return 6 if year and int(year[1])<1980 else 2
def stock_sound(body,name):
 # Identification alone does not certify a new factory audio assignment.
 if name.startswith('Lamborghini '):return 0
 if 'Porsche 911' in name:return 20008
 if 'Clio V6' in name:return 20064
 if body==94:return 1502
 if any(x in name for x in ['Subaru','BRZ']):return 20005
 if any(x in name for x in ['RX-7','RX-8','RX-3']):return 1513
 if 'LFA' in name:return 1507
 if 'Viper' in name:return 1506
 if 'GT-R' in name and 'R35' in name:return 1007
 if 'Skyline' in name:return 1005
 if any(x in name for x in ['Supra','Aristo','Chaser','Soarer','Crown','2000GT']):return 1002
 if any(x in name for x in ['Silvia','180SX','Sileighty','Onevia']):return 1001
 if any(x in name for x in ['Lancer','Eclipse','Talon']):return 1003
 if any(x in name for x in ['Civic','Integra','Fit','CR-X','S2000']):return 1003
 if 'NSX' in name or '350Z' in name or '370Z' in name or 'G35' in name:return 20064
 if 'AMG' in name and '45' not in name:return 1501
 if 'Mustang' in name or 'Shelby' in name:return 1505
 if any(x in name for x in ['Chevrolet','Dodge','Pontiac','Cadillac','Ford GT','HSV','F-Type','Lexus RC','Lexus LC','IS-F','Vantage']):return 1008
 return 1003 if stocks[body][5]<=2.5 else 1008 if stocks[body][5]>=4 else 1002
underground=json.loads((G/'underground-catalog.json').read_text()) if (G/'underground-catalog.json').exists() else {};under_names={r['body']:r['name'] for r in underground.get('body_variants',[])}
rows=[];definitions=[];engines=[];q=lambda x:json.dumps(x,ensure_ascii=True)
for index,choice in enumerate(choices):
 body,source,mask=choice[:3];variant=choice[3] if len(choice)>3 else 0;extra=variant_rows.get((body,source,variant),{})
 name=under_names[body] if source==2 else alternate.get(body,original[body]) if source==0 else original[body];name=extra.get('name',name);cat=category(body,name)
 key='pcr-'+('underground' if source==2 else 'shared' if mask&3==3 else 'original' if source==1 else 'unbound')+f'-{body:03d}'
 key=extra.get('id',key)
 reference=extra.get('factory_engine_id',origins.get((body,source),0));stock_id=30000+index
 mechanical=list(stocks[body]);mechanical[6]=int(mechanical[6]);provisional=body==63 and source==0
 if provisional:
  # Identified 911 family, trim/year uncertain: conservative F6/RWD calibration,
  # not the Golf mechanics underneath the old sprite slot.
  reference=next(e['id'] for e in nfs['engines'] if e['family']=='F6' and e['hp']==281 and e['litres']==3.6)
  mechanical=[1350/.45359237,281,1250,165,6800,3.6,1]
 if extra:
  e=next(e for e in nfs['engines'] if e['id']==reference)
  mechanical[1]=e['hp'];mechanical[4]=7500;mechanical[5]=e['litres'];mechanical[6]=1
  provisional=True
 factory_id=reference or stock_id
 hp=mechanical[1];litres=mechanical[5];rpm=mechanical[4];sound=stock_sound(body,name)
 if cat==7:sound=0
 if extra:sound=reference
 legacy_lamps=body in variant_data['legacy_lamp_masks'].get('unbound' if source==0 else 'underground' if source==2 else 'original',[])
 label=f'Origine {litres:g}L - {name}'
 definitions.append('{'+f'{q(key)},{q(name)},{cat},{body},{source},{mask},{factory_id},{stock_id},{sound},'+ '{'+','.join(map(str,mechanical))+'},'+str(reference>0).lower()+','+str(provisional).lower()+','+str(variant)+','+str(extra.get('base_kit',0))+','+str(float(extra.get('wheel_front',0)))+'f,'+str(legacy_lamps).lower()+'},')
 engines.append('{'+f'{stock_id},PartSlot::Engine,{q(label)},{hp},250,0,0,{mask},-1'+'},')
 rows.append({'id':key,'name':name,'category':categories[cat],'body_asset':body,'source':source,'source_mask':mask,'retired':False,'visual_variant':variant,'base_kit':extra.get('base_kit',0),'legacy_lamp_masks':legacy_lamps,'factory_engine_id':factory_id,'fallback_factory_engine_id':stock_id,'nfs_origin_reference':reference or None,'factory_assignment_kind':'NFS_Ford_GT_2017_powertrain; source-slot chassis calibration' if extra else 'provisional_Porsche_911_family; trim/year unconfirmed' if provisional else 'declared_model_bridge; year/trim may differ' if reference else 'recovered_per_vehicle_stock','mechanics':{'mass_kg':mechanical[0]*.45359237,'hp':hp,'grip_raw':mechanical[2],'speed_mph':mechanical[3],'redline_rpm':rpm,'litres':litres,'drive':int(mechanical[6])},'provisional_physics':provisional,'recovered_hp':hp,'recovered_litres':litres,'recovered_redline_rpm':rpm,'fallback_audio_engine_id':sound,'identity_uncertain':cat==7 or (source==0 and any(r['body']==body and r['status'] not in ('user_confirmed','visually_reviewed') for r in identities['unbound_visual_replacements']))})
header=['// Generated named vehicle catalogue. Renderer body IDs are implementation details.','#pragma once','namespace pcr {','struct VehicleDefinition {const char* id;const char* name;int category,body,source,sourceMask,factoryEngineId,stockEngineId,audioEngineId;StockVehicle stock;bool nfsReference,provisionalPhysics;int visualVariant,baseKit;float wheelFront;bool legacyLampMasks;};','inline constexpr const char* VehicleCategories[]={'+','.join(q(s) for s in categories)+'};','inline constexpr VehicleDefinition VehicleCatalog[]={',*definitions,'};','inline constexpr Part FactoryEngineCatalog[]={',*engines,'};','inline const VehicleDefinition* vehicleForStockEngine(int id){return id>=30000&&id<'+str(30000+len(rows))+'?&VehicleCatalog[id-30000]:nullptr;}','}']
(G/'src/vehicle_catalog.hpp').write_text('\n'.join(header)+'\n')
(G/'vehicles.json').write_text(json.dumps({'source_meaning':{'0':'Unbound','1':'Original','2':'Underground'},'categories':categories,'vehicles':rows,'limits':['Names derive from reviewed source identities; uncertain models remain labelled.','NFS assignments are model bridges, not exact trim/year certification.','Unmapped vehicles retain their recovered per-vehicle factory engine, power and revs.','No donor compatibility restriction applies to NFS engines.']},ensure_ascii=False,indent=2)+'\n')
print(json.dumps({'vehicles':len(rows),'categories':dict(collections.Counter(r['category'] for r in rows)),'factory_nfs':sum(r['nfs_origin_reference'] is not None for r in rows),'factory_recovered':sum(r['nfs_origin_reference'] is None for r in rows)},ensure_ascii=False))
