#include "hook.hpp"
#include "../../csgo/global.hpp"
#include <intrin.h>
#include <algorithm>

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
	static auto original = surface_hook->get_original_func<lock_cursor_fn>(
		utilities::hooking::lock_cursor_idx);

	if (GetAsyncKeyState(VK_INSERT)) {
		csgo::valve::interfaces::c_surface->unlock_cursor();
		csgo::valve::interfaces::c_input_system->enable_input(false);
	} else {
		csgo::valve::interfaces::c_input_system->enable_input(true);
	}

	if (original)
		return original(csgo::valve::interfaces::c_surface);
}

static void __stdcall paint_traverse(unsigned int panel, bool force_repaint,
				     bool allow_force) noexcept
{
	static auto original = panel_hook->get_original_func<paint_traverse_fn>(
		utilities::hooking::paint_traverse_idx);

	if (csgo::valve::interfaces::c_panel->get_name(panel) ==
	    STR("MatSystemTopPanel")) {

		/*
		debugging purposes
		utilities::render::render_box(
			15, 15, 20, 20, utilities::color(255, 255, 255, 255), true);
		utilities::render::render_box(
			50, 15, 20, 20, utilities::color(255, 255, 255, 255), true);
		utilities::render::render_box(
			90, 15, 90 + 10, 20, utilities::color(255, 255, 255, 255), false);
		utilities::render::render_circle(
			15, 40, 25, utilities::color(255, 255, 255, 255));
		utilities::render::render_circle_outline(
			50, 40, 25, 25, utilities::color(255, 255, 255, 255));
	utilities::render::render_text(
			15, 90, utilities::render::verdana,
			utilities::color(255, 255, 255, 255), L"hello there!");
		*/

		if (csgo::valve::interfaces::c_engine_client->is_in_game()) {
			csgo::hacks::visuals::esp::run_esp();
		}
	}

	original(csgo::valve::interfaces::c_panel, panel, force_repaint,
		 allow_force);
}

static bool __fastcall create_move(void *ecx, void *edx,
				   int input_sample_frametime,
				   csgo::valve::classes::user_cmd *cmd) noexcept
{
	if (!input_sample_frametime || !cmd || !cmd->command_number)
		return false;

	utilities::globals::cmd = cmd;
	utilities::globals::local =
		csgo::valve::interfaces::c_entity_list->get_entity(
			csgo::valve::interfaces::c_engine_client
				->get_local_player());

	csgo::hacks::misc::movement::on_create_move();

	cmd->forward_move = std::clamp(cmd->forward_move, -450.0f, 450.0f);
	cmd->side_move = std::clamp(cmd->side_move, -450.0f, 450.0f);
	cmd->up_move = std::clamp(cmd->up_move, -450.0f, 450.0f);

	cmd->viewangles.x = std::clamp(cmd->viewangles.x, -89.0f, 89.0f);
	cmd->viewangles.y = std::clamp(cmd->viewangles.y, -180.0f, 180.0f);
	cmd->viewangles.z = 0.0f;

	return false;
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

	client_mode_hook = std::make_unique<utilities::hooking::vmt>();
	client_mode_hook->init(csgo::valve::interfaces::c_client_mode);
	client_mode_hook->hook_func(
		utilities::hooking::create_move_idx,
		reinterpret_cast<void *>(utilities::hooking::create_move));

	surface_hook = std::make_unique<utilities::hooking::vmt>();
	surface_hook->init(csgo::valve::interfaces::c_surface);
	surface_hook->hook_func(
		utilities::hooking::lock_cursor_idx,
		reinterpret_cast<void *>(utilities::hooking::lock_cursor));

	panel_hook = std::make_unique<utilities::hooking::vmt>();
	panel_hook->init(csgo::valve::interfaces::c_panel);
	panel_hook->hook_func(
		utilities::hooking::paint_traverse_idx,
		reinterpret_cast<void *>(utilities::hooking::paint_traverse));
}

void release_hooks() noexcept
{
	sv_cheats_hook->unhook();
	cl_grenadepreview_hook->unhook();
	client_mode_hook->unhook();
	surface_hook->unhook();
	panel_hook->unhook();
}
} // namespace utilities::hooking