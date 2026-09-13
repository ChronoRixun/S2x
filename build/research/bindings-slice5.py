from pathlib import Path
import re
s=Path('build/research/ghidra/slice5-strings.txt').read_text(); rows=[]
for m in re.finditer(r'STRING ([0-9a-f]+) ([^\n]+)\n pair\+8=([0-9a-f]+)\n ref ([0-9a-f]+) fn=none',s):
 name=m[2]; fn=int(m[3],16)
 if re.fullmatch(r'[A-Za-z_][A-Za-z_0-9]*',name) and 0x10000<fn<0x900000:
  rows.append((name,m[4],f'{fn:06X}'))
Path('build/research/ghidra/slice5-binding-pairs.txt').write_text('\n'.join(' '.join(r) for r in rows)+'\n')
print(' '.join(r[2] for r in rows if not (Path('build/research/ghidra/decomp-slice5')/(r[2]+'.c')).exists()))
