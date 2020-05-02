#include "hook.hpp"
#include <intrin.h>
#include "../../csgo/global.hpp"

namespace utilities::hooking
{
static bool __stdcall sv_cheats()
{
	static auto original =
		sv_cheats_hook->get_original_func<decltype(&sv_cheats)>(
			utilities::hooking::get_int);

	return true;
}
static bool __stdcall cl_grenadepreview()
{
	static auto original =
		cl_grenadepreview_hook
			->get_original_func<decltype(&cl_grenadepreview)>(
				utilities::hooking::get_int);

	return true;
}
void run_hooks() noexcept
{
	sv_cheats_hook = std::make_unique<utilities::hooking::vmt>();
	sv_cheats_hook->init(
		csgo::valve::interfaces::c_console->find_var(STR("sv_cheats")));
	sv_cheats_hook->hook_func(
		utilities::hooking::get_int,
		reinterpret_cast<void *>(utilities::hooking::sv_cheats));

	cl_grenadepreview_hook = std::make_unique<utilities::hooking::vmt>();
	cl_grenadepreview_hook->init(
		csgo::valve::interfaces::c_console->find_var(
			STR("cl_grenadepreview")));
	cl_grenadepreview_hook->hook_func(
		utilities::hooking::get_int,
		reinterpret_cast<void *>(
			utilities::hooking::cl_grenadepreview));
}
void release_hooks() noexcept
{
	sv_cheats_hook->unhook();
	cl_grenadepreview_hook->unhook();
}
} // namespace utilities::hooking