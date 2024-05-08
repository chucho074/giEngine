/**
 * @file    giModel.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/04/2021
 * @brief   For load models.
 */
 
/**
 * @include
 */
#include "giModel.h"

namespace giEngineSDK {

  Model::~Model() {
    unload();
  }

  void 
  Model::unload() {
    while (!m_meshes.empty()) {
      m_meshes.at(0)->destroy();
    }
  }

  void 
  Model::drawModel() {

    //Draw every mesh into the map
    for (uint32 i = 0; i < m_meshes.size(); i++) {
      m_meshes[i]->drawMesh();
    }
  }
}