#pragma once

#include "../../../utilities/global.hpp"
#include "../../valve/global.hpp"

namespace CS::Features::ESP {
  // thanks to poliacs for the calculations from UnknownCheats, was a time saver.
  inline bool BoundingBox( CS::Classes::CCSPlayer * Player, CS::Classes::Box & Box ) noexcept {
    const Utils::Math::Vector2 flb{}, brt{}, blb{}, frt{}, frb{}, brb{}, blt{}, flt{}, out{};

    const Utils::Math::Vector Origin = Player->Origin( );
    const Utils::Math::Vector Mins = Player->GetCollideable( )->OBBMins( ) + Origin;
    const Utils::Math::Vector Maxs = Player->GetCollideable( )->OBBMaxs( ) + Origin;

    Utils::Math::Vector points[] = {
      Utils::Math::Vector( Mins.x, Mins.y, Mins.z ), Utils::Math::Vector( Mins.x, Maxs.y, Mins.z ),
      Utils::Math::Vector( Maxs.x, Maxs.y, Mins.z ), Utils::Math::Vector( Maxs.x, Mins.y, Mins.z ),
      Utils::Math::Vector( Maxs.x, Maxs.y, Maxs.z ), Utils::Math::Vector( Mins.x, Maxs.y, Maxs.z ),
      Utils::Math::Vector( Mins.x, Mins.y, Maxs.z ), Utils::Math::Vector( Maxs.x, Mins.y, Maxs.z )
    };

    // vector constructors wouldn't work so I had to do this, will be fixed later
    Utils::Math::Vector rgPostWTSVec[] = { Utils::Math::Vector( blb.x, blb.y, 0.f ), Utils::Math::Vector( brb.x, brb.y, 0.f ),
                                           Utils::Math::Vector( frb.x, frb.y, 0.f ), Utils::Math::Vector( flb.x, flb.y, 0.f ),
                                           Utils::Math::Vector( frt.x, frt.y, 0.f ), Utils::Math::Vector( brt.x, brt.y, 0.f ),
                                           Utils::Math::Vector( blt.x, blt.y, 0.f ), Utils::Math::Vector( flt.x, flt.y, 0.f ) };

    for ( auto i = 0; i <= 7; ++i )
      if ( CS::Interfaces::g_pDebugOverlay->WorldToScreen( points[ i ], rgPostWTSVec[ i ] ) )
        return false;

    auto left = rgPostWTSVec[ 3 ].x, right = rgPostWTSVec[ 3 ].x, top = rgPostWTSVec[ 3 ].y, bottom = rgPostWTSVec[ 3 ].y;

    for ( auto i = 0; i <= 7; i++ ) {
      if ( top > rgPostWTSVec[ i ].y )
        top = rgPostWTSVec[ i ].y;

      if ( bottom < rgPostWTSVec[ i ].y )
        bottom = rgPostWTSVec[ i ].y;

      if ( left > rgPostWTSVec[ i ].x )
        left = rgPostWTSVec[ i ].x;

      if ( right < rgPostWTSVec[ i ].x )
        right = rgPostWTSVec[ i ].x;
    }

    Box.x = left;
    Box.y = top;
    Box.w = right - left;
    Box.h = bottom - top;

    return true;
  }

  inline void DrawBox( CS::Classes::Box & Box, Utils::Color ColorMain, Utils::Color ColorOutline ) noexcept {
    Utils::Render::RenderBoxOutline( Box.x, Box.y, Box.Right( ), Box.Bottom( ), ColorMain, false );

    Utils::Render::RenderBoxOutline( Box.x - 1, Box.y - 1, Box.Right( ) + 1, Box.Bottom( ) + 1, ColorOutline, false );
    Utils::Render::RenderBoxOutline( Box.x + 1, Box.y + 1, Box.Right( ) - 1, Box.Bottom( ) - 1, ColorOutline, false );
  }
  
  inline void DrawHealth( int x, int y, Utils::Color ColorMain, std::wstring_view{ int Health; } ) noexcept {
     Utils::Render::RenderText( X + 1, Y + 1, Utils::Render::ESP, ColorMain, Health );
  }

  inline void DrawLine( Utils::Math::Vector & EntityOrigin, Utils::Color Color ) noexcept {
    Utils::Math::Vector PostWTSVec{};
    CS::Interfaces::g_pDebugOverlay->WorldToScreen( EntityOrigin, PostWTSVec );

    auto [ width, height ] = CS::Interfaces::g_pSurface->GetScreenSize( );

    Utils::Render::RenderLine( width / 2, height / 2, PostWTSVec.x, PostWTSVec.y, Color );
  }

  inline void RunEsp( ) noexcept {
    for ( int i = 1; i <= CS::Interfaces::g_pGlobalVars->MaxClients; i++ ) {
      auto Player = CS::Interfaces::g_pEntityList->GetEntity( i );

      if ( !Player || !Player->bIsAlive( ) || Player == Utils::Context::g_pLocal )
        continue;
      //declare a color so we can just use EspColor later. 
      Utils::Color EspColor = Utils::Color( 255, 255, 255, Player->bDormant( ) ? 100 : 255 );
      CS::Classes::Box Box;

      if ( !BoundingBox( Player, Box ) )
        continue;
      // players that are dormant will have reduced alpha

      DrawBox( Box, EspColor, Utils::Color( 0, 0, 0, EspColor.uAlpha ) );
      DrawLine( Player->Origin( ), EspColor );

      DrawHealth( Box.x, Box.y, EspColor, std::wstring_view{ Player->Health( ) } );
      
      

    }
  }
} // namespace CS::Features::ESP
