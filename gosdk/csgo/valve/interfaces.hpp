#pragma once

#include "../../utilities/global.hpp"
#include "../../dependencies/global.hpp"
#include "interfaces/global.hpp"

namespace csgo::valve::interfaces
{
// I'm sorry
class i_client_mode;

extern i_console *c_console;
extern i_surface *c_surface;
extern i_input_system *c_input_system;
extern i_panel *c_panel;
extern i_base_client_dll *c_client;
extern i_client_mode *c_client_mode;
extern i_entity_list *c_entity_list;
extern i_engine_client *c_engine_client;

void run_interfaces() noexcept;
void release_interfaces() noexcept;
} // namespace csgo::valve::interfaces