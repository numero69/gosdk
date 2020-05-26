#include "hook.hpp"
#include "../../config/config.hpp"
#include "../../csgo/global.hpp"
#include <algorithm>
#include <intrin.h>

namespace Utils::Hooking {
  static bool __stdcall bSvCheats( ) noexcept { return true; }

  static bool __stdcall bGrenadePreview( ) noexcept { return true; }

  static void __fastcall LockCursor( ) noexcept {
    static auto Original = g_SurfaceHook.GetOriginalFunction<LockCursor_t>( EFuncIndexes::LockCursor_index );

    if ( GetAsyncKeyState( VK_INSERT ) ) {
      CS::Interfaces::g_pSurface->UnlockCursor( );
      return;
    }

    if ( Original )
      return Original( CS::Interfaces::g_pSurface );
  }

  static void __stdcall PaintTraverse( unsigned int Panel, bool ForceRepaint, bool AllowForce ) noexcept {
    static auto Original = g_PanelHook.GetOriginalFunction<PaintTraverse_t>( EFuncIndexes::PaintTraverse_index );

    if ( CS::Interfaces::g_pPanel->GetName( Panel ) == STR( "MatSystemTopPanel" ) ) {
      Utils::Render::RenderText( 15, 15, Utils::Render::Verdana, Utils::Color( 255, 255, 255, 255 ), L"Test" );
      if ( CS::Interfaces::g_pEngineClient->IsInGame( ) && CS::Interfaces::g_pEngineClient->IsConnected( ) ) {
        CS::Features::ESP::RunEsp( );
      }
    }

    if ( Original )
      Original( CS::Interfaces::g_pPanel, Panel, ForceRepaint, AllowForce );
  }

  static bool __fastcall bCreateMove( void * ecx, void * edx, int InputSampleFrameTime, CS::Classes::CUserCmd * Cmd ) noexcept {
    if ( !InputSampleFrameTime || !Cmd || !Cmd->m_iCommandNumber )
      return false;

    Utils::Context::g_pCmd = Cmd;
    Utils::Context::g_pLocal = CS::Interfaces::g_pEntityList->GetEntity( CS::Interfaces::g_pEngineClient->GetLocalPlayer( ) );

    CS::Features::Movement::BunnyHop( );
    CS::Features::Movement::NoDuckDelay( );

    Cmd->m_fForwardMove = std::clamp( Cmd->m_fForwardMove, -450.0f, 450.0f );
    Cmd->m_fSideMove = std::clamp( Cmd->m_fSideMove, -450.0f, 450.0f );
    Cmd->m_fUpMove = std::clamp( Cmd->m_fUpMove, -320.0f, 320.0f );

    Cmd->m_ViewAngles.m_X = std::clamp( Cmd->m_ViewAngles.m_X, -89.0f, 89.0f );
    Cmd->m_ViewAngles.m_Y = std::clamp( Cmd->m_ViewAngles.m_Y, -180.0f, 180.0f );
    Cmd->m_ViewAngles.m_Z = 0.0f;

    return false;
  }

  static LRESULT WINAPI lipWinProc( HWND WindowHandle, UINT Message, WPARAM WindowParams, LPARAM lpParams ) noexcept {
    if ( Message == WM_KEYUP ) {
      switch ( WindowParams ) {
        case VK_INSERT:
          Utils::Console::Log<std::string_view>( "Hit" );
          /* There you can handle stuff such as input disabling / enabling, although that can
             also be done in places like LockCursor. This is to help with stuff like menu frameworks
             such as ImGui. This also only handles events if they're done within the window the DLL is injected in. */
          break;
      }
    }

    if ( GetAsyncKeyState( VK_INSERT ) ) {
      return true;
    }

    return CallWindowProcW( g_pWindowOriginal, WindowHandle, Message, WindowParams, lpParams );
  }

  static long WINAPI liPresent( IDirect3DDevice9 * Device,
                                RECT * SourceRect,
                                RECT * DestinationRect,
                                HWND DestinationWindowOverride,
                                RGNDATA * DirtyRegion ) noexcept {
    return g_OriginalPresent( Device, SourceRect, DestinationRect, DestinationWindowOverride, DirtyRegion );
  }

  static long WINAPI liReset( IDirect3DDevice9 * Device, D3DPRESENT_PARAMETERS * PresentParams ) noexcept {
    long hr = g_OriginalReset( Device, PresentParams );
    return hr;
  }

  void RunHooks( ) noexcept {
    g_CheatsHook.bInit( CS::Interfaces::g_pConsole->FindVar( STR( "sv_cheats" ) ) );
    g_CheatsHook.bHookFunction( EFuncIndexes::GetInt_index, Utils::Hooking::bSvCheats );

    g_GrenadePreviewHook.bInit( CS::Interfaces::g_pConsole->FindVar( STR( "cl_grenade_preview" ) ) );
    g_GrenadePreviewHook.bHookFunction( EFuncIndexes::GetInt_index, Utils::Hooking::bGrenadePreview );

    g_ClientModeHook.bInit( CS::Interfaces::g_pClientMode );
    g_ClientModeHook.bHookFunction( EFuncIndexes::CreateMove_index, Utils::Hooking::bCreateMove );

    g_SurfaceHook.bInit( CS::Interfaces::g_pSurface );
    g_SurfaceHook.bHookFunction( EFuncIndexes::LockCursor_index, Utils::Hooking::LockCursor );

    g_PanelHook.bInit( CS::Interfaces::g_pPanel );
    g_PanelHook.bHookFunction( EFuncIndexes::PaintTraverse_index, Utils::Hooking::PaintTraverse );

    /* May not be visually appleasing to have all of those
       things laying around here, but it is done so to not
       have to worry about the order of how things are called.
       I tried other methods, more visually pleasing, and that didn't work.
       Well, I guess that sucks. */
    g_upPresentAddress = Utils::Memory::FindPattern( STR( "gameoverlayrenderer.dll" ), STR( "FF 15 ? ? ? ? 8B F8 85 DB" ) ) + 0x2;
    g_upResetAddress =
        Utils::Memory::FindPattern( STR( "gameoverlayrenderer.dll" ), STR( "FF 15 ? ? ? ? 8B F8 85 FF 78 18" ) ) + 0x2;

    g_OriginalPresent = **reinterpret_cast<Present_t **>( g_upPresentAddress );
    g_OriginalReset = **reinterpret_cast<Reset_t **>( g_upResetAddress );

    **reinterpret_cast<void ***>( g_upPresentAddress ) = reinterpret_cast<void *>( &liPresent );
    **reinterpret_cast<void ***>( g_upResetAddress ) = reinterpret_cast<void *>( &liReset );

    g_pWindow = FindWindowW( L"Valve001", nullptr );
    g_pWindowOriginal =
        reinterpret_cast<WNDPROC>( SetWindowLongW( g_pWindow, GWL_WNDPROC, reinterpret_cast<LONG>( lipWinProc ) ) );
  }

  void ReleaseHooks( ) noexcept {
    g_CheatsHook.bUnhook( );
    g_GrenadePreviewHook.bUnhook( );
    g_ClientModeHook.bUnhook( );
    g_SurfaceHook.bUnhook( );
    g_PanelHook.bUnhook( );
  }
} // namespace Utils::Hooking
