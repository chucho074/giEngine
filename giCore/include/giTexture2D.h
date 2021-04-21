/**
 * @file     giTexture2D.h
 * @author   Jesús Alberto Del Moral Cupil
 * @e        idv18c.jmoral@uartesdigitales.edu.mx
 * @date     10/03/2021
 * @brief    Management of the Textures.
 * @bug      No known Bugs.
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
   * @bug     No known Bugs.
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
   * @class   CTexutre2D.
   * @brief   Management for textures2D.
   * @bug     No known Bugs.
   */
  class Texture2D {
   public:
     /**
      * @brief  Constructor.
      * @bug    No Bugs known.
      */
     Texture2D() = default;
     
     /**
      * @brief    Destructor.
      * @bug      No Bugs known.
      */
     virtual
     ~Texture2D() = default;
     
     
   protected:
     friend class CGraphicsAPI;
  
  };
}