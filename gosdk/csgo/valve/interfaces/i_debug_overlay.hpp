#pragma once

#include "../../../utilities/global.hpp"

namespace csgo::valve::interfaces
{
class i_debug_overlay {
    public:
	constexpr auto world_to_screen(const utilities::math::vec3_t &point,
			    utilities::math::vec3_t &screen)
	{
		return utilities::memory::call_virtual_method<
			int, const utilities::math::vec3_t &,
			utilities::math::vec3_t &>(this, 13, point, screen);
	}
};
} // namespace csgo::valve::interfaces