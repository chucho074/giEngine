#include "giDegrees.h"
#include "giRadians.h"
#include "giMath.h"

namespace giEngineSDK {
  giDegrees::giDegrees(const giRadians& inVal) {
    m_degreesAngle = inVal.getRadians();
  }

  float
  giDegrees::getRadians() const {
    return getDegrees() * Math::DEG2RAD;
  }

  float
  giDegrees::getDegrees() const {
    return m_degreesAngle;
  }
  
  const giDegrees& 
  giDegrees::operator+() const {
    return getDegrees();
  }
  
  giDegrees 
  giDegrees::operator+(const giDegrees& inDeg) const {
    return giDegrees(m_degreesAngle + inDeg.getDegrees());
  }
  
  giDegrees 
  giDegrees::operator+(const giRadians& inRad) const {
    return giDegrees(getDegrees() + inRad.getDegrees());
  }
  
  giDegrees& 
  giDegrees::operator+=(const giDegrees& inDeg) {
    m_degreesAngle += inDeg.m_degreesAngle;
    return *this;
  }
  
  giDegrees& 
  giDegrees::operator+=(const giRadians& inRad) {
    m_degreesAngle += inRad.getDegrees();
    return *this;
  }
  
  giDegrees 
  giDegrees::operator-() const {
    return giDegrees(-m_degreesAngle);
  }
  
  giDegrees 
  giDegrees::operator-(const giDegrees& inDeg) const {
    return giDegrees(getDegrees() - inDeg.getDegrees());
  }
  
  giDegrees 
  giDegrees::operator-(const giRadians& inRad) const {
    return giDegrees(getDegrees() - inRad.getDegrees());
  }
  
  giDegrees& 
  giDegrees::operator-=(const giDegrees& inDeg) {
    m_degreesAngle -= inDeg.m_degreesAngle;
    return *this;
  }
  
  giDegrees& 
  giDegrees::operator-=(giRadians& inRad) {
    m_degreesAngle -= inRad.getDegrees();
    return *this;
  }
  
  giDegrees 
  giDegrees::operator*(float inFloat) const {
    return giDegrees(getDegrees() * inFloat);
  }
  
  giDegrees 
  giDegrees::operator*(const giDegrees& inFloat) const {
    return giDegrees(getDegrees() * inFloat.getDegrees());
  }
  
  giDegrees& 
  giDegrees::operator*=(float inFloat) {
    m_degreesAngle *= inFloat;
    return *this;
  }
  
  giDegrees 
  giDegrees::operator/(float inFloat) const {
    return giDegrees(getDegrees() / inFloat);
  }
  
  giDegrees& 
  giDegrees::operator/=(float inFloat) {
    m_degreesAngle /= inFloat;
    return *this;
  }
  
  bool 
  giDegrees::operator<(const giDegrees& inDeg) const {
    return getDegrees() < inDeg.getDegrees();
  }
  
  bool 
  giDegrees::operator<=(const giDegrees& inDeg) const {
    return getDegrees() <= inDeg.getDegrees();
  }
  
  bool 
  giDegrees::operator==(const giDegrees& inDeg) const {
    return getDegrees() == inDeg.getDegrees();
  }
  
  bool 
  giDegrees::operator!=(const giDegrees& inDeg) const {
    return getDegrees() != inDeg.getDegrees();
  }
  
  bool 
  giDegrees::operator>=(const giDegrees& inDeg) const {
    return getDegrees() >= inDeg.getDegrees();
  }
  
  bool 
  giDegrees::operator>(const giDegrees& inDeg) const {
    return getDegrees() > inDeg.getDegrees();
  }
  
  bool 
  giDegrees::operator<(const float& inVal) const {
    return getDegrees() < inVal;
  }
  
  bool 
  giDegrees::operator<=(const float& inVal) const {
    return getDegrees() <= inVal;
  }
  
  bool 
  giDegrees::operator==(const float& inVal) const {
    return getDegrees() == inVal;
  }
  
  bool 
  giDegrees::operator!=(const float& inVal) const {
    return getDegrees() != inVal;
  }
  
  bool 
  giDegrees::operator>=(const float& inVal) const {
    return getDegrees() >= inVal;
  }
  
  bool 
  giDegrees::operator>(const float& inVal) const {
    return getDegrees() > inVal;
  }
}