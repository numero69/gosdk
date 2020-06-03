#include "config/global.hpp"
#include "csgo/valve/global.hpp"
#include "dependencies/global.hpp"
#include "utilities/global.hpp"

std::uint8_t Initialize( const HMODULE Instance ) {

  Utils::g_Context.g_pModule = Instance;

  try {
    Utils::g_Console.RunConsole( STR( "gosdk" ), STR( "welcome, initialized" ) );

    /// <summary>
    /// Run config after everything so that there is no calls to the getter before it is initialized
    /// </summary>
    Config::RunConfig( );

    CS::g_Interfaces.RunInterfaces( );
    CS::g_Netvar.RunNetvar( );
    Utils::g_Render.RunRender( );
    Utils::g_Hooking.RunHooks( );
  } catch ( const std::exception & e ) {
    Utils::g_Console.Log<std::string_view>( e.what( ) );
  }

  while ( !GetAsyncKeyState( VK_END ) ) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for( 15ms );
  }

  FreeLibraryAndExitThread( Instance, NULL );
}

std::uint8_t Shutdown( ) {
  Utils::g_Console.ReleaseConsole( );
  Utils::g_Hooking.ReleaseHooks( );
  Utils::g_Render.ReleaseRender( );
  CS::g_Netvar.ReleaseNetvars( );
  CS::g_Interfaces.ReleaseInterfaces( );

  /// <summary>
  /// Since there were still calls to the getter, we have to release config after everything
  /// </summary>
  Config::ReleaseConfig( );

  return TRUE;
}

std::uint8_t WINAPI DllMain( HINSTANCE Instance, DWORD CallReason, LPVOID Reserved [[maybe_unused]] ) {
  DisableThreadLibraryCalls( Instance );

  if ( CallReason == DLL_PROCESS_ATTACH ) {
    const auto ThreadHandle =
        CreateThread( nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>( Initialize ), Instance, NULL, nullptr );

    if ( ThreadHandle == nullptr || ThreadHandle == INVALID_HANDLE_VALUE ) {
      MessageBoxA( nullptr, STR( "failed to create initialization thread." ), STR( "error" ), MB_OKCANCEL );
      return FALSE;
    }

    CloseHandle( ThreadHandle );
  }

  if ( CallReason == DLL_PROCESS_DETACH ) {
    Shutdown( );
  }

  return TRUE;
}
