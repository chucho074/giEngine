/**
 * @file    giResourceManager.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/05/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giResourceManager.h"

namespace giEngineSDK {

  WeakPtr<Material> 
  ResourceManager::getMaterialByID(uint32 inID) {
    return m_materials.find(inID)->second;
  }

}