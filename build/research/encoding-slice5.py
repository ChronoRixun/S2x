from pathlib import Path
import subprocess,re
p=Path('build/research/hq-economy-slice1-report.md');b=p.read_bytes();suffix=b[b.index(b'\r\n\r\n## Slice 5 -'):];original=subprocess.check_output(['git','show','HEAD:build/research/hq-economy-slice1-report.md']);p.write_bytes(original+suffix)
p=Path('build/RUNBOOK.md');s=p.read_text(encoding='utf-8')
def restore(m):
 try:return m[0].encode('cp1252').decode('utf-8')
 except (UnicodeEncodeError,UnicodeDecodeError):return m[0]
s=re.sub(r'[^\x00-\x7f]+',restore,s);p.write_bytes(s.replace('\n','\r\n').encode('utf-8'))
# Preserve prior report bytes when this script is rerun; all new scripts specify UTF-8.
p=Path('build/research/append-slice5-report.py');s=p.read_text(encoding='utf-8');s=s.replace("p.write_bytes((p.read_text()+report).replace('\\n','\\r\\n').encode())", "p.write_bytes(p.read_bytes()+report.replace('\\n','\\r\\n').encode('utf-8'))").replace('s=p.read_text()',"s=p.read_text(encoding='utf-8')");p.write_bytes(s.replace('\n','\r\n').encode('utf-8'))
