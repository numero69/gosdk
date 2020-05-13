#pragma once

#include "../../../utilities/global.hpp"

namespace CS::Features::Movement {
  inline void BunnyHop( ) noexcept {
    if ( Utils::Context::g_pLocal->Movetype( ) != CS::Classes::EMovetypes::MOVETYPE_LADDER &&
         Utils::Context::g_pLocal->Movetype( ) != CS::Classes::EMovetypes::MOVETYPE_NOCLIP ) {
      if ( !( Utils::Context::g_pLocal->Flags( ).bCheckFlag( CS::Classes::EEntityFlags::FL_ONGROUND ) &&
              Utils::Context::g_pCmd->Buttons.bCheckFlag( CS::Classes::CUserCmd::IN_JUMP ) ) ) {
        Utils::Context::g_pCmd->Buttons.RemoveFlag( CS::Classes::CUserCmd::IN_JUMP );
      }
    }
  }

  inline void NoDuckDelay( ) noexcept { Utils::Context::g_pCmd->Buttons.AddFlag( CS::Classes::CUserCmd::IN_BULLRUSH ); }
  
    inline void AutoStrafer() noexcept {
    if ( Utils::Context::g_pLocal->Movetype( ) != CS::Classes::EMovetypes::MOVETYPE_LADDER &&
         Utils::Context::g_pLocal->Movetype( ) != CS::Classes::EMovetypes::MOVETYPE_NOCLIP &&
         !Utils::Context::g_pLocal->Flags( ).bCheckFlag( CS::Classes::EEntityFlags::FL_ONGROUND ) ) {
      if ( Utils::Context::g_pCmd->MouseDX < 0 ) {
        Utils::Context::g_pCmd->SideMove = -450.0f;
      } else if ( Utils::Context::g_pCmd->MouseDX > 0 ) {
        Utils::Context::g_pCmd->SideMove = 450.0f;
      }
    }
  }
} // namespace CS::Features::Movement
