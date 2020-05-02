#pragma once

#include <inttypes.h>

namespace utilities::easing::bitflag
{
struct bitflag {
	bitflag() = default;

	bitflag(uintptr_t flags) : m_flags(flags)
	{
	}

	~bitflag() = default;

	uintptr_t m_flags{};

	inline bool check_flag(uintptr_t flag)
	{
		return m_flags & flag;
	}

	inline void add_flag(uintptr_t flag)
	{
		m_flags |= flag;
	}

	inline void remove_flag(uintptr_t flag)
	{
		m_flags &= ~flag;
	}

	inline bool is_empty()
	{
		return !m_flags;
	}
};
} // namespace utilities::easing::bitflag