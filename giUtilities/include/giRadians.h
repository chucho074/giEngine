/**
 * @file    giRadians.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    01/02/2021
 * @brief   A basic Radians.
 * @bug     No known Bugs.
 */

/**
  * @include
  */
#pragma once

#include "giPrerequisitesUtilities.h"



/**
 * @class    Radians. 
 */
namespace giEngineSDK {

  class Degrees;

  class GI_UTILITY_EXPORT Radians 
  {
   public:
    Radians() = default;
    
    Radians(float inVal);
    
    Radians(const Degrees& inDeg);
    
    
    ~Radians() = default;
    
    float 
    getRadians() const;
    
    float 
    getDegrees() const;
    
    Radians
    operator+(const Radians& inRad) const;
    
    Radians&
    operator+=(const Radians& inRad);
    
    Radians
    operator-() const ;
    
    Radians
    operator-(const Radians& inRad) const;
    
    Radians&
    operator-=(const Radians& inRad);
    
    Radians
    operator*(float inVal) const ;
    
    Radians
    operator*(const Radians& inVal) const;
    
    Radians&
    operator*=(float inVal);
    
    Radians
    operator/(float inVal) const;
    
    Radians&
    operator/=(float inVal);
    
    bool
    operator<(const Radians& inRad) const;
    
    bool
    operator<=(const Radians& inRad) const;
    
    bool
    operator==(const Radians& inRad) const;
    
    bool
    operator!=(const Radians& inRad) const;
    
    bool
    operator>=(const Radians& inRad) const;
    
    bool
    operator>(const Radians& inRad) const;
    
   private:
  
     float m_radianAngle;
  };
}