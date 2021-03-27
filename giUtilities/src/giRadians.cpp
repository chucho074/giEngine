#include "giRadians.h"
#include "giDegrees.h"
#include "giMath.h"

namespace giEngineSDK {

  giRadians::giRadians(float inVal) {
    m_radianAngle = inVal;
  }

  giRadians::giRadians(const giDegrees& inDeg) {
    m_radianAngle = inDeg.getRadians();
  }

  float
  giRadians::getRadians() const {
    return m_radianAngle;
  }

  float
  giRadians::getDegrees() const {
    return getRadians() * Math::RAD2DEG;
  }
  
  const giRadians&
  giRadians::operator+() const {
    return getRadians();
  }
  
  giRadians 
  giRadians::operator+(const giRadians& inRad) const {
    return giRadians(getRadians() + inRad.getRadians());
  }
  
  giRadians& 
  giRadians::operator+=(const giRadians& inRad) {
    m_radianAngle += inRad.getRadians();
    return *this;
  }
  
  giRadians 
  giRadians::operator-() const {
    return giRadians(-getRadians());
  }
  
  giRadians 
  giRadians::operator-(const giRadians& inRad) const {
    return giRadians(getRadians() - inRad.getRadians());
  }
  
  giRadians& 
  giRadians::operator-=(const giRadians& inRad) {
    m_radianAngle -= inRad.getRadians();
    return *this;
  }
  
  giRadians 
  giRadians::operator*(float inFloat) const {
    return giRadians(getRadians() * inFloat);
  }
  
  giRadians 
  giRadians::operator*(const giRadians& inRad) const {
    return giRadians(getRadians() * inRad.getRadians());
  }
  
  giRadians& 
  giRadians::operator*=(float inFloat) {
    m_radianAngle *= inFloat;
    return *this;
  }
  
  giRadians 
  giRadians::operator/(float inFloat) const {
    return giRadians(getRadians() / inFloat);
  }
  
  giRadians& 
  giRadians::operator/=(float inFloat) {
    m_radianAngle /= inFloat;
    return *this;
  }
  
  bool 
  giRadians::operator<(const giRadians& inRad) const {
    return getRadians() < inRad.getRadians();
  }
  
  bool 
  giRadians::operator<=(const giRadians& inRad) const {
    return getRadians() <= inRad.getRadians();
  }
  
  bool 
  giRadians::operator==(const giRadians& inRad) const {
    return getRadians() == inRad.getRadians();
  }
  
  bool 
  giRadians::operator!=(const giRadians& inRad) const {
    return getRadians() != inRad.getRadians();
  }
  
  bool 
  giRadians::operator>=(const giRadians& inRad) const {
    return getRadians() >= inRad.getRadians();
  }
  
  bool 
  giRadians::operator>(const giRadians& inRad) const {
    return getRadians() > inRad.getRadians();
  }
  
}