#pragma once

// GLOBAL
#include "netvar.hpp"

// MACROS
#define offset(t, func, offset)                                                \
	t &func()                                                              \
	{                                                                      \
		return *reinterpret_cast<t *>(std::uintptr_t(this) + offset);  \
	}

#define get_netvar(func_name, type, ...)                                       \
	type &func_name                                                        \
	{                                                                      \
		return *reinterpret_cast<type *>(                              \
			reinterpret_cast<std::uintptr_t>(this) +               \
			csgo::valve::netvar::netvar_tree->get_offset(          \
				__VA_ARGS__));                                 \
	};

#define get_netvar_additive(func_name, type, off, ...)                         \
	type &func_name                                                        \
	{                                                                      \
		return *reinterpret_cast<type *>(                              \
			reinterpret_cast<std::uintptr_t>(this) +               \
			csgo::valve::netvar::netvar_tree->get_offset(          \
				__VA_ARGS__) +                                 \
			off);                                                  \
	};
