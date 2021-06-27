#include "giPlatformMath.h"

namespace giEngineSDK {
  const float platformMath::PI = static_cast<float>(4.0f * std::atan(1.0f));

  const float platformMath::DEG2RAD = static_cast<float>(PI / 180.0f);

  const float platformMath::RAD2DEG = static_cast<float>(180.0f / PI);

  const float platformMath::SMALL_NUMBER = static_cast<float>(1.e-6f);

  const float platformMath::KINDA_SMALL_NUMBER = static_cast<float>(1.e-4f);

  const float platformMath::BIG_NUMBER = static_cast<float>(3.4e+38f);

  const float platformMath::EULER_NUMBER = 2.718f;

  const float platformMath::DELTA = 1.e-5f;

}