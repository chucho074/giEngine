#pragma once

#include "giPlatformMath.h"

class giVector2
{
 public:
  
  giVector2() = default;

  giVector2(float inX, float inY);

  giVector2(giVector2 & inVect);
  
  ~giVector2();

  float
  getX() {
    return x;
  }
  
  float
  getY() {
    return y;
  }

  void
  setX(float inVal) {
    x = inVal;
  }
  void
  setY(float inVal) {
    y = inVal;
  }

  //+ - * / vectores
  giVector2
  operator+(const giVector2& otherVect);

  giVector2
  operator-(const giVector2& otherVect);

  giVector2
  operator*(const giVector2& otherVect);

  giVector2
  operator/(const giVector2& otherVect);
  
  //+ - * / float
  giVector2
  operator+(const float& otherVal);

  giVector2
  operator-(const float& otherVal);

  giVector2
  operator*(const float& otherVal);

  giVector2
  operator/(const float& otherVal);


  // += -= <= >= ==
  bool
  operator+=(const float& otherVal);

  bool
  operator-=(const float& otherVal);
  
  bool
  operator>=(const float& otherVal);

  bool
  operator<=(const float& otherVal);

  bool
  operator==(const float& otherVal);


 protected:
 	

 private:
  float x;
  float y;
  
};