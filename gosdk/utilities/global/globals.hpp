#pragma once

#include <Windows.h>
#include <chrono>
#include <thread>

#include "../../csgo/valve/classes/players.hpp"
#include "../../csgo/valve/classes/user_cmd.hpp"

namespace Utils {
  class Context {
  public:
    CS::Classes::CUserCmd * g_pCmd{ };
    CS::Classes::CCSPlayer * g_pLocal{ };
    HMODULE g_pModule{ };
    bool bShouldUnload{ false };
  };
  
  inline Context g_Context{ };
} // namespace Utils