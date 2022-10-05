/**
 * @file    giSceneNode.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    10/06/2021
 * @brief   A implementation of a Node of a Scene.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesUtilities.h"
#include "giActor.h"
#include "giUUID.h"

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
    ~SceneNode() = default;

    /**
     * @brief    Gets an actor by an ID.
     * @param    inID          The ID to search.
     */
    SharedPtr<Actor>
    getActorByID(const int32& inID);

    /**
     * @brief    Gets an actor by its name.
     * @param    inName        The name of the actor to search.
     */
    SharedPtr<Actor>
    getActorByName(StringView inName);

    /**
     * @brief    Gets a list of nodes by it parent.
     * @param    inParent      The parent to search in the parent of the nodes.
     */
    List<SharedPtr<SceneNode>>
    getNodesByParent(WeakPtr<SceneNode> inParent);

    /**
     * @brief    Delete that actor, asign the childs to the parent.
     */
    void
    deleteActor(const SharedPtr<Actor>& inActor);

    /**
     * @brief    Updates the information of the node.
     * @param    inDeltaTime   The delta Time.
     */
    void
    udpate(float inDeltaTime);

    /**
     * @brief    Renders the actor of the node.
     */
    void
    render();

    /**
     * @brief    Destroys the information of the Node.
     */
    void
    destroy();

    WeakPtr<SceneNode> m_parent;

    List<SharedPtr<SceneNode>> m_childs;

    SharedPtr<Actor> m_actor;

    UUID m_nodeId;
  };
}