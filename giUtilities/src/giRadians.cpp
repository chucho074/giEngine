#include "giRadians.h"
#include "giDegrees.h"
#include "giMath.h"

namespace giEngineSDK {
  float 
  giRadians::getRadians() const {
    return m_radianAngle;
  }

  float
  giRadians::getDegrees() const {
    return m_radianAngle * Math::RAD2DEG;
  }
  
  const giRadians&
  giRadians::operator+() const {
    return *this;
  }
  
  giRadians 
  giRadians::operator+(const giRadians& inRad) const {
    return giRadians(m_radianAngle + inRad.m_radianAngle);
  }
  
  giRadians 
  giRadians::operator+(const giDegrees& inDeg) const {
    return giRadians(m_radianAngle + inDeg.radVal());
  }
  
  giRadians& 
  giRadians::operator+=(const giRadians& inRad) {
    m_radianAngle += inRad.m_radianAngle;
    return *this;
  }
  
  giRadians& 
  giRadians::operator+=(const giDegrees& inDeg) {
    m_radianAngle += inDeg.radVal();
    return *this;
  }
  
  giRadians 
  giRadians::operator-() const {
    return giRadians(-m_radianAngle);
  }
  
  giRadians 
  giRadians::operator-(const giRadians& inRad) const {
    return giRadians(m_radianAngle - inRad.m_radianAngle);
  }
  
  giRadians 
  giRadians::operator-(const giDegrees& inDeg) const {
    return giRadians(m_radianAngle - inDeg.radVal());
  }
  
  giRadians& 
  giRadians::operator-=(const giRadians& inRad) {
    m_radianAngle -= inRad.m_radianAngle;
    return *this;
  }
  
  giRadians& 
  giRadians::operator-=(const giDegrees& inDeg) {
    m_radianAngle -= inDeg.radVal();
    return *this;
  }
  
  giRadians 
  giRadians::operator*(float inFloat) const {
    return giRadians(m_radianAngle * inFloat);
  }
  
  giRadians 
  giRadians::operator*(const giRadians& inRad) const {
    return giRadians(m_radianAngle * inRad.m_radianAngle);
  }
  
  giRadians& 
  giRadians::operator*=(float inFloat) {
    m_radianAngle *= inFloat;
    return *this;
  }
  
  giRadians 
  giRadians::operator/(float inFloat) const {
    return giRadians(m_radianAngle / inFloat);
  }
  
  giRadians& 
  giRadians::operator/=(float inFloat) {
    m_radianAngle /= inFloat;
    return *this;
  }
  
  bool 
  giRadians::operator<(const giRadians& inRad) const {
    return m_radianAngle < inRad.m_radianAngle;
  }
  
  bool 
  giRadians::operator<=(const giRadians& inRad) const {
    return m_radianAngle <= inRad.m_radianAngle;
  }
  
  bool 
  giRadians::operator==(const giRadians& inRad) const {
    return m_radianAngle == inRad.m_radianAngle;
  }
  
  bool 
  giRadians::operator!=(const giRadians& inRad) const {
    return m_radianAngle != inRad.m_radianAngle;
  }
  
  bool 
  giRadians::operator>=(const giRadians& inRad) const {
    return m_radianAngle >= inRad.m_radianAngle;
  }
  
  bool 
  giRadians::operator>(const giRadians& inRad) const {
    return m_radianAngle > inRad.m_radianAngle;
  }
  
  bool 
  giRadians::operator<(const float& inVal) const {
    return m_radianAngle < inVal;
  }
  
  bool 
  giRadians::operator<=(const float& inVal) const {
    return m_radianAngle <= inVal;
  }
  
  bool 
  giRadians::operator==(const float& inVal) const {
    return m_radianAngle == inVal;
  }
  
  bool 
  giRadians::operator!=(const float& inVal) const {
    return m_radianAngle != inVal;
  }
  
  bool 
  giRadians::operator>=(const float& inVal) const {
    return m_radianAngle >= inVal;
  }
  
  bool 
  giRadians::operator>(const float& inVal) const {
    return m_radianAngle > inVal;
  }
}