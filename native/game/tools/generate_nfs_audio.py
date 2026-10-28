#!/usr/bin/env python3
"""Generate the five additional NFS catalogue audio families with physical Engine Sim."""
import argparse,subprocess,sys
from pathlib import Path
repo=Path(__file__).resolve().parents[3]
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exporter-root',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args()
a.output.mkdir(parents=True,exist_ok=False)
skill=repo/'.agents/skills/car-engine-audio'
for name in ['nfs-i4','nfs-i6','nfs-h4','nfs-v6','nfs-v8-flat']:
 subprocess.run([sys.executable,str(skill/'scripts/generate.py'),'--description',str(skill/'profiles'/(name+'.json')),'--exporter-root',str(a.exporter_root),'--output',str(a.output/name),'--duration','3','--warmup','3'],check=True)
