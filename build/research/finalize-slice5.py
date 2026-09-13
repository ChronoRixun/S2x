from pathlib import Path
import re
p=Path('build/research/hq-economy-slice1-report.md');b=p.read_bytes();i=b.index(b'## Slice 5 -');s=b[i:].decode('utf-8')
s=re.sub(r'\bPID(\d+)',r'PID \1',s)
s=re.sub(r'\b(integration|revision|reader|setter|registration|table|Entry|entry|with|from|at|via|Fetch|records|eventType|balanceReady|inventoryReady|type|ready|count|price|ID|GUID|blob|blobs|field|task|Task|DW|size|stride|limit|kind|amount|quantity|maxQuantity|controller)(?=[0-9A-F])',r'\1 ',s)
s=s.replace('->',' -> ').replace('>=',' >= ').replace('13 slots','13 slots')
p.write_bytes((b[:i]+s.encode()).replace(b'\r\n',b'\n').replace(b'\n',b'\r\n'))
# Keep new text artifacts in the repository's CRLF style.
for name in ['slice5-payroll.md','slice5-quartermaster.md','slice5-mail.md','lui-vendor-bindings.txt']:
 p=Path('build/research')/name;b=p.read_bytes();p.write_bytes(b.replace(b'\r\n',b'\n').replace(b'\n',b'\r\n'))
