#pragma once


#include "giPrerequisitesUtilities.h"


namespace giEngineSDK {
  
  class GI_UTILITY_EXPORT giVector2i
  {
   public:

    giVector2i() = default;

    giVector2i(int32 inX, int32 inY);

    giVector2i(giVector2i& inVect);

    ~giVector2i();

    int32
    getX() {
      return x;
    }

    int32
    getY() {
      return y;
    }

    void
    setX(int32 inVal) {
      x = inVal;
    }

    void
    setY(int32 inVal) {
      y = inVal;
    }


    giVector2i
    operator+(const giVector2i& otherVect);
  
    giVector2i
    operator-(const giVector2i& otherVect);
  
    giVector2i
    operator*(const giVector2i& otherVect);
  
    giVector2i
    operator/(const giVector2i& otherVect);
  
  
    giVector2i
    operator+(const int32& otherVal);
  
    giVector2i
    operator-(const int32& otherVal);
  
    giVector2i
    operator*(const int32& otherVal);
  
    giVector2i
    operator/(const int32& otherVal);
  
  
  
    bool
    operator>=(const giVector2i& otherVect);
  
    bool
    operator<=(const giVector2i& otherVect);
  
    bool
    operator==(const giVector2i& otherVect);
  
    bool
    operator<(const giVector2i& otherVect);
  
    bool
    operator>(const giVector2i& otherVect);
  
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
    dotProd(const giVector2i& inVect);
  
    int32
    crossProd(const giVector2i& inVect);
  
    void
    normalize();
  
    int32
    magnitude();
  
  
  private:
    int32 x;
    int32 y;
  
  };
  
}