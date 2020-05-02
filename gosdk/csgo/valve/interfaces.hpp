#pragma once

#include "../../utilities/global.hpp"
#include "../../dependencies/global.hpp"
#include "interfaces/global.hpp"

namespace csgo::valve::interfaces
{
extern i_console *c_console;

void run_interfaces() noexcept;
void release_interfaces() noexcept;
} // namespace csgo::valve::interfaces