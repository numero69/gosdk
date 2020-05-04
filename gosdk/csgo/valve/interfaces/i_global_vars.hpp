#pragma once

namespace csgo::valve::interfaces
{
class i_global_vars {
    public:
	float real_time;
	int frame_count;
	float absolute_frame_time;
	float absolute_frame_time_stddev;
	float current_time;
	float frame_time;
	int max_clients;
	int tick_count;
	float interval_per_tick;
	float interpolation_amount;
	std::int32_t sim_ticks_this_frame;
	std::int32_t network_protocol;
	void *save_data;
	bool client;
	bool remote_client;
};
} // namespace csgo::valve::interfaces