#pragma once

#include "../../../utilities/global.hpp"

/* Indexes */
enum EDebugOverlayIndexes : short { WorldToScreen_index = 13 };

namespace CS::Interfaces {
  class IDebugOverlay {
  public:
    constexpr auto WorldToScreen( const Utils::Math::Vector & Point, Utils::Math::Vector & ToScreen ) {
      return Utils::Memory::CallVirtualMethod<int, const Utils::Math::Vector &, Utils::Math::Vector &>(
          this, EDebugOverlayIndexes::WorldToScreen_index, Point, ToScreen );
    }
  };
} // namespace CS::Interfaces