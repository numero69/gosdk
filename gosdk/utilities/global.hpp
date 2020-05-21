#pragma once

// D3D9
#include <d3d9.h>
#include <dwmapi.h>

/* Watch out, CMake users!
   Anyway, if you're using CMake you might aswell
   just consider writing your prerequisite includes
   within one pcx file and not have to bother about
   these ever again. Pragma commenting IIRC is VS19
   solutioning system specific. */
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "dwmapi.lib" )

// HOOKS
#include "hooking/hook.hpp"

// CONSOLE
#include "console/console.hpp"

// GLOBAL
#include "global/globals.hpp"

// RENDER
#include "rendering/render.hpp"

// SHARED
#include "easing/global.hpp"
#include "math/global.hpp"
#include "color/color.hpp"
#include "memory/global.hpp"

