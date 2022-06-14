/**
 * @file    Degrees.h
 * @author  Jesus Alberto Del Moral Cupil
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
 * @class    Degrees.
 * @bug      No known Bugs.
 */
namespace giEngineSDK {
  
  class Radians;

  class GI_UTILITY_EXPORT Degrees 
  {
   public:
    Degrees() = default;
    
    Degrees(float inVal);
    
    Degrees(const Radians& inRad);
    
    ~Degrees() = default;
    
    float 
    getRadians() const;
    
    float 
    getDegrees() const;
    
    Degrees
    operator+(const Degrees& inDeg) const;
    
    Degrees&
    operator+=(const Degrees& inDeg);
    
    Degrees
    operator-() const;
    
    Degrees
    operator-(const Degrees& inDeg) const;
    
    Degrees&
    operator-=(const Degrees& inDeg);
    
    Degrees
    operator*(const Degrees& inDeg) const;
    
    bool
    operator<(const Degrees& inDeg) const;
    
    bool
    operator<=(const Degrees& inDeg) const;
    
    bool
    operator==(const Degrees& inDeg) const;
    
    bool
    operator!=(const Degrees& inDeg) const;
    
    bool
    operator>=(const Degrees& inDeg) const;
    
    bool 
    operator>(const Degrees& inDeg) const;
     
   private:
    float m_degreesAngle;
  };
}