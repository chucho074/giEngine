/**
 * @file    giSceneGraph.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    10/06/2021
 * @brief   An implementation of a Scene Graph.
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
   * @brief    An implementation of a Scene Graph.   
   */
  class GI_CORE_EXPORT SceneGraph : public Module<SceneGraph>
  {
   public:
    //Default Constructor.
    SceneGraph();

    //Destructor.
    ~SceneGraph() = default;

    /**
     * @brief    Adds an actor to the list.
     * @param    inActor       The actor reference to add.
     * @param    inParent      The parent to atatch the actor.
     */
    void
    addActor(const SharedPtr<Actor>& inActor, 
             SharedPtr<SceneNode> inParent);

    /**
     * @brief    Gets any actor by its ID.
     * @param    inID          The ID of the actor.
     */
    SharedPtr<Actor>
    getActorByID(const uint32& inID);

    /**
     * @brief    Gets the actor by its name.
     * @param    inName        The name of the actor.
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
     * @brief    Gets a list of actors by the parent.
     * @param    inParent      The reference of the parent to search.
     */
    List<SharedPtr<SceneNode>>
    getNodesByParent(WeakPtr<SceneNode> inParent);

    /**
     * @brief    Gets the root of the scene.
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
     * @param    inDelta       The delta time.
     */
    void
    update(float inDelta);

    /**
     * @brief    Draw every actor.
     */
    void 
    draw();

    /**
     * @brief    Gets the selected actor.
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

    /**
     * @brief    Clears the list of actors of the Graph.
     */
    void
    clearGraph();

   private:

    /**
     * @brief    The root of the Scene.
     */
    SharedPtr<SceneNode> m_root;

    /**
     * @brief    The actor selected in the scene.
     */
    SharedPtr<Actor> m_selectedActor;

   public:
    
    /**
     * @brief    The name of the active Scene Graph.
     */
    String m_sceneName = "Untitled scene";

    /**
     * @brief    The ID of the scene.
     */
    UUID m_sceneID;

    /**
     * @brief    The number of the actors.
     */
    uint32 m_numActors;

   protected:

    friend class Omni;
    
  };

  GI_CORE_EXPORT SceneGraph&
  g_sceneGraph();

}