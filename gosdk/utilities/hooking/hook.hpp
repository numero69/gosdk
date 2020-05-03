#pragma once

#include <Windows.h>
#include <memory>
#include <stdexcept>
#include <assert.h>
#include <stdio.h>
#include "../../dependencies/global.hpp"
#include "../../utilities/global.hpp"
#include "../../csgo/valve/classes/user_cmd.hpp"

namespace utilities::hooking
{
class protect_guard {
    public:
	protect_guard(void *base, size_t len, std::uint32_t flags)
	{
		_base = base;
		_length = len;
		if (!VirtualProtect(base, len, flags, (PDWORD)&_old))
			throw std::runtime_error(
				STR("[gosdk] - failed to protect region."));
	}
	~protect_guard()
	{
		VirtualProtect(_base, _length, _old, (PDWORD)&_old);
	}

    private:
	void *_base;
	size_t _length;
	std::uint32_t _old;
};

class vmt {
    public:
	vmt();

	bool init(void *base);

	bool hook_func(const std::uint16_t index, void *function);

	bool unhook_func(const std::uint16_t index);

	bool unhook();

	template <typename T = void *>
	T get_original_func(const std::uint16_t index)
	{
		return reinterpret_cast<T>(orig_vmt[index]);
	}

    private:
	std::uint32_t get_vt_length(std::uintptr_t *table);

	std::uintptr_t **vmt_base = nullptr;
	std::uint16_t table_length = 0;
	std::uintptr_t *orig_vmt = nullptr;
	std::unique_ptr<uintptr_t[]> replace_vmt = nullptr;
	DWORD old_protection{};
};

enum funcs_indexes {
	get_int_idx = 13,
	create_move_idx = 24,
	paint_traverse_idx = 41,
	lock_cursor_idx = 67
};

inline std::unique_ptr<utilities::hooking::vmt> sv_cheats_hook;
inline std::unique_ptr<utilities::hooking::vmt> cl_grenadepreview_hook;
inline std::unique_ptr<utilities::hooking::vmt> client_mode_hook;
inline std::unique_ptr<utilities::hooking::vmt> surface_hook;
inline std::unique_ptr<utilities::hooking::vmt> panel_hook;

static bool __stdcall sv_cheats() noexcept;
static bool __stdcall cl_grenadepreview() noexcept;

static void __fastcall lock_cursor() noexcept;
using lock_cursor_fn = void(__thiscall *)(void *);

static void __stdcall paint_traverse(unsigned int panel, bool force_repaint,
				     bool allow_force) noexcept;
using paint_traverse_fn = void(__thiscall *)(void *, unsigned int, bool, bool);

static bool __fastcall create_move(void *ecx, void *edx,
				   int input_sample_frametime,
				   csgo::valve::classes::user_cmd *cmd) noexcept;
using create_move_fn = bool(__stdcall *)(float, void *);

void run_hooks() noexcept;
void release_hooks() noexcept;
} // namespace utilities::hooking