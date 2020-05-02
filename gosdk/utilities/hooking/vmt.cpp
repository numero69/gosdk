#include "hook.hpp"

namespace utilities::hooking
{
vmt::vmt()
{
}

bool vmt::init(void *base)
{
	if (!base)
		return false;

	vmt_base = static_cast<std::uintptr_t **>(base);

	if (!vmt_base)
		return false;

	orig_vmt = *vmt_base;

	if (!orig_vmt)
		return false;

	VirtualProtect(vmt_base, sizeof(std::uintptr_t), PAGE_READWRITE,
		       &old_protection);

	table_length = get_vt_length(orig_vmt);

	if (!table_length)
		return false;

	replace_vmt = std::make_unique<std::uintptr_t[]>(table_length + 1);

	if (!replace_vmt)
		return false;

	std::memset(replace_vmt.get(), 0,
		    table_length * sizeof(std::uintptr_t) +
			    sizeof(std::uintptr_t));
	std::memcpy(&replace_vmt[1], orig_vmt,
		    table_length * sizeof(std::uintptr_t));
	std::memcpy(replace_vmt.get(), &orig_vmt[-1], sizeof(std::uintptr_t));

	*vmt_base = &replace_vmt[1];

	return true;
}

bool vmt::hook_func(const std::uint16_t index, void *function)
{
	if (!replace_vmt || index < 0 || index > table_length)
		return false;

	replace_vmt[index + 1] = reinterpret_cast<std::uintptr_t>(function);

	return true;
}

bool vmt::unhook_func(const std::uint16_t index)
{
	if (!orig_vmt || !replace_vmt || index < 0 || index > table_length)
		return false;

	replace_vmt[index + 1] = orig_vmt[index];

	return true;
}

bool vmt::unhook()
{
	if (!orig_vmt)
		return false;

	VirtualProtect(vmt_base, sizeof(std::uintptr_t), PAGE_READWRITE,
		       &old_protection);
	*vmt_base = orig_vmt;

	orig_vmt = nullptr;

	return true;
}

std::uint32_t vmt::get_vt_length(std::uintptr_t *table)
{
	std::uintptr_t length = std::uintptr_t{};

	// walk through every function until it is no longer valid
	for (length = 0; table[length]; length++)
		if (IS_INTRESOURCE(table[length]))
			break;

	return length;
}
}; // namespace utilities::hooking
