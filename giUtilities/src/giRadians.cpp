#include "giRadians.h"
#include "giDegrees.h"
#include "giPlatformMath.h"

namespace giEngineSDK {
  float giRadians::degVal() const
  {
    return m_RadianAngle * PlatformMath::RAD2DEG;
  }
  
  const giRadians&
  giRadians::operator+() const
  {
    return *this;
  }
  
  giRadians 
  giRadians::operator+(const giRadians& inRad) const
  {
    return giRadians(m_RadianAngle + inRad.m_RadianAngle);
  }
  
  giRadians 
  giRadians::operator+(const giDegrees& inDeg) const
  {
    return giRadians(m_RadianAngle + inDeg.radVal());
  }
  
  giRadians& 
  giRadians::operator+=(const giRadians& inRad)
  {
    m_RadianAngle += inRad.m_RadianAngle;
    return *this;
  }
  
  giRadians& 
  giRadians::operator+=(const giDegrees& inDeg)
  {
    m_RadianAngle += inDeg.radVal();
    return *this;
  }
  
  giRadians 
  giRadians::operator-() const
  {
    return giRadians(-m_RadianAngle);
  }
  
  giRadians 
  giRadians::operator-(const giRadians& inRad) const
  {
    return giRadians(m_RadianAngle - inRad.m_RadianAngle);
  }
  
  giRadians 
  giRadians::operator-(const giDegrees& inDeg) const
  {
    return giRadians(m_RadianAngle - inDeg.radVal());
  }
  
  giRadians& 
  giRadians::operator-=(const giRadians& inRad)
  {
    m_RadianAngle -= inRad.m_RadianAngle;
    return *this;
  }
  
  giRadians& 
  giRadians::operator-=(const giDegrees& inDeg)
  {
    m_RadianAngle -= inDeg.radVal();
    return *this;
  }
  
  giRadians 
  giRadians::operator*(float inFloat) const
  {
    return giRadians(m_RadianAngle * inFloat);
  }
  
  giRadians 
  giRadians::operator*(const giRadians& inRad) const
  {
    return giRadians(m_RadianAngle * inRad.m_RadianAngle);
  }
  
  giRadians& 
  giRadians::operator*=(float inFloat)
  {
    m_RadianAngle *= inFloat;
    return *this;
  }
  
  giRadians 
  giRadians::operator/(float inFloat) const
  {
    return giRadians(m_RadianAngle / inFloat);
  }
  
  giRadians& 
  giRadians::operator/=(float inFloat)
  {
    m_RadianAngle /= inFloat;
    return *this;
  }
  
  bool 
  giRadians::operator<(const giRadians& inRad) const
  {
    return m_RadianAngle < inRad.m_RadianAngle;
  }
  
  bool 
  giRadians::operator<=(const giRadians& inRad) const
  {
    return m_RadianAngle <= inRad.m_RadianAngle;
  }
  
  bool 
  giRadians::operator==(const giRadians& inRad) const
  {
    return m_RadianAngle == inRad.m_RadianAngle;
  }
  
  bool 
  giRadians::operator!=(const giRadians& inRad) const
  {
    return m_RadianAngle != inRad.m_RadianAngle;
  }
  
  bool 
  giRadians::operator>=(const giRadians& inRad) const
  {
    return m_RadianAngle >= inRad.m_RadianAngle;
  }
  
  bool 
  giRadians::operator>(const giRadians& inRad) const
  {
    return m_RadianAngle > inRad.m_RadianAngle;
  }
  
  bool 
  giRadians::operator<(const float& inVal) const
  {
    return m_RadianAngle < inVal;
  }
  
  bool 
  giRadians::operator<=(const float& inVal) const
  {
    return m_RadianAngle <= inVal;
  }
  
  bool 
  giRadians::operator==(const float& inVal) const
  {
    return m_RadianAngle == inVal;
  }
  
  bool 
  giRadians::operator!=(const float& inVal) const
  {
    return m_RadianAngle != inVal;
  }
  
  bool 
  giRadians::operator>=(const float& inVal) const
  {
    return m_RadianAngle >= inVal;
  }
  
  bool 
  giRadians::operator>(const float& inVal) const
  {
    return m_RadianAngle > inVal;
  }
}