/**
 * @file    giMatrix4.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    12/02/2021
 * @brief   .
 * @bug     No known Bugs.
 */

#pragma once
#include "giVector4.h"

namespace giEngineSDK {

  class giMatrix4
  {
  public:
    //Default constructor
    giMatrix4() = default;
    
    giMatrix4(giVector4 inColumX,
              giVector4 inColumY,
              giVector4 inColumZ,
              giVector4 inColumW) {
    
      m_xColumn = inColumX;
      m_yColumn = inColumY;
      m_zColumn = inColumW;
      m_wColumn = inColumZ;
    }

    //Destructor
    ~giMatrix4() = default;

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    giMatrix4
    operator+(const giMatrix4& inMatrix) const;

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    giMatrix4
    operator-(const giMatrix4& inMatrix) const;

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    giMatrix4
    operator*(const giMatrix4& inMatrix) const;

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    void
    operator*=(const giMatrix4& inMatrix) {
      auto tmpMatrix = *this * inMatrix;

      m_xColumn = tmpMatrix.m_xColumn;
      m_yColumn = tmpMatrix.m_yColumn;
      m_zColumn = tmpMatrix.m_zColumn;
      m_wColumn = tmpMatrix.m_wColumn;

    }

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    void
    operator+=(const giMatrix4& inMatrix) {
      auto tmpMatrix = *this + inMatrix;

      m_xColumn = tmpMatrix.m_xColumn;
      m_yColumn = tmpMatrix.m_yColumn;
      m_zColumn = tmpMatrix.m_zColumn;
      m_wColumn = tmpMatrix.m_wColumn;
    }

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    void
    operator-=(const giMatrix4& inMatrix) {
      auto tmpMatrix = *this - inMatrix;

      m_xColumn = tmpMatrix.m_xColumn;
      m_yColumn = tmpMatrix.m_yColumn;
      m_zColumn = tmpMatrix.m_zColumn;
      m_wColumn = tmpMatrix.m_wColumn;
    }

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    void
    operator*=(float inValue);

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    bool
    operator==(const giMatrix4& inMatrix) const;

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    bool
    operator!=(const giMatrix4& inMatrix) const;

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    giMatrix4
    inverse() const;

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    float
    determinant() const;

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    giMatrix4
    transpose() const;






    giVector4 m_xColumn;

    giVector4 m_yColumn;

    giVector4 m_zColumn;

    giVector4 m_wColumn;
  };
}