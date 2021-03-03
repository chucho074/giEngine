#include "giDegrees.h"
#include "giRadians.h"
#include "giPlatformMath.h"

namespace giEngineSDK {
  
  float 
  giDegrees::radVal() const
  {
    return m_DegreesAngle * PlatformMath::DEG2RAD;
  }
  
  const 
  giDegrees& giDegrees::operator+() const
  {
    return *this;
  }
  
  giDegrees 
  giDegrees::operator+(const giDegrees& inDeg) const
  {
    return giDegrees(m_DegreesAngle + inDeg.m_DegreesAngle);
  }
  
  giDegrees 
  giDegrees::operator+(const giRadians& inRad)
  {
    return giDegrees(m_DegreesAngle + inRad.degVal());
  }
  
  giDegrees& 
  giDegrees::operator+=(const giDegrees& inDeg)
  {
    m_DegreesAngle += inDeg.m_DegreesAngle;
    return *this;
  }
  
  giDegrees& 
  giDegrees::operator+=(const giRadians& inRad)
  {
    m_DegreesAngle += inRad.degVal();
    return *this;
  }
  
  giDegrees 
  giDegrees::operator-() const
  {
    return giDegrees(-m_DegreesAngle);
  }
  
  giDegrees 
  giDegrees::operator-(const giDegrees& inDeg) const
  {
    return giDegrees(m_DegreesAngle - inDeg.m_DegreesAngle);
  }
  
  giDegrees 
  giDegrees::operator-(const giRadians& inRad)
  {
    return giDegrees(m_DegreesAngle - inRad.degVal());
  }
  
  giDegrees& 
  giDegrees::operator-=(const giDegrees& inDeg)
  {
    m_DegreesAngle -= inDeg.m_DegreesAngle;
    return *this;
  }
  
  giDegrees& 
  giDegrees::operator-=(giRadians& inRad)
  {
    m_DegreesAngle -= inRad.degVal();
    return *this;
  }
  
  giDegrees 
  giDegrees::operator*(float inFloat) const
  {
    return giDegrees(m_DegreesAngle * inFloat);
  }
  
  giDegrees 
  giDegrees::operator*(const giDegrees& inFloat) const
  {
    return giDegrees(m_DegreesAngle * inFloat.m_DegreesAngle);
  }
  
  giDegrees& 
  giDegrees::operator*=(float inFloat)
  {
    m_DegreesAngle *= inFloat;
    return *this;
  }
  
  giDegrees 
  giDegrees::operator/(float inFloat) const
  {
    return giDegrees(m_DegreesAngle / inFloat);
  }
  
  giDegrees& 
  giDegrees::operator/=(float inFloat)
  {
    m_DegreesAngle /= inFloat;
    return *this;
  }
  
  bool 
  giDegrees::operator<(const giDegrees& inDeg) const
  {
    return m_DegreesAngle < inDeg.m_DegreesAngle;
  }
  
  bool 
  giDegrees::operator<=(const giDegrees& inDeg) const
  {
    return m_DegreesAngle <= inDeg.m_DegreesAngle;
  }
  
  bool 
  giDegrees::operator==(const giDegrees& inDeg) const
  {
    return m_DegreesAngle == inDeg.m_DegreesAngle;
  }
  
  bool 
  giDegrees::operator!=(const giDegrees& inDeg) const
  {
    return m_DegreesAngle != inDeg.m_DegreesAngle;
  }
  
  bool 
  giDegrees::operator>=(const giDegrees& inDeg) const
  {
    return m_DegreesAngle >= inDeg.m_DegreesAngle;
  }
  
  bool 
  giDegrees::operator>(const giDegrees& inDeg) const
  {
    return m_DegreesAngle > inDeg.m_DegreesAngle;
  }
  
  bool 
  giDegrees::operator<(const float& inVal) const
  {
    return m_DegreesAngle < inVal;
  }
  
  bool 
  giDegrees::operator<=(const float& inVal) const
  {
    return m_DegreesAngle <= inVal;
  }
  
  bool 
  giDegrees::operator==(const float& inVal) const
  {
    return m_DegreesAngle == inVal;
  }
  
  bool 
  giDegrees::operator!=(const float& inVal) const
  {
    return m_DegreesAngle != inVal;
  }
  
  bool 
  giDegrees::operator>=(const float& inVal) const
  {
    return m_DegreesAngle >= inVal;
  }
  
  bool 
  giDegrees::operator>(const float& inVal) const
  {
    return m_DegreesAngle > inVal;
  }
}