#include "config/global.hpp"
#include "csgo/valve/global.hpp"
#include "dependencies/global.hpp"
#include "utilities/global.hpp"

LPVOID Init( const HMODULE instance ) {

  Utils::Context::g_pModule = instance;

  try {
    Utils::Console::Initialize( STR( "gosdk" ), STR( "welcome, initialized" ) );

    // run config before everything
    Config::RunConfig( );

    CS::Interfaces::RunInterfaces( );
    CS::Utilities::Netvar::Init( );
    Utils::Render::RunRender( );
    Utils::Hooking::RunHooks( );
  } catch ( const std::exception & e ) {
    Utils::Console::Log<std::string>( e.what( ) );
  }

  while ( !Utils::Context::bShouldUnload ) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for( 15ms );
  }

  Utils::Console::Destroy( );
  Utils::Hooking::ReleaseHooks( );
  Utils::Render::ReleaseRender( );
  CS::Interfaces::ReleaseInterfaces( );

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
