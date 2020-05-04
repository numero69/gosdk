#pragma once

#include "../../../utilities/global.hpp"
#include "../../valve/global.hpp"

namespace csgo::hacks::visuals::esp
{
// thanks to poliacs for the calculations from UnknownCheats, was a time saver.
inline bool bounding_box(csgo::valve::classes::c_player *player,
			 csgo::valve::classes::rect &box) noexcept
{
	const utilities::math::vec2_t flb{}, brt{}, blb{}, frt{}, frb{}, brb{}, blt{},
		flt{}, out{};

	const utilities::math::vec3_t origin = player->origin();
	const utilities::math::vec3_t mins =
		player->get_collideable()->obb_mins() + origin;
	const utilities::math::vec3_t maxs =
		player->get_collideable()->obb_maxs() + origin;

	utilities::math::vec3_t points[] = {
		utilities::math::vec3_t(mins.x, mins.y, mins.z),
		utilities::math::vec3_t(mins.x, maxs.y, mins.z),
		utilities::math::vec3_t(maxs.x, maxs.y, mins.z),
		utilities::math::vec3_t(maxs.x, mins.y, mins.z),
		utilities::math::vec3_t(maxs.x, maxs.y, maxs.z),
		utilities::math::vec3_t(mins.x, maxs.y, maxs.z),
		utilities::math::vec3_t(mins.x, mins.y, maxs.z),
		utilities::math::vec3_t(maxs.x, mins.y, maxs.z)
	};

	// vector constructors wouldn't work so I had to do this, will be fixed later
	utilities::math::vec3_t scr_array[] = {
		utilities::math::vec3_t(blb.x, blb.y, 0.f),
		utilities::math::vec3_t(brb.x, brb.y, 0.f),
		utilities::math::vec3_t(frb.x, frb.y, 0.f),
		utilities::math::vec3_t(flb.x, flb.y, 0.f),
		utilities::math::vec3_t(frt.x, frt.y, 0.f),
		utilities::math::vec3_t(brt.x, brt.y, 0.f),
		utilities::math::vec3_t(blt.x, blt.y, 0.f),
		utilities::math::vec3_t(flt.x, flt.y, 0.f)
	};

	for (auto i = 0; i <= 7; ++i)
		if (csgo::valve::interfaces::c_debug_overlay->world_to_screen(
			    points[i], scr_array[i]))
			return false;

	auto left = scr_array[3].x, right = scr_array[3].x,
	     top = scr_array[3].y, bottom = scr_array[3].y;

	for (auto i = 0; i <= 7; i++) {
		if (top > scr_array[i].y)
			top = scr_array[i].y;

		if (bottom < scr_array[i].y)
			bottom = scr_array[i].y;

		if (left > scr_array[i].x)
			left = scr_array[i].x;

		if (right < scr_array[i].x)
			right = scr_array[i].x;
	}

	box.x = left;
	box.y = top;
	box.w = right - left;
	box.h = bottom - top;

	return true;
}

inline void draw_box(csgo::valve::classes::rect &box,
		     utilities::color color_main, utilities::color color_outline) noexcept
{
	csgo::valve::interfaces::c_surface->set_draw_color(color_main);
	csgo::valve::interfaces::c_surface->draw_outlined_rect(
		box.x, box.y, box.right(), box.bottom());

	csgo::valve::interfaces::c_surface->set_draw_color(color_outline);
	csgo::valve::interfaces::c_surface->draw_outlined_rect(
		box.x - 1, box.y - 1, box.right() + 1, box.bottom() + 1);
	csgo::valve::interfaces::c_surface->draw_outlined_rect(
		box.x + 1, box.y + 1, box.right() - 1, box.bottom() - 1);
}

inline void run_esp() noexcept
{
	for (int i = 1; i <= csgo::valve::interfaces::c_global_vars->max_clients;
	     i++) {
		auto player =
			csgo::valve::interfaces::c_entity_list->get_entity(i);

		if (!player || !player->is_alive() ||
		    player == utilities::globals::local)
			continue;

		csgo::valve::classes::rect box;

		if (!bounding_box(player, box))
			continue;

		draw_box(box, utilities::color(255, 255, 255, 255), utilities::color(0, 0, 0, 255));
	}
}

auto on_paint_traverse = []() { esp::run_esp(); };
} // namespace csgo::hacks::misc::visuals