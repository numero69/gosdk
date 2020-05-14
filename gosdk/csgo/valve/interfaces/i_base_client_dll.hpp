#pragma once

#include "../../../utilities/global.hpp"
#include "../classes/global.hpp"

/* Indexes */
enum EBaseClientIndexes : short { GetAllClasses_index = 8 };

namespace CS::Interfaces {
  class IBaseClientDLL {
  public:
    constexpr auto GetAllClasses( ) noexcept {
      return Utils::Memory::CallVirtualMethod<CS::Classes::CClientClass *>( this, EBaseClientIndexes::GetAllClasses_index );
    }
  };
} // namespace CS::Interfaces