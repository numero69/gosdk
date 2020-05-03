#pragma once

#include "../../utilities/global.hpp"
#include "../../dependencies/global.hpp"
#include "interfaces/global.hpp"

namespace csgo::valve::interfaces
{
extern i_console *c_console;
extern i_surface *c_surface;
extern i_input_system *c_input_system;
extern i_panel *c_panel;

void run_interfaces() noexcept;
void release_interfaces() noexcept;
} // namespace csgo::valve::interfaces