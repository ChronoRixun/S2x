from pathlib import Path
import re,shutil
src=Path(r'D:\Program Files\Steam\steamapps\common\Call of Duty WWII\s2x')
out=Path('build/research/run-40144'); (out/'dw').mkdir(parents=True,exist_ok=True)
log=(src/'logs/console.log').read_text(errors='replace')
first=log.index('hq_injected_ae_request_40144_0.bin')
start=log.rfind('[DW]: [auth]: user requested authentication.',0,first)
s=log[start:]
s=re.sub(r'^.*(?:AES dec key|AES enc key|Hash verify|Response id):.*$', '[authentication diagnostic redacted]',s,flags=re.M)
(out/'console-from-launch.log').write_text(s)
files=list((src/'dump/dw').glob('hq_*_40144_*.bin'))
for name in re.findall(r'wrote s2x/dump/dw/(\S+)',s):
 p=src/'dump/dw'/name
 if p.exists(): files.append(p)
for p in files: shutil.copy2(p,out/'dw'/p.name)
print(len(files),'dumps copied; no startup banner in console, last auth boundary used')
