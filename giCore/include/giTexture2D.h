/**
 * @file     giTexture2D.h
 * @author   Jesus Alberto Del Moral Cupil
 * @e        idv18c.jmoral@uartesdigitales.edu.mx
 * @date     10/03/2021
 * @brief    Management of the Textures. 
 */

/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"

namespace giEngineSDK {
  /**
   * @struct  TextureDesc.
   * @brief   Data to the Textures.
 
   */
  struct TextureDesc {
    uint32 W;
    uint32 H;
    uint32 mipLevels;
    uint32 arraySize;
    uint32 format;
    uint32 sampleDescCount;
    uint32 sampleDescQuality;
    uint32 usage;
    uint32 flags;
    uint32 cpuAccessFlags;
    uint32 miscFlags;
  };  

  /**
   * @class   Texutre2D.
   * @brief   Management for textures2D.
   */
  class Texture2D {
   public:
     /**
      * @brief   Constructor.
      */
     Texture2D() = default;
     
     /**
      * @brief    Destructor.
      */
     virtual
     ~Texture2D() = default;

     /**
      * @brief    Getter for the texture as void*.
      * @return   The texture of the specific API.
      */
     virtual void *
     getApiTexture() {
       return nullptr;
     };
     
     
   protected:
     friend class CGraphicsAPI;
  
  };
}