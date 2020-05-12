#include "interfaces.hpp"

namespace csgo::valve::interfaces
{
void run_interfaces() noexcept
{
	p_client = reinterpret_cast<i_base_client_dll *>(
		utilities::memory::scan_interface(STR("client_panorama.dll"),
						  STR("VClient018")));

	if (!p_client)
		utilities::console::log<std::string>(STR(
			"failed @ p_client | client_panorama.dll | VClient018"));

	p_client_mode = **reinterpret_cast<i_client_mode ***>(
		(*reinterpret_cast<uintptr_t **>(p_client))[10] + 5);

	if (!p_client_mode)
		utilities::console::log<std::string>(STR(
			"failed @ p_client_mode | check source for more information...")); // ohh yeahh ohh yeahh ohh yeaaaaahhh

	p_global_vars = **reinterpret_cast<i_global_vars ***>(
		(*reinterpret_cast<uintptr_t **>(p_client))[11] + 10);

	if (!p_global_vars)
		utilities::console::log<std::string>(STR(
			"failed @ p_global_vars | check source for more information...")); // ohh yeahh ohh yeahh ohh yeaaaaahhh x2

	p_entity_list = reinterpret_cast<i_entity_list *>(
		utilities::memory::scan_interface(STR("client_panorama.dll"),
						  STR("VClientEntityList003")));

	if (!p_entity_list)
		utilities::console::log<std::string>(STR(
			"failed @ p_entity_list | client_panorama.dll | VClientEntityList003"));

	p_engine_client = reinterpret_cast<i_engine_client *>(
		utilities::memory::scan_interface(STR("engine.dll"),
						  STR("VEngineClient014")));

	if (!p_engine_client)
		utilities::console::log<std::string>(STR(
			"failed @ p_engine_client | engine.dll | VEngineClient014"));

	p_debug_overlay = reinterpret_cast<i_debug_overlay *>(
		utilities::memory::scan_interface(STR("engine.dll"),
						  STR("VDebugOverlay004")));

	if (!p_debug_overlay)
		utilities::console::log<std::string>(STR(
			"failed @ p_debug_overlay | engine.dll | VDebugOverlay004"));

	p_console =
		reinterpret_cast<i_console *>(utilities::memory::scan_interface(
			STR("vstdlib.dll"), STR("VEngineCvar007")));

	if (!p_console)
		utilities::console::log<std::string>(STR(
			"failed @ p_console | vstdlib.dll | VEngineCvar007"));

	p_surface =
		reinterpret_cast<i_surface *>(utilities::memory::scan_interface(
			STR("vguimatsurface.dll"), STR("VGUI_Surface031")));

	if (!p_surface)
		utilities::console::log<std::string>(STR(
			"failed @ p_surface | vguimatsurface.dll | VGUI_Surface031"));

	p_input_system = reinterpret_cast<i_input_system *>(
		utilities::memory::scan_interface(
			STR("inputsystem.dll"), STR("InputSystemVersion001")));

	if (!p_input_system)
		utilities::console::log<std::string>(STR(
			"failed @ p_input_system | inputsystem.dll | InputSystemVersion001"));

	p_panel = reinterpret_cast<i_panel *>(utilities::memory::scan_interface(
		STR("vgui2.dll"), STR("VGUI_Panel009")));

	if (!p_panel)
		utilities::console::log<std::string>(
			STR("failed @ p_panel | vgui2.dll | VGUI_Panel009"));
}

void release_interfaces() noexcept
{
	p_console = nullptr;
	p_surface = nullptr;
	p_input_system = nullptr;
	p_panel = nullptr;
	p_client = nullptr;
	p_client_mode = nullptr;
	p_entity_list = nullptr;
	p_engine_client = nullptr;
	p_global_vars = nullptr;
	p_debug_overlay = nullptr;
}
} // namespace csgo::valve::interfaces