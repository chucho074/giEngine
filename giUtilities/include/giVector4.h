#pragma once

#include "giPlatformMath.h"

class giVector4
{
public:

  giVector4() = default;

  giVector4(float inX, float inY, float inZ, float inW);

  giVector4(giVector4& inVect);

  ~giVector4();

  float
  getX() const {
    return x;
  }

  float
  getY() const {
    return y;
  }

  float
  getZ() const {
    return z;
  }

  float
  getW() const {
    return w;
  }

  void
  setX(float inVal) {
    x = inVal;
  }

  void
  setY(float inVal) {
    y = inVal;
  }

  void
  setZ(float inVal) {
    z = inVal;
  }

  void
  setW(float inVal) {
    w = inVal;
  }


  giVector4
  operator+(const giVector4& otherVect) const;
  
  giVector4
  operator-(const giVector4& otherVect) const;
  
  giVector4
  operator*(const giVector4& otherVect) const;
  
  giVector4
  operator/(const giVector4& otherVect) const;
  
  
  giVector4
  operator+(const float& otherVal);
  
  giVector4
  operator-(const float& otherVal);

  giVector4
  operator*(const float& otherVal);
  
  giVector4
  operator/(const float& otherVal);
  
  
  
  bool
  operator>=(const giVector4& otherVect) const;
  
  bool
  operator<=(const giVector4& otherVect) const;
  
  bool
  operator==(const giVector4& otherVect) const;
  
  bool
  operator!=(const giVector4& otherVect) const;
  
  bool
  operator<(const giVector4& otherVect) const;
  
  bool
  operator>(const giVector4& otherVect) const;
  
  bool
  operator>=(const float& otherVal);
  
  bool
  operator<=(const float& otherVal);
  
  bool
  operator==(const float& otherVal);
  
  bool
  operator<(const float& otherVal);
  
  bool
  operator>(const float& otherVal);
 
  float
  dotProd(const giVector4& inVect);
  
  float
  crossProd(const giVector4& inVect);
  
  void
  normalize();
  
  float
  magnitude();


private:
  float x;
  float y;
  float z;
  float w;

};