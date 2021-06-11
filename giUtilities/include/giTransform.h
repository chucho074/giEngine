/**
 * @file    giTransform.h
 * @author  Jesús Alberto Del Moral Cupil
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

namespace giEngineSDK {
  /**
* @class    Transform.
* @brief    .
* @bug      No known Bugs.
*/
  class Transform
  {
   public:
    //Default Constructor.
    Transform();
    //Destructor.
    ~Transform();

   protected:


   private:
    Quaternion m_rotation = Quaternion::IDENTITY;
    
    Vector3 m_translation = Vector3::ZERO;
    
    Vector3 m_scale = Vector3::UNIT;
  };

}
