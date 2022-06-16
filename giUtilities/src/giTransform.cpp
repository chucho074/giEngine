/**
 * @file    giTransform.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    15/07/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giTransform.h"

namespace giEngineSDK {
  void
  Transform::setScale(Vector3 inScale) {
    m_scale = inScale;
  }

  void 
  Transform::setRotation(Quaternion inRotation) {
    m_rotationQuat = inRotation;
  }

  void 
  Transform::setTranslation(Vector3 inTranslation) {
    m_translation = inTranslation;
  }

  Matrix4 
  Transform::getMatrix() {
    Matrix4 tmpMatrix;
    tmpMatrix = Matrix4::IDENTITY;
    //Scale
    tmpMatrix.m_xColumn.x = m_scale.x;
    tmpMatrix.m_yColumn.y = m_scale.y;
    tmpMatrix.m_zColumn.z = m_scale.z;
    //Rotation
    //Quaternion tempQuat = Quaternion::fromEuler(m_localRotation);
    //tempQuat.normalize();
    //m_localTransform *= Matrix4::fromQuat(tempQuat);
    //Translation
    tmpMatrix.m_xColumn.w = m_translation.x;
    tmpMatrix.m_yColumn.w = m_translation.y;
    tmpMatrix.m_zColumn.w = m_translation.z;

    return tmpMatrix;
  }
}