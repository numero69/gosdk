#pragma once

#include <map>
#include <memory>
#include <string>
#include <unordered_map>

namespace CS::Utilities::Netvar {
  inline std::unordered_map<std::string, std::uintptr_t> Offsets;

  /* Handler */
  void Init( );
}; // namespace CS::Utilities::Netvar

/* Handlers */
// clang-format off
#define netvar_additive(t, func, name, off)\
	t &func()\
	{\
		static auto offset = CS::Utilities::Netvar::Offsets[(STR(name))];\
		return *reinterpret_cast<t*>(std::uintptr_t(this) + offset + off);\
	}

#define netvar(t, func, name)\
	t &func()\
	{\
		static auto offset = CS::Utilities::Netvar::Offsets[(STR(name))];\
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

#define foffset(type, ptr, offset) (*reinterpret_cast<type *>((std::uintptr_t)(ptr) + (offset)))
// clang-format on