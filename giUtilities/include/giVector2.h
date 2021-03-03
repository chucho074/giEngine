#pragma once

#include "giPlatformMath.h"

namespace giEngineSDK {

  class GI_UTILITY_EXPORT giVector2
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
    
    
    giVector2
    operator+(const giVector2& otherVect);
    
    giVector2
    operator-(const giVector2& otherVect);
    
    giVector2
    operator*(const giVector2& otherVect);
    
    giVector2
    operator/(const giVector2& otherVect);
    
    
    giVector2
    operator+(const float& otherVal);
    
    giVector2
    operator-(const float& otherVal);
    
    giVector2
    operator*(const float& otherVal);
    
    giVector2
    operator/(const float& otherVal);
    
    
    
    bool
    operator>=(const giVector2& otherVect);
    
    bool
    operator<=(const giVector2& otherVect);
    
    bool
    operator==(const giVector2& otherVect);
    
    bool
    operator<(const giVector2& otherVect);
    
    bool
    operator>(const giVector2& otherVect);
    
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
    dotProd(const giVector2& inVect);
    
    float 
    crossProd(const giVector2& inVect);
    
    void
    normalize();
    
    float
    magnitude();

  protected:
  	
  
  private:
    float x;
    float y;
  
  };
  
}