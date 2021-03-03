#pragma once

#include "giPlatformMath.h"

using::giEngineSDK::int32;

namespace giEngineSDK {

  class GI_UTILITY_EXPORT giVector4i
  {
   public:
  
    giVector4i() = default;
  
    giVector4i(int32 inX, int32 inY, int32 inZ, int32 inW);
  
    giVector4i(giVector4i& inVect);
  
    ~giVector4i();
  
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
  
    int32
    getW() {
      return w;
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
  
    void
    setW(int32 inVal) {
      w = inVal;
    }
  
  
    giVector4i
    operator+(const giVector4i& otherVect);
    
    giVector4i
    operator-(const giVector4i& otherVect);
    
    giVector4i
    operator*(const giVector4i& otherVect);
    
    giVector4i
    operator/(const giVector4i& otherVect);
    
    
    giVector4i
    operator+(const int32& otherVal);
    
    giVector4i
    operator-(const int32& otherVal);
  
    giVector4i
    operator*(const int32& otherVal);
    
    giVector4i
    operator/(const int32& otherVal);
    
    
    
    bool
    operator>=(const giVector4i& otherVect);
    
    bool
    operator<=(const giVector4i& otherVect);
    
    bool
    operator==(const giVector4i& otherVect);
    
    bool
    operator<(const giVector4i& otherVect);
    
    bool
    operator>(const giVector4i& otherVect);
    
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
    dotProd(const giVector4i& inVect);
    
    int32
    crossProd(const giVector4i& inVect);
    
    void
    normalize();
    
    int32
    magnitude();
  
  
   private:
     int32 x;
     int32 y;
     int32 z;
     int32 w;
  
  };
}