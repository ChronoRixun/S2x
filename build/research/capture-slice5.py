from pathlib import Path
p=Path('build/research/ghidra/scripts/Slice4Strings.java')
s=p.read_text().replace('Slice4Strings','Slice5Strings').replace('l.contains("vendor")||l.contains("marketplace")||l.contains("inventory_")||l.contains("marketing")||l.contains("storeready")||l.contains("entitlement")','l.matches(".*(store|market|vendor|quartermaster|sku|entitle|inventory|purchase|catalog|currency|balance|ready|fetched|payroll).* ".trim())')
s=s.replace('Function f=getFunctionContaining(r.getFromAddress());','Function f=getFunctionContaining(r.getFromAddress()); if(f==null) { try { out.println(" pair+8="+Long.toHexString(getLong(r.getFromAddress().add(8))-currentProgram.getImageBase().getOffset())); } catch(Exception e) {} }')
Path('build/research/ghidra/scripts/Slice5Strings.java').write_text(s)
p=Path('build/research/run-46420'); log=(p/'console-from-launch.log').read_text(); import re,shutil,json
src=Path(r'D:\Program Files\Steam\steamapps\common\Call of Duty WWII\s2x\dump\dw')
for name in re.findall(r'wrote s2x/dump/dw/(\S+)',log):
 if (src/name).exists(): shutil.copy2(src/name,p/'dw'/name)
out=['PID 46420 ordered observations. No click timestamps/manual hqmail output exist; UI attribution uses load boundaries and the payroll event.','Replies: captured files where available; otherwise source 5a6d86f only, not observed wire data.','Frontend: initial balance132, inventory165, SKU111, Mail6. Slim HQ: SKU111, conversion242 succeeds, metadata168. Payroll: Reward12 repeated, no balance refresh or AE claim. Full HQ: conversion242 succeeds, Orders actions; no Mail redemption request.','Unscoped dump files may have been overwritten by other PIDs; preserved as found.','']
for i,l in enumerate(log.splitlines(),1):
 out.append(f'L{i:04}: {l}')
 m=re.search(r'(?:at|wrote) s2x/dump/dw/(\S+)',l)
 if m and (p/'dw'/m[1]).exists():
  b=(p/'dw'/m[1]).read_bytes(); out.append('  '+(b.decode() if b.startswith(b'{') else b.hex()))
 if "executing task" in l:
  if 'bdReward' in l: out.append('  SOURCE REPLY: empty successful acknowledgement; separate AE injection for admitted tasks; events settled locally.')
  elif "'132'" in l: out.append('  SOURCE REPLY: persisted currency records (ubyte id, uint32 amount); run-start amount not captured.')
  elif "'111'" in l: out.append('  SOURCE REPLY: successful terminal empty SKU page.')
(p/'actions.txt').write_text('\n'.join(out)+'\n')
