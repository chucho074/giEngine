#include "giPlatformMath.h"

namespace giEngineSDK {
  const float PlatformMath::PI = static_cast<float>(3.14159265383f);

  const float PlatformMath::DEG2RAD = static_cast<float>(PI / 180.0f);

  const float PlatformMath::RAD2DEG = static_cast<float>(180.0f / PI);

  const float PlatformMath::SMALL_NUMBER = static_cast<float>(1.e-6f);

  const float PlatformMath::KINDA_SMALL_NUMBER = static_cast<float>(1.e-4f);

  const float PlatformMath::BIG_NUMBER = static_cast<float>(3.4e+38f);

}