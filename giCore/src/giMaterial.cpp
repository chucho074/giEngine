/**
 * @file    giMaterial.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       edgv24c.jmoral@uartesdigitales.edu.mx
 * @date    08/5/2025
 */

/**
 * @include
 */
#include "giMaterial.h"
#include "giResourceManager.h"

namespace giEngineSDK {

  void 
  Material::render() {
    auto& RM = g_resourceManager();

    //Get the material constant buffer
    MaterialConstantBuffer tmpMaterialCB;

    //Set the values of the material
    tmpMaterialCB.AlbedoColor      = m_albedoColor;
    tmpMaterialCB.EmissiveColor    = m_emissiveColor;
    tmpMaterialCB.metalic          = m_metalic;
    tmpMaterialCB.roughness        = m_roughness;
    tmpMaterialCB.ambientOclussion = m_ambientOclussion;
    tmpMaterialCB.opacity          = m_opacity;
    tmpMaterialCB.gloss            = m_gloss;
    tmpMaterialCB.specular         = m_specular;
    
    //Set the material constant buffer

    
  }
}