#pragma once

#include "../../../utilities/global.hpp"

namespace CS::Interfaces {
  class ISurface {
  public:
    /* Namings with ExA are due to WINAPI overriding names */

    constexpr auto SetDrawColor( int r, int g, int b, int a = 255 ) noexcept {
      Utils::Memory::CallVirtualMethod<void, int, int, int, int>( this, 15, r, g, b, a );
    }

    const auto SetDrawColor( Utils::Color color ) noexcept {
      Utils::Memory::CallVirtualMethod<void, int, int, int, int>( this, 15, color.uRed, color.uGreen, color.uBlue, color.uAlpha );
    }

    template <typename T> constexpr auto DrawFilledRect( T x0, T y0, T x1, T y1 ) noexcept {
      Utils::Memory::CallVirtualMethod<void, int, int, int, int>(
          this, 16, static_cast<int>( x0 ), static_cast<int>( y0 ), static_cast<int>( x1 ), static_cast<int>( y1 ) );
    }

    template <typename T> constexpr auto DrawOutlinedRect( T x0, T y0, T x1, T y1 ) noexcept {
      Utils::Memory::CallVirtualMethod<void, int, int, int, int>(
          this, 18, static_cast<int>( x0 ), static_cast<int>( y0 ), static_cast<int>( x1 ), static_cast<int>( y1 ) );
    }

    template <typename T> constexpr auto DrawLine( T x0, T y0, T x1, T y1 ) noexcept {
      Utils::Memory::CallVirtualMethod<void, int, int, int, int>(
          this, 19, static_cast<int>( x0 ), static_cast<int>( y0 ), static_cast<int>( x1 ), static_cast<int>( y1 ) );
    }

    constexpr auto SetTextFont( unsigned font ) noexcept { Utils::Memory::CallVirtualMethod<void, unsigned>( this, 23, font ); }

    constexpr auto SetTextColor( int r, int g, int b, int a = 255 ) noexcept {
      Utils::Memory::CallVirtualMethod<void, int, int, int, int>( this, 25, r, g, b, a );
    }

    const auto SetTextColor( Utils::Color color ) noexcept {
      Utils::Memory::CallVirtualMethod<void, int, int, int, int>( this, 25, color.uRed, color.uGreen, color.uBlue, color.uAlpha );
    }

    template <typename T> constexpr auto SetTextPosition( T x, T y ) noexcept {
      Utils::Memory::CallVirtualMethod<void, int, int>( this, 26, static_cast<int>( x ), static_cast<int>( y ) );
    }

    constexpr auto PrintText( const std::wstring_view text, int drawType = 0 ) noexcept {
      Utils::Memory::CallVirtualMethod<void, const wchar_t *, int, int>( this, 28, text.data( ), text.length( ), drawType );
    }

    constexpr auto GetScreenSize( ) noexcept {
      int width{}, height{};
      Utils::Memory::CallVirtualMethod<void, int &, int &>( this, 44, width, height );
      return std::make_pair( width, height );
    }

    constexpr auto UnlockCursor( ) noexcept { Utils::Memory::CallVirtualMethod<void>( this, 66 ); }

    constexpr auto CreateFontExA( ) noexcept { return Utils::Memory::CallVirtualMethod<unsigned>( this, 71 ); }

    constexpr auto SetFontGlyphSet( unsigned font,
                                    const char * font_name,
                                    int tall,
                                    int weight,
                                    int blur,
                                    int scanlines,
                                    int flags,
                                    int range_min = 0,
                                    int range_max = 0 ) noexcept {
      return Utils::Memory::CallVirtualMethod<bool, unsigned, const char *, int, int, int, int, int, int, int>(
          this, 72, font, font_name, tall, weight, blur, scanlines, flags, range_min, range_max );
    }

    constexpr auto GetTextSize( unsigned font, const wchar_t * text ) noexcept {
      int width{}, height{};
      Utils::Memory::CallVirtualMethod<void, unsigned, const wchar_t *, int &, int &>( this, 79, font, text, width, height );
      return std::make_pair( width, height );
    }

    template <typename T> constexpr auto DrawOutlinedCircle( T x, T y, int r, int seg ) noexcept {
      Utils::Memory::CallVirtualMethod<void, int, int, int, int>(
          this, 103, static_cast<int>( x ), static_cast<int>( y ), r, seg );
    }

    template <typename T> constexpr auto DrawFilledCircle( T x, T y, int r ) noexcept {
      for ( int i = 0; i <= r; i++ ) {
        DrawOutlinedCircle( x, y, i, i );
      }
    }
  };
} // namespace CS::Interfaces
