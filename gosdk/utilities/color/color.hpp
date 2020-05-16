#pragma once

#include <array>
#include <inttypes.h>

namespace Utils {
  struct Color {
    std::uint8_t m_uRed, m_uGreen, m_uBlue, m_uAlpha;

    Color( ) { m_uRed = 0, m_uGreen = 0, m_uBlue = 0, m_uAlpha = 255; }

    Color( const int r, const int g, const int b, const int a ) { m_uRed = r, m_uGreen = g, m_uBlue = b, m_uAlpha = a; }

    Color( const int r, const int g, const int b ) { m_uRed = r, m_uGreen = g, m_uBlue = b, m_uAlpha = 255; }
  };
} // namespace Utils
