#pragma once

#include "../utilities/netvar/global.hpp"

namespace csgo::valve::classes
{
class c_player {
    public:
	netvar(int, health, "DT_BasePlayer->m_iHealth");
};
} // namespace csgo::valve::classes
