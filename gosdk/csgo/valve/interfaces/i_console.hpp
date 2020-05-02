#pragma once

#include "../../../utilities/global.hpp"
#include "../classes/convar.hpp"

namespace csgo::valve::interfaces
{
class i_console {
    public:
	constexpr auto find_var(const char *name) noexcept
	{
		return utilities::memory::call_virtual_method<
			csgo::valve::classes::convar *, const char *>(this, 15,
								      name);
	}
};
} // namespace csgo::valve::interfaces