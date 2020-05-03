#pragma once

#include "../../../utilities/global.hpp"

namespace csgo::valve::interfaces
{
class i_panel {
    public:
	constexpr std::string_view get_name(unsigned int panel) noexcept
	{
		return std::string_view{ utilities::memory::call_virtual_method<
			const char *, unsigned int>(this, 36, panel) };
	}
};
} // namespace csgo::valve::interfaces