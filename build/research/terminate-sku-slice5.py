from pathlib import Path
def edit(p,f):
 p=Path(p);p.write_bytes(f(p.read_text()).replace('\n','\r\n').encode())
edit('src/client/game/demonware/hq_vendor.hpp',lambda s:s.replace('buffer->write_blob("sd_mp");','buffer->write_blob(std::string{"sd_mp", 6});').replace('buffer->write_blob(""); // +80','buffer->write_blob(std::string(1, \'\\0\')); // +80'))
edit('build/research/hq-tests/tests.cpp',lambda s:s.replace('sku_data == "sd_mp"','sku_data == std::string("sd_mp", 6)').replace('offer_reader.read_blob(&promo) && promo.empty()', 'offer_reader.read_blob(&promo) && promo == std::string(1, \'\\0\')'))
edit('build/research/slice5-mail.md',lambda s:s.replace('Stage3 also fixes diagnostic RVA', 'Stage3 also explicitly terminates the SKU/promotional blobs (native cache copies\nread them as strings), fixes diagnostic RVA'))
