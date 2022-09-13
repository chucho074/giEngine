/**
 * @file    giSceneNode.h
 * @author  Jesus Alberto Del Moral Cupil
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
#include "giActor.h"

namespace giEngineSDK {
  /**
   * @class    SceneNode.
   * @brief    .   
   */
  class GI_CORE_EXPORT SceneNode
  {
  public:
    //Default Constructor.
    SceneNode();

    //Destructor.
    ~SceneNode();

    /**
     * @brief    .
     * @param    inID 
     */
    SharedPtr<Actor>
    getActorByID(const uint32& inID);

    /**
     * @brief    .
     * @param    inName 
     */
    SharedPtr<Actor>
    getActorByName(const String& inName);

    /**
     * @brief    .
     * @param    inParent
     */
    List<SharedPtr<SceneNode>>&
    getNodesByParent(WeakPtr<SceneNode> inParent);

    /**
     * @brief   Delete that actor, asign the childs to the parent.
     */
    void
    deleteActor(const SharedPtr<Actor>& inActor);

    /**
     * @brief    
     * @param    inDeltaTime 
     */
    void
    udpate(float inDeltaTime);

    /**
     * @brief    
     */
    void
    render();

    WeakPtr<SceneNode> m_parent;

    List<SharedPtr<SceneNode>> m_childs;

    SharedPtr<Actor> m_actor;

  };
}