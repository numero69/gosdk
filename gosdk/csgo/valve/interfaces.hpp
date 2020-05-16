#pragma once

#include "../../dependencies/global.hpp"
#include "../../utilities/global.hpp"
#include "interfaces/global.hpp"

namespace CS::Interfaces {
  // I'm sorry
  class IClientMode;

  inline IConsole * g_pConsole{};
  inline ISurface * g_pSurface{};
  inline IInputSystem * g_pInputSystem{};
  inline IPanel * g_pPanel{};
  inline IBaseClientDLL * g_pClient{};
  inline IClientMode * g_pClientMode{};
  inline IEntityList * g_pEntityList{};
  inline IEngineClient * g_pEngineClient{};
  inline IGlobalVars * g_pGlobalVars{};
  inline IDebugOverlay * g_pDebugOverlay{};
  
  /* Handlers */
  void RunInterfaces( ) noexcept;
  void ReleaseInterfaces( ) noexcept;
} // namespace CS::Interfaces