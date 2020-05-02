#include "hook.hpp"
#include <intrin.h>
#include "../../csgo/global.hpp"

namespace utilities::hooking
{
static bool __stdcall sv_cheats() noexcept
{
	return true;
}
static bool __stdcall cl_grenadepreview() noexcept
{
	return true;
}
static void __fastcall lock_cursor() noexcept
{
	static auto original =
		surface_hook->get_original_func<lock_cursor_fn>(utilities::hooking::lock_cursor_idx);

	if (GetAsyncKeyState(VK_INSERT)) {
		csgo::valve::interfaces::c_surface->unlock_cursor();
		csgo::valve::interfaces::c_input_system->enable_input(false);
	} else {
		csgo::valve::interfaces::c_input_system->enable_input(true);
	}

	if (original)
		return original(csgo::valve::interfaces::c_surface);
}
void run_hooks() noexcept
{
	sv_cheats_hook = std::make_unique<utilities::hooking::vmt>();
	sv_cheats_hook->init(
		csgo::valve::interfaces::c_console->find_var(STR("sv_cheats")));
	sv_cheats_hook->hook_func(
		utilities::hooking::get_int_idx,
		reinterpret_cast<void *>(utilities::hooking::sv_cheats));

	cl_grenadepreview_hook = std::make_unique<utilities::hooking::vmt>();
	cl_grenadepreview_hook->init(
		csgo::valve::interfaces::c_console->find_var(
			STR("cl_grenadepreview")));
	cl_grenadepreview_hook->hook_func(
		utilities::hooking::get_int_idx,
		reinterpret_cast<void *>(
			utilities::hooking::cl_grenadepreview));

	surface_hook = std::make_unique<utilities::hooking::vmt>();
	surface_hook->init(csgo::valve::interfaces::c_surface);
	surface_hook->hook_func(
		utilities::hooking::lock_cursor_idx, reinterpret_cast<void *>(utilities::hooking::lock_cursor));
}
void release_hooks() noexcept
{
	sv_cheats_hook->unhook();
	cl_grenadepreview_hook->unhook();
	surface_hook->unhook();
}
} // namespace utilities::hooking