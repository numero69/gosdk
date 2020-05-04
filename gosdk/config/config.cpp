#include "config.hpp"
#include <Windows.h>
#include <sstream>

namespace config
{
bool settings::save(const std::string &config_file_name)
{
	nlohmann::json config;
	for (const auto &[setting, value] : m_settings) {
		if (std::holds_alternative<int>(value))
			config[setting] = { { STR("type"), value.index() },
					    { STR("itself"),
					      this->get<int>(setting) } };
		else if (std::holds_alternative<bool>(value))
			config[setting] = { { STR("type"), value.index() },
					    { STR("itself"),
					      this->get<bool>(setting) } };
		else if (std::holds_alternative<float>(value))
			config[setting] = { { STR("type"), value.index() },
					    { STR("itself"),
					      this->get<float>(setting) } };
		else if (std::holds_alternative<std::string>(value))
			config[setting] = { { STR("type"), value.index() },
					    { STR("itself"),
					      this->get<std::string>(
						      setting) } };
		else if (std::holds_alternative<utilities::color>(value))
			config[setting] = {
				{ STR("type"), value.index() },
				{ STR("itself_r"),
				  this->get<utilities::color>(setting).red },
				{ STR("itself_g"),
				  this->get<utilities::color>(setting).green },
				{ STR("itself_b"),
				  this->get<utilities::color>(setting).blue }

			};
	}
	std::ofstream output_config(config_file_name);
#ifdef _DEBUG
	output_config << std::setw(2) << config << std::endl;
#else
	// Reduce configs file size in release mode.
	output_config << config << std::endl;
#endif
	output_config.close();
	return true;
}

bool settings::load(const std::string &config_file_name)
{
	if (!std::filesystem::exists(std::filesystem::current_path() /
				     config_file_name))
		return false;

	std::ifstream input_config(config_file_name);
	nlohmann::json config = nlohmann::json::parse(input_config);
	for (const auto &[setting, value] : config.items()) {
		switch (value[STR("type")].get<int>()) {
		case 0:
			m_settings[setting] = value[STR("itself")].get<int>();
			break;
		case 1:
			m_settings[setting] = value[STR("itself")].get<bool>();
			break;
		case 2:
			m_settings[setting] = value[STR("itself")].get<float>();
			break;
		case 3:
			m_settings[setting] =
				value[STR("itself")].get<std::string>();
			break;
		case 4:
			this->get<utilities::color>(setting).red =
				value[STR("itself_r")].get<float>();
			this->get<utilities::color>(setting).green =
				value[STR("itself_g")].get<float>();
			this->get<utilities::color>(setting).blue =
				value[STR("itself_b")].get<float>();
			break;
		}
	}
	input_config.close();
	return true;
}

bool settings::load_clipboard(const std::string &data)
{
	nlohmann::json config = nlohmann::json::parse(data);
	for (const auto &[setting, value] : config.items()) {
		switch (value[STR("type")].get<int>()) {
		case 0:
			m_settings[setting] = value[STR("itself")].get<int>();
			break;
		case 1:
			m_settings[setting] = value[STR("itself")].get<bool>();
			break;
		case 2:
			m_settings[setting] = value[STR("itself")].get<float>();
			break;
		case 3:
			m_settings[setting] =
				value[STR("itself")].get<std::string>();
			break;
		case 4:
			this->get<utilities::color>(setting).red =
				value[STR("itself_r")].get<float>();
			this->get<utilities::color>(setting).green =
				value[STR("itself_g")].get<float>();
			this->get<utilities::color>(setting).blue =
				value[STR("itself_b")].get<float>();
			break;
		}
	}
	return true;
}
} // namespace config