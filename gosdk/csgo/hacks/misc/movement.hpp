#pragma once

#include "../../../utilities/global.hpp"

namespace CS::Features {
  class CMovement {
  public:
    /// <summary>
    /// Function that handles Local flags to perfectly sync IN_JUMP
    /// </summary>
    /// <returns></returns>
    void BunnyHop( ) noexcept {
      if ( Utils::g_Context.g_pLocal->m_Movetype( ) != CS::Classes::EMovetypes::MOVETYPE_LADDER &&
           Utils::g_Context.g_pLocal->m_Movetype( ) != CS::Classes::EMovetypes::MOVETYPE_NOCLIP ) {
        if ( !( Utils::g_Context.g_pLocal->m_Flags( ).bCheckFlag( CS::Classes::EEntityFlags::FL_ONGROUND ) &&
                Utils::g_Context.g_pCmd->m_Buttons.bCheckFlag( CS::Classes::CUserCmd::IN_JUMP ) ) ) {
          Utils::g_Context.g_pCmd->m_Buttons.RemoveFlag( CS::Classes::CUserCmd::IN_JUMP );
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
    void NoDuckDelay( ) noexcept { Utils::g_Context.g_pCmd->m_Buttons.AddFlag( CS::Classes::CUserCmd::IN_BULLRUSH ); }
  };

  inline CMovement g_Movement{ };
} // namespace CS::Features