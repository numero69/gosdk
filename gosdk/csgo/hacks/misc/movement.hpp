#pragma once

#include "../../../utilities/global.hpp"

namespace csgo::hacks::misc::movement
{
inline void bunny_hop() noexcept
{
	if (utilities::globals::local->movetype() !=
		    csgo::valve::classes::movetypes::movetype_ladder &&
	    utilities::globals::local->movetype() !=
		    csgo::valve::classes::movetypes::movetype_noclip) {

		if (!(utilities::globals::local->flags() &
		      csgo::valve::classes::entity_flags::fl_onground) &&
		    utilities::globals::cmd->buttons.check_flag(
			    csgo::valve::classes::user_cmd::in_jump)) {

			utilities::globals::cmd->buttons.remove_flag(
				csgo::valve::classes::user_cmd::in_jump);
		}
	}
}

inline void no_duck_delay() noexcept
{
	utilities::globals::cmd->buttons.add_flag(
		csgo::valve::classes::user_cmd::in_bullrush);
}
} // namespace csgo::hacks::misc::movement