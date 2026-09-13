from pathlib import Path
def write(p,s):Path(p).write_bytes(s.replace('\n','\r\n').encode())
def edit(p,f):write(p,f(Path(p).read_text()))
edit('src/client/game/demonware/hq_marketplace.hpp',lambda s:s.replace('bool parse_skus(byte_buffer* buffer, inventory_request& request);','bool parse_skus(byte_buffer* buffer, inventory_request& request, bool* includes_local_sku = nullptr);'))
edit('src/client/game/demonware/hq_marketplace.cpp',lambda s:s.replace('bool parse_skus(byte_buffer* buffer, inventory_request& request)','bool parse_skus(byte_buffer* buffer, inventory_request& request, bool* includes_local_sku)').replace('''		bool show_all{};''','''		if (includes_local_sku) *includes_local_sku = false;
		bool show_all{};''').replace('''		for (std::uint32_t i = 0; i < ids; ++i) if (!buffer->read_uint32(&id)) return false;''','''		bool selected_id = ids == 0;
		for (std::uint32_t i = 0; i < ids; ++i)
		{
			if (!buffer->read_uint32(&id)) return false;
			selected_id |= id == 1;
		}''').replace('''		for (std::uint32_t i = 0; i < types; ++i) if (!buffer->read_ubyte(&type)) return false;
		return buffer->read_string(&token) && token.size() <= 64 && hq_protocol::padding(buffer);''','''		bool selected_type = types == 0;
		for (std::uint32_t i = 0; i < types; ++i)
		{
			if (!buffer->read_ubyte(&type)) return false;
			selected_type |= type == 100;
		}
		if (!buffer->read_string(&token) || token.size() > 64 || !hq_protocol::padding(buffer)) return false;
		if (includes_local_sku) *includes_local_sku = request.page == 1 && selected_id && selected_type && token.empty();
		return true;'''))
edit('src/client/game/demonware/hq_vendor.hpp',lambda s:s.replace('\n\tclass result final', '''
	// Read-side chain A4A5A0 -> A4A510 -> A4A2C0, native stride 0x370.
	// One local display offer: table supplydroptypes.csv sd_mp, item GUID 1.
	// SKU/product ID and price are local policy; purchasing is unsupported.
	class catalog_result final : public bdTaskResult
	{
	public:
		void serialize(byte_buffer* buffer) override
		{
			buffer->write_uint32(1); // +20 SKU ID
			buffer->write_uint32(1); // +24 product ID
			buffer->write_ubyte(1); // +28
			buffer->write_blob("sd_mp"); // +29 bounded SKU data (64 bytes)
			buffer->write_ubyte(1); // +6A
			buffer->write_uint32(0); // +6C
			buffer->write_uint32(0); // +70 sale end
			buffer->write_uint32(0); // +74
			buffer->write_ubyte(0); // +78
			buffer->write_blob(""); // +80 promotional text (135 bytes)
			buffer->write_uint32(0); // +10C
			buffer->write_uint16(0); // +110
			buffer->write_uint32(0); // +114
			buffer->write_ubyte(0); // +6B
			buffer->write_uint32(1); // +118 price count, fixed native capacity 10
			buffer->write_ubyte(2); // price +20 currency ID
			buffer->write_uint32(200); // price +24 absolute price
			buffer->write_ubyte(100); // +350 SKU type, excludes collection type150
			buffer->write_uint32(1); // +358 max quantity
			buffer->write_bool(false); // +35C sold out
		}
	};

	class result final'''))
edit('src/client/game/demonware/services/bdMarketplace.cpp',lambda s:s.replace('''void bdMarketplace::purchaseSkus(service_server* server, byte_buffer* /*buffer*/) const
	{
		// TODO:
		auto reply = server->create_reply(this->task_id());
		reply.send();
	}''','''void bdMarketplace::purchaseSkus(service_server* server, byte_buffer* buffer) const
	{
		if (!game::environment::is_zombies())
		{
			hq_protocol::trace("marketplace_106_rejected", buffer->get_remaining());
			server->create_reply(this->task_id(), BD_HANDLE_TASK_FAILED).send();
			return;
		}
		server->create_reply(this->task_id()).send();
	}''').replace('''			if (!game::environment::is_zombies() && !hq_marketplace::parse_skus(buffer, request))''','''			bool includes_local_sku{};
			if (!game::environment::is_zombies() && !hq_marketplace::parse_skus(buffer, request, &includes_local_sku))''').replace('''			// 0x27B700 marks SKUs fetched when result count < requested page size.
			// Zero is a terminal page; the SDK result count is the paging signal.
			// There is no extra page object or token in this reply.
			console::info("[HQ marketplace] getSkusPaginated: terminal empty page %u, limit %u\\n",
				request.page, request.limit);
			server->create_reply(this->task_id()).send();''','''			auto reply = server->create_reply(this->task_id());
			if (includes_local_sku)
			{
				auto result = std::make_unique<hq_vendor::catalog_result>();
				byte_buffer encoded; result->serialize(&encoded);
				hq_protocol::trace("marketplace_111_sku", encoded.get_buffer());
				reply.add(result);
			}
			// SDK count is the paging signal; page2 is empty even for limit1.
			console::info("[HQ marketplace] SKU page %u limit %u count %u (local display offer; purchases rejected)\\n",
				request.page, request.limit, unsigned(includes_local_sku));
			reply.send();'''))
