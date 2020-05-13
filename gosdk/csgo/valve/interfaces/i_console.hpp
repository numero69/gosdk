#pragma once

#include "../../../utilities/global.hpp"
#include "../classes/convar.hpp"

namespace CS::Interfaces {
  class IConsole {
  public:
    constexpr auto FindVar( const char * name ) noexcept {
      return Utils::Memory::CallVirtualMethod<CS::Classes::CConvar *, const char *>( this, 15, name );
    }
  };
} // namespace CS::Interfaces