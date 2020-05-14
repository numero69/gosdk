#pragma once

#include "../../csgo/valve/classes/user_cmd.hpp"
#include "../../dependencies/global.hpp"
#include "../../utilities/global.hpp"
#include <Windows.h>
#include <assert.h>
#include <memory>
#include <stdexcept>
#include <stdio.h>

namespace Utils::Hooking {
  /* Utilities */
  class CVMT {
  public:
    CVMT( );

    bool bInit( void * base );

    bool bHookFunction( const std::uint16_t index, void * function );

    bool bUnhookFunction( const std::uint16_t index );

    bool bUnhook( );

    template <typename T = void *> T GetOriginalFunction( const std::uint16_t index ) {
      return reinterpret_cast<T>( OriginalVMT[ index ] );
    }

  private:
    std::uint32_t GetVTLength( std::uintptr_t * table );
    std::uintptr_t ** VMTBase = nullptr;
    std::uint16_t TableLength = 0;
    std::uintptr_t * OriginalVMT = nullptr;
    std::unique_ptr<uintptr_t[]> ReplaceVMT = nullptr;
    DWORD OldProtection{};
  };

  /* Indexes */
  enum EFuncIndexes { GetIntIndex = 13, CreateMoveIndex = 24, PaintTraverseIndex = 41, LockCursorIndex = 67 };

  /* Declarations */
  inline Utils::Hooking::CVMT g_CheatsHook;
  inline Utils::Hooking::CVMT g_GrenadePreviewHook;
  inline Utils::Hooking::CVMT g_ClientModeHook;
  inline Utils::Hooking::CVMT g_SurfaceHook;
  inline Utils::Hooking::CVMT g_PanelHook;

  /* These don't require originals because we want them to stay true at all times */

  static bool __stdcall bSvCheats( ) noexcept;
  static bool __stdcall bGrenadePreview( ) noexcept;

  /* Note - You could instead use decltype within the */
  /* GetOriginal function, but, after my testing */
  /* Results from that were inaccurate and caused */
  /* Rather weird issues. I advice you pass typedefinitions */
  /* To not runinto issues in the future. */

  static void __fastcall LockCursor( ) noexcept;
  using LockCursor_t = void( __thiscall * )( void * );

  static void __stdcall PaintTraverse( unsigned int Panel, bool ForceRepaint, bool AllowForce ) noexcept;
  using PaintTraverse_t = void( __thiscall * )( void *, unsigned int, bool, bool );

  static bool __fastcall bCreateMove( void * ecx, void * edx, int InputSampleFrameTime, CS::Classes::CUserCmd * Cmd ) noexcept;
  using CreateMove_t = bool( __stdcall * )( float, void * );

  /* Handlers */
  void RunHooks( ) noexcept;
  void ReleaseHooks( ) noexcept;
} // namespace Utils::Hooking