/**
 * @file    giRadians.h
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


class giRadians;

/**
 * @class    giDegrees.
 * @bug      No known Bugs.
 */
class giDegrees {
public:
  giDegrees() = default;

  giDegrees(float inVal) {
    m_DegreesAngle = inVal;
  }

  ~giDegrees() = default;
protected:
  
private:
  float m_DegreesAngle;
};