#pragma once

#include <Windows.h>
#include <thread>
#include <chrono>

#include "../../csgo/valve/classes/user_cmd.hpp"
#include "../../csgo/valve/classes/players.hpp"
namespace utilities::globals
{
inline csgo::valve::classes::user_cmd *cmd{};
inline csgo::valve::classes::c_player *local{};
inline HMODULE this_module{};
inline bool should_unload{ false };
} // namespace utilities::globals