/**
 * @file    giActor.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    10/06/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesUtilities.h"
#include "giObject.h"
#include "giTransform.h"
#include "giComponent.h"



namespace giEngineSDK {

  /**
   * @class    Actor.
   * @brief    .
   * @bug      No known Bugs.
   */
  class Actor : public Object
  {
   public:
    //Default Constructor.
    Actor() = default;
    //Destructor.
    virtual 
    ~Actor() = default;

    bool
    addComponent(Component inComponent);


    Transform m_transform;

    Map<String, SharedPtr<Component>> m_components;
   protected:


   private:

  };


}