#pragma once

#include "../utilities/netvar/global.hpp"
#include "../interfaces/i_client_unknown.hpp"

namespace csgo::valve::classes
{
enum class movetypes {
	movetype_none = 0,
	movetype_isometric,
	movetype_walk,
	movetype_step,
	movetype_fly,
	movetype_flygravity,
	movetype_vphysics,
	movetype_push,
	movetype_noclip,
	movetype_ladder,
	movetype_observer,
	movetype_custom,
	movetype_last = movetype_custom,
	movetype_max_bits = 4
};

enum entity_flags {
	fl_onground = (1 << 0),
	fl_ducking = (1 << 1),
	fl_waterjump = (1 << 2),
	fl_ontrain = (1 << 3),
	fl_inrain = (1 << 4),
	fl_frozen = (1 << 5),
	fl_atcontrols = (1 << 6),
	fl_client = (1 << 7),
	fl_fakeclient = (1 << 8),
	fl_inwater = (1 << 9),
	fl_fly = (1 << 10),
	fl_swim = (1 << 11),
	fl_conveyor = (1 << 12),
	fl_npc = (1 << 13),
	fl_godmode = (1 << 14),
	fl_notarget = (1 << 15),
	fl_aimtarget = (1 << 16),
	fl_partialground = (1 << 17),
	fl_staticprop = (1 << 18),
	fl_graphed = (1 << 19),
	fl_grenade = (1 << 20),
	fl_stepmovement = (1 << 21),
	fl_donttouch = (1 << 22),
	fl_basevelocity = (1 << 23),
	fl_worldbrush = (1 << 24),
	fl_object = (1 << 25),
	fl_killme = (1 << 26),
	fl_onfire = (1 << 27),
	fl_dissolving = (1 << 28),
	fl_transragdoll = (1 << 29),
	fl_unblockable_by_player = (1 << 30)
};

// XOR'd in wrapper
class c_player : public csgo::valve::interfaces::i_client_unknown {
    public:
	netvar(int, health, "DT_BasePlayer->m_iHealth");
	netvar(std::uint8_t, life_state, "DT_BasePlayer->m_lifeState");
	netvar(int, armor, "DT_CSPlayer->m_ArmorValue");
	netvar(bool, has_helmet, "DT_CSPlayer->m_bHasHelmet");
	netvar(std::uint32_t, flags, "DT_BasePlayer->m_fFlags");
	netvar(bool, immune, "DT_CSPlayer->m_bGunGameImmunity");
	netvar(bool, scoped, "DT_CSPlayer->m_bIsScoped");
	netvar(float, flash_duration, "DT_CSPlayer->m_flFlashDuration");
	netvar(float, flash_alpha, "DT_CSPlayer->m_flFlashMaxAlpha");
	netvar(float, crouch_amount, "DT_BasePlayer->m_flDuckAmount");
	netvar(utilities::math::vec3_t, view_punch, "DT_BasePlayer->m_viewPunchAngle");
	netvar(utilities::math::vec3_t, aim_punch,
	       "DT_BasePlayer->m_aimPunchAngle");
	netvar(utilities::math::vec3_t, vel,
	       "DT_LocalPlayerExclusive->m_vecVelocity[0]");
	netvar_additive(movetypes, movetype, "DT_BaseEntity->m_nRenderMode", 1);
	netvar(utilities::math::vec3_t, origin, "DT_BaseEntity->m_vecOrigin");

	bool is_alive()
	{
		if (!this)
			return false;

		return this->health() > 0;
	}
};
} // namespace csgo::valve::classes
