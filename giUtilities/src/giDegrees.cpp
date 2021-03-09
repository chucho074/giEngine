#include "giDegrees.h"
#include "giRadians.h"
#include "giMath.h"

namespace giEngineSDK {
  
  float 
  giDegrees::radVal() const {
    return m_degreesAngle * Math::DEG2RAD;
  }
  
  const 
  giDegrees& giDegrees::operator+() const {
    return *this;
  }
  
  giDegrees 
  giDegrees::operator+(const giDegrees& inDeg) const {
    return giDegrees(m_degreesAngle + inDeg.m_degreesAngle);
  }
  
  giDegrees 
  giDegrees::operator+(const giRadians& inRad) const {
    return giDegrees(m_degreesAngle + inRad.degVal());
  }
  
  giDegrees& 
  giDegrees::operator+=(const giDegrees& inDeg) {
    m_degreesAngle += inDeg.m_degreesAngle;
    return *this;
  }
  
  giDegrees& 
  giDegrees::operator+=(const giRadians& inRad) {
    m_degreesAngle += inRad.degVal();
    return *this;
  }
  
  giDegrees 
  giDegrees::operator-() const {
    return giDegrees(-m_degreesAngle);
  }
  
  giDegrees 
  giDegrees::operator-(const giDegrees& inDeg) const {
    return giDegrees(m_degreesAngle - inDeg.m_degreesAngle);
  }
  
  giDegrees 
  giDegrees::operator-(const giRadians& inRad) const {
    return giDegrees(m_degreesAngle - inRad.degVal());
  }
  
  giDegrees& 
  giDegrees::operator-=(const giDegrees& inDeg) {
    m_degreesAngle -= inDeg.m_degreesAngle;
    return *this;
  }
  
  giDegrees& 
  giDegrees::operator-=(giRadians& inRad) {
    m_degreesAngle -= inRad.degVal();
    return *this;
  }
  
  giDegrees 
  giDegrees::operator*(float inFloat) const {
    return giDegrees(m_degreesAngle * inFloat);
  }
  
  giDegrees 
  giDegrees::operator*(const giDegrees& inFloat) const {
    return giDegrees(m_degreesAngle * inFloat.m_degreesAngle);
  }
  
  giDegrees& 
  giDegrees::operator*=(float inFloat) {
    m_degreesAngle *= inFloat;
    return *this;
  }
  
  giDegrees 
  giDegrees::operator/(float inFloat) const {
    return giDegrees(m_degreesAngle / inFloat);
  }
  
  giDegrees& 
  giDegrees::operator/=(float inFloat) {
    m_degreesAngle /= inFloat;
    return *this;
  }
  
  bool 
  giDegrees::operator<(const giDegrees& inDeg) const {
    return m_degreesAngle < inDeg.m_degreesAngle;
  }
  
  bool 
  giDegrees::operator<=(const giDegrees& inDeg) const {
    return m_degreesAngle <= inDeg.m_degreesAngle;
  }
  
  bool 
  giDegrees::operator==(const giDegrees& inDeg) const {
    return m_degreesAngle == inDeg.m_degreesAngle;
  }
  
  bool 
  giDegrees::operator!=(const giDegrees& inDeg) const {
    return m_degreesAngle != inDeg.m_degreesAngle;
  }
  
  bool 
  giDegrees::operator>=(const giDegrees& inDeg) const {
    return m_degreesAngle >= inDeg.m_degreesAngle;
  }
  
  bool 
  giDegrees::operator>(const giDegrees& inDeg) const {
    return m_degreesAngle > inDeg.m_degreesAngle;
  }
  
  bool 
  giDegrees::operator<(const float& inVal) const {
    return m_degreesAngle < inVal;
  }
  
  bool 
  giDegrees::operator<=(const float& inVal) const {
    return m_degreesAngle <= inVal;
  }
  
  bool 
  giDegrees::operator==(const float& inVal) const {
    return m_degreesAngle == inVal;
  }
  
  bool 
  giDegrees::operator!=(const float& inVal) const {
    return m_degreesAngle != inVal;
  }
  
  bool 
  giDegrees::operator>=(const float& inVal) const {
    return m_degreesAngle >= inVal;
  }
  
  bool 
  giDegrees::operator>(const float& inVal) const {
    return m_degreesAngle > inVal;
  }
}