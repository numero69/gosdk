#pragma once

#include "../../../utilities/math/vector3d.hpp"
#include "../../../utilities/easing/bitflag/bitflag.hpp"

namespace csgo::valve::classes
{
struct user_cmd {
	enum { IN_ATTACK = 1 << 0,
	       IN_JUMP = 1 << 1,
	       IN_DUCK = 1 << 2,
	       IN_FORWARD = 1 << 3,
	       IN_BACK = 1 << 4,
	       IN_USE = 1 << 5,
	       IN_MOVELEFT = 1 << 9,
	       IN_MOVERIGHT = 1 << 10,
	       IN_ATTACK2 = 1 << 11,
	       IN_SCORE = 1 << 16,
	       IN_BULLRUSH = 1 << 22 };
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