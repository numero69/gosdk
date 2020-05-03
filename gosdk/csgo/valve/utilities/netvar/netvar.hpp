#pragma once

#include <map>
#include <unordered_map>
#include <string>
#include <memory>

// credits: unknowncheats
namespace csgo::valve::netvar
{
extern std::unordered_map<std::string, std::uintptr_t> offsets;

void init();
}; // namespace csgo::valve::netvar

// clang-format off
#define netvar_additive(t, func, name, off)\
	t &func()\
	{\
		static auto offset = csgo::valve::netvar::offsets[(STR(name))];\
		return *reinterpret_cast<t*>(std::uintptr_t(this) + offset + off);\
	}

#define netvar(t, func, name)\
	t &func()\
	{\
		static auto offset = csgo::valve::netvar::offsets[(STR(name))];\
		return *reinterpret_cast<t*>(std::uintptr_t(this) + offset);\
	}

#define offset(t, func, offset)\
	t &func()\
	{\
		return *reinterpret_cast<t*>(std::uintptr_t(this) + offset);\
	}

#define poffset(t, func, offset)\
	t func()\
	{\
		return reinterpret_cast<t>(std::uintptr_t(this) + offset);\
	}

#define foffset(type, ptr, offset) (*(type *)((std::uintptr_t)(ptr) + (offset)))
// clang-format on