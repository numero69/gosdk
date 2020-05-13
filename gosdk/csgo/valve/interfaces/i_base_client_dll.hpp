#pragma once

#include "../../../utilities/global.hpp"
#include "../classes/global.hpp"

namespace CS::Interfaces {
  class IBaseClientDLL {
  public:
    constexpr auto GetAllClasses( ) noexcept { return Utils::Memory::CallVirtualMethod<CS::Classes::CClientClass *>( this, 8 ); }
  };
} // namespace CS::Interfaces