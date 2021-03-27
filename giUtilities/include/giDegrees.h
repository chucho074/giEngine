/**
 * @file    giDegrees.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    02/02/2021
 * @brief   A basic Degrees.
 * @bug     No known Bugs.
 */

/**
 * @include
 */
#pragma once

#include "giPrerequisitesUtilities.h"


/**
 * @class    giDegrees.
 * @bug      No known Bugs.
 */
namespace giEngineSDK {
  
  class giRadians;

  class GI_UTILITY_EXPORT giDegrees 
  {
   public:
    giDegrees() = default;
    
    giDegrees(float inVal);
    
    giDegrees(const giRadians& inRad);
    
    ~giDegrees() = default;
    
    float 
    getRadians() const;
    
    float 
    getDegrees() const;
    
    const giDegrees&
    operator+() const;
    
    giDegrees
    operator+(const giDegrees& inDeg) const;
    
    giDegrees&
    operator+=(const giDegrees& inDeg);
    
    giDegrees
    operator-() const;
    
    giDegrees
    operator-(const giDegrees& inDeg) const;
    
    giDegrees&
    operator-=(const giDegrees& inDeg);
    
    giDegrees
    operator*(const giDegrees& inDeg) const;
    
    bool
    operator<(const giDegrees& inDeg) const;
    
    bool
    operator<=(const giDegrees& inDeg) const;
    
    bool
    operator==(const giDegrees& inDeg) const;
    
    bool
    operator!=(const giDegrees& inDeg) const;
    
    bool
    operator>=(const giDegrees& inDeg) const;
    
    bool 
    operator>(const giDegrees& inDeg) const;
     
   private:
     float m_degreesAngle;
  };
}