#pragma once

#include "../../../utilities/math/vector2d.hpp"
#include "../../../utilities/math/vector3d.hpp"
#include "../classes/client_class.hpp"

namespace CS::Interfaces {
  class CCSPlayer;

  class IHandleEntity {
  public:
    virtual ~IHandleEntity( ) = default;

    virtual void SetRefHandle( const std::uint32_t & handle ) = 0;
    virtual const std::uint32_t & GetRefHandle( ) const = 0;
  };

  class ICollidable {
  public:
    virtual IHandleEntity * GetEntityHandle( ) = 0;
    virtual Utils::Math::Vector & OBBMins( ) const = 0;
    virtual Utils::Math::Vector & OBBMaxs( ) const = 0;
  };

  class CClientThinkable;
  class CClientAlphaProperty;
  class CClientRenderable;
  class CClientUnknown : public IHandleEntity {
  public:
    virtual ICollidable * GetCollideable( ) = 0;
    virtual CS::Classes::CClientNetworkable * GetClientNetworkable( ) = 0;
    virtual CClientRenderable * GetClientRenderable( ) = 0;
    virtual CCSPlayer * GetIClientEntity( ) = 0;
    virtual CCSPlayer * GetBaseEntity( ) = 0;
    virtual CClientThinkable * GetClientThinkable( ) = 0;
    virtual CClientAlphaProperty * GetClientAlphaProperty( ) = 0;
  };
}; // namespace CS::Interfaces
