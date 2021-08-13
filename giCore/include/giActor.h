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
#include "giComponent.h"
#include <giTransform.h>

namespace giEngineSDK {

  /**
   * @class    Actor.
   * @brief    .
   * @bug      No known Bugs.
   */
  class GI_CORE_EXPORT Actor final : public Object
  {
   public:
    //Default Constructor.
    Actor() = default;

    //Destructor.
    ~Actor() = default;

    /**
     * @brief    
     * @param    inComponentType  .
     * @return 
     */
    bool
    addComponent(COMPONENT_TYPE::E inComponentType);

    /**
     * @brief 
     * @param    inDeltaTime 
     */
    void
    update(float inDeltaTime);

    /**
     * @brief    .
     */
    void
    render();

    /**
     * @brief    Get a component from the actor by type.
     * @param    inComponent 
     * @return   Returns the component
     */
    SharedPtr<Component> &
    getComponent(COMPONENT_TYPE::E inComponent);

   protected:

    /**
     * @brief    Components in the actor.
     */
    Map<COMPONENT_TYPE::E, SharedPtr<Component>> m_components;

   public:

    /**
     * @brief    The actor name.
     */
    String m_actorName = "Empty Actor";

    /**
     * @brief    The general id for the actor.
     */
    int32 m_actorId;
    
    /**
     * @brief    Base Transform for the actor.
     */
    Transform m_transform;
  };
}