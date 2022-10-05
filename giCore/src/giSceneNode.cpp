/**
 * @file    giSceneNode.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    16/07/2021
 * @brief   A implementation of a Node of a Scene.
 */
 
/**
 * @include
 */
#include "giSceneNode.h"

namespace giEngineSDK {

  SceneNode::SceneNode() {

  }

  SharedPtr<Actor>
  SceneNode::getActorByID(const int32& inID) {
    
    if (m_actor->m_actorId == inID) {
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
  SceneNode::getActorByName(StringView inName) {
    // TODO: Read this node, in case is == inName return this
    //       otherwise read the childs list and serch it.
    if (inName == m_actor->m_actorName) {
      return m_actor;
    }
    else {
      for (auto nodes : m_childs) {
        auto tmpActor = nodes->getActorByName(inName);
        if(nullptr != tmpActor) {
          auto tmpName = tmpActor->m_actorName;
          if (inName == tmpName) {
            return tmpActor;
          }
        }
      }
    }
    return nullptr;
  }

  List<SharedPtr<SceneNode>>
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
        
        if (!tmpListNodes.empty() && (inParent.lock()->m_parent.lock() == nodes->m_parent.lock())) {
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

  void 
  SceneNode::destroy() {
    m_actor->destroy();
    m_parent.reset();
    for(auto iterChilds : m_childs) {
      iterChilds->destroy();
    }
    m_childs.clear();
  }

}
