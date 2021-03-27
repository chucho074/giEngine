/**
 * @file    giRadians.h
 * @author  Jesús Alberto Del Moral Cupil
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
 * @class    giRadians.
 * @bug      No known Bugs.
 */
namespace giEngineSDK {

  class giDegrees;

  class GI_UTILITY_EXPORT giRadians 
  {
   public:
    giRadians() = default;
    
    giRadians(float inVal);
    
    giRadians(const giDegrees& inDeg);
    
    
    ~giRadians() = default;
    
    float 
    getRadians() const;
    
    float 
    getDegrees() const;
     
    const giRadians&
    operator+() const;
    
    giRadians
    operator+(const giRadians& inRad) const;
    
    giRadians&
    operator+=(const giRadians& inRad);
    
    giRadians
    operator-() const ;
    
    giRadians
    operator-(const giRadians& inRad) const;
    
    giRadians&
    operator-=(const giRadians& inRad);
    
    giRadians
    operator*(float inVal) const ;
    
    giRadians
    operator*(const giRadians& inVal) const;
    
    giRadians&
    operator*=(float inVal);
    
    giRadians
    operator/(float inVal) const;
    
    giRadians&
    operator/=(float inVal);
    
    bool
    operator<(const giRadians& inRad) const;
    
    bool
    operator<=(const giRadians& inRad) const;
    
    bool
    operator==(const giRadians& inRad) const;
    
    bool
    operator!=(const giRadians& inRad) const;
    
    bool
    operator>=(const giRadians& inRad) const;
    
    bool
    operator>(const giRadians& inRad) const;
    
   private:
  
     float m_radianAngle;
  };
}