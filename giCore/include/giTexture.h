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
  class Texture final : public Resource
  {
   public:
    Texture() = default;

  	~Texture() = default;

    void
    unload() override {};

    //The id in the proyect.
    uint32 id;                            
    //The type of the texture.
    String type;                          
    //The path of the file.
    String path;                          
    //The texture.
    SharedPtr<Texture2D> texture;         
    //The sampler for the texture.
    SharedPtr<SamplerState> samplerState; 
  };
}