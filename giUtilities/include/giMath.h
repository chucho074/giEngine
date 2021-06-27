/**
 * @file    giMath.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    26/03/2021
 * @brief   Management of the Math.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once

#include "giPrerequisitesUtilities.h"
#include "giPlatformMath.h"

#if GI_PLATFORM == GI_PLATFORM_WIN32
#include "giWindowsMath.h"
#elif GI_PLATFORM == GI_PLATFORM_LINUX
#include "giLinuxMath.h"
#endif

namespace giEngineSDK {
#if GI_PLATFORM == GI_PLATFORM_WIN32
  using Math = windowsMath;
#elif GI_PLATFORM == GI_PLATFORM_LINUX
  using Math = linuxMath;
#else
  using Math = platformMath;
#endif
}