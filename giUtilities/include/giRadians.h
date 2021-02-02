#pragma once
#include <cmath>

class giRadians {
public:
  giRadians() = default;
  giRadians(float inVal) {
    m_Angle = inVal;
  }
  ~giRadians() = default;

  float getRadians() { return m_Angle; }
  float getDegrees() { return m_Angle; }

private:
  float m_Angle = 0;
};