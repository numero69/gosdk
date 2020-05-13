#pragma once

#include "../interfaces/i_client_unknown.hpp"
#include "../utilities/netvar/global.hpp"

namespace CS::Classes {
  enum class EMovetypes {
    MOVETYPE_NONE = 0,
    MOVETYPE_ISOMETRIC,
    MOVETYPE_WALK,
    MOVETYPE_STEP,
    MOVETYPE_FLY,
    MOVETYPE_FLYGRAVITY,
    MOVETYPE_VPHYSICS,
    MOVETYPE_PUSH,
    MOVETYPE_NOCLIP,
    MOVETYPE_LADDER,
    MOVETYPE_OBSERVER,
    MOVETYPE_CUSTOM,
    MOVETYPE_LAST = MOVETYPE_CUSTOM,
    MOVETYPE_MAX_BITS = 4
  };

  enum EEntityFlags {
    FL_ONGROUND = ( 1 << 0 ),
    FL_DUCKING = ( 1 << 1 ),
    FL_WATERJUMP = ( 1 << 2 ),
    FL_ONTRAIN = ( 1 << 3 ),
    FL_INRAIN = ( 1 << 4 ),
    FL_FROZEN = ( 1 << 5 ),
    FL_ATCONTROLS = ( 1 << 6 ),
    FL_CLIENT = ( 1 << 7 ),
    FL_FAKECLIENT = ( 1 << 8 ),
    FL_INWATER = ( 1 << 9 ),
    FL_FLY = ( 1 << 10 ),
    FL_SWIM = ( 1 << 11 ),
    FL_CONVEYOR = ( 1 << 12 ),
    FL_NPC = ( 1 << 13 ),
    FL_GODMODE = ( 1 << 14 ),
    FL_NOTARGET = ( 1 << 15 ),
    FL_AIMTARGET = ( 1 << 16 ),
    FL_PARTIALGROUND = ( 1 << 17 ),
    FL_STATICPROP = ( 1 << 18 ),
    FL_GRAPHED = ( 1 << 19 ),
    FL_GRENADE = ( 1 << 20 ),
    FL_STEPMOVEMENT = ( 1 << 21 ),
    FL_DONTTOUCH = ( 1 << 22 ),
    FL_BASEVELOCITY = ( 1 << 23 ),
    FL_WORLDBRUSH = ( 1 << 24 ),
    FL_OBJECT = ( 1 << 25 ),
    FL_KILLME = ( 1 << 26 ),
    FL_ONFIRE = ( 1 << 27 ),
    FL_DISSOLVING = ( 1 << 28 ),
    FL_TRANSRAGDOLL = ( 1 << 29 ),
    FL_UNBLOCKABLE_BY_PLAYER = ( 1 << 30 )
  };

  // Elements are XOR'd in the wrapper.
  class CCSPlayer : public CS::Interfaces::CClientUnknown {
  public:
    netvar( int, Health, "DT_BasePlayer->m_iHealth" );
    netvar( std::uint8_t, uLifeState, "DT_BasePlayer->m_lifeState" );
    netvar( int, Armor, "DT_CSPlayer->m_ArmorValue" );
    netvar( bool, HasHelmet, "DT_CSPlayer->m_bHasHelmet" );
    netvar( Utils::Easing::BitFlag, Flags, "DT_BasePlayer->m_fFlags" );
    netvar( bool, Immune, "DT_CSPlayer->m_bGunGameImmunity" );
    netvar( bool, Scoped, "DT_CSPlayer->m_bIsScoped" );
    netvar( float, FlashDuration, "DT_CSPlayer->m_flFlashDuration" );
    netvar( float, FlashAlpha, "DT_CSPlayer->m_flFlashMaxAlpha" );
    netvar( float, CrouchAmount, "DT_BasePlayer->m_flDuckAmount" );
    netvar( Utils::Math::Vector, ViewPunch, "DT_BasePlayer->m_viewPunchAngle" );
    netvar( Utils::Math::Vector, AimPunch, "DT_BasePlayer->m_aimPunchAngle" );
    netvar( Utils::Math::Vector, Velocity, "DT_LocalPlayerExclusive->m_vecVelocity[0]" );
    netvar_additive( EMovetypes, Movetype, "DT_BaseEntity->m_nRenderMode", 1 );
    netvar( Utils::Math::Vector, Origin, "DT_BaseEntity->m_vecOrigin" );
    offset( bool, bDormant, 0xED );
    bool bIsAlive( ) {
      if ( !this )
        return false;

      return this->Health( ) > 0;
    }
  };
} // namespace CS::Classes
