from pathlib import Path
import re, shutil, json
root=Path(r'D:\Program Files\Steam\steamapps\common\Call of Duty WWII')
dump=root/'s2x/dump/dw'
latest=max(dump.glob('hq_marketplace_111_*'),key=lambda p:p.stat().st_mtime)
pid=latest.stem.split('_')[-2]
dest=Path('build/research')/('run-'+pid); (dest/'dw').mkdir(parents=True,exist_ok=True)
for p in dump.glob('*_'+pid+'_*.bin'): shutil.copy2(p,dest/'dw'/p.name)
log=(root/'s2x/logs/console.log').read_text(errors='replace')
boundary=log.rfind('Auth3')
# Preserve diagnostics but suppress authentication credential lines.
lines=[l for l in log.splitlines() if not re.search(r'(?i)ticket|auth.*(?:token|key)|session.?key|password',l)]
(dest/'console-redacted.log').write_text('\n'.join(lines)+'\n')
shutil.copy2(root/'players2/user/hq_economy.json',dest/'hq_economy.json')
data=json.loads((dest/'hq_economy.json').read_text())
(dest/'slice6-observations.txt').write_text('Latest task111 PID '+pid+'. Log copied as found (may span launches); credential lines redacted. No game run by agent.\n'+ '\n'.join(f"{a['name']} kind={a['kind']} status={a['status']} offerDay={a['offerDay']}" for a in data['achievements'])+'\n')
print(dest)
