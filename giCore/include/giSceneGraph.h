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
  class SceneGraph
  {
   public:
    //Default Constructor.
    SceneGraph();
    //Destructor.
    ~SceneGraph();

    void
    addActor(const SharedPtr<Actor>& inActor);



    UniquePtr<SceneNode> m_root;

   protected:


   private:

  };

}


//Se recorre en deep