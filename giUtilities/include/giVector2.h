/**
 * @file    giVector2.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    26/03/2021
 * @brief   A basic Vector 2.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once

#include "giPrerequisitesUtilities.h"

namespace giEngineSDK {

  class GI_UTILITY_EXPORT Vector2
  {
   public:
    
    Vector2() = default;
    
    Vector2(float inX, float inY);
    
    //Vector2(const Vector2 & inVect);
    
    ~Vector2();
    
    Vector2
    operator+(const Vector2& otherVect);
    
    Vector2
    operator-(const Vector2& otherVect);
    
    Vector2
    operator*(const Vector2& otherVect);
    
    Vector2
    operator/(const Vector2& otherVect);
    
    
    Vector2
    operator+(const float& otherVal);
    
    Vector2
    operator-(const float& otherVal);
    
    Vector2
    operator*(const float& otherVal);
    
    Vector2
    operator/(const float& otherVal);
    
    bool
    operator>=(const Vector2& otherVect);
    
    bool
    operator<=(const Vector2& otherVect);
    
    bool
    operator==(const Vector2& otherVect);
    
    bool
    operator<(const Vector2& otherVect);
    
    bool
    operator>(const Vector2& otherVect);
    
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
    dotProd(const Vector2& inVect);
    
    float 
    crossProd(const Vector2& inVect);
    
    void
    normalize();
    
    float
    magnitude();

    float x;
    float y;
  
  };
}