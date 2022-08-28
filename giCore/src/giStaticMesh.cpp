/**
 * @file    giStaticMesh.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    17/08/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giStaticMesh.h"
#include "giResourceManager.h"

namespace giEngineSDK {
  
  void 
  StaticMesh::update(float inDeltaTime) {
    GI_UNREFERENCED_PARAMETER(inDeltaTime);
  }

  void 
  StaticMesh::render() {
    auto& RM = g_resourceManager().instance();

    RM.renderResource(m_model);
  }
  
  ResourceRef 
  StaticMesh::getModel() {
      return m_model;
  }
}