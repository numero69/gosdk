#pragma once

#include "../../../utilities/global.hpp"

/* Indexes */
enum EPanelIndexes : short { GetName_index = 36 };

namespace CS::Interfaces {
  class IPanel {
  public:
    constexpr auto GetName( unsigned int panel ) noexcept {
      return std::string_view{ Utils::Memory::CallVirtualMethod<const char *, unsigned int>(
          this, EPanelIndexes::GetName_index, panel ) };
    }
  };
} // namespace CS::Interfaces