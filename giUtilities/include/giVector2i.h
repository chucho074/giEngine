/**
 * @file    giVector2i.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    26/03/2021
 * @brief   A basic Vector 2 dor ints.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once

#include "giPrerequisitesUtilities.h"


namespace giEngineSDK {
  
  class GI_UTILITY_EXPORT Vector2i
  {
   public:

    Vector2i();

    Vector2i(int32 inX, int32 inY);

    Vector2i(Vector2i& inVect);

    ~Vector2i();

    Vector2i
    operator+(const Vector2i& otherVect);
  
    Vector2i
    operator-(const Vector2i& otherVect);
  
    Vector2i
    operator*(const Vector2i& otherVect);
  
    Vector2i
    operator/(const Vector2i& otherVect);
  
    Vector2i
    operator+(const int32& otherVal);
  
    Vector2i
    operator-(const int32& otherVal);
  
    Vector2i
    operator*(const int32& otherVal);
  
    Vector2i
    operator/(const int32& otherVal);
  
    bool
    operator>=(const Vector2i& otherVect);
  
    bool
    operator<=(const Vector2i& otherVect);
  
    bool
    operator==(const Vector2i& otherVect);
  
    bool
    operator<(const Vector2i& otherVect);
  
    bool
    operator>(const Vector2i& otherVect);
  
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
    dotProd(const Vector2i& inVect);
  
    int32
    crossProd(const Vector2i& inVect);
  
    void
    normalize();
  
    int32
    magnitude();
  

    int32 x;
    int32 y;

    /**
     * @brief A zero vector (0,0)
     */
    static const Vector2i ZERO;

    /**
     * @brief A unit vector (1,1)
     */
    static const Vector2i UNIT;
  
  };
  
}