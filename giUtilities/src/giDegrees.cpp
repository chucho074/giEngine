#include "giDegrees.h"
#include "giRadians.h"
#include "giMath.h"

namespace giEngineSDK {

  giDegrees::giDegrees(float inVal) {
    m_degreesAngle = inVal;
  }

  giDegrees::giDegrees(const giRadians& inRad) {
    m_degreesAngle = inRad.getRadians();
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
    return giDegrees(getDegrees() + inDeg.getDegrees());
  }
  
  giDegrees& 
  giDegrees::operator+=(const giDegrees& inDeg) {
    m_degreesAngle += inDeg.m_degreesAngle;
    return *this;
  }
  
  giDegrees 
  giDegrees::operator-() const {
    return giDegrees(-getDegrees());
  }
  
  giDegrees 
  giDegrees::operator-(const giDegrees& inDeg) const {
    return giDegrees(getDegrees() - inDeg.getDegrees());
  }
  
  giDegrees& 
  giDegrees::operator-=(const giDegrees& inDeg) {
    m_degreesAngle -= inDeg.getDegrees();
    return *this;
  }

  giDegrees 
  giDegrees::operator*(const giDegrees& inFloat) const {
    return giDegrees(getDegrees() * inFloat.getDegrees());
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
  
}