#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <memory>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <variant>

#include "../dependencies/global.hpp"
#include "../utilities/global.hpp"

namespace config
{
#define add_setting(setting, default_value) m_settings[setting] = default_value;
struct settings {
	using setting_t =
		std::variant<int, bool, float, std::string, utilities::color>;
	std::unordered_map<std::string, setting_t> m_settings;

    public:
	settings()
	{
		add_setting(STR("test_boolean"), false);
	}

	template <typename type> type &get(const std::string &setting)
	{
		return std::get<type>(m_settings[setting]);
	}

	bool save(const std::string &config_file_name);

	bool load(const std::string &config_file_name);
	bool load_clipboard(const std::string &data);
};

inline std::unique_ptr<config::settings> configs{ nullptr };
} // namespace config