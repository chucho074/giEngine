/**
 * @file    giTexture.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    12/07/2022
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

namespace giEngineSDK {
  
  namespace TEXTURE_TYPE {
    enum E {
      kUnknown = 0,
      kAlbedo,
      kMetalic,
      kRoughness,
      kAmbientOclussion,
      kNormal,
      kGloss,
      kSpecular,
      kOpacity,
      kSuportedTextureTypes
    };
  }


  class Texture final : public Resource
  {
   public:
    Texture() = default;

  	~Texture() = default;

    void
    unload() override {};

    //The name of the Texture.
    String m_name;

    //The type of the Texture.
    TEXTURE_TYPE::E m_type;

    //The path of the file.
    Path m_path;
    
    //The texture.
    SharedPtr<Texture2D> m_texture;
    
    //The sampler for the texture.
    SharedPtr<SamplerState> m_samplerState;
  };
}