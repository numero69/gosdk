#pragma once

#include "../../../utilities/global.hpp"

namespace csgo::hacks::misc
{
inline void no_duck_delay()
{
	utilities::globals::cmd->buttons.add_flag(csgo::valve::classes::user_cmd::IN_BULLRUSH);
}
} // namespace csgo::hacks::misc