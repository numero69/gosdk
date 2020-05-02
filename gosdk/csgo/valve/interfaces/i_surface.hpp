#pragma once

#include "../../../utilities/global.hpp"

namespace csgo::valve::interfaces
{
class i_surface {
    public:
	constexpr void set_draw_color(int r, int g, int b, int a = 255) noexcept
	{
		utilities::memory::call_virtual_method<void, int, int, int, int>(
			this, 15, r, g, b, a);
	}

	const void set_draw_color(utilities::color color) noexcept
	{
		utilities::memory::call_virtual_method<void, int, int, int, int>(
			this, 15, color.red, color.green, color.blue,
			color.alpha);
	}

	template <typename T>
	constexpr void draw_filled_rect(T x0, T y0, T x1, T y1) noexcept
	{
		utilities::memory::call_virtual_method<void, int, int, int, int>(
			this, 16, static_cast<int>(x0), static_cast<int>(y0),
			static_cast<int>(x1), static_cast<int>(y1));
	}

	template <typename T>
	constexpr void draw_outlined_rect(T x0, T y0, T x1, T y1) noexcept
	{
		utilities::memory::call_virtual_method<void, int, int, int, int>(
			this, 18, static_cast<int>(x0), static_cast<int>(y0),
			static_cast<int>(x1), static_cast<int>(y1));
	}

	template <typename T>
	constexpr void draw_line(T x0, T y0, T x1, T y1) noexcept
	{
		utilities::memory::call_virtual_method<void, int, int, int, int>(
			this, 19, static_cast<int>(x0), static_cast<int>(y0),
			static_cast<int>(x1), static_cast<int>(y1));
	}

	constexpr void set_text_font(std::uint32_t font) noexcept
	{
		utilities::memory::call_virtual_method<void, unsigned>(this, 23,
								       font);
	}

	constexpr void set_text_color(int r, int g, int b, int a = 255) noexcept
	{
		utilities::memory::call_virtual_method<void, int, int, int, int>(
			this, 25, r, g, b, a);
	}

	const void set_text_color(utilities::color color) noexcept
	{
		utilities::memory::call_virtual_method<void, int, int, int, int>(
			this, 25, color.red, color.green, color.blue,
			color.alpha);
	}

	template <typename T>
	constexpr void set_text_position(T x, T y) noexcept
	{
		utilities::memory::call_virtual_method<void, int, int>(
			this, 26, static_cast<int>(x), static_cast<int>(y));
	}

	constexpr void print_text(const std::wstring_view text,
				  int drawType = 0) noexcept
	{
		utilities::memory::call_virtual_method<void, const wchar_t *,
						       int, int>(
			this, 28, text.data(), text.length(), drawType);
	}

	constexpr auto get_screen_size() noexcept
	{
		int width{}, height{};
		utilities::memory::call_virtual_method<void, int &, int &>(
			this, 44, width, height);
		return std::make_pair(width, height);
	}

	constexpr void unlock_cursor() noexcept
	{
		utilities::memory::call_virtual_method<void>(this, 66);
	}

	constexpr unsigned create_font() noexcept
	{
		return utilities::memory::call_virtual_method<unsigned>(this,
									71);
	}

	constexpr bool set_font_glyph_set(std::uint32_t font,
					  const char *fontName, int tall,
					  int weight, int blur, int scanlines,
					  int flags, int rangeMin = 0,
					  int rangeMax = 0) noexcept
	{
		return utilities::memory::call_virtual_method<
			bool, unsigned, const char *, int, int, int, int, int,
			int, int>(this, 72, font, fontName, tall, weight, blur,
				  scanlines, flags, rangeMin, rangeMax);
	}

	constexpr auto get_text_size(std::uint32_t font,
				     const wchar_t *text) noexcept
	{
		int width{}, height{};
		utilities::memory::call_virtual_method<
			void, unsigned, const wchar_t *, int &, int &>(
			this, 79, font, text, width, height);
		return std::make_pair(width, height);
	}

	template <typename T>
	constexpr void draw_outlined_circle(T x, T y, int r, int seg) noexcept
	{
		utilities::memory::call_virtual_method<void, int, int, int, int>(
			this, 103, static_cast<int>(x), static_cast<int>(y), r,
			seg);
	}

	template <typename T>
	constexpr void draw_filled_circle(T x, T y, int r) noexcept
	{
		for (int i = 0; i <= r; i++) {
			draw_outlined_circle(x, y, i, i);
		}
	}
};
} // namespace csgo::valve::interfaces
