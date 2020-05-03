#pragma once

#include "../../../utilities/math/vector3d.hpp"
#include "../../../utilities/easing/bitflag/bitflag.hpp"

namespace csgo::valve::classes
{
struct user_cmd {
	enum { in_attack = 1 << 0,
	       in_jump = 1 << 1,
	       in_duck = 1 << 2,
	       in_forward = 1 << 3,
	       in_back = 1 << 4,
	       in_use = 1 << 5,
	       in_moveleft = 1 << 9,
	       in_moveright = 1 << 10,
	       in_attack2 = 1 << 11,
	       in_score = 1 << 16,
	       in_bullrush = 1 << 22 };
	int pad;
	int command_number;
	int tick_count;
	utilities::math::vec3_t viewangles;
	utilities::math::vec3_t aimdirection;
	float forward_move;
	float side_move;
	float up_move;
	utilities::easing::bitflag buttons;
	char impulse;
	int weapon_select;
	int weapon_subtype;
	int random_seed;
	short mouse_dx;
	short mouse_dy;
	bool has_been_predicted;
};
} // namespace csgo::valve::classes