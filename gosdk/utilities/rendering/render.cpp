#include "render.hpp"
#include "../../csgo/valve/global.hpp"

namespace utilities::render
{
void render_box(const int x, const int y, const int w, const int h,
		utilities::color color, bool is_additive) noexcept
{
	csgo::valve::interfaces::c_surface->set_draw_color(color);
	csgo::valve::interfaces::c_surface->draw_filled_rect(
		x, y, is_additive ? x + w : w, is_additive ? y + h : h);
}

void render_box_outline(const int x, const int y, const int w, const int h,
			utilities::color color, bool is_additive) noexcept
{
	csgo::valve::interfaces::c_surface->set_draw_color(color);
	csgo::valve::interfaces::c_surface->draw_outlined_rect(
		x, y, is_additive ? x + w : w, is_additive ? y + h : h);
}

void render_circle(const int x, const int y, const int radius,
		   utilities::color color) noexcept
{
	csgo::valve::interfaces::c_surface->set_draw_color(color);
	csgo::valve::interfaces::c_surface->draw_filled_circle(x, y, radius);
}

void render_circle_outline(const int x, const int y, const int radius,
			   const int segments, utilities::color color) noexcept
{
	csgo::valve::interfaces::c_surface->set_draw_color(color);
	csgo::valve::interfaces::c_surface->draw_outlined_circle(x, y, radius,
								 segments);
}

void render_text(const int x, const int y, unsigned font,
		 utilities::color color, const std::wstring_view text) noexcept
{
	csgo::valve::interfaces::c_surface->set_text_position(x, y);
	csgo::valve::interfaces::c_surface->set_text_font(font);
	csgo::valve::interfaces::c_surface->set_text_color(color);
	csgo::valve::interfaces::c_surface->print_text(text);
}

void run_render() noexcept
{
	verdana = csgo::valve::interfaces::c_surface->create_font();
	
	csgo::valve::interfaces::c_surface->set_font_glyph_set(
		verdana, "Verdana", 13, 600, 0, 0, font_flags::fontflag_antialias | font_flags::fontflag_outline);
}

void release_render() noexcept
{
	verdana = NULL;
}
} // namespace utilities::render