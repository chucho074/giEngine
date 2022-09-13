/**
 * @file    giInputLayoutOGL.h
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
#include "giInputLayout.h"

namespace giEngineSDK {
  /**
   * @class    InputLayoutOGL.
   * @brief    .   
   */
  class InputLayoutOGL : public InputLayout
  {
   public:
    //Default Constructor.
    InputLayoutOGL() = default;
    //Destructor.
    ~InputLayoutOGL() {
      glDeleteVertexArrays(1, &m_vao);
    }

    uint32 m_vao;
  };
}