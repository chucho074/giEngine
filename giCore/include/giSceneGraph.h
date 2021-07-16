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

namespace giEngineSDK {

  /**
   * @class    SceneGraph.
   * @brief    .
   * @bug      No known Bugs.
   */
  class GI_CORE_EXPORT SceneGraph
  {
   public:
    //Default Constructor.
    SceneGraph();

    //Destructor.
    ~SceneGraph();

    /**
     * @brief    .
     * @param    inActor 
     */
    void
    addActor(const SharedPtr<Actor>& inActor);

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

    

   protected:


   private:

    /**
     * @brief    The root of the Scenex.
     */
    SharedPtr<SceneNode> m_root;


  };

}
