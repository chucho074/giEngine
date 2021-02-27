#pragma once

#include "giPlatformMath.h"

namespace giEngineSDK {
  
  class giVector3
  {
   public:

   giVector3() = default;
   
   giVector3(float inX, float inY, float inZ);
   
   giVector3(giVector3& inVect);
   
   ~giVector3();
   
   float
   getX() {
    return x;
  }
   
   float
   getY() {
    return y;
  }
   
   float
   getZ() {
    return z;
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
   
   
   giVector3
   operator+(const giVector3& otherVect);
   
   giVector3
   operator-(const giVector3& otherVect);
   
   giVector3
   operator*(const giVector3& otherVect);
   
   giVector3
   operator/(const giVector3& otherVect);
   
   
   giVector3
   operator+(const float& otherVal);
   
   giVector3
   operator-(const float& otherVal);
   
   giVector3
   operator*(const float& otherVal);
   
   giVector3
   operator/(const float& otherVal);
   
   
   
   bool
   operator>=(const giVector3& otherVect);
   
   bool
   operator<=(const giVector3& otherVect);
   
   bool
   operator==(const giVector3& otherVect);
   
   bool
   operator<(const giVector3& otherVect);
   
   bool
   operator>(const giVector3& otherVect);
   
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
   dotProd(const giVector3& inVect);
   
   float
   crossProd(const giVector3& inVect);
   
   void
   normalize();
   
   float
   magnitude();


  private:
   float x;
   float y;
   float z;

  };
  
}