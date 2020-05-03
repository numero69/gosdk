#include "netvar.hpp"
#include <fstream>

// credits: unknowncheats
namespace csgo::valve::netvar
{
netvars::netvars()
{
}

bool netvars::init()
{
	if (!csgo::valve::interfaces::c_client)
		return false;

	csgo::valve::classes::c_client_class *client_class =
		csgo::valve::interfaces::c_client->get_all_classes();

	if (!client_class)
		return false;

	std::ofstream output;

	while (client_class != nullptr) {
		auto class_info = std::make_shared<node_t>(0);

		auto recv_table = client_class->recvtable_ptr;

		populate_nodes(recv_table, &class_info->nodes, output);

		nodes.emplace(recv_table->table_name, class_info);

		client_class = client_class->next_ptr;
		output.clear();
		output.close();
	}

	return true;
}

void netvars::populate_nodes(csgo::valve::classes::recv_table *recv_table,
			     MapType *map, std::ofstream &file)
{
	for (auto i = 0; i < recv_table->props_count; i++) {
		csgo::valve::classes::recv_prop *prop = &recv_table->props[i];

		auto prop_info = std::make_shared<node_t>(prop->offset);

		if (prop->prop_type == 6)
			populate_nodes(prop->data_table, &prop_info->nodes,
				       file);

		map->emplace(prop->prop_name, prop_info);
	}
}

void initialize()
{
	netvar_tree = std::make_unique<netvars>();

	netvar_tree->init();
}
} // namespace csgo::valve::netvar
