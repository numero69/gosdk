#pragma once

#include "../color/color.hpp"

namespace utilities::render
{
enum font_flags {
	fontflag_none,
	fontflag_italic = 0x001,
	fontflag_underline = 0x002,
	fontflag_strikeout = 0x004,
	fontflag_symbol = 0x008,
	fontflag_antialias = 0x010,
	fontflag_gaussianblur = 0x020,
	fontflag_rotary = 0x040,
	fontflag_dropshadow = 0x080,
	fontflag_additive = 0x100,
	fontflag_outline = 0x200,
	fontflag_custom = 0x400,
	fontflag_bitmap = 0x800
};

void render_box(const int x, const int y, const int w, const int h,
		       utilities::color color, bool is_additive) noexcept;
void render_box_outline(const int x, const int y, const int w,
			       const int h, utilities::color color,
			       bool is_additive) noexcept;
void render_circle(const int x, const int y, const int radius,
			  utilities::color color) noexcept;
void render_circle_outline(const int x, const int y, const int radius,
				  const int segments,
				  utilities::color color) noexcept;
void render_line(const int x, const int y, const int x1, const int y1,
		 utilities::color color) noexcept;
void render_text(const int x, const int y, unsigned font,
			utilities::color color,
			const std::wstring_view text) noexcept;

inline unsigned verdana{};

void run_render() noexcept;
void release_render() noexcept;
} // namespace utilities::render