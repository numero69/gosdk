#pragma once
#include <Windows.h>
#include <iostream>
#include <string>

namespace Utils::Console {
  static HWND console{};

  /* Handlers */
  inline void Initialize( const LPCSTR & name, const std::string & init_message ) {
    console = GetConsoleWindow( );

    AllocConsole( );
    freopen_s( reinterpret_cast<FILE **>( stdin ), STR( "CONIN$" ), STR( "r" ), stdin );
    freopen_s( reinterpret_cast<FILE **>( stdout ), STR( "CONOUT$" ), STR( "w" ), stdout );

    constexpr static RECT rect = { 100, 100, 600, 600 };
    MoveWindow( console, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE );

    static LONG_PTR style = GetWindowLongPtr( console, GWL_STYLE );
    SetWindowLong( console, GWL_STYLE, style & ~WS_SIZEBOX & ~WS_SYSMENU );

    SetConsoleTitle( STR( name ) );
    std::cout << init_message << std::endl;
  }

  inline void Destroy( ) {
    console = GetConsoleWindow( );

    fclose( stdin );
    fclose( stdout );

    FreeConsole( );
    PostMessageW( console, WM_CLOSE, 0, 0 );
    Beep( 10, 1000 );
  }

  template <typename T> void Log( T ref ) {
    std::cout << STR( "[gosdk] - " );
    std::cout << ref << std::endl;
  }
} // namespace Utils::Console