#include "config/global.hpp"
#include "csgo/valve/global.hpp"
#include "dependencies/global.hpp"
#include "utilities/global.hpp"

LPVOID Init( const HMODULE instance ) {

  Utils::g_Context.g_pModule = instance;

  try {
    Utils::g_Console.Initialize( STR( "gosdk" ), STR( "welcome, initialized" ) );

    // run config before everything
    Config::RunConfig( );

    CS::g_Interfaces.RunInterfaces( );
    CS::g_Netvar.Init( );
    Utils::g_Render.RunRender( );
    Utils::g_Hooking.RunHooks( );
  } catch ( const std::exception & e ) {
    Utils::g_Console.Log<std::string_view>( e.what( ) );
  }

  while ( !Utils::g_Context.bShouldUnload ) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for( 15ms );
  }

  Utils::g_Console.Destroy( );
  Utils::g_Hooking.ReleaseHooks( );
  Utils::g_Render.ReleaseRender( );
  CS::g_Interfaces.ReleaseInterfaces( );

  // release config after everything
  Config::ReleaseConfig( );

  FreeLibraryAndExitThread( instance, NULL );
}

std::uint8_t WINAPI DllMain( HINSTANCE Instance, DWORD CallReason, LPVOID Reserved [[maybe_unused]] ) {
  if ( CallReason != DLL_PROCESS_ATTACH )
    return false;

  const auto ThreadHandle = CreateThread(
      nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>( Init ), reinterpret_cast<LPVOID>( Instance ), NULL, nullptr );

  if ( ThreadHandle == nullptr || ThreadHandle == INVALID_HANDLE_VALUE ) {
    MessageBoxA( nullptr, STR( "failed to create initialization thread." ), STR( "error" ), MB_OKCANCEL );
    return false;
  }

  CloseHandle( ThreadHandle );
  return true;
}
