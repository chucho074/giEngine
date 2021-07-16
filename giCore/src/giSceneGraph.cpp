/**
 * @file    giSceneGraph.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    16/07/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giSceneGraph.h"

namespace giEngineSDK {
  SceneGraph::SceneGraph() {

  }

  SceneGraph::~SceneGraph() {

  }

  void 
  SceneGraph::addActor(const SharedPtr<Actor>& inActor) {
    
  }

  void 
  SceneGraph::update(float inDelta) {
    m_root->udpate(inDelta);
  }

  void 
  SceneGraph::draw() {
    m_root->render();
  }
}