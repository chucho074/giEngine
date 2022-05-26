/**
 * @file    giBufferOGL.h
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
#include <giBuffer.h>

namespace giEngineSDK {
  /**
   * @class    BufferOGL.
   * @brief    .
   * @bug      No known Bugs.
   */
  class BufferOGL : public Buffer
  {
   public:
    //Default Constructor.
    BufferOGL() = default;
    //Destructor.
    ~BufferOGL() {
      if (0 != m_buffer) {
        glDeleteBuffers(1, &m_buffer);
        m_type = 0;
        m_size = 0;
      }
    };
   
   
     uint32 m_buffer = 0;

     uint32 m_type = 0;

     int32 m_size = 0;
  };
}