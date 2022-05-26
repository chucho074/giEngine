/**
 * @file    giVector3i.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    26/03/2021
 * @brief   A basic Vector 3 for int.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once

#include "giPrerequisitesUtilities.h"


namespace giEngineSDK {
  
  class GI_UTILITY_EXPORT Vector3i
  {
   public:
  
    Vector3i() = default;
  
    Vector3i(int32 inX, int32 inY, int32 inZ);
  
    Vector3i(Vector3i& inVect);
  
    ~Vector3i();
  
    Vector3i
    operator+(const Vector3i& otherVect);
    
    Vector3i
    operator-(const Vector3i& otherVect);
    
    Vector3i
    operator*(const Vector3i& otherVect);
    
    Vector3i
    operator/(const Vector3i& otherVect);
    
    
    Vector3i
    operator+(const int32& otherVal);
    
    Vector3i
    operator-(const int32& otherVal);
  
    Vector3i
    operator*(const int32& otherVal);
    
    Vector3i
    operator/(const int32& otherVal);
    
    bool
    operator>=(const Vector3i& otherVect);
    
    bool
    operator<=(const Vector3i& otherVect);
    
    bool
    operator==(const Vector3i& otherVect);
    
    bool
    operator<(const Vector3i& otherVect);
    
    bool
    operator>(const Vector3i& otherVect);
    
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
    dotProd(const Vector3i& inVect);
    
    int32
    crossProd(const Vector3i& inVect);
    
    void
    normalize();
    
    int32
    magnitude();
  
    int32 x;
    int32 y;
    int32 z;
  
  };

}