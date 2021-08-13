#include "giDegrees.h"
#include "giRadians.h"
#include "giMath.h"

namespace giEngineSDK {

  Degrees::Degrees(float inVal) {
    m_degreesAngle = inVal;
  }

  Degrees::Degrees(const Radians& inRad) {
    m_degreesAngle = inRad.getRadians();
  }

  float
  Degrees::getRadians() const {
    return getDegrees() * Math::DEG2RAD;
  }

  float
  Degrees::getDegrees() const {
    return m_degreesAngle;
  }
  
  Degrees 
  Degrees::operator+(const Degrees& inDeg) const {
    return Degrees(getDegrees() + inDeg.getDegrees());
  }
  
  Degrees& 
  Degrees::operator+=(const Degrees& inDeg) {
    m_degreesAngle += inDeg.m_degreesAngle;
    return *this;
  }
  
  Degrees 
  Degrees::operator-() const {
    return Degrees(-getDegrees());
  }
  
  Degrees 
  Degrees::operator-(const Degrees& inDeg) const {
    return Degrees(getDegrees() - inDeg.getDegrees());
  }
  
  Degrees& 
  Degrees::operator-=(const Degrees& inDeg) {
    m_degreesAngle -= inDeg.getDegrees();
    return *this;
  }

  Degrees 
  Degrees::operator*(const Degrees& inFloat) const {
    return Degrees(getDegrees() * inFloat.getDegrees());
  }
  
  bool 
  Degrees::operator<(const Degrees& inDeg) const {
    return getDegrees() < inDeg.getDegrees();
  }
  
  bool 
  Degrees::operator<=(const Degrees& inDeg) const {
    return getDegrees() <= inDeg.getDegrees();
  }
  
  bool 
  Degrees::operator==(const Degrees& inDeg) const {
    return getDegrees() == inDeg.getDegrees();
  }
  
  bool 
  Degrees::operator!=(const Degrees& inDeg) const {
    return getDegrees() != inDeg.getDegrees();
  }
  
  bool 
  Degrees::operator>=(const Degrees& inDeg) const {
    return getDegrees() >= inDeg.getDegrees();
  }
  
  bool 
  Degrees::operator>(const Degrees& inDeg) const {
    return getDegrees() > inDeg.getDegrees();
  }
  
}