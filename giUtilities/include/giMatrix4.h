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
#include "giVector3.h"
#include "giVector4.h"
#include "giMath.h"

namespace giEngineSDK { 

  /**
   * @class    Matrix4.
   * @brief    Basic Matrix 4.
   * @bug      No known Bugs.
   */
  class GI_UTILITY_EXPORT Matrix4
  {
   public:
    //Default constructor
    Matrix4() = default;
    
    //Constructor from another matrix
    Matrix4(Matrix4 & inMatrix);

    /**
     * @brief    Constructor with Vectors as parameters.
     * @param    inColumX   Vector for the column x.
     * @param    inColumY   Vector for the column y.
     * @param    inColumZ   Vector for the column z.
     * @param    inColumW   Vector for the column w.
     */
    Matrix4(Vector4 inColumX,
            Vector4 inColumY,
            Vector4 inColumZ,
            Vector4 inColumW) {
      m_xColumn = inColumX;
      m_yColumn = inColumY;
      m_zColumn = inColumZ;
      m_wColumn = inColumW;
    }

    //Destructor
    ~Matrix4() = default;

    /**
     * @brief    Increment.
     * @param    inMatrix   The matrix for make the increment.
     * @return   Returns the result of the increment.
     */
    Matrix4
    operator+(const Matrix4& inMatrix) const;

    /**
     * @brief    Decrement.
     * @param    inMatrix   The matrix for make the decrement.
     * @return   Returns the result of the decrement.
     */
    Matrix4
    operator-(const Matrix4& inMatrix) const;

    /**
     * @brief    Multiply.
     * @param    inMatrix    The matrix for make the multiply.
     * @return   Returns the result of the multiply.
     */
    Matrix4
    operator*(const Matrix4& inMatrix);

    /**
     * @brief    Multiply and assign.
     * @param    inMatrix    The matrix for make the multiply.
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
     * @brief    Increment and assing.
     * @param    inMatrix    The matrix for make the increment.
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
     * @brief    Decrement and assign.
     * @param    inMatrix    The matrix for make the decrement.
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
     * @brief    Multiply by a constant.
     * @param    inValue    The value for make the multiply.
     */
    void
    operator*=(float inValue);

    /**
     * @brief    Equal.
     * @param    inMatrix    The matrix.
     * @return   Returns true if is equal.
     */
    bool
    operator==(const Matrix4& inMatrix) const;

    /**
     * @brief    Not equal.
     * @param    inMatrix    The matrix.
     * @return   Returns true if is not equal.
     */
    bool
    operator!=(const Matrix4& inMatrix) const;

    /**
     * @brief    Inverse matrix.
     * @return   Returns the inverse matrix.
     */
    Matrix4
    inverse() const;

    /**
     * @brief    Determinant of a matrix.
     * @return   Returns the determinant.
     */
    float
    determinant() const;

    /**
     * @brief    Info of the function.
     * @return   Returns the transpose of the matrix.
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
     * @brief    Negate every value of the matrix.
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

  /**
   * @class    lookToLH.
   * @brief    For generate the lookAt Matrix in LH.
   */
  class GI_UTILITY_EXPORT lookToLH : public Matrix4
  {
   public:
    lookToLH(Vector4 inEyePos,
             Vector4 inEyeDirection,
             Vector4 inUpDirection);
  };

  /**
   * @class    perspectiveFovLH.
   * @brief    For generate the perspective matrix.
   */
  class GI_UTILITY_EXPORT perspectiveFovLH : public Matrix4
  {
   public:
    perspectiveFovLH(float inFov,
                     float inAR,
                     float inNear,
                     float inFar);
  };

  /**
   * @class    matrixRotationX.
   * @brief    For generate a rotation in a matrix.
   */
  class GI_UTILITY_EXPORT matrixRotationX : public Matrix4
  {
   public:
    matrixRotationX(float inAngle);
  };

  /**
   * @class    matrixRotationY.
   * @brief    For generate a rotation in a matrix.
   */
  class GI_UTILITY_EXPORT matrixRotationY : public Matrix4
  {
   public:
    matrixRotationY(float inAngle);
  };

  /**
   * @class    matrixRotationZ.
   * @brief    For generate a rotation in a matrix.
   */
  class GI_UTILITY_EXPORT matrixRotationZ : public Matrix4
  {
   public:
    matrixRotationZ(float inAngle);
  };

  /**
   * @class    matrixTranslation.
   * @brief    For generate translation in a matrix.
   */
  class GI_UTILITY_EXPORT matrixTranslation : public Matrix4
  {
   public:
    matrixTranslation(Vector3 inVector);
  };
}