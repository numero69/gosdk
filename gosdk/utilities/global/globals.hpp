#pragma once

#include <Windows.h>
#include <chrono>
#include <thread>

#include "../../csgo/valve/classes/players.hpp"
#include "../../csgo/valve/classes/user_cmd.hpp"

namespace Utils::Context {
  inline CS::Classes::CUserCmd * g_pCmd{};
  inline CS::Classes::CCSPlayer * g_pLocal{};
  inline HMODULE g_pModule{};
  inline bool bShouldUnload{ false };
} // namespace Utils::Context