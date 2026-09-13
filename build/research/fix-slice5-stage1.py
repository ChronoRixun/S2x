from pathlib import Path
p=Path('build/research/hq-tests/tests.cpp');s=p.read_text().replace('bdMarketplaceCurrency currency_wire{}; currency_wire.m_currencyId = 2; currency_wire.m_value = 200;', 'bdMarketplaceCurrency native_currency{}; native_currency.m_currencyId = 2; native_currency.m_value = 200;').replace('currency_wire.serialize(&currency_packet)', 'native_currency.serialize(&currency_packet)');p.write_bytes(s.replace('\n','\r\n').encode())
for name in ['A6069E0.c','A606FD0.c','A607030.c','00000B.c','00278F.c']:
 p=Path('build/research/ghidra/decomp-slice5')/name
 if p.exists():p.unlink()
