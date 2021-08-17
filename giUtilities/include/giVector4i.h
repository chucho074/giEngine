/**
 * @file    giVector4i.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    05/03/2021
 * @brief   Vectors 4 for ints management.
 * @bug     No known Bugs.
 */

/**
 * @include
 */
#pragma once

#include "giPrerequisitesUtilities.h"
#include "giMath.h"

using giEngineSDK::int32;

/**
 * @class    Vector4i.
 * @brief    Vectors 4 for ints management.
 * @bug      No known Bugs.
 */
namespace giEngineSDK {
  class Vector4;

  class GI_UTILITY_EXPORT Vector4i
  {
   public:
  
    Vector4i() = default;
  
    Vector4i(int32 inX, int32 inY, int32 inZ, int32 inW);

    Vector4i(Vector4 inVect);
  
    Vector4i(Vector4i& inVect);
  
    ~Vector4i() = default;

    Vector4i
    operator+(const Vector4i& otherVect);
    
    Vector4i
    operator-(const Vector4i& otherVect);
    
    Vector4i
    operator*(const Vector4i& otherVect);
    
    Vector4i
    operator/(const Vector4i& otherVect);
    
    void
    operator=(const Vector4i& otherVect);
    
    Vector4i
    operator+(const int32& otherVal);
    
    Vector4i
    operator-(const int32& otherVal);
  
    Vector4i
    operator*(const int32& otherVal);
    
    Vector4i
    operator/(const int32& otherVal);
    
    bool
    operator>=(const Vector4i& otherVect);
    
    bool
    operator<=(const Vector4i& otherVect);
    
    bool
    operator==(const Vector4i& otherVect);
    
    bool
    operator<(const Vector4i& otherVect);
    
    bool
    operator>(const Vector4i& otherVect);
    
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
    dotProd(const Vector4i& inVect);
    
    static Vector4i
    crossProd(const Vector4i& inVectA, const Vector4i& inVectB);
    
    void
    normalize();
    
    int32
    magnitude();

  
    int32 x;

    int32 y;

    int32 z;

    int32 w;
  
  };
}