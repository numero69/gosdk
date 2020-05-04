#pragma once

#include "../color/color.hpp"

namespace utilities::render
{
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
void render_text(const int x, const int y, unsigned font,
			utilities::color color,
			const std::wstring_view text) noexcept;

} // namespace utilities::render