/**
 * @file    giMaterial.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    15/08/2021
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giResourceManager.h"
#include "giResource.h"
#include "giTexture2D.h"
#include "giTexture.h"  
#include "giSampler.h"  

namespace giEngineSDK {
  
  namespace MATERIAL_FLAGS {
    enum E {
      kTWO_SIDES
    };
  }

  /**
   * @class   Material.
   */
  class Material final : public Resource
  {
   public:
    //Default Constructor
    Material() = default;

    //Destructor
    ~Material() = default;

    /**
     * @brief    Unload the material.     
     */
    void
    unload() override {};


    Vector<ResourceRef> m_textures;


    MATERIAL_FLAGS::E m_flags;

  };
}