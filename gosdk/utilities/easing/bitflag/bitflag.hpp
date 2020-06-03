#pragma once

#include <inttypes.h>

namespace Utils::Easing {
  struct BitFlag {
    uintptr_t u_pFlags{ };

    BitFlag( ) = default;

    BitFlag( const uintptr_t flags ) : u_pFlags( flags ) {}

    ~BitFlag( ) = default;

    /// <summary>
    /// Function made to return pointer to BitFlag object and cast it to a specific datatype
    /// </summary>
    /// <returns>Function casted to automatically deducted type or specified type</returns>
    template <typename T> T pThis( ) { return reinterpret_cast<T>( *this ); }

    inline bool bCheckFlag( const uintptr_t flag ) { return u_pFlags & flag; }

    inline void AddFlag( const uintptr_t flag ) { u_pFlags |= flag; }

    inline void RemoveFlag( const uintptr_t flag ) { u_pFlags &= ~flag; }

    inline bool bIsEmpty( ) { return !u_pFlags; }
  };
} // namespace Utils::Easing
