/**
 * @file    giStaticMesh.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    17/08/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giStaticMesh.h"

namespace giEngineSDK {
  
  void 
  StaticMesh::update(float inDeltaTime) {
    
  }

  void 
  StaticMesh::render() {
    m_model->drawModel();
  }
  
  void 
  StaticMesh::setModel(SharedPtr<Model> inModel) {
    m_model = inModel;
  }
}