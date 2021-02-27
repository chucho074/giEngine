/**
 * @file    giMatrix4.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    12/02/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */

#include "giMatrix4.h"

namespace giEngineSDK {

  giMatrix4
  giMatrix4::operator+(const giMatrix4& inMatrix) const
  {
    giMatrix4 tmpMatrix;
    tmpMatrix.m_xColumn = m_xColumn + inMatrix.m_xColumn;
    tmpMatrix.m_yColumn = m_yColumn + inMatrix.m_yColumn;
    tmpMatrix.m_zColumn = m_zColumn + inMatrix.m_zColumn;
    tmpMatrix.m_wColumn = m_wColumn + inMatrix.m_wColumn;
    return tmpMatrix;
  }

  giMatrix4
  giMatrix4::operator-(const giMatrix4& inMatrix) const
  {
    giMatrix4 tmpMatrix;
    tmpMatrix.m_xColumn = m_xColumn - inMatrix.m_xColumn;
    tmpMatrix.m_yColumn = m_yColumn - inMatrix.m_yColumn;
    tmpMatrix.m_zColumn = m_zColumn - inMatrix.m_zColumn;
    tmpMatrix.m_wColumn = m_wColumn - inMatrix.m_wColumn;
    return tmpMatrix;
  }

  giMatrix4
  giMatrix4::operator*(const giMatrix4& inMatrix) const
  {
    giMatrix4 Result;
    //Transponer y multiplicar los vectores
    Result.m_xColumn.setX(m_xColumn.getX() * inMatrix.m_xColumn.getX()
      + m_xColumn.getY() * inMatrix.m_yColumn.getX()
      + m_xColumn.getZ() * inMatrix.m_zColumn.getX()
      + m_xColumn.getW() * inMatrix.m_wColumn.getX());

    Result.m_xColumn.setY(m_yColumn.getX() * inMatrix.m_xColumn.getY()
      + m_yColumn.getY() * inMatrix.m_yColumn.getY()
      + m_yColumn.getZ() * inMatrix.m_zColumn.getY()
      + m_yColumn.getW() * inMatrix.m_wColumn.getY());

    Result.m_xColumn.setZ(m_zColumn.getX() * inMatrix.m_xColumn.getZ()
      + m_zColumn.getY() * inMatrix.m_yColumn.getZ()
      + m_zColumn.getZ() * inMatrix.m_zColumn.getZ()
      + m_zColumn.getW() * inMatrix.m_wColumn.getZ());

    Result.m_xColumn.setW(m_wColumn.getX() * inMatrix.m_xColumn.getW()
      + m_wColumn.getY() * inMatrix.m_yColumn.getW()
      + m_wColumn.getZ() * inMatrix.m_zColumn.getW()
      + m_wColumn.getW() * inMatrix.m_wColumn.getW());

    //
    Result.m_yColumn.setX(m_xColumn.getX() * inMatrix.m_xColumn.getX()
      + m_xColumn.getY() * inMatrix.m_yColumn.getX()
      + m_xColumn.getZ() * inMatrix.m_zColumn.getX()
      + m_xColumn.getW() * inMatrix.m_wColumn.getX());

    Result.m_yColumn.setY(m_yColumn.getX() * inMatrix.m_xColumn.getY()
      + m_yColumn.getY() * inMatrix.m_yColumn.getY()
      + m_yColumn.getZ() * inMatrix.m_zColumn.getY()
      + m_yColumn.getW() * inMatrix.m_wColumn.getY());

    Result.m_yColumn.setZ(m_zColumn.getX() * inMatrix.m_xColumn.getZ()
      + m_zColumn.getY() * inMatrix.m_yColumn.getZ()
      + m_zColumn.getZ() * inMatrix.m_zColumn.getZ()
      + m_zColumn.getW() * inMatrix.m_wColumn.getZ());

    Result.m_yColumn.setW(m_wColumn.getX() * inMatrix.m_xColumn.getW()
      + m_wColumn.getY() * inMatrix.m_yColumn.getW()
      + m_wColumn.getZ() * inMatrix.m_zColumn.getW()
      + m_wColumn.getW() * inMatrix.m_wColumn.getW());

    //
    Result.m_zColumn.setX(m_xColumn.getX() * inMatrix.m_xColumn.getX()
      + m_xColumn.getY() * inMatrix.m_yColumn.getX()
      + m_xColumn.getZ() * inMatrix.m_zColumn.getX()
      + m_xColumn.getW() * inMatrix.m_wColumn.getX());

    Result.m_zColumn.setY(m_yColumn.getX() * inMatrix.m_xColumn.getY()
      + m_yColumn.getY() * inMatrix.m_yColumn.getY()
      + m_yColumn.getZ() * inMatrix.m_zColumn.getY()
      + m_yColumn.getW() * inMatrix.m_wColumn.getY());

    Result.m_zColumn.setZ(m_zColumn.getX() * inMatrix.m_xColumn.getZ()
      + m_zColumn.getY() * inMatrix.m_yColumn.getZ()
      + m_zColumn.getZ() * inMatrix.m_zColumn.getZ()
      + m_zColumn.getW() * inMatrix.m_wColumn.getZ());

    Result.m_zColumn.setW(m_wColumn.getX() * inMatrix.m_xColumn.getW()
      + m_wColumn.getY() * inMatrix.m_yColumn.getW()
      + m_wColumn.getZ() * inMatrix.m_zColumn.getW()
      + m_wColumn.getW() * inMatrix.m_wColumn.getW());

    //
    Result.m_wColumn.setX(m_xColumn.getX() * inMatrix.m_xColumn.getX()
      + m_xColumn.getY() * inMatrix.m_yColumn.getX()
      + m_xColumn.getZ() * inMatrix.m_zColumn.getX()
      + m_xColumn.getW() * inMatrix.m_wColumn.getX());

    Result.m_wColumn.setY(m_yColumn.getX() * inMatrix.m_xColumn.getY()
      + m_yColumn.getY() * inMatrix.m_yColumn.getY()
      + m_yColumn.getZ() * inMatrix.m_zColumn.getY()
      + m_yColumn.getW() * inMatrix.m_wColumn.getY());

    Result.m_wColumn.setZ(m_zColumn.getX() * inMatrix.m_xColumn.getZ()
      + m_zColumn.getY() * inMatrix.m_yColumn.getZ()
      + m_zColumn.getZ() * inMatrix.m_zColumn.getZ()
      + m_zColumn.getW() * inMatrix.m_wColumn.getZ());

    Result.m_wColumn.setW(m_wColumn.getX() * inMatrix.m_xColumn.getW()
      + m_wColumn.getY() * inMatrix.m_yColumn.getW()
      + m_wColumn.getZ() * inMatrix.m_zColumn.getW()
      + m_wColumn.getW() * inMatrix.m_wColumn.getW());

    return Result;
  }

  void
  giMatrix4::operator*=(float inValue)
  {
    m_xColumn = m_xColumn * inValue;
    m_yColumn = m_yColumn * inValue;
    m_zColumn = m_zColumn * inValue;
    m_wColumn = m_wColumn * inValue;
  }

  bool
  giMatrix4::operator==(const giMatrix4& inMatrix) const
  {
    if ((m_xColumn == inMatrix.m_xColumn) &&
      (m_yColumn == inMatrix.m_yColumn) &&
      (m_zColumn == inMatrix.m_zColumn) &&
      (m_wColumn == inMatrix.m_wColumn)) {

      return true;
    }

    return false;
  }

  bool
  giMatrix4::operator!=(const giMatrix4& inMatrix) const
  {
    return !this->operator==(inMatrix);
  }

  giMatrix4 
  giMatrix4::inverse() const
  {
    return giMatrix4();
  }

  float
  giMatrix4::determinant() const
  {
    return m_xColumn.getX() * (
      m_yColumn.getY() * (m_zColumn.getZ() *
        m_wColumn.getW() - m_zColumn.getW() *
        m_wColumn.getZ()) - m_zColumn.getY() *
        (m_yColumn.getZ() * m_wColumn.getW() -
        m_yColumn.getW() * m_wColumn.getZ()) +
      m_wColumn.getY() * (m_yColumn.getZ() *
        m_zColumn.getW() - m_yColumn.getW() *
        m_zColumn.getZ())) -
      m_yColumn.getX() * (
        m_xColumn.getY() * (m_zColumn.getZ() *
          m_wColumn.getW() - m_zColumn.getW() *
          m_wColumn.getZ()) - m_zColumn.getY() *
        (m_xColumn.getZ() * m_wColumn.getW() -
          m_xColumn.getW() * m_wColumn.getZ()) +
        m_wColumn.getY() * (m_xColumn.getZ() *
          m_zColumn.getW() - m_xColumn.getW() *
          m_yColumn.getZ())) +
      m_zColumn.getX() * (
        m_xColumn.getY() * (m_yColumn.getZ() *
          m_zColumn.getW() - m_yColumn.getW() *
          m_wColumn.getZ()) - m_yColumn.getY() *
        (m_xColumn.getZ() * m_wColumn.getW() -
          m_xColumn.getW() * m_wColumn.getZ()) +
        m_wColumn.getY() * (m_xColumn.getZ() *
          m_xColumn.getW() - m_xColumn.getW() *
          m_yColumn.getZ())) -
      m_wColumn.getX() * (
        m_xColumn.getY() * (m_yColumn.getZ() *
          m_zColumn.getW() - m_yColumn.getW() *
          m_zColumn.getZ()) - m_yColumn.getY() *
        (m_xColumn.getZ() * m_zColumn.getW() -
          m_xColumn.getW() * m_zColumn.getZ()) +
        m_zColumn.getY() * (m_xColumn.getZ() *
          m_yColumn.getW() - m_xColumn.getW() *
          m_yColumn.getZ()));
  }
  
  giMatrix4 
  giMatrix4::transpose() const
  {
    giMatrix4	Result;

    //Result.m[0][0] = m[0][0];
    //Result.m[0][1] = m[1][0];
    //Result.m[0][2] = m[2][0];
    //Result.m[0][3] = m[3][0];
    //
    //Result.m[1][0] = m[0][1];
    //Result.m[1][1] = m[1][1];
    //Result.m[1][2] = m[2][1];
    //Result.m[1][3] = m[3][1];
    //
    //Result.m[2][0] = m[0][2];
    //Result.m[2][1] = m[1][2];
    //Result.m[2][2] = m[2][2];
    //Result.m[2][3] = m[3][2];
    //
    //Result.m[3][0] = m[0][3];
    //Result.m[3][1] = m[1][3];
    //Result.m[3][2] = m[2][3];
    //Result.m[3][3] = m[3][3];

    return Result;
  }
}