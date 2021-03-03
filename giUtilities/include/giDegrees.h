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

class giRadians;

/**
 * @class    giDegrees.
 * @bug      No known Bugs.
 */
namespace giEngineSDK {
  
  class GI_UTILITY_EXPORT giDegrees {
  public:
    giDegrees() = default;
  
    giDegrees(float inVal) {
    m_DegreesAngle = inVal;
  }
  
    ~giDegrees() = default;
  
    float
    radVal() const;
  
    const giDegrees&
    operator+() const;
    
    giDegrees
    operator+(const giDegrees& inDeg) const;
    
    giDegrees
    operator+(const giRadians& inRad);
    
    giDegrees&
    operator+=(const giDegrees& inDeg);
    
    giDegrees&
    operator+=(const giRadians& inRad);
    
    giDegrees
    operator-() const;
    
    giDegrees
    operator-(const giDegrees& inDeg) const;
    
    giDegrees
    operator-(const giRadians& inRad);
    
    giDegrees&
    operator-=(const giDegrees& inDeg);
    
    giDegrees&
    operator-=(giRadians& inRad);
    
    giDegrees
    operator*(float inFloat) const;
    
    giDegrees
    operator*(const giDegrees& inFloat) const;
    
    giDegrees&
    operator*=(float inFloat);
    
    giDegrees
    operator/(float inFloat) const;
    
    giDegrees&
    operator/=(float inFloat);
    
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
    
    bool
    operator<(const float& inVal) const;
    
    bool
    operator<=(const float& inVal) const;
    
    bool
    operator==(const float& inVal) const;
    
    bool
    operator!=(const float& inVal) const;
    
    bool
    operator>=(const float& inVal) const;
    
    bool
    operator>(const float& inVal) const;
  
  
  protected:
    
  private:
    float m_DegreesAngle;
  };
}