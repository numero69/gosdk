#include "netvar.hpp"
#include "../../interfaces.hpp"
#include <fstream>

// credits: unknowncheats

std::unordered_map<std::string, std::uintptr_t> csgo::valve::netvar::offsets;

std::ofstream ofs("netvar_dump.dmp");

void dump_recursive(csgo::valve::classes::recv_table *table)
{
	for (auto i = 0; i < table->props_count; ++i) {
		const auto prop = &table->props[i];

		if (!prop || std::isdigit(prop->prop_name[0]) ||
		    !std::strcmp(prop->prop_name, "baseclass"))
			continue;

		if (prop->prop_type == 6 && prop->data_table &&
		    prop->data_table->table_name[0] == 'D')
			dump_recursive(prop->data_table);

		ofs << table->table_name + std::string("->") + prop->prop_name
		    << "=" << prop->offset << '\n';

		csgo::valve::netvar::offsets[table->table_name +
					     std::string("->") +
					     prop->prop_name] = prop->offset;
	}
}

void csgo::valve::netvar::init()
{
	ofs << "csgo netvar dump taken on " << __DATE__ << '\n';

	for (auto pclass = csgo::valve::interfaces::c_client->get_all_classes();
	     pclass; pclass = pclass->next_ptr) {
		const auto table = pclass->recvtable_ptr;

		if (!table)
			continue;

		dump_recursive(table);
	}
}