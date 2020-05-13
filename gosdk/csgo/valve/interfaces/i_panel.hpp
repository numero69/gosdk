#pragma once

#include "../../../utilities/global.hpp"

namespace CS::Interfaces {
  class IPanel {
  public:
    constexpr auto GetName( unsigned int panel ) noexcept {
      return std::string_view{ Utils::Memory::CallVirtualMethod<const char *, unsigned int>( this, 36, panel ) };
    }
  };
} // namespace CS::Interfaces