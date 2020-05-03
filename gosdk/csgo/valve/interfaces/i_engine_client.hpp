#pragma once

#include "../../../utilities/global.hpp"

namespace csgo::valve::interfaces
{
struct player_info {
	std::uint64_t version;
	union {
		std::uint64_t xuid;
		struct {
			std::uint32_t xuid_low;
			std::uint32_t xuid_high;
		};
	};
	char name[128];
	int user_id;
	char guid[33];
	std::uint32_t friends_id;
	char friends_name[128];
	bool fake_player;
	bool hltv;
	int custom_files[4];
	unsigned char files_downloaded;
	int entity_index;
};

class net_channel;

class i_engine_client {
    public:
	constexpr auto get_player_info(int entity_index,
				       const player_info &p_info) noexcept
	{
		return utilities::memory::call_virtual_method<
			bool, int, const player_info &>(this, 8, entity_index,
							p_info);
	}

	constexpr auto get_player_for_uid(int user_id) noexcept
	{
		return utilities::memory::call_virtual_method<int, int>(
			this, 9, user_id);
	}

	constexpr auto get_local_player() noexcept
	{
		return utilities::memory::call_virtual_method<int>(this, 12);
	}

	constexpr auto get_view_angles(utilities::math::vec3_t &angles) noexcept
	{
		utilities::memory::call_virtual_method<
			void, utilities::math::vec3_t &>(this, 18, angles);
	}

	constexpr auto
	set_view_angles(const utilities::math::vec3_t &angles) noexcept
	{
		utilities::memory::call_virtual_method<
			void, const utilities::math::vec3_t &>(this, 19,
							       angles);
	}

	constexpr auto get_max_clients() noexcept
	{
		return utilities::memory::call_virtual_method<int>(this, 20);
	}

	constexpr auto is_in_game() noexcept
	{
		return utilities::memory::call_virtual_method<bool>(this, 26);
	}

	constexpr auto is_connected() noexcept
	{
		return utilities::memory::call_virtual_method<bool>(this, 27);
	}

	using matrix = float[4][4];

	constexpr auto world_to_screen_4x4() noexcept
	{
		return utilities::memory::call_virtual_method<const matrix &>(
			this, 37);
	}

	constexpr auto get_level_name() noexcept
	{
		return utilities::memory::call_virtual_method<const char *>(
			this, 53);
	}

	constexpr auto get_net_channel() noexcept
	{
		return utilities::memory::call_virtual_method<net_channel *>(
			this, 78);
	}

	constexpr auto client_cmd_unrestricted(const char *cmd) noexcept
	{
		utilities::memory::call_virtual_method<void, const char *, bool>(
			this, 114, cmd, false);
	}
};
} // namespace csgo::valve::interfaces