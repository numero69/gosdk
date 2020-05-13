#pragma once

#include "../../../utilities/memory/global.hpp"
#include "../classes/players.hpp"

namespace CS::Interfaces {
  class IEntityList {
  public:
    constexpr auto GetEntity( int index ) noexcept {
      return Utils::Memory::CallVirtualMethod<CS::Classes::CCSPlayer *, int>( this, 3, index );
    }

    constexpr auto GetEntityFromHandle( int handle ) noexcept {
      return Utils::Memory::CallVirtualMethod<CS::Classes::CCSPlayer *, int>( this, 4, handle );
    }

    constexpr auto GetHighestEntityIndex( ) noexcept { return Utils::Memory::CallVirtualMethod<int>( this, 6 ); }
  };
} // namespace CS::Interfaces