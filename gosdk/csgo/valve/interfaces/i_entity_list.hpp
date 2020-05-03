#pragma once

#include "../../../utilities/memory/global.hpp"
#include "../classes/players.hpp"

namespace csgo::valve::interfaces
{
class i_entity_list {
    public:
	constexpr auto get_entity(int index) noexcept
	{
		return utilities::memory::call_virtual_method<
			csgo::valve::classes::c_player *, int>(this, 3, index);
	}

	constexpr auto get_entity_from_handle(int handle) noexcept
	{
		return utilities::memory::call_virtual_method<
			csgo::valve::classes::c_player *, int>(this, 4, handle);
	}

	constexpr auto get_highest_entity_index() noexcept
	{
		return utilities::memory::call_virtual_method<int>(this, 6);
	}
};
} // namespace csgo::valve::interfaces