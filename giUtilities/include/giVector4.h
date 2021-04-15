/**
 * @file    giVector4.h
 * @author  Jes�s Alberto Del Moral Cupil
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
  class Vector4i;

  class GI_UTILITY_EXPORT Vector4
  {
   public:
  
    Vector4() = default;
  
    Vector4(float inX, float inY, float inZ, float inW);

    Vector4(Vector4i inVect);
  
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
    operator=(const Vector4& otherVect);
    
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
   
    /**
     * @brief   Dot product in a float.
     * @param   inVectA .
     * @param   inVectB .
     * @return  Returns the dot product between two vectors.
     */
    float
    dotProd(const Vector4& inVectA);
    
    void
    normalize();
    
    float
    magnitude();

    float x;

    float y;
    
    float z;
    
    float w;
  
  };

  class crossProduct : public Vector4
  {
   public:
     crossProduct(const Vector4& inVectA, const Vector4& inVectB);
  };

}