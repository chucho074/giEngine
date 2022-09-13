/**
 * @file    giSceneGraph.h
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
#include "giActor.h"
#include "giSceneNode.h"
#include <giModule.h>


namespace giEngineSDK {

  /**
   * @class    SceneGraph.
   * @brief    .   
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
     * @brief    Obtain the actor childs of the root.
     * @return   Returns the list of the actors who there parent is the root.
     */
    Vector<SharedPtr<Actor>>
    getActorsFromRoot();

    /**
     * @brief    .
     * @param    inParent
     */
    List<SharedPtr<SceneNode>>&
    getNodesByParent(WeakPtr<SceneNode> inParent);

    /**
     * @brief    .
     * @return   Returns the root of the scene.
     */
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

    /**
     * @brief    .
     * @return   Get a selected Actor.
     */
    SharedPtr<Actor>
    getSelectedActor() {
      return m_selectedActor;
    }
    
    /**
     * @brief    Set a selected Actor.
     */
    void
    setSelectedActor(SharedPtr<Actor> inActor) {
      m_selectedActor = inActor;
    }

   private:

    /**
     * @brief    The root of the Scene.
     */
    SharedPtr<SceneNode> m_root;

    SharedPtr<Actor> m_selectedActor;

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