/**
 * @file    giTexture2DOGL.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    21/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesOGL.h"
#include <giTexture2D.h>

namespace giEngineSDK {
  /**
   * @class    Texture2DOGL.
   * @brief    .
   * @bug      No known Bugs.
   */
  class Texture2DOGL : public Texture2D
  {
   public:
    //Default Constructor.
    Texture2DOGL() = default;
    //Destructor.
    ~Texture2DOGL() {
      if (0 != m_texture && 0 != m_bufferFrame) {
        glDeleteTextures(1, &m_texture);
        glDeleteFramebuffers(1, &m_bufferFrame);
      }
    }

    //The texture
    uint32 m_texture;

    //The frame for draw the texture
    uint32 m_bufferFrame;
  };
} 