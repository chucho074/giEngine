/**
 * @file    giSceneGraph.h
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
#include "giActor.h"
#include "giSceneNode.h"
#include <giModule.h>


namespace giEngineSDK {

  /**
   * @class    SceneGraph.
   * @brief    .
   * @bug      No known Bugs.
   */
  class GI_CORE_EXPORT SceneGraph : public Module<SceneGraph>
  {
   public:
    //Default Constructor.
    SceneGraph();

    //Destructor.
    ~SceneGraph() = default;

    /**
     * @brief    .
     * @param    inActor 
     */
    void
    addActor(const SharedPtr<Actor>& inActor, SharedPtr<SceneNode> inParent);

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

    SharedPtr<SceneNode>
    getRoot();

    /**
     * @brief    Delete that actor, asign the childs to the parent.
     */
    void
    deleteActor(const SharedPtr<Actor>& inActor);

    /**
     * @brief    Update every actor.
     * @param    inDelta 
     */
    void
    update(float inDelta);

    /**
     * @brief    Draw every actor.
     */
    void 
    draw();


   private:

    /**
     * @brief    The root of the Scene.
     */
    SharedPtr<SceneNode> m_root;

   protected:
    /**
     * @brief    The number of the actors.
     */
    uint32 m_numActors;

    friend class Omni;
    
  };

  SceneGraph& 
  g_sceneGraph();

}