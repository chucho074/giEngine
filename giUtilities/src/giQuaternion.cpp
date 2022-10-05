/**
 * @file    giCuaternion.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    04/06/2021
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giQuaternion.h"
#include "giVector3.h"

namespace giEngineSDK {

  const Quaternion Quaternion::IDENTITY = Quaternion(0.f, 0.f, 0.f, 1.f);

  Quaternion::Quaternion(const Vector3& inVector, const float inScalar) {
    x = inVector.x;
    y = inVector.y;
    z = inVector.z;
    w = inScalar;
  }

  Quaternion 
  Quaternion::operator+(const Quaternion& inOterQuat) {
    return Quaternion(inOterQuat.x + x, 
                      inOterQuat.y + y,
                      inOterQuat.z + z,
                      inOterQuat.w + w);
  }
  
  Quaternion 
  Quaternion::operator-(const Quaternion& inOterQuat) {
    return Quaternion(inOterQuat.x - x, 
                      inOterQuat.y - y, 
                      inOterQuat.z - z, 
                      inOterQuat.w - w);
  }

  Quaternion
  Quaternion::operator*(const Quaternion& inOterQuat) {
    
    Vector3 tmpVecA (x, y, z);
    Vector3 tmpVecB (inOterQuat.x, inOterQuat.y, inOterQuat.z);

    //float tmpDot = tmpVecA.dotProd(tmpVecB);
    float tmpCross = tmpVecA.crossProd(tmpVecB);

    Vector3 tmpVecRes = (tmpVecB * w) + (tmpVecA * inOterQuat.w) + tmpCross;

    return Quaternion(tmpVecRes, ((w * inOterQuat.w) - tmpCross));
  }

  Quaternion
  Quaternion::operator*(const float inScalar) {
    return Quaternion((Vector3(x, y, z) * inScalar), (inScalar * w));
  }

  Quaternion
  Quaternion::normalize() {
    float tmpMag = sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2) + powf(w, 2));

    if (tmpMag > 0) {
      float tmpValue = 1.0f / tmpMag;
      x *= tmpValue;
      y *= tmpValue;
      z *= tmpValue;
      w *= tmpValue;
    }
    else {
      x = 0.0f;
      y = 0.0f;
      z = 0.0f;
      w = 0.0f;
    }

    return *this;
  }
  
  Matrix4 
  Quaternion::getMatrix() {
    Matrix4 rotMatrix;

    //
    rotMatrix.m_xColumn.x = 2 * (x * x + y * y) - 1;
    rotMatrix.m_xColumn.y = 2 * (y * z - x * w);
    rotMatrix.m_xColumn.z = 2 * (y * w - x * z);

    //
    rotMatrix.m_yColumn.x = 2 * (y * z - x * w);
    rotMatrix.m_yColumn.y = 2 * (x * x + z * z) - 1;
    rotMatrix.m_yColumn.z = 2 * (z * w + x * y);

    //
    rotMatrix.m_zColumn.x = 2 * (y * w + x * z);
    rotMatrix.m_zColumn.y = 2 * (z * w - x * y);
    rotMatrix.m_zColumn.z = 2 * (x * x + w * w) - 1;

    rotMatrix.m_wColumn.w = 1;

    return rotMatrix;
  }
}