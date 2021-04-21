/**
 * @file    giVector3.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    26/03/2021
 * @brief   A basic Vector 3.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once

#include "giPrerequisitesUtilities.h"

namespace giEngineSDK {
  
  class GI_UTILITY_EXPORT Vector3
  {
   public:

    Vector3() = default;
    
    Vector3(float inX, float inY, float inZ);
    
    //Vector3(const Vector3 & inVect);
    
    ~Vector3();
   
    Vector3
    operator+(const Vector3& otherVect);
    
    Vector3
    operator-(const Vector3& otherVect);
    
    Vector3
    operator*(const Vector3& otherVect);
    
    Vector3
    operator/(const Vector3& otherVect); 
    
    Vector3
    operator+(const float& otherVal);
    
    Vector3
    operator-(const float& otherVal);
    
    Vector3
    operator*(const float& otherVal);
    
    Vector3
    operator/(const float& otherVal);
    
    bool
    operator>=(const Vector3& otherVect);
    
    bool
    operator<=(const Vector3& otherVect);
    
    bool
    operator==(const Vector3& otherVect);
    
    bool
    operator<(const Vector3& otherVect);
    
    bool
    operator>(const Vector3& otherVect);
    
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
    dotProd(const Vector3& inVect);
    
    float
    crossProd(const Vector3& inVect);
    
    void
    normalize();
    
    float
    magnitude();
    
   
    float x;
    float y;
    float z;

  };
  
}