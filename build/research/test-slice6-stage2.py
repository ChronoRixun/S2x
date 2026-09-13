from pathlib import Path
p=Path('build/research/hq-tests/tests.cpp'); s=p.read_text()
s=s.replace('hq_vendor::catalog_result offer; byte_buffer offer_wire;', 'hq_vendor::catalog_result offer; offer.entry = *hq_marketplace::find_sku(0x20000D); byte_buffer offer_wire;')
s=s.replace('sku_id == 1','sku_id == 0x20000D').replace('product == 1','product == 0x20000D').replace('std::string("sd_mp", 6)',"std::to_string(0x20000D) + '\\0'").replace('currency_id == 2 && offer_reader','currency_id == 7 && offer_reader').replace('value == 200 &&\n  offer_reader','value == 50 &&\n  offer_reader')
s=s.replace('{0u,1u,999u}', '{0u,0x20000Du,999u}').replace('(type==100 && page==1 && id!=999)','(id == 0 || (id == 0x20000D && page == 1))').replace('hq_marketplace::parse_skus(&unknown_catalog,query,&selected) && !selected','!hq_marketplace::parse_skus(&unknown_catalog,query,&selected) && !selected')
at=s.index(' byte_buffer no_terminator')
s=s[:at]+'''
	{
		const auto entries = hq_marketplace::catalog();
		require(entries.size() == 774 && !hq_marketplace::find_sku(1) && !hq_marketplace::find_sku(2), "full table-derived collection catalog excludes drops");
		std::vector<unsigned> seen;
		hq_marketplace::sku_request page; page.limit = 100; page.types = {100};
		for (page.page = 1; ; ++page.page)
		{
			const auto values = hq_marketplace::sku_page(page);
			for (const auto& value : values) seen.push_back(value.id);
			if (values.size() < page.limit) break;
			require(page.page < 10, "catalog paging terminates");
		}
		require(seen.size() == entries.size() && std::adjacent_find(seen.begin(), seen.end()) == seen.end() && page.page == 8, "all catalog pages covered without duplicates");
		page.page = UINT32_MAX; require(hq_marketplace::sku_page(page).empty(), "page multiplication cannot overflow");
		page.page = 1; page.ids = {entries.front().id, entries.front().id}; page.types = {100,150};
		require(hq_marketplace::sku_page(page).size() == 2, "mixed byte type filters and duplicate ID filter");
		page.types = {99}; require(hq_marketplace::sku_page(page).empty(), "undefined SKU type has no fabricated offers");
		hq_marketplace::set_rarities({{entries.front().id, 4}, {entries.back().id, 999}});
		require(hq_marketplace::find_sku(entries.front().id)->price == 5000 && hq_marketplace::find_sku(entries.back().id)->price == 50, "single rarity price policy bounds");
		const auto buy_id = entries.back().id;
		require(hq_economy::transact([](auto& next) { next.currencies[7] = 49; return true; }), "purchase funds fixture");
		const auto before = hq_economy::snapshot();
		require(hq_marketplace::purchase("buy-test", buy_id, 1) == BD_MARKETPLACE_INSUFFICIENT_FUNDS_ERROR, "proper insufficient funds code");
		require(hq_economy::snapshot().revision == before.revision && !hq_economy::snapshot().inventory.contains({buy_id,0}), "failed purchase cannot grant or persist");
		require(hq_economy::transact([](auto& next) { next.currencies[7] = 150; return true; }), "fund purchase");
		require(hq_marketplace::purchase("buy-test", buy_id, 1) == BD_NO_ERROR, "collection purchase commits");
		hq_economy::invalidate();
		require(hq_marketplace::purchase("buy-test", buy_id, 1) == BD_NO_ERROR && hq_economy::snapshot().currencies.at(7) == 100 && hq_economy::snapshot().inventory.at({buy_id,0}).quantity == 1, "purchase replay after reload is exactly once");
		require(hq_marketplace::purchase("buy-test", entries.front().id, 1) == BD_MARKETPLACE_RESOURCE_CONFLICT, "purchase transaction reuse rejected");
		require(hq_marketplace::purchase("buy-again", buy_id, 1) == BD_MARKETPLACE_ITEM_MULTIPLE_PURCHASE_ERROR, "owned collection item cannot be charged twice");
		require(hq_marketplace::purchase("bad", buy_id, UINT32_MAX) == BD_MARKETPLACE_INVALID_PARAMETER && hq_marketplace::purchase("bad", 1, 1) == BD_MARKETPLACE_RESOURCE_NOT_FOUND, "invalid quantity and supply SKU rejected");
	}
''' + s[at:]
p.write_bytes(s.replace('\n','\r\n').encode())
