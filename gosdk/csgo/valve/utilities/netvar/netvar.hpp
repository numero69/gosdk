#pragma once

#include "../../interfaces.hpp"

// credits: unknowncheats
namespace csgo::valve::netvar
{
class netvars {
	struct node_t;

	using MapType =
		std::unordered_map<std::string, std::shared_ptr<node_t> >;

	struct node_t {
		node_t(int offset) : offset(offset)
		{
		}

		MapType nodes;

		int offset;
	};

	MapType nodes{};

    public:
	netvars();

	bool init();
	template <typename... T> int get_offset(const char *name, T... args)
	{
		if (name != nullptr) {
			auto &node = nodes[name];

			if (node != nullptr) {
				return GetOffsetRecursive(
					node->nodes, node->offset, args...);
			}
		}
	}

    private:
	void populate_nodes(csgo::valve::classes::recv_table *recv_table,
			    MapType *map, std::ofstream &file);

	static int get_offset_recursive(MapType &map, int acc, const char *name)
	{
		return acc + map[name]->offset;
	}

	template <typename... T>
	int get_offset_recursive(MapType &map, int acc, const char *name,
				 T... args)
	{
		auto &node = map[name];

		return get_offset_recursive(node->nodes, acc + node->offset,
					    args...);
	}
};

inline std::unique_ptr<netvars> netvar_tree;

void initialize();
}; // namespace csgo::valve::netvar
