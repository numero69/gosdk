#pragma once

#include <inttypes.h>

namespace Utils::Easing {
  struct BitFlag {
    BitFlag( ) = default;

    BitFlag( uintptr_t flags ) : upFlags( flags ) {}

    ~BitFlag( ) = default;

    uintptr_t upFlags{};

    inline bool bCheckFlag( uintptr_t flag ) { return upFlags & flag; }

    inline void AddFlag( uintptr_t flag ) { upFlags |= flag; }

    inline void RemoveFlag( uintptr_t flag ) { upFlags &= ~flag; }

    inline bool bIsEmpty( ) { return !upFlags; }
  };
} // namespace Utils::Easing