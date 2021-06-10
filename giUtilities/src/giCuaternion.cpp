/**
 * @file    giCuaternion.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    04/06/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giCuaternion.h"
#include "giVector3.h"

namespace giEngineSDK {

  Quaternion::Quaternion(const Vector3& inVector, const float inScalar) {
    m_X = inVector.x;
    m_Y = inVector.y;
    m_Z = inVector.z;
    m_W = inScalar;
  }

  Quaternion 
  Quaternion::operator+(const Quaternion& inOterQuat) {
    return Quaternion(inOterQuat.m_X + m_X, 
    /****************/inOterQuat.m_Y + m_Y, 
    /****************/inOterQuat.m_Z + m_Z, 
    /****************/inOterQuat.m_W + m_W);
  }
  
  Quaternion 
  Quaternion::operator-(const Quaternion& inOterQuat) {
    return Quaternion(inOterQuat.m_X - m_X, 
    /****************/inOterQuat.m_Y - m_Y, 
    /****************/inOterQuat.m_Z - m_Z, 
    /****************/inOterQuat.m_W - m_W);
  }

  Quaternion
  Quaternion::operator*(const Quaternion& inOterQuat) {
    
    Vector3 tmpVecA (m_X, m_Y, m_Z);
    Vector3 tmpVecB (inOterQuat.m_X, inOterQuat.m_Y, inOterQuat.m_Z);

    float tmpDot = tmpVecA.dotProd(tmpVecB);
    float tmpCross = tmpVecA.crossProd(tmpVecB);

    Vector3 tmpVecRes = (tmpVecB * m_W) + (tmpVecA * inOterQuat.m_W) + tmpCross;

    return Quaternion(tmpVecRes, ((m_W * inOterQuat.m_W) - tmpCross));
  }

  Quaternion
  Quaternion::operator*(const float inScalar) {
    return Quaternion((Vector3(m_X, m_Y, m_Z) * inScalar), (inScalar * m_W));
  }

  Quaternion
  Quaternion::normalize() {
    float tmpMag = sqrtf(powf(m_X, 2) + powf(m_Y, 2) + powf(m_Z, 2) + powf(m_W, 2));

    if (tmpMag > 0) {
      float tmpValue = 1.0f / tmpMag;
      m_X *= tmpValue;
      m_Y *= tmpValue;
      m_Z *= tmpValue;
      m_W *= tmpValue;
    }
    else {
      m_X = 0.0f;
      m_Y = 0.0f;
      m_Z = 0.0f;
      m_W = 0.0f;
    }

    return *this;
  }
}