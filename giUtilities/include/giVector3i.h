#pragma once

#include "giPlatformMath.h"

using giEngineSDK::int32;

namespace giEngineSDK {
  
  class giVector3i
  {
   public:
  
    giVector3i() = default;
  
    giVector3i(int32 inX, int32 inY, int32 inZ);
  
    giVector3i(giVector3i& inVect);
  
    ~giVector3i();
  
    int32
    getX() {
      return x;
    }
  
    int32
    getY() {
      return y;
    }
  
    int32
    getZ() {
      return z;
    }
  
    void
    setX(int32 inVal) {
      x = inVal;
    }
  
    void
    setY(int32 inVal) {
      y = inVal;
    }
  
    void
    setZ(int32 inVal) {
      z = inVal;
    }
  
  
    giVector3i
    operator+(const giVector3i& otherVect);
    
    giVector3i
    operator-(const giVector3i& otherVect);
    
    giVector3i
    operator*(const giVector3i& otherVect);
    
    giVector3i
    operator/(const giVector3i& otherVect);
    
    
    giVector3i
    operator+(const int32& otherVal);
    
    giVector3i
    operator-(const int32& otherVal);
  
    giVector3i
    operator*(const int32& otherVal);
    
    giVector3i
    operator/(const int32& otherVal);
    
    
    
    bool
    operator>=(const giVector3i& otherVect);
    
    bool
    operator<=(const giVector3i& otherVect);
    
    bool
    operator==(const giVector3i& otherVect);
    
    bool
    operator<(const giVector3i& otherVect);
    
    bool
    operator>(const giVector3i& otherVect);
    
    bool
    operator>=(const int32& otherVal);
    
    bool
    operator<=(const int32& otherVal);
    
    bool
    operator==(const int32& otherVal);
    
    bool
    operator<(const int32& otherVal);
    
    bool
    operator>(const int32& otherVal);
   
    int32
    dotProd(const giVector3i& inVect);
    
    int32
    crossProd(const giVector3i& inVect);
    
    void
    normalize();
    
    int32
    magnitude();
  
  
   private:
    int32 x;
    int32 y;
    int32 z;
  
  };

}