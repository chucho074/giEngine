/**
 * @file    giSceneNode.h
 * @author  Jes�s Alberto Del Moral Cupil
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
* @bug      No known Bugs.
*/
  class SceneNode
  {
  public:
    //Default Constructor.
    SceneNode();
    //Destructor.
    ~SceneNode();


    WeakPtr<SceneNode> m_parent;

    List<WeakPtr<SceneNode>> m_childs;

    WeakPtr<Actor> m_actor;
  protected:


  private:

  };


}