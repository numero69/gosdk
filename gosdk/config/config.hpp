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

// clang-format off
#define CONFIG_GET(type, name) \
([]() { \
return Config::SSettings->get<type>(STR(name)); \
})()
#define CONFIG_SET(type, name, value) \
Config::SSettings->get<type>(STR(name)) = value;
// clang-format on

namespace Config {

// clang-format off
#define add_setting(setting, default_value) \
mSettings[STR(setting)] = default_value;
  // clang-format on

  struct SSettings {
    using Setting_t = std::variant<int, bool, float, std::string, Utils::Color>;
    std::unordered_map<std::string, Setting_t> mSettings;

  public:
    SSettings( ) { /* Add your settings there */
      add_setting( "test_boolean", false );
    }

    template <typename Type> Type & get( const std::string & setting ) { return std::get<Type>( mSettings[ setting ] ); }

    bool bSave( const std::string & config_file_name );
    bool bLoad( const std::string & config_file_name );
    bool bLoadClip( const std::string & data );
  };

  inline std::unique_ptr<Config::SSettings> g_pConfig{ nullptr };
} // namespace Config