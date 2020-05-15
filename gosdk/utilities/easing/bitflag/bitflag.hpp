#pragma once

#include <inttypes.h>

namespace Utils::Easing {
  struct BitFlag {
    BitFlag( ) = default;

    BitFlag( uintptr_t flags ) : u_pFlags( flags ) {}

    ~BitFlag( ) = default;

    uintptr_t u_pFlags{};

    inline bool bCheckFlag( uintptr_t flag ) { return u_pFlags & flag; }

    inline void AddFlag( uintptr_t flag ) { u_pFlags |= flag; }

    inline void RemoveFlag( uintptr_t flag ) { u_pFlags &= ~flag; }

    inline bool bIsEmpty( ) { return !u_pFlags; }
  };
} // namespace Utils::Easing
