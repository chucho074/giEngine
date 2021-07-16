/**
 * @file    giSceneNode.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    16/07/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giSceneNode.h"

namespace giEngineSDK {

  SceneNode::SceneNode() {

  }

  SceneNode::~SceneNode() {

  }

  void 
  SceneNode::udpate(float inDeltaTime) {
    m_actor.lock()->update(inDeltaTime);

    for(auto nodes : m_childs) {
      nodes.lock()->udpate(inDeltaTime);
    }
  }

  void 
  SceneNode::render() {
    m_actor.lock()->render();

    for(auto nodes : m_childs) {
      nodes.lock()->render();
    }

  }
}
