from pathlib import Path
import re,json
p=Path('build/research/run-40144'); log=(p/'console-from-launch.log').read_text(); decoded=(p/'decoded.txt').read_text(encoding='utf-8-sig')
sections={}
for m in re.finditer(r'^service=.*?file=(\S+).*\n(.*?)(?=^service=|^===|\Z)',decoded,re.M|re.S):
 sections[m[1]]=m[2].split('  embedded JSON:')[0]
out=['PID 40144: console order (threads interleave; file sequence is allocation order).', 'Raw replies were not captured except injected AE JSON. Reply descriptions below are reconstructed from HEAD 384073d; unknown replies are explicitly not inferred.', 'No startup banner exists: slice begins at last authentication before PID 40144. Authentication diagnostics redacted.', 'All three unscoped task168 dumps match PID 40144 console lengths/previews. Earlier PID 57268 used the same filenames; its original _001 was overwritten by this newer run.', '']
reply={'111':'success; uint32 result count 0 (terminal SKU page)', '242':'success structured result: 17 08 00 00 00 00 (typed empty struct)', '42':'success, zero result count','60':'success, zero result count','49':'success, expired inventory records (count not logged)','132':'success, persisted currency records (count not logged)','165':'success, persisted inventory page (count not logged)','6':'MarketingComms only: success typed struct with 14 allocated ID-zero placeholders; each 0a10080012001a0022002a00320038004001'}
for n,line in enumerate(log.splitlines(),1):
 if not (line.startswith('[DW] ') or line.startswith('[HQ') or line.startswith('  ') or 'zone mp_hub' in line or '[DW-trace]' in line): continue
 out.append(f'L{n:04}: {line}')
 m=re.search(r"(bd\w+): (executing|missing) task '(\d+)'",line)
 if m:
  service,kind,task=m.groups()
  if kind=='missing': out.append('  REPLY: generic fallback success with zero results; no task implementation.')
  elif service=='bdReward': out.append('  REPLY: empty success acknowledgement; AE JSON delivered separately only for admitted native tasks; event tasks process batches locally.')
  elif service=='bdMarketplace': out.append('  REPLY (source): '+reply.get(task,'not captured'))
  elif service=='bdMarketingComms': out.append('  REPLY (source): '+reply.get(task,'not captured'))
  else: out.append('  REPLY: not captured (outside HQ handler investigation).')
 m=re.search(r'(?:at|wrote) s2x/dump/dw/(\S+)',line)
 if m and (p/'dw'/m[1]).exists():
  f=p/'dw'/m[1]; b=f.read_bytes()
  if b.startswith(b'{'):
   out.append('  JSON '+json.dumps(json.loads(b),separators=(',',':')))
  else: out.append(sections.get(f.name,'  decode unavailable').rstrip())
(p/'actions.txt').write_text('\n'.join(out)+'\n')
