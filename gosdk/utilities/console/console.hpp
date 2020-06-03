#pragma once
#include <Windows.h>
#include <iostream>
#include <string>

namespace Utils {
  static HWND ConsoleHandle{ };

  class Console {
  public:
    /* Handlers */
    inline void Initialize( const LPCSTR & name, const std::string & init_message ) {
      ConsoleHandle = GetConsoleWindow( );

      AllocConsole( );
      freopen_s( reinterpret_cast<FILE **>( stdin ), STR( "CONIN$" ), STR( "r" ), stdin );
      freopen_s( reinterpret_cast<FILE **>( stdout ), STR( "CONOUT$" ), STR( "w" ), stdout );

      constexpr static RECT rect = { 100, 100, 600, 600 };
      MoveWindow( ConsoleHandle, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE );

      static LONG_PTR style = GetWindowLongPtr( ConsoleHandle, GWL_STYLE );
      SetWindowLong( ConsoleHandle, GWL_STYLE, style & ~WS_SIZEBOX & ~WS_SYSMENU );

      SetConsoleTitle( name );
      std::cout << init_message << std::endl;
    }

    inline void Destroy( ) {
      ConsoleHandle = GetConsoleWindow( );

      fclose( stdin );
      fclose( stdout );

      FreeConsole( );
      PostMessageW( ConsoleHandle, WM_CLOSE, 0, 0 );
      Beep( 10, 1000 );
    }

    template <typename T> void Log( T ref ) {
      std::cout << STR( "[gosdk] - " );
      std::cout << ref << std::endl;
    }
  };

  inline Console g_Console;
} // namespace Utils
