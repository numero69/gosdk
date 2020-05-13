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
    int Pad;
    int CommandNumber;
    int TickCount;
    Utils::Math::Vector ViewAngles;
    Utils::Math::Vector AimDirection;
    float ForwardMove;
    float SideMove;
    float UpMove;
    Utils::Easing::BitFlag Buttons;
    char Impulse;
    int WeaponSelect;
    int WeaponSubtype;
    int RandomSeed;
    short MouseDX;
    short MouseDY;
    bool HasBeenPredicted;
  }; // namespace CS::Classes
} // namespace CS::Classes