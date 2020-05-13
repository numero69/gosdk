#include "hook.hpp"
#include "../../config/config.hpp"
#include "../../csgo/global.hpp"
#include <algorithm>
#include <intrin.h>

namespace Utils::Hooking {
  static bool __stdcall bSvCheats( ) noexcept { return true; }

  static bool __stdcall bGrenadePreview( ) noexcept { return true; }

  static void __fastcall LockCursor( ) noexcept {
    static auto Original = g_pSurfaceHook->GetOriginalFunction<LockCursor_t>( EFuncIndexes::LockCursorIndex );

    if ( GetAsyncKeyState( VK_INSERT ) ) {
      CS::Interfaces::g_pSurface->UnlockCursor( );
      CS::Interfaces::g_pInputSystem->EnableInput( false );
      return;
    } else {
      CS::Interfaces::g_pInputSystem->EnableInput( true );
    }

    if ( Original )
      return Original( CS::Interfaces::g_pSurface );
  }

  static void __stdcall PaintTraverse( unsigned int Panel, bool ForceRepaint, bool AllowForce ) noexcept {
    static auto Original = g_pPanelHook->GetOriginalFunction<PaintTraverse_t>( EFuncIndexes::PaintTraverseIndex );

    if ( CS::Interfaces::g_pPanel->GetName( Panel ) == STR( "MatSystemTopPanel" ) ) {
      //		if (CONFIG_GET(bool, "test_boolean"))
      Utils::Render::RenderText( 15, 15, Utils::Render::Verdana, Utils::Color( 255, 255, 255, 255 ), L"Test" );
      if ( CS::Interfaces::g_pEngineClient->IsInGame( ) && CS::Interfaces::g_pEngineClient->IsConnected( ) ) {
        CS::Features::ESP::RunEsp( );
      }
    }

    if ( Original )
      Original( CS::Interfaces::g_pPanel, Panel, ForceRepaint, AllowForce );
  }

  static bool __fastcall bCreateMove( void * ecx, void * edx, int InputSampleFrameTime, CS::Classes::CUserCmd * Cmd ) noexcept {
    if ( !InputSampleFrameTime || !Cmd || !Cmd->CommandNumber )
      return false;

    Utils::Context::g_pCmd = Cmd;
    Utils::Context::g_pLocal = CS::Interfaces::g_pEntityList->GetEntity( CS::Interfaces::g_pEngineClient->GetLocalPlayer( ) );

    CS::Features::Movement::BunnyHop( );
    CS::Features::Movement::NoDuckDelay( );

    Cmd->ForwardMove = std::clamp( Cmd->ForwardMove, -450.0f, 450.0f );
    Cmd->SideMove = std::clamp( Cmd->SideMove, -450.0f, 450.0f );
    Cmd->UpMove = std::clamp( Cmd->UpMove, -320.0f, 320.0f );

    Cmd->ViewAngles.x = std::clamp( Cmd->ViewAngles.x, -89.0f, 89.0f );
    Cmd->ViewAngles.y = std::clamp( Cmd->ViewAngles.y, -180.0f, 180.0f );
    Cmd->ViewAngles.z = 0.0f;

    return false;
  }

  void RunHooks( ) noexcept {
    g_pCheatsHook = std::make_unique<Utils::Hooking::CVMT>( );
    g_pCheatsHook->bInit( CS::Interfaces::g_pConsole->FindVar( STR( "sv_cheats" ) ) );
    g_pCheatsHook->bHookFunction( EFuncIndexes::GetIntIndex, Utils::Hooking::bSvCheats );

    g_pGrenadePreviewHook = std::make_unique<Utils::Hooking::CVMT>( );
    g_pGrenadePreviewHook->bInit( CS::Interfaces::g_pConsole->FindVar( STR( "cl_grenade_preview" ) ) );
    g_pGrenadePreviewHook->bHookFunction( EFuncIndexes::GetIntIndex, Utils::Hooking::bGrenadePreview );

    g_pClientModeHook = std::make_unique<Utils::Hooking::CVMT>( );
    g_pClientModeHook->bInit( CS::Interfaces::g_pClientMode );
    g_pClientModeHook->bHookFunction( EFuncIndexes::CreateMoveIndex, Utils::Hooking::bCreateMove );

    g_pSurfaceHook = std::make_unique<Utils::Hooking::CVMT>( );
    g_pSurfaceHook->bInit( CS::Interfaces::g_pSurface );
    g_pSurfaceHook->bHookFunction( EFuncIndexes::LockCursorIndex, Utils::Hooking::LockCursor );

    g_pPanelHook = std::make_unique<Utils::Hooking::CVMT>( );
    g_pPanelHook->bInit( CS::Interfaces::g_pPanel );
    g_pPanelHook->bHookFunction( EFuncIndexes::PaintTraverseIndex, Utils::Hooking::PaintTraverse );
  }

  void ReleaseHooks( ) noexcept {
    g_pCheatsHook->bUnhook( );
    g_pGrenadePreviewHook->bUnhook( );
    g_pClientModeHook->bUnhook( );
    g_pSurfaceHook->bUnhook( );
    g_pPanelHook->bUnhook( );
  }
} // namespace Utils::Hooking
