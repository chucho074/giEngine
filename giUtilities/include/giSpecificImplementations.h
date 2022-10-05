/**
 * @file    giSpecificImplementations.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    27/09/2022
 * @brief   Management of specific things for platforms.
 */
 
/**
 * @include
 */
#pragma once

#include "giPrerequisitesUtilities.h"
#include "giBaseImplementations.h"

#if GI_PLATFORM == GI_PLATFORM_WIN32
#include "giWindowsImplementations.h"
#elif GI_PLATFORM == GI_PLATFORM_LINUX
#include "giLinuxImplementations.h"
#endif

namespace giEngineSDK {
#if GI_PLATFORM == GI_PLATFORM_WIN32
  using FileDialogs = WindowsFileDialogs;
#elif GI_PLATFORM == GI_PLATFORM_LINUX
  using FileDialogs = LinuxFileDialogs;
#else
  using FileDialogs = BaseFileDialogs;
#endif
}