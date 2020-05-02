#pragma once

#include <Windows.h>
#include <thread>
#include <chrono>

namespace utilities::globals
{
inline HMODULE this_module{};
inline bool should_unload{ false };
} // namespace utilities::globals