#pragma once

#include "../../utilities/global.hpp"
#include "../../dependencies/global.hpp"
#include "interfaces/global.hpp"

namespace csgo::valve::interfaces
{
// I'm sorry
class i_client_mode;

inline i_console *c_console{};
inline i_surface *c_surface{};
inline i_input_system *c_input_system{};
inline i_panel *c_panel{};
inline i_base_client_dll *c_client{};
inline i_client_mode *c_client_mode{};
inline i_entity_list *c_entity_list{};
inline i_engine_client *c_engine_client{};
inline i_global_vars *c_global_vars{};

void run_interfaces() noexcept;
void release_interfaces() noexcept;
} // namespace csgo::valve::interfaces