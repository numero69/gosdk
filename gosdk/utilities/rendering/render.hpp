#pragma once

#include "../color/color.hpp"
#include <string_view>

namespace Utils {
  class CRender {
  public:
    enum EFontFlags {
      FONTFLAG_NONE,
      FONTFLAG_ITALIC = 0x001,
      FONTFLAG_UNDERLINE = 0x002,
      FONTFLAG_STRIKEOUT = 0x004,
      FONTFLAG_SYMBOL = 0x008,
      FONTFLAG_ANTIALIAS = 0x010,
      FONTFLAG_GAUSSIANBLUR = 0x020,
      FONTFLAG_ROTARY = 0x040,
      FONTFLAG_DROPSHADOW = 0x080,
      FONTFLAG_ADDITIVE = 0x100,
      FONTFLAG_OUTLINE = 0x200,
      FONTFLAG_CUSTOM = 0x400,
      FONTFLAG_BITMAP = 0x800
    };

    void RenderBox( const int x, const int y, const int w, const int h, Utils::Color color, bool is_additive ) noexcept;
    void RenderBoxOutline( const int x, const int y, const int w, const int h, Utils::Color color, bool is_additive ) noexcept;
    void RenderCircle( const int x, const int y, const int radius, Utils::Color color ) noexcept;
    void RenderCircleOutline( const int x, const int y, const int radius, const int segments, Utils::Color color ) noexcept;
    void RenderLine( const int x, const int y, const int x1, const int y1, Utils::Color color ) noexcept;
    void RenderText( const int x, const int y, unsigned font, Utils::Color color, const std::wstring_view text ) noexcept;

    unsigned Verdana{ };
    unsigned ESP{ };

    /* Handlers */
    void RunRender( ) noexcept;
    void ReleaseRender( ) noexcept;
  };

  inline CRender g_Render{ };
} // namespace Utils::Render