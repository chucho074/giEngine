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
    unsigned int W;
    unsigned int H;
    unsigned int mipLevels;
    unsigned int arraySize;
    unsigned int format;
    unsigned int sampleDescCount;
    unsigned int sampleDescQuality;
    unsigned int usage;
    unsigned int flags;
    unsigned int cpuAccessFlags;
    unsigned int miscFlags;
  };
  
  /**
   * @class   CTexutre2D.
   * @brief   Management for textures2D.
   * @bug     No known Bugs.
   */
  class CTexture2D {
   public:
     /**
      * @brief  Constructor.
      * @bug    No Bugs known.
      */
     CTexture2D() {};
     
     /**
      * @brief    Destructor.
      * @bug      No Bugs known.
      */
     ~CTexture2D() {};
     
     
   protected:
     friend class CGraphicsAPI;
  
  
   private:
  };
}