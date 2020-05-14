#pragma once

#include <Psapi.h>
#include <TlHelp32.h>
#include <Windows.h>
#include <cmath>
#include <vector>

#include "../../dependencies/global.hpp"

namespace Utils::Memory {
  /* Credits go to the people who made these functions and various edits by @cristeigabriel [minimal] */
  inline static void * ScanInterface( const char * ModuleName, const char * InterfaceName ) noexcept {
    const auto ModuleHandle = GetModuleHandleA( ModuleName );

    if ( !ModuleHandle )
      return nullptr;

    const auto CreateInterface_t =
        reinterpret_cast<void * (*)( const char *, int * )>( GetProcAddress( ModuleHandle, STR( "CreateInterface" ) ) );

    if ( !CreateInterface_t )
      return nullptr;

    const auto InterfaceAddress = CreateInterface_t( InterfaceName, nullptr );

    if ( !InterfaceAddress )
      return nullptr;

    return InterfaceAddress;
  }

  inline static std::uint8_t * FindPattern( const char * ModuleName, const char * Signature ) noexcept {
    const auto ModuleHandle = GetModuleHandleA( ModuleName );

    if ( !ModuleHandle )
      return nullptr;

    static auto PatternToBytes = []( const char * pattern ) {
      auto bytes = std::vector<int>{};
      auto start = const_cast<char *>( pattern );
      auto end = const_cast<char *>( pattern ) + std::strlen( pattern );

      for ( auto current = start; current < end; ++current ) {
        if ( *current == '?' ) {
          ++current;

          if ( *current == '?' )
            ++current;

          bytes.push_back( -1 );
        } else {
          bytes.push_back( std::strtoul( current, &current, 16 ) );
        }
      }
      return bytes;
    };

    auto DosHeaders = reinterpret_cast<PIMAGE_DOS_HEADER>( ModuleHandle );
    auto NtHeaders =
        reinterpret_cast<PIMAGE_NT_HEADERS>( reinterpret_cast<std::uint8_t *>( ModuleHandle ) + DosHeaders->e_lfanew );

    auto SizeOfImage = NtHeaders->OptionalHeader.SizeOfImage;
    auto PatternBytes = PatternToBytes( Signature );
    auto ScanBytes = reinterpret_cast<std::uint8_t *>( ModuleHandle );

    auto s = PatternBytes.size( );
    auto d = PatternBytes.data( );

    for ( auto i = 0ul; i < SizeOfImage - s; ++i ) {
      bool found = true;

      for ( auto j = 0ul; j < s; ++j ) {
        if ( ScanBytes[ i + j ] != d[ j ] && d[ j ] != -1 ) {
          found = false;
          break;
        }
      }
      if ( found )
        return &ScanBytes[ i ];
    }

    return nullptr;
  }

  template <typename T, typename... Args>
  inline constexpr auto CallVirtualMethod( void * class_base, int index, Args... args ) noexcept {
    return ( ( *reinterpret_cast<T( __thiscall *** )( void *, Args... )>( class_base ) )[ index ] )( class_base, args... );
  }
} // namespace Utils::Memory