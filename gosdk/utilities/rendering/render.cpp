#include "render.hpp"
#include "../../csgo/valve/global.hpp"

namespace Utils::Render {
  void RenderBox( const int x, const int y, const int w, const int h, Utils::Color color, bool is_additive ) noexcept {
    CS::Interfaces::g_pSurface->SetDrawColor( color );
    CS::Interfaces::g_pSurface->DrawFilledRect( x, y, is_additive ? x + w : w, is_additive ? y + h : h );
  }

  void RenderBoxOutline( const int x, const int y, const int w, const int h, Utils::Color color, bool is_additive ) noexcept {
    CS::Interfaces::g_pSurface->SetDrawColor( color );
    CS::Interfaces::g_pSurface->DrawOutlinedRect( x, y, is_additive ? x + w : w, is_additive ? y + h : h );
  }

  void RenderCircle( const int x, const int y, const int radius, Utils::Color color ) noexcept {
    CS::Interfaces::g_pSurface->SetDrawColor( color );
    CS::Interfaces::g_pSurface->DrawFilledCircle( x, y, radius );
  }

  void RenderCircleOutline( const int x, const int y, const int radius, const int segments, Utils::Color color ) noexcept {
    CS::Interfaces::g_pSurface->SetDrawColor( color );
    CS::Interfaces::g_pSurface->DrawOutlinedCircle( x, y, radius, segments );
  }

  void RenderLine( const int x, const int y, const int x1, const int y1, Utils::Color color ) noexcept {
    CS::Interfaces::g_pSurface->SetDrawColor( color );
    CS::Interfaces::g_pSurface->DrawLine( x, y, x1, y1 );
  }

  void RenderText( const int x, const int y, unsigned font, Utils::Color color, const std::wstring_view text ) noexcept {
    CS::Interfaces::g_pSurface->SetTextPosition( x, y );
    CS::Interfaces::g_pSurface->SetTextFont( font );
    CS::Interfaces::g_pSurface->SetTextColor( color );
    CS::Interfaces::g_pSurface->PrintText( text );
  }

  void RunRender( ) noexcept {
    /* Namings with ExA are due to WINAPI overriding names */
    Verdana = CS::Interfaces::g_pSurface->CreateFontExA( );

    /* Lambda used to only initialize fonts once */
    /* If you plan to reinitialize them, get rid of the lambda */
    /* Or, make it an actual function to be called on a specific event */
    /* Currently, as I didn't do stuff like, hook OnScreenSizeChanged */
    /* To reinitialize the Render manager, I have no reason to do so. */
    ( []( ) {
      CS::Interfaces::g_pSurface->SetFontGlyphSet(
          Verdana, "Verdana", 13, 600, 0, 0, EFontFlags::FONTFLAG_ANTIALIAS | EFontFlags::FONTFLAG_OUTLINE );
    } )( );
  }

  void ReleaseRender( ) noexcept { Verdana = NULL; }
} // namespace Utils::Render