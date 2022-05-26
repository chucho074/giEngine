/**
 * @file    giMaterial.h
 * @author  Jesus Alberto Del Moral Cupil
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
    uint32 id;              //The id in the proyect.
    String type;            //The type of the texture.
    String path;            //The path of the file.
    Texture2D * texture;    //The texture.
    SamplerState * samplerState; //The sampler for the texture.
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

    Vector<Texture> m_textures;

  };
}