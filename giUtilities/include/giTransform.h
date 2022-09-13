/**
 * @file    giTransform.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    11/06/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesUtilities.h"
#include "giQuaternion.h"
#include "giVector3.h"
#include "giMatrix4.h"

namespace giEngineSDK {
  /**
   * @class    Transform.
   * @brief    .   
   */
  class GI_UTILITY_EXPORT Transform
  {
   public:
    //Default Constructor.
    Transform() = default;

    //Destructor.
    ~Transform() = default;

    void
    setScale(Vector3 inScale);

    void
    setRotation(Quaternion inRotation);

    void
    setTranslation(Vector3 inTranslation);

    Matrix4
    getMatrix();

   public:
    Quaternion m_rotationQuat = Quaternion::IDENTITY;
    
    Vector3 m_rotation = Vector3::ZERO;
    
    Vector3 m_translation = Vector3::ZERO;
    
    Vector3 m_scale = Vector3::UNIT;
  };

}
