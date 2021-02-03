/**
 * @file    giRadians.h
 * @author  Jes�s Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    01/02/2021
 * @brief   A basic Radians.
 * @bug     No known Bugs.
 */

 /**
   * @include
   */
#pragma once


class giDegrees;


/**
 * @class    giRadians.
 * @bug      No known Bugs.
 */
class giRadians {
public:
  giRadians() = default;
  giRadians(float inVal) {
    m_RadianAngle = inVal;
  }
  ~giRadians() = default;

  float getRadians() { return m_RadianAngle; }

  float getDegrees() { return m_RadianAngle; }

  //+ += - -= * *= / /= < <= == != >= > 
  //Radians 

  const giRadians&
  operator+() const;

  giRadians
  operator+(const giRadians& inRad) const;

  giRadians
  operator+(const giDegrees& inDeg) const;

  giRadians&
  operator+=(const giRadians& inRad);

  giRadians&
  operator+=(const giDegrees& d);

  giRadians
  operator-() const ;

  giRadians
  operator-(const giRadians& r) const;

  giRadians
  operator-(const giDegrees& d) const;

  giRadians&
  operator-=(const giRadians& inRad);

  giRadians&
  operator-=(const giDegrees& d);

  giRadians
  operator*(float f) const ;

  giRadians
  operator*(const giRadians& f) const;

  giRadians&
  operator*=(float f);

  giRadians
  operator/(float f) const;

  giRadians&
  operator/=(float f);

  bool
  operator<(const giRadians& r) const;

  bool
  operator<=(const giRadians& r) const;

  bool
  operator==(const giRadians& r) const;

  bool
  operator!=(const giRadians& r) const;

  bool
  operator>=(const giRadians& r) const;

  bool
  operator>(const giRadians& r) const;

  bool
  operator<(const float& v) const;

  bool
  operator<=(const float& v) const;

  bool
  operator==(const float& v) const;

  bool
  operator!=(const float& v) const ;

  bool
  operator>=(const float& v) const;

  bool 
  operator>(const float& v) const;
  
private:

  float m_RadianAngle = 0;
};