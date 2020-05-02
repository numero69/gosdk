#pragma once

#include "../utilities/c_utl.hpp"
#include "../../../utilities/global.hpp"

namespace csgo::valve::classes
{
class convar;
using fn_change_callback_t = void (*)(convar *var, const char *pOldValue,
				      float flOldValue);
class convar {
    public:
	constexpr void set_value(const char *value)
	{
		utilities::memory::call_virtual_method<void, const char *>(
			this, 14, value);
	}
	constexpr void set_value(float value)
	{
		utilities::memory::call_virtual_method<void, float>(this, 15,
								    value);
	}
	constexpr void set_value(int value)
	{
		utilities::memory::call_virtual_method<void, int>(this, 16,
								  value);
	}
	constexpr float get_float() noexcept
	{
		return utilities::memory::call_virtual_method<float>(this, 12);
	}

	constexpr int get_int() noexcept
	{
		return utilities::memory::call_virtual_method<int>(this, 13);
	}

    private:
	char pad_0x0000[0x4];

    public:
	convar *next;
	__int32 is_registered;
	char *name;
	char *help_string;
	__int32 flags;

    private:
	char pad_0x0018[0x4];

    public:
	convar *parent;
	char *default_value;
	char *string;
	__int32 string_length;
	float float_value;
	__int32 numerical_value;
	__int32 has_min;
	float min;
	__int32 has_max;
	float max;
	CUtlVector<fn_change_callback_t> callbacks;
};
} // namespace csgo::valve::classes