from pathlib import Path
import subprocess, hashlib, json
# Preserve the report's historical byte encoding; only normalize line endings.
names=subprocess.check_output(['git','diff','55eec3b','--name-only']).decode('utf-8').splitlines()
for name in names:
    p=Path(name)
    if p.suffix in ['.cpp','.hpp','.py','.md']:
        raw=p.read_bytes().replace(b'\r\n',b'\n')
        p.write_bytes(raw.replace(b'\n',b'\r\n'))
# Reproducible inventory of the archived evidence without dumping private log text.
root=Path('build/research/run-51584')
paths=[root/'hq_economy.json',root/'console-redacted.log',root/'slice6-observations.txt',*sorted((root/'dw').glob('*.bin'))]
(root/'slice6-manifest.txt').write_bytes(('\n'.join(f'{hashlib.sha256(p.read_bytes()).hexdigest()}  {p.relative_to(root).as_posix()}' for p in paths)+'\n').replace('\n','\r\n').encode())
# Defined-string raw paths used by the report; the incorrect194BA0 offset was discarded.
p=Path('build/research/ghidra/decomp-slice6/194BA0.c')
if p.exists(): p.unlink()
print('Archived files:',len(paths),'scope: src/client and build/research; runbook HQ status only')
