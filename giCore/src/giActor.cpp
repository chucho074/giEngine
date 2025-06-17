/**
 * @file    giActor.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/07/2021
 * @brief   A basic Actors Objects implementation.
 */
 
/**
 * @include
 */
#include "giActor.h"
#include "giBaseRenderer.h"
#include "giCamera.h"

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


  Actor::~Actor() {
    destroy();
  }

  bool
  Actor::addComponent(SharedPtr<Component> inComponent, 
                      COMPONENT_TYPE::E inComponentType) {
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
        if(components.first == COMPONENT_TYPE::kLightCamera) {
          auto camera = static_pointer_cast<Camera>(components.second);
          auto pos = m_transform.m_translation;
          camera->setPosition({pos.x, pos.y, pos.z, 0}, {0, 0, 0, 0}, {0, 1, 0, 0});
        }
        components.second->update(inDeltaTime);
      }
    }
  }

  void 
  Actor::render() {
    auto& renderer = g_renderer();
    auto tmpMatrix = m_transform.getMatrix();
    renderer.setTransform(tmpMatrix);

    if(!m_components.empty()) {
      for (auto components : m_components) {
        components.second->render();
      }
    }
  }

  void 
  Actor::destroy() {
    for (auto iterComp : m_components) {
      iterComp.second->destroy();
    }
    m_components.clear();
  }

  SharedPtr<Component>&
  Actor::getComponent(COMPONENT_TYPE::E inComponent) {
    auto tmp = m_components.find(inComponent);
    
    return tmp->second;
  }

  bool 
  Actor::hasComponent(COMPONENT_TYPE::E inComponent) const {
    if (m_components.count(inComponent) > 0) {
      return true;
    }
    else {
      return false;
    }
  }

}