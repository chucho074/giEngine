/**
 * @file    giActor.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    10/06/2021
 * @brief   A basic Actors Objects implementation.
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
   * @brief    A basic Actors Objects implementation.
   */
  class GI_CORE_EXPORT Actor final : public Object
  {
   public:
    //Default Constructor.
    Actor() = default;

    //Destructor.
    ~Actor();

    
    /**
     * @brief    Adds a component to the actor.
     * @param    inComponent       The component to add.
     * @param    inComponentType   The type of the component to add.
     * @return   Returns true if the component has been added correctly.
     */
    bool
    addComponent(SharedPtr<Component> inComponent, 
                 COMPONENT_TYPE::E inComponentType);

    /**
     * @brief    Updates (if needed) the information of the actor.
     * @param    inDeltaTime   The deltaTime.
     */
    void
    update(float inDeltaTime);

    /**
     * @brief    Renders (if needed) the information of the actor.
     */
    void
    render();

    /**
     * @brief    Destroys the information of the current actor.
     */
    void
    destroy();

    /**
     * @brief    Get a component from the actor by type.
     * @param    inComponent   The type of the component to get.
     * @return   Returns the component
     */
    SharedPtr<Component>&
    getComponent(COMPONENT_TYPE::E inComponent);

   //protected:

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
    int32 m_actorId = 0;
    
    /**
     * @brief    Base Transform for the actor.
     */
    Transform m_transform;

    /**
     * @brief    Flag if contains a static mesh component.
     */
    bool isStaticMesh = false;

    /**
     * @brief    The reference of thte actor in a Omniverse scene.
     */
    String m_omniRefPath = "";
    

    friend class Encoder;
  };
}