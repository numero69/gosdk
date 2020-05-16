#pragma once

#include "../../../utilities/easing/bitflag/bitflag.hpp"
#include "../../../utilities/math/vector3d.hpp"

namespace CS::Classes {
  class CUserCmd {
  public:
    enum {
      IN_ATTACK = 1 << 0,
      IN_JUMP = 1 << 1,
      IN_DUCK = 1 << 2,
      IN_FORWARD = 1 << 3,
      IN_BACK = 1 << 4,
      IN_USE = 1 << 5,
      IN_MOVELEFT = 1 << 9,
      IN_MOVERIGHT = 1 << 10,
      IN_ATTACK2 = 1 << 11,
      IN_SCORE = 1 << 16,
      IN_BULLRUSH = 1 << 22
    };
    int m_iPad;
    int m_iCommandNumber;
    int m_iTickCount;
    Utils::Math::Vector m_ViewAngles;
    Utils::Math::Vector m_AimDirection;
    float m_fForwardMove;
    float m_fSideMove;
    float m_fUpMove;
    Utils::Easing::BitFlag m_Buttons;
    char m_cImpulse;
    int m_iWeaponSelect;
    int m_iWeaponSubtype;
    int m_iRandomSeed;
    short m_siMouseDX;
    short m_siMouseDY;
    bool m_bHasBeenPredicted;
  }; // namespace CS::Classes
} // namespace CS::Classes