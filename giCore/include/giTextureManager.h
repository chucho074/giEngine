/**
 * @file    giTextureManager.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    30/07/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giTexture2D.h"

namespace giEngineSDK {

  /**
   * @class    TextureManager.
   * @brief    .
   * @bug      No known Bugs.
   */
  class TextureManager
  {
   public:
    //Default Constructor.
    TextureManager();

    //Destructor.
    ~TextureManager();

    //
    SharedPtr<Texture2D>
    load(const String& inFilePath);

    //
    bool
    isLoaded(const String& inFilePath);

   protected:


   private:

  };


}