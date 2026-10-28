#!/usr/bin/env python3
"""Install user-local build prerequisites, then build the pinned headless exporter."""
import argparse,hashlib,json,lzma,os,platform,subprocess,sys,urllib.request
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--work',type=Path,required=True);a=p.parse_args();work=a.work.resolve();work.mkdir(parents=True,exist_ok=True)
if platform.system()!='Linux' or platform.machine()!='x86_64':raise SystemExit('This bootstrap targets Linux x86_64. Use upstream CMake/Windows build on Windows; see SKILL.md.')
# No apt system mutation; extract build tools below the selected work directory.
python_root=work/'python';subprocess.run([sys.executable,'-m','pip','install','--target',str(python_root),'cmake==4.4.4','numpy>=1.26,<3'],check=True)
base='https://deb.debian.org/debian/';index=urllib.request.urlopen(base+'dists/bookworm/main/binary-amd64/Packages.xz',timeout=120).read();debs=work/'debs';debs.mkdir(exist_ok=True);sysroot=work/'sysroot';packages=[]
for block in lzma.decompress(index).decode().split('\n\n'):
    rows=dict(line.split(': ',1) for line in block.splitlines() if ': ' in line and not line.startswith(' '))
    if rows.get('Package') not in {'bison','flex','m4','libfl2','libfl-dev'}:continue
    filename=rows['Filename'];dest=debs/Path(filename).name;data=urllib.request.urlopen(base+filename,timeout=120).read()
    if hashlib.sha256(data).hexdigest()!=rows['SHA256']:raise RuntimeError('Debian package SHA256 mismatch')
    dest.write_bytes(data);subprocess.run(['dpkg-deb','-x',str(dest),str(sysroot)],check=True);packages.append({'name':rows['Package'],'version':rows['Version'],'sha256':rows['SHA256']})
env=dict(os.environ,BISON_PKGDATADIR=str(sysroot/'usr/share/bison'),M4=str(sysroot/'usr/bin/m4'))
cmd=[sys.executable,str(Path(__file__).with_name('build_exporter.py')),'--work',str(work/'exporter'),'--cmake',str(python_root/'cmake/data/bin/cmake'),'--flex',str(sysroot/'usr/bin/flex'),'--bison',str(sysroot/'usr/bin/bison')]
subprocess.run(cmd,env=env,check=True)
(work/'environment.json').write_text(json.dumps({'packages':packages,'exporter_root':str(work/'exporter'),'python_path':str(python_root),'command':cmd},indent=2)+'\n')
print('Use --exporter-root '+str(work/'exporter')+'; PYTHONPATH='+str(python_root)+' if numpy is not already installed.')
