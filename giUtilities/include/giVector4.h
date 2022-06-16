/**
 * @file    giVector4.h
 * @author  Jesus Alberto Del Moral Cupil
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
  class Vector3;
  class Vector4i;

  class GI_UTILITY_EXPORT Vector4
  {
   public:
  
    Vector4();
  
    Vector4(float inX, float inY, float inZ, float inW);

    Vector4(Vector4i inVect);
  
    Vector4(Vector4& inVect);

    Vector4(Vector3 inVect, float inScalar);
  
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
    
    Vector4
    operator-()const;
    
    
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

    Vector4
    cross(Vector4 inVector);
    
    void
    normalize();
    
    float
    magnitude();


    float x;

    float y;
    
    float z;
    
    float w;

    /**
     * @brief A zero vector (0,0,0,0)
     */
    static const Vector4 ZERO;

    /**
     * @brief A unit vector (1,1,1,1)
     */
    static const Vector4 UNIT;
  
  };

}