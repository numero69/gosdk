#pragma once

#include "../../../utilities/global.hpp"

namespace CS::Features::Movement {
  /// <summary>
  /// Function that handles Local flags to perfectly sync IN_JUMP
  /// </summary>
  /// <returns></returns>
  inline void BunnyHop( ) noexcept {
    if ( Utils::Context::g_pLocal->m_Movetype( ) != CS::Classes::EMovetypes::MOVETYPE_LADDER &&
         Utils::Context::g_pLocal->m_Movetype( ) != CS::Classes::EMovetypes::MOVETYPE_NOCLIP ) {
      if ( !( Utils::Context::g_pLocal->m_Flags( ).bCheckFlag( CS::Classes::EEntityFlags::FL_ONGROUND ) &&
              Utils::Context::g_pCmd->m_Buttons.bCheckFlag( CS::Classes::CUserCmd::IN_JUMP ) ) ) {
        Utils::Context::g_pCmd->m_Buttons.RemoveFlag( CS::Classes::CUserCmd::IN_JUMP );
      }
    }
  }

  /// <summary>
  /// Quoting CS:GO source code:
  /// 	// HACK: IN_BULLRUSH isn't used anywhere.  We use it to store the "raw" value of whether
  ///       IN_DUCK was held, before it is modified by code. This way when m_nButtons is
  ///       copied to m_nOldButtons we can tell if duck was pressed or released on the next
  ///       frame.
  /// 
  /// Used to get rid of the duck delay
  /// </summary>
  inline void NoDuckDelay( ) noexcept { Utils::Context::g_pCmd->m_Buttons.AddFlag( CS::Classes::CUserCmd::IN_BULLRUSH ); }
} // namespace CS::Features::Movement