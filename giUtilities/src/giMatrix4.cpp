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
  const Matrix4 Matrix4::IDENTITY({ 1, 0, 0, 0 },
  /******************************/{ 0, 1, 0, 0 },
  /******************************/{ 0, 0, 1, 0 },
  /******************************/{ 0, 0, 0, 1 });

  Matrix4
  Matrix4::operator+(const Matrix4& inMatrix) const {
    Matrix4 tmpMatrix;
    tmpMatrix.m_xColumn = m_xColumn + inMatrix.m_xColumn;
    tmpMatrix.m_yColumn = m_yColumn + inMatrix.m_yColumn;
    tmpMatrix.m_zColumn = m_zColumn + inMatrix.m_zColumn;
    tmpMatrix.m_wColumn = m_wColumn + inMatrix.m_wColumn;
    return tmpMatrix;
  }

  Matrix4
  Matrix4::operator-(const Matrix4& inMatrix) const {
    Matrix4 tmpMatrix;
    tmpMatrix.m_xColumn = m_xColumn - inMatrix.m_xColumn;
    tmpMatrix.m_yColumn = m_yColumn - inMatrix.m_yColumn;
    tmpMatrix.m_zColumn = m_zColumn - inMatrix.m_zColumn;
    tmpMatrix.m_wColumn = m_wColumn - inMatrix.m_wColumn;
    return tmpMatrix;
  }

  Matrix4
  Matrix4::operator*(const Matrix4& inMatrix) const {
    Matrix4 Result;
    

    //xColumn
    Result.m_xColumn.x = ((m_xColumn.x * inMatrix.m_xColumn.x)
                          + (m_yColumn.x * inMatrix.m_xColumn.y)
                          + (m_zColumn.x * inMatrix.m_xColumn.z)
                          + (m_wColumn.x * inMatrix.m_xColumn.w));

    Result.m_xColumn.y = ((m_xColumn.y * inMatrix.m_xColumn.x)
                          + (m_yColumn.y * inMatrix.m_xColumn.y)
                          + (m_zColumn.y * inMatrix.m_xColumn.z)
                          + (m_wColumn.y * inMatrix.m_xColumn.w));

    Result.m_xColumn.z = ((m_xColumn.z * inMatrix.m_xColumn.x)
                          + (m_yColumn.z * inMatrix.m_xColumn.y)
                          + (m_zColumn.z * inMatrix.m_xColumn.z)
                          + (m_wColumn.z * inMatrix.m_xColumn.w));

    Result.m_xColumn.w = ((m_xColumn.w * inMatrix.m_xColumn.x)
                          + (m_yColumn.w * inMatrix.m_xColumn.y)
                          + (m_zColumn.w * inMatrix.m_xColumn.z)
                          + (m_wColumn.w * inMatrix.m_xColumn.w));

    //yColumn
    Result.m_yColumn.x = ((m_xColumn.x * inMatrix.m_yColumn.x)
                           + (m_yColumn.x * inMatrix.m_yColumn.y)
                           + (m_zColumn.x * inMatrix.m_yColumn.z)
                           + (m_wColumn.x * inMatrix.m_yColumn.w));

    Result.m_yColumn.y = ((m_xColumn.y * inMatrix.m_yColumn.x)
                          + (m_yColumn.y * inMatrix.m_yColumn.y)
                          + (m_zColumn.y * inMatrix.m_yColumn.z)
                          + (m_wColumn.y * inMatrix.m_yColumn.w));

    Result.m_yColumn.z = ((m_xColumn.z * inMatrix.m_yColumn.x)
                          + (m_yColumn.z * inMatrix.m_yColumn.y)
                          + (m_zColumn.z * inMatrix.m_yColumn.z)
                          + (m_wColumn.z * inMatrix.m_yColumn.w));

    Result.m_yColumn.w = ((m_xColumn.w * inMatrix.m_yColumn.x)
                          + (m_yColumn.w * inMatrix.m_yColumn.y)
                          + (m_zColumn.w * inMatrix.m_yColumn.z)
                          + (m_wColumn.w * inMatrix.m_yColumn.w));

    //zColumn
    Result.m_zColumn.x =((m_xColumn.x * inMatrix.m_zColumn.x)
                         + (m_yColumn.x * inMatrix.m_zColumn.y)
                         + (m_zColumn.x * inMatrix.m_zColumn.z)
                         + (m_wColumn.x * inMatrix.m_zColumn.w));

    Result.m_zColumn.y = ((m_xColumn.y * inMatrix.m_zColumn.x)
                          + (m_yColumn.y * inMatrix.m_zColumn.y)
                          + (m_zColumn.y * inMatrix.m_zColumn.z)
                          + (m_wColumn.y * inMatrix.m_zColumn.w));

    Result.m_zColumn.z = ((m_xColumn.z * inMatrix.m_zColumn.x)
                          + (m_yColumn.z * inMatrix.m_zColumn.y)
                          + (m_zColumn.z * inMatrix.m_zColumn.z)
                          + (m_wColumn.z * inMatrix.m_zColumn.w));

    Result.m_zColumn.w = ((m_xColumn.w * inMatrix.m_zColumn.x)
                          + (m_yColumn.w * inMatrix.m_zColumn.y)
                          + (m_zColumn.w * inMatrix.m_zColumn.z)
                          + (m_wColumn.w * inMatrix.m_zColumn.w));

    //wColumn
    Result.m_wColumn.x =((m_xColumn.x * inMatrix.m_wColumn.x)
                         + (m_yColumn.x * inMatrix.m_wColumn.y)
                         + (m_zColumn.x * inMatrix.m_wColumn.z)
                         + (m_wColumn.x * inMatrix.m_wColumn.w));

    Result.m_wColumn.y = ((m_xColumn.y * inMatrix.m_wColumn.x)
                          + (m_yColumn.y * inMatrix.m_wColumn.y)
                          + (m_zColumn.y * inMatrix.m_wColumn.z)
                          + (m_wColumn.y * inMatrix.m_wColumn.w));

    Result.m_wColumn.z = ((m_xColumn.z * inMatrix.m_wColumn.x)
                          + (m_yColumn.z * inMatrix.m_wColumn.y)
                          + (m_zColumn.z * inMatrix.m_wColumn.z)
                          + (m_wColumn.z * inMatrix.m_wColumn.w));

    Result.m_wColumn.w = ((m_xColumn.w * inMatrix.m_wColumn.x)
                          + (m_yColumn.w * inMatrix.m_wColumn.y)
                          + (m_zColumn.w * inMatrix.m_wColumn.z)
                          + (m_wColumn.w * inMatrix.m_wColumn.w));
      
    
    return Result;
  }

  void
  Matrix4::operator*=(float inValue) {
    m_xColumn = m_xColumn * inValue;
    m_yColumn = m_yColumn * inValue;
    m_zColumn = m_zColumn * inValue;
    m_wColumn = m_wColumn * inValue;
  }

  bool
  Matrix4::operator==(const Matrix4& inMatrix) const {
    if ((m_xColumn == inMatrix.m_xColumn) &&
      (m_yColumn == inMatrix.m_yColumn) &&
      (m_zColumn == inMatrix.m_zColumn) &&
      (m_wColumn == inMatrix.m_wColumn)) {

      return true;
    }

    return false;
  }

  bool
  Matrix4::operator!=(const Matrix4& inMatrix) const {
    return !this->operator==(inMatrix);
  }

  Matrix4 
  Matrix4::inverse() const {
    return Matrix4();
  }

  float
  Matrix4::determinant() const {
    return m_xColumn.x * (
    /***********/m_yColumn.y * (m_zColumn.z * m_wColumn.w - m_zColumn.w * m_wColumn.z) -
    /***********/m_zColumn.y * (m_yColumn.z * m_wColumn.w - m_yColumn.w * m_wColumn.z) +
    /***********/m_wColumn.y * (m_yColumn.z * m_zColumn.w - m_yColumn.w * m_zColumn.z)
    /***********/) - m_yColumn.x * (
    /***********/m_xColumn.y * (m_zColumn.z * m_wColumn.w - m_zColumn.w * m_wColumn.z) -
    /***********/m_zColumn.y * (m_xColumn.z * m_wColumn.w - m_xColumn.w * m_wColumn.z) +
    /***********/m_wColumn.y * (m_xColumn.z * m_zColumn.w - m_xColumn.w * m_zColumn.z)
    /***********/) + m_zColumn.x * (
    /***********/m_xColumn.y * (m_yColumn.z * m_wColumn.w - m_yColumn.w * m_wColumn.z) -
    /***********/m_yColumn.y * (m_xColumn.z * m_wColumn.w - m_xColumn.w * m_wColumn.z) +
    /***********/m_wColumn.y * (m_xColumn.z * m_yColumn.w - m_xColumn.w * m_yColumn.z)
    /***********/) - m_wColumn.x * (
    /***********/m_xColumn.y * (m_yColumn.z * m_zColumn.w - m_yColumn.w * m_zColumn.z) -
    /***********/m_yColumn.y * (m_xColumn.z * m_zColumn.w - m_xColumn.w * m_zColumn.z) +
    /***********/m_zColumn.y * (m_xColumn.z * m_yColumn.w - m_xColumn.w * m_yColumn.z));
  }
  
  Matrix4 
  Matrix4::transpose() const {
    Matrix4  Result;
    //
    Result.m_xColumn.x = m_xColumn.x;
    Result.m_xColumn.y = m_yColumn.x;
    Result.m_xColumn.z = m_zColumn.x;
    Result.m_xColumn.w = m_wColumn.x;
    //
    Result.m_yColumn.x = m_xColumn.y;
    Result.m_yColumn.y = m_yColumn.y;
    Result.m_yColumn.z = m_zColumn.y;
    Result.m_yColumn.w = m_wColumn.y;
    //
    Result.m_zColumn.x = m_xColumn.z;
    Result.m_zColumn.y = m_yColumn.z;
    Result.m_zColumn.z = m_zColumn.z;
    Result.m_zColumn.w = m_wColumn.z;
    //
    Result.m_wColumn.x = m_xColumn.w;
    Result.m_wColumn.y = m_yColumn.w;
    Result.m_wColumn.z = m_zColumn.w;
    Result.m_wColumn.w = m_wColumn.w;

    return Result;
  }
}