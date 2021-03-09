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
    using Math == WindowsMath;
  #elif GI_PLATFORM == GI_PLATFORM_LINUX
    using Math = LinuxMath;
  #else
  using Math = PlatformMath;
  #endif
}