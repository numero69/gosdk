#pragma once
#include <Windows.h>
#include <assert.h>
#include <memory>
#include <stdexcept>
#include <stdio.h>

namespace Utils {
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
    std::uintptr_t GetVTLength( std::uintptr_t * table );
    std::uintptr_t ** VMTBase = nullptr;
    std::uintptr_t TableLength = 0;
    std::uintptr_t * OriginalVMT = nullptr;
    std::unique_ptr<uintptr_t[]> ReplaceVMT = nullptr;
    DWORD OldProtection{ };
  };
} // namespace Utils
