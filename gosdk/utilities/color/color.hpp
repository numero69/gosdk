#pragma once

#include <array>
#include <inttypes.h>

namespace Utils {
  struct Color {
    std::uint8_t uRed, uGreen, uBlue, uAlpha;

    Color( ) { uRed = 0, uGreen = 0, uBlue = 0, uAlpha = 255; }

    Color( const int r, const int g, const int b, const int a ) { uRed = r, uGreen = g, uBlue = b, uAlpha = a; }

    Color( const int r, const int g, const int b ) { uRed = r, uGreen = g, uBlue = b, uAlpha = 255; }
  };
} // namespace Utils
