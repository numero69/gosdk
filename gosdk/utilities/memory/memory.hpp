#pragma once

#include <Psapi.h>
#include <TlHelp32.h>
#include <Windows.h>
#include <cmath>
#include <vector>

#include "../../dependencies/global.hpp"

namespace Utils::Memory {
  /* Credits go to the people who made these functions. */
  inline static void * ScanInterface( const char * module_name, const char * interface_name ) noexcept {
    const auto module_handle = GetModuleHandleA( module_name );

    if ( !module_handle )
      return nullptr;

    const auto create_interface_fn =
        reinterpret_cast<void * (*)( const char *, int * )>( GetProcAddress( module_handle, STR( "CreateInterface" ) ) );

    if ( !create_interface_fn )
      return nullptr;

    const auto interface_address = create_interface_fn( interface_name, nullptr );

    if ( !interface_address )
      return nullptr;

    return interface_address;
  }
  inline static std::uint8_t * FindPattern( const char * module_name, const char * signature ) noexcept {
    const auto module_handle = GetModuleHandleA( module_name );

    if ( !module_handle )
      return nullptr;

    static auto pattern_to_byte = []( const char * pattern ) {
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

    auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>( module_handle );
    auto nt_headers =
        reinterpret_cast<PIMAGE_NT_HEADERS>( reinterpret_cast<std::uint8_t *>( module_handle ) + dos_header->e_lfanew );

    auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
    auto pattern_bytes = pattern_to_byte( signature );
    auto scan_bytes = reinterpret_cast<std::uint8_t *>( module_handle );

    auto s = pattern_bytes.size( );
    auto d = pattern_bytes.data( );

    for ( auto i = 0ul; i < size_of_image - s; ++i ) {
      bool found = true;

      for ( auto j = 0ul; j < s; ++j ) {
        if ( scan_bytes[ i + j ] != d[ j ] && d[ j ] != -1 ) {
          found = false;
          break;
        }
      }
      if ( found )
        return &scan_bytes[ i ];
    }

    return nullptr;
  }
  inline static std::uintptr_t FindPattern( const wchar_t * module, const char * pattern, size_t offset = 0 ) noexcept {
    static auto id = 0;
    ++id;

    if ( MODULEINFO module_info;
         GetModuleInformation( GetCurrentProcess( ), GetModuleHandleW( module ), &module_info, sizeof( module_info ) ) ) {
      auto start = static_cast<const char *>( module_info.lpBaseOfDll );
      const auto end = start + module_info.SizeOfImage;

      auto first = start;
      auto second = pattern;

      while ( first < end && *second ) {
        if ( *first == *second || *second == '?' ) {
          ++first;
          ++second;
        } else {
          first = ++start;
          second = pattern;
        }
      }

      if ( !*second )
        return reinterpret_cast<std::uintptr_t>( const_cast<char *>( start ) + offset );
    }
    return 0;
  }
  template <typename T, typename... Args>
  inline constexpr auto CallVirtualMethod( void * class_base, int index, Args... args ) noexcept {
    return ( ( *reinterpret_cast<T( __thiscall *** )( void *, Args... )>( class_base ) )[ index ] )( class_base, args... );
  }
} // namespace Utils::Memory