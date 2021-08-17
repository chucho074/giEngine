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

  SharedPtr<Actor>
  SceneNode::getActorByID(const uint32& inID) {
    // TODO: Read this node, in case is == inID return this
    //       otherwise read the childs list and serch it.

    if (inID == m_actor->m_actorId) {
      return m_actor;
    }
    else {
      for (auto nodes : m_childs) {
        auto tmpActor = nodes->getActorByID(inID);
        auto tmpID = tmpActor->m_actorId;
        if (inID == tmpID) {
          return tmpActor;
        }
      }
    }
    return nullptr;
  }

  SharedPtr<Actor>
  SceneNode::getActorByName(const String& inName) {
    // TODO: Read this node, in case is == inName return this
    //       otherwise read the childs list and serch it.
    if (inName == m_actor->m_actorName) {
      return m_actor;
    }
    else {
      for (auto nodes : m_childs) {
        auto tmpActor = nodes->getActorByName(inName);
        auto tmpName = tmpActor->m_actorName;
        if (inName == tmpName) {
          return tmpActor;
        }
      }
    }
    return nullptr;
  }

  List<SharedPtr<SceneNode>>&
  SceneNode::getNodesByParent(WeakPtr<SceneNode> inParent) {
    // TODO: Read this node, in case it parent == inParent 
    //       return the parent childs, otherwise read the 
    //       childs list and serch it.
    if (inParent.lock() == m_parent.lock()) {
      return m_parent.lock()->m_childs;
    }
    else {
      for (auto nodes : m_childs) {
        auto tmpListNodes = nodes->getNodesByParent(inParent);
        if (inParent.lock()->m_parent.lock() == nodes->m_parent.lock()) {
          return tmpListNodes;
        }
      }
    }
    return m_childs;
  }

  void 
  SceneNode::deleteActor(const SharedPtr<Actor>& inActor) {
    if (inActor == m_actor) {
      //Reasign the childs to the parent
      for (auto childNode : m_childs) {
        //Asign the new parent to the childs
        childNode->m_parent = m_parent;
        //Asign the new childs to the parent
        m_parent.lock()->m_childs.push_back(childNode);
      }
      m_childs.clear();
    }
    else {
      for (auto nodes : m_childs) {
        nodes->deleteActor(inActor);
      }
    }
  }

  void 
  SceneNode::udpate(float inDeltaTime) {
    m_actor->update(inDeltaTime);

    for(auto nodes : m_childs) {
      nodes->udpate(inDeltaTime);
    }
  }

  void 
  SceneNode::render() {
    m_actor->render();

    for(auto nodes : m_childs) {
      nodes->render();
    }

  }
}
