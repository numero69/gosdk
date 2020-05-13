#pragma once
#include "config.hpp"

namespace Config {
  inline void RunConfig( ) { g_pConfig = std::make_unique<Config::SSettings>( ); }

  inline void ReleaseConfig( ) { g_pConfig.reset( ); }

  inline void ToClipboard( const std::string & s ) {
    OpenClipboard( 0 );
    EmptyClipboard( );
    HGLOBAL hg = GlobalAlloc( GMEM_MOVEABLE, s.size( ) );
    if ( !hg ) {
      CloseClipboard( );
      return;
    }
    memcpy( GlobalLock( hg ), s.c_str( ), s.size( ) );
    GlobalUnlock( hg );
    SetClipboardData( CF_TEXT, hg );
    CloseClipboard( );
    GlobalFree( hg );
  }
} // namespace Config