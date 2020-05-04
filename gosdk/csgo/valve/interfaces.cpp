#include "interfaces.hpp"

namespace csgo::valve::interfaces
{
void run_interfaces() noexcept
{
	c_client = reinterpret_cast<i_base_client_dll *>(
		utilities::memory::scan_interface(STR("client_panorama.dll"),
						  STR("VClient018")));

	if (!c_client)
		utilities::console::log<std::string>(STR(
			"failed @ c_client | client_panorama.dll | VClient018"));

	c_client_mode = **reinterpret_cast<i_client_mode ***>(
		(*reinterpret_cast<uintptr_t **>(c_client))[10] + 5);

	if (!c_client_mode)
		utilities::console::log<std::string>(STR(
			"failed @ c_client_mode | check source for more information...")); // ohh yeahh ohh yeahh ohh yeaaaaahhh

	c_global_vars = **reinterpret_cast<i_global_vars ***>(
		(*reinterpret_cast<uintptr_t **>(c_client))[11] + 10);

	if (!c_global_vars)
		utilities::console::log<std::string>(STR(
			"failed @ c_global_vars | check source for more information...")); // ohh yeahh ohh yeahh ohh yeaaaaahhh x2

	c_entity_list = reinterpret_cast<i_entity_list *>(
		utilities::memory::scan_interface(STR("client_panorama.dll"),
						  STR("VClientEntityList003")));

	if (!c_entity_list)
		utilities::console::log<std::string>(STR(
			"failed @ c_entity_list | client_panorama.dll | VClientEntityList003"));

	c_engine_client = reinterpret_cast<i_engine_client *>(
		utilities::memory::scan_interface(STR("engine.dll"),
						  STR("VEngineClient014")));

	if (!c_engine_client)
		utilities::console::log<std::string>(STR(
			"failed @ c_engine_client | engine.dll | VEngineClient014"));

	c_debug_overlay = reinterpret_cast<i_debug_overlay *>(
		utilities::memory::scan_interface(STR("engine.dll"),
						  STR("VDebugOverlay004")));

	if (!c_debug_overlay)
		utilities::console::log<std::string>(STR(
			"failed @ c_debug_overlay | engine.dll | VDebugOverlay004"));

	c_console =
		reinterpret_cast<i_console *>(utilities::memory::scan_interface(
			STR("vstdlib.dll"), STR("VEngineCvar007")));

	if (!c_console)
		utilities::console::log<std::string>(STR(
			"failed @ c_console | vstdlib.dll | VEngineCvar007"));

	c_surface =
		reinterpret_cast<i_surface *>(utilities::memory::scan_interface(
			STR("vguimatsurface.dll"), STR("VGUI_Surface031")));

	if (!c_surface)
		utilities::console::log<std::string>(STR(
			"failed @ c_surface | vguimatsurface.dll | VGUI_Surface031"));

	c_input_system = reinterpret_cast<i_input_system *>(
		utilities::memory::scan_interface(
			STR("inputsystem.dll"), STR("InputSystemVersion001")));

	if (!c_input_system)
		utilities::console::log<std::string>(STR(
			"failed @ c_input_system | inputsystem.dll | InputSystemVersion001"));

	c_panel = reinterpret_cast<i_panel *>(utilities::memory::scan_interface(
		STR("vgui2.dll"), STR("VGUI_Panel009")));

	if (!c_panel)
		utilities::console::log<std::string>(
			STR("failed @ c_panel | vgui2.dll | VGUI_Panel009"));
}

void release_interfaces() noexcept
{
	c_console = nullptr;
	c_surface = nullptr;
	c_input_system = nullptr;
	c_panel = nullptr;
	c_client = nullptr;
	c_client_mode = nullptr;
	c_entity_list = nullptr;
	c_engine_client = nullptr;
	c_global_vars = nullptr;
	c_debug_overlay = nullptr;
}
} // namespace csgo::valve::interfaces