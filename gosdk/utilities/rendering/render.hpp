#pragma once

#include "../color/color.hpp"

namespace Utils::Render {
  enum EFontFlags {
    FONTFLAG_NONE,
    FONTFLAG_ITALIC = 0X001,
    FONTFLAG_UNDERLINE = 0X002,
    FONTFLAG_STRIKEOUT = 0X004,
    FONTFLAG_SYMBOL = 0X008,
    FONTFLAG_ANTIALIAS = 0X010,
    FONTFLAG_GAUSSIANBLUR = 0X020,
    FONTFLAG_ROTARY = 0X040,
    FONTFLAG_DROPSHADOW = 0X080,
    FONTFLAG_ADDITIVE = 0X100,
    FONTFLAG_OUTLINE = 0X200,
    FONTFLAG_CUSTOM = 0X400,
    FONTFLAG_BITMAP = 0X800
  };

  void RenderBox( const int x, const int y, const int w, const int h, Utils::Color color, bool is_additive ) noexcept;
  void RenderBoxOutline( const int x, const int y, const int w, const int h, Utils::Color color, bool is_additive ) noexcept;
  void RenderCircle( const int x, const int y, const int radius, Utils::Color color ) noexcept;
  void RenderCircleOutline( const int x, const int y, const int radius, const int segments, Utils::Color color ) noexcept;
  void RenderLine( const int x, const int y, const int x1, const int y1, Utils::Color color ) noexcept;
  void RenderText( const int x, const int y, unsigned font, Utils::Color color, const std::wstring_view text ) noexcept;

  inline unsigned Verdana{};

  void RunRender( ) noexcept;
  void ReleaseRender( ) noexcept;
} // namespace Utils::Render