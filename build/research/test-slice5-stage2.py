from pathlib import Path
p=Path('build/research/hq-tests/tests.cpp');s=p.read_text();mark=' byte_buffer no_terminator';block='''
 // Native catalog read-side order A4A2C0/A4A510/A4A5A0, including bounded blobs.
 hq_vendor::catalog_result offer; byte_buffer offer_wire; offer.serialize(&offer_wire);
 byte_buffer offer_reader(offer_wire.get_buffer());
 unsigned sku_id{}, product{}, value{}, price_count{}, max_quantity{}; unsigned short collision{};
 unsigned char field{}, currency_id{}, sku_type{}; bool sold_out{}; std::string sku_data{}, promo{};
 require(offer_reader.read_uint32(&sku_id) && sku_id == 1 && offer_reader.read_uint32(&product) && product == 1 &&
  offer_reader.read_ubyte(&field) && offer_reader.read_blob(&sku_data) && sku_data == "sd_mp" &&
  offer_reader.read_ubyte(&field) && offer_reader.read_uint32(&value) && offer_reader.read_uint32(&value) &&
  offer_reader.read_uint32(&value) && offer_reader.read_ubyte(&field) && offer_reader.read_blob(&promo) && promo.empty() &&
  offer_reader.read_uint32(&value) && offer_reader.read_uint16(&collision) && offer_reader.read_uint32(&value) &&
  offer_reader.read_ubyte(&field) && offer_reader.read_uint32(&price_count) && price_count == 1 &&
  offer_reader.read_ubyte(&currency_id) && currency_id == 2 && offer_reader.read_uint32(&value) && value == 200 &&
  offer_reader.read_ubyte(&sku_type) && sku_type == 100 && offer_reader.read_uint32(&max_quantity) && max_quantity == 1 &&
  offer_reader.read_bool(&sold_out) && !sold_out && !offer_reader.has_more_data(), "native SKU record layout and price");
 auto catalog_query = [](unsigned page, unsigned type, unsigned id, const std::string& token) {
  byte_buffer b; b.write_string("s2_steam"); b.write_uint32(page); b.write_uint32(1); b.write_bool(false);
  b.write_uint32(id ? 1 : 0); if(id) b.write_uint32(id); b.write_uint32(1); b.write_ubyte(static_cast<unsigned char>(type)); b.write_string(token); return b.get_buffer();
 };
 bool selected{};
 for (auto type : {100u,150u}) for (auto page : {1u,2u}) for (auto id : {0u,1u,999u}) {
  byte_buffer b(catalog_query(page,type,id,""));
  require(hq_marketplace::parse_skus(&b,query,&selected) && selected == (type==100 && page==1 && id!=999), "SKU page and type/ID filtering");
 }
 auto catalog_capture = catalog_query(1,100,0,"");
 for(std::size_t n=0;n<catalog_capture.size();++n) {
  byte_buffer b(catalog_capture.substr(0,n)); selected=true;
  require(!hq_marketplace::parse_skus(&b,query,&selected) && !selected, "truncated catalog cannot select offer");
 }
 byte_buffer unknown_catalog(catalog_query(1,100,0,"unknown"));
 require(hq_marketplace::parse_skus(&unknown_catalog,query,&selected) && !selected, "unknown catalog token cannot select offer");
''';s=s.replace(mark,block+mark);p.write_bytes(s.replace('\n','\r\n').encode())
