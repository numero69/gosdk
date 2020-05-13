#pragma once

#include "../../../utilities/global.hpp"
#include "../utilities/c_utl.hpp"

namespace CS::Classes {
  class CConvar;
  using ChangeCallback_t = void ( * )( CConvar * var, const char * pOldValue, float flOldValue );
  class CConvar {
  public:
    constexpr auto GetFloat( ) noexcept { return Utils::Memory::CallVirtualMethod<float>( this, 12 ); }
    constexpr auto GetInt( ) noexcept { return Utils::Memory::CallVirtualMethod<int>( this, 13 ); }
    constexpr auto SetValue( const char * value ) { Utils::Memory::CallVirtualMethod<void, const char *>( this, 14, value ); }
    constexpr auto SetValue( float value ) { Utils::Memory::CallVirtualMethod<void, float>( this, 15, value ); }
    constexpr auto SetValue( int value ) { Utils::Memory::CallVirtualMethod<void, int>( this, 16, value ); }

  private:
    char Pad[ 0x4 ];

  public:
    CConvar * Next;
    __int32 IsRegistered;
    char * Name;
    char * HelpString;
    __int32 Flags;

  private:
    char Pad2[ 0x4 ];

  public:
    CConvar * Parent;
    char * DefaultValue;
    char * String;
    __int32 StringLength;
    float FloatValue;
    __int32 NumericalValue;
    __int32 HasMin;
    float Min;
    __int32 HasMax;
    float Max;
    CUtlVector<ChangeCallback_t> Callbacks;
  };
} // namespace CS::Classes