/**
 * @file    giActor.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/07/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giActor.h"

namespace giEngineSDK {

  //bool
  //Actor::addComponent(COMPONENT_TYPE::E inComponentType) {
  //  //Check if the component exist.
  //  if(m_components.count(inComponentType) == 0) {
  //    auto tmpComponent = std::pair<COMPONENT_TYPE::E, SharedPtr<Component>>();
  //    m_components.insert(tmpComponent);

  //  }
  //  return false;
  //}

  Actor::Actor() {
    
  }

  bool
  Actor::addComponent(SharedPtr<Component> inComponent, COMPONENT_TYPE::E inComponentType) {
    if (m_components.count(inComponentType) == 0) {
      auto tmpComponent = std::pair<COMPONENT_TYPE::E, SharedPtr<Component>>();
      tmpComponent.first = inComponentType;
      tmpComponent.second = inComponent;
      m_components.insert(tmpComponent);
      if(inComponentType == COMPONENT_TYPE::kStaticMesh) {
        isStaticMesh = true;
      }
    }
    return false;
  }

  void
  Actor::update(float inDeltaTime) {
    if (!m_components.empty()) {
      for (auto components : m_components) {
        components.second->update(inDeltaTime);
      }
    }
  }

  void 
  Actor::render() {
    

    if(!m_components.empty()) {
      for (auto components : m_components) {
        components.second->render();
      }
    }
  }

  SharedPtr<Component>& 
  Actor::getComponent(COMPONENT_TYPE::E inComponent) {
    auto tmp = m_components.find(inComponent);
    
    return tmp->second;
  }

}