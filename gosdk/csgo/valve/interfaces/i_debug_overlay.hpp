#pragma once

#include "../../../utilities/global.hpp"

namespace CS::Interfaces {
  class IDebugOverlay {
  public:
    constexpr auto WorldToScreen( const Utils::Math::Vector & point, Utils::Math::Vector & screen ) {
      return Utils::Memory::CallVirtualMethod<int, const Utils::Math::Vector &, Utils::Math::Vector &>( this, 13, point, screen );
    }
  };
} // namespace CS::Interfaces