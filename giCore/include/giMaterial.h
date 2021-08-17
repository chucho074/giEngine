/**
 * @file    giMaterial.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    15/08/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giResource.h"
#include "giTexture2D.h"
#include "giSampler.h"  

namespace giEngineSDK {

  /**
   * @struct   Texture.
   */
  struct Texture {
    uint32 id;
    String type;
    String path;
    Texture2D * texture;
    Sampler * samplerState;
  };
  
  /**
   * @class   Material.
   */
  class Material : Resource
  {
   public:
    //Default Constructor
    Material() = default;

    //Destructor
    ~Material() = default;

   protected:

    Map<uint32, Texture> m_textures;

  };
}