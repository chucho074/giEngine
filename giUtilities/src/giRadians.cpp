#include "giRadians.h"
#include "giDegrees.h"
#include "giMath.h"

namespace giEngineSDK {

  Radians::Radians(float inVal) {
    m_radianAngle = inVal;
  }

  Radians::Radians(const Degrees& inDeg) {
    m_radianAngle = inDeg.getRadians();
  }

  float
  Radians::getRadians() const {
    return m_radianAngle;
  }

  float
  Radians::getDegrees() const {
    return getRadians() * Math::RAD2DEG;
  }
  
  Radians 
  Radians::operator+(const Radians& inRad) const {
    return Radians(getRadians() + inRad.getRadians());
  }
  
  Radians& 
  Radians::operator+=(const Radians& inRad) {
    m_radianAngle += inRad.getRadians();
    return *this;
  }
  
  Radians 
  Radians::operator-() const {
    return Radians(-getRadians());
  }
  
  Radians 
  Radians::operator-(const Radians& inRad) const {
    return Radians(getRadians() - inRad.getRadians());
  }
  
  Radians& 
  Radians::operator-=(const Radians& inRad) {
    m_radianAngle -= inRad.getRadians();
    return *this;
  }
  
  Radians 
  Radians::operator*(float inFloat) const {
    return Radians(getRadians() * inFloat);
  }
  
  Radians 
  Radians::operator*(const Radians& inRad) const {
    return Radians(getRadians() * inRad.getRadians());
  }
  
  Radians& 
  Radians::operator*=(float inFloat) {
    m_radianAngle *= inFloat;
    return *this;
  }
  
  Radians 
  Radians::operator/(float inFloat) const {
    return Radians(getRadians() / inFloat);
  }
  
  Radians& 
  Radians::operator/=(float inFloat) {
    m_radianAngle /= inFloat;
    return *this;
  }
  
  bool 
  Radians::operator<(const Radians& inRad) const {
    return getRadians() < inRad.getRadians();
  }
  
  bool 
  Radians::operator<=(const Radians& inRad) const {
    return getRadians() <= inRad.getRadians();
  }
  
  bool 
  Radians::operator==(const Radians& inRad) const {
    return getRadians() == inRad.getRadians();
  }
  
  bool 
  Radians::operator!=(const Radians& inRad) const {
    return getRadians() != inRad.getRadians();
  }
  
  bool 
  Radians::operator>=(const Radians& inRad) const {
    return getRadians() >= inRad.getRadians();
  }
  
  bool 
  Radians::operator>(const Radians& inRad) const {
    return getRadians() > inRad.getRadians();
  }
  
}