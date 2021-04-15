/**
 * @file    giMatrix4.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    12/02/2021
 * @brief   .
 * @bug     No known Bugs.
 */

/**
 * @include
 */
#pragma once

#include "giPrerequisitesUtilities.h"
#include "giVector4.h"

namespace giEngineSDK { 

  class GI_UTILITY_EXPORT Matrix4
  {
   public:
    //Default constructor
    Matrix4() = default;
    
    Matrix4(Vector4 inColumX,
    /******/Vector4 inColumY,
    /******/Vector4 inColumZ,
    /******/Vector4 inColumW) {
    
      m_xColumn = inColumX;
      m_yColumn = inColumY;
      m_zColumn = inColumZ;
      m_wColumn = inColumW;
    }

    //Destructor
    ~Matrix4() = default;

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    Matrix4
    operator+(const Matrix4& inMatrix) const;

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    Matrix4
    operator-(const Matrix4& inMatrix) const;

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    Matrix4
    operator*(const Matrix4& inMatrix) const;

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    void
    operator*=(const Matrix4& inMatrix) {
      
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
    operator+=(const Matrix4& inMatrix) {
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
    operator-=(const Matrix4& inMatrix) {
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
    operator==(const Matrix4& inMatrix) const;

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    bool
    operator!=(const Matrix4& inMatrix) const;

    /**
     * @brief    Info of the function.
     * @param    _param1 parameter one.
     * @bug      No known Bugs.
     * @return   Returns .
     */
    Matrix4
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
    Matrix4
    transpose() const;

    /**
     * @brief    Intercambiar valores de 2 matrices
     * @bug      No known Bugs.
     */
    void 
    swap();
    
    /**
     * @brief 
     * @bug      No known Bugs.
     */
    void 
    negateMatrix();
    
    Vector4 m_xColumn;

    Vector4 m_yColumn;

    Vector4 m_zColumn;

    Vector4 m_wColumn;

    static const Matrix4 
    IDENTITY;
    
  };

  class lookToLH : public Matrix4
  {
   public:
     lookToLH(Vector4 inEyePos,
     /*******/Vector4 inEyeDirection,
     /*******/Vector4 inUpDirection);
  };

  class perspectiveFovLH : public Matrix4
  {
   public:
     perspectiveFovLH(float inFov,
     /***************/float inAR,
     /***************/float inNear,
     /***************/float inFar);
  };
}