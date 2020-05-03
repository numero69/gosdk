#pragma once

#include <array>
#include <inttypes.h>

namespace utilities
{
struct color {
	std::uint8_t red, green, blue, alpha;

	color()
	{
		red = 0, green = 0, blue = 0, alpha = 255;
	}

	color(const int r, const int g, const int b, const int a)
	{
		red = r, green = g, blue = b, alpha = a;
	}

	color(const int r, const int g, const int b)
	{
		red = r, green = g, blue = b, alpha = 255;
	}
};
} // namespace utilities
