from pathlib import Path
import re
base=0x7ff7a3190000
folder=Path('build/research/ghidra/decomp-slice5')
rows=[]; globals_seen={}
for line in Path('build/research/ghidra/slice5-binding-pairs.txt').read_text().splitlines():
 name,reg,fn=line.split(); p=folder/(fn+'.c')
 if not p.exists():continue
 s=p.read_text(); calls=set(re.findall(r'FUN_([0-9a-f]+)',s)); examined={fn}; data=s
 # Include recovered inventory/store helpers; keep explicit frontier for other callees.
 for a in calls:
  off=int(a,16)-base; f=folder/(f'{off:06X}.c')
  if 0x270000<=off<0x280000 and f.exists():data+='\n'+f.read_text(); examined.add(f'{off:06X}')
 offsets={int(x,16)-base for x in re.findall(r'(?:DAT|Ram|PTR)_(?:FUN_)?([0-9a-f]{12,16})',data)}
 runtime=sorted(x for x in offsets if 0x1000000<x<0x10000000 and x!=0x1BD3D08)
 for v in runtime:globals_seen.setdefault(v,[]).append(name)
 rows.append(f'{name} table={reg} function={fn} examined={",".join(sorted(examined))}\n  runtime globals: '+(', '.join(f'{v:X}' for v in runtime) or 'none directly recovered')+'\n  direct calls: '+', '.join(sorted(f'{int(a,16)-base:X}' for a in calls if int(a,16)-base!=int(fn,16))))
Path('build/research/lui-vendor-bindings.txt').write_text('S2xFull; offsets = address - 7ff7a3190000. Defined-string registration pairs matching requested names, including unrelated namespaces for completeness.\nRuntime globals include table bases, not just scalar flags. Direct calls outside examined functions are a transitive-analysis frontier, not a claim of no further globals.\n\n'+'\n\n'.join(rows)+'\n')
# Diagnostic reads show bytes at each recovered runtime base; never dereference arbitrary values.
entries='\n'.join(f'\t\t0x{v:X}_g, // '+', '.join(names[:2]) for v,names in sorted(globals_seen.items()))
header='#pragma once\n\n// Recovered runtime references; provenance: build/research/lui-vendor-bindings.txt.\nnamespace hq_native\n{\n\tinline const std::uintptr_t vendor_globals[] =\n\t{\n'+entries+'\n\t};\n}\n'
Path('src/client/component/hq_vendor_globals.hpp').write_bytes(header.replace('\n','\r\n').encode())
print(len(rows),'bindings;',len(globals_seen),'runtime references')
p=Path('src/client/component/hq_native.cpp');s=p.read_text().replace('#include "component/scheduler.hpp"','#include "component/scheduler.hpp"\n#include "hq_vendor_globals.hpp"')
s=s.replace('\t\tutils::hook::detour sku_success_hook;', '\t\tutils::hook::detour sku_success_hook;\n\t\tutils::hook::detour purchase_hook;')
s=s.replace('\n\t\tvoid vendor_status()', '''
		void reject_purchase(unsigned, unsigned sku, unsigned, void* transaction, int)
		{
			// 276580 initializes this caller-owned bdString before validating a purchase.
			// A null string returns Lua nil in 11FDF0, without creating a native task.
			std::memset(transaction, 0, 25);
			console::warn("[HQ vendor] SKU %u purchase unavailable (local display catalog)\\n", sku);
		}

		void vendor_status()''')
s=s.replace('\t\t\tstatus();\n\t\t\tconsole::info("[HQ vendor]', '''			status();
			wallet_status();
			unsigned sku_count{};
			for (unsigned i = 0; i < 400; ++i)
			{
				const auto* sku = reinterpret_cast<const unsigned char*>(0x81038B0_g) + i * 0x2E8;
				if (!*reinterpret_cast<const unsigned*>(sku)) continue;
				++sku_count;
				console::info("[HQ vendor] SKU slot=%u id=%u type=%u max=%u prices=%u product=%u items=%u\\n", i,
					*reinterpret_cast<const unsigned*>(sku), *reinterpret_cast<const unsigned*>(sku + 4),
					*reinterpret_cast<const unsigned*>(sku + 12), sku[0x2E1],
					*reinterpret_cast<const unsigned*>(sku + 0x240), sku[0x244]);
			}
			console::info("[HQ vendor] catalogType=%u nonzeroSKUs=%u inventoryAndBalanceReady=%u\\n",
				*reinterpret_cast<const unsigned*>(0x81038AC_g), sku_count,
				utils::hook::invoke<bool>(0x27A210_g, 0));
			for (const auto address : vendor_globals)
			{
				MEMORY_BASIC_INFORMATION region{};
				if (!VirtualQuery(reinterpret_cast<const void*>(address), &region, sizeof(region)) ||
					region.State != MEM_COMMIT || (region.Protect & (PAGE_GUARD | PAGE_NOACCESS)) ||
					address - reinterpret_cast<std::uintptr_t>(region.BaseAddress) + 8 > region.RegionSize) continue;
				std::uint64_t raw{};
				std::memcpy(&raw, reinterpret_cast<const void*>(address), sizeof(raw));
				console::info("[HQ vendor global] offset=%llX raw8=%016llX (table base or scalar; see lui-vendor-bindings.txt)\\n",
					address - 0x0_g, raw);
			}
			console::info("[HQ vendor]''',1)
s=s.replace('\t\t\tsku_success_hook.create(0x27B700_g, sku_success);','\t\t\tsku_success_hook.create(0x27B700_g, sku_success);\n\t\t\tpurchase_hook.create(0x276580_g, reject_purchase);')
p.write_bytes(s.replace('\n','\r\n').encode())
