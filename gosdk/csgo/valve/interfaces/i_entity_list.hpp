#pragma once

#include "../../../utilities/memory/global.hpp"
#include "../classes/players.hpp"

/* Indexes */
enum EEntityListIndexes : short { GetEntity_index = 3, GetEntityFromHandle_index = 4, GetHighestEntity_index = 6 };

namespace CS::Interfaces {
  class IEntityList {
  public:
    constexpr auto GetEntity( int index ) noexcept {
      return Utils::g_Memory.CallVirtualMethod<CS::Classes::CCSPlayer *, int>( this, EEntityListIndexes::GetEntity_index, index );
    }

    constexpr auto GetEntityFromHandle( int handle ) noexcept {
      return Utils::g_Memory.CallVirtualMethod<CS::Classes::CCSPlayer *, int>(
          this, EEntityListIndexes::GetEntityFromHandle_index, handle );
    }

    constexpr auto GetHighestEntityIndex( ) noexcept {
      return Utils::g_Memory.CallVirtualMethod<int>( this, EEntityListIndexes::GetHighestEntity_index );
    }
  };
} // namespace CS::Interfaces