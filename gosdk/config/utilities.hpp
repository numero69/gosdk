#pragma once
#include "config.hpp"

namespace Config {
  inline void RunConfig( ) { g_pConfig = std::make_unique<Config::SSettings>( ); }

  inline void ReleaseConfig( ) { g_pConfig.reset( ); }
} // namespace Config