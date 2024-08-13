/**
 * @file    giTexture.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    26/7/2024
 * @brief   A basic Texture implementation.
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
  
  namespace TEXTURE_TYPE {
    enum E {
      kUnknown = 0,
      kAlbedo,
      kDiffuse,
      kShininess,
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

  class Texture {
   public:
    Texture() {
      m_texture = make_shared<Texture2D>();
      m_samplerState = make_shared<SamplerState>();
    }

    ~Texture() {
      unload();
    }

    void 
    unload() {
      m_texture.reset();
      m_samplerState.reset();
    }

    //The name of the Texture
    String m_name;
    
    //The tupe of the Texture.
    TEXTURE_TYPE::E m_type = TEXTURE_TYPE::kUnknown;

    //The path of the file.
    Path m_path;

    //The texture.
    SharedPtr<Texture2D> m_texture;

    //The sampler for the texture.
    SharedPtr<SamplerState> m_samplerState;
  };
}
