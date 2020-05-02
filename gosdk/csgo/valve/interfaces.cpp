#include "interfaces.hpp"

namespace csgo::valve::interfaces
{
i_console *c_console = nullptr;

void run_interfaces() noexcept
{
	c_console =
		reinterpret_cast<i_console *>(utilities::memory::scan_interface(
			STR("vstdlib.dll"), STR("VEngineCvar007")));

	if (!c_console)
		utilities::console::log<std::string>(
			STR("failed @ c_console | vstdlib.dll | VEngineCvar007"));
}

void release_interfaces() noexcept
{
	c_console = nullptr;
}
} // namespace csgo::valve::interfaces