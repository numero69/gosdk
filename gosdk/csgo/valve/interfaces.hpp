#pragma once

#include "../../utilities/global.hpp"
#include "../../dependencies/global.hpp"
#include "interfaces/global.hpp"

namespace csgo::valve::interfaces
{
// I'm sorry
class i_client_mode;

inline i_console *p_console{};
inline i_surface *p_surface{};
inline i_input_system *p_input_system{};
inline i_panel *p_panel{};
inline i_base_client_dll *p_client{};
inline i_client_mode *p_client_mode{};
inline i_entity_list *p_entity_list{};
inline i_engine_client *p_engine_client{};
inline i_global_vars *p_global_vars{};
inline i_debug_overlay *p_debug_overlay{};

void run_interfaces() noexcept;
void release_interfaces() noexcept;
} // namespace csgo::valve::interfaces