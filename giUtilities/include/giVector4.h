/**
 * @file    giVector4.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    26/03/2021
 * @brief   A basic Vector 4.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once

#include "giPrerequisitesUtilities.h"

namespace giEngineSDK {

  class GI_UTILITY_EXPORT Vector4
  {
   public:
  
    Vector4() = default;
  
    Vector4(float inX, float inY, float inZ, float inW);
  
    Vector4(Vector4& inVect);
  
    ~Vector4();
  
    
  
    Vector4
    operator+(const Vector4& otherVect) const;
    
    Vector4
    operator-(const Vector4& otherVect) const;
    
    Vector4
    operator*(const Vector4& otherVect) const;
    
    Vector4
    operator/(const Vector4& otherVect) const;
    
    void
    operator+=(const Vector4& otherVect);
    
    void
    operator-=(const Vector4& otherVect);
    
    void
    operator*=(const Vector4& otherVect);
    
    void
    operator/=(const Vector4& otherVect);
    
    
    Vector4
    operator+(const float& otherVal);
    
    Vector4
    operator-(const float& otherVal);
  
    Vector4
    operator*(const float& otherVal);
    
    Vector4
    operator/(const float& otherVal);
    
    
    
    bool
    operator>=(const Vector4& otherVect) const;
    
    bool
    operator<=(const Vector4& otherVect) const;
    
    bool
    operator==(const Vector4& otherVect) const;
    
    bool
    operator!=(const Vector4& otherVect) const;
    
    bool
    operator<(const Vector4& otherVect) const;
    
    bool
    operator>(const Vector4& otherVect) const;
    
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
    dotProd(const Vector4& inVect);
    
    float
    crossProd(const Vector4& inVect);
    
    void
    normalize();
    
    float
    magnitude();
  
    float x;

    float y;
    
    float z;
    
    float w;
  
  };

}