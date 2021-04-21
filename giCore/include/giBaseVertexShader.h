/**
 * @file    giBaseVertexShader.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/04/2021
 * @brief   A basic Vertex Shader.
 * @bug     No known Bugs.
 */

 /**
  * @include
  */
#pragma once
#include "giPrerequisitesCore.h"
#include "giBaseShader.h"

namespace giEngineSDK {
  /**
   * @class    BaseVertexShader.
   * @brief    A base for the Vertex Shaders.
   */
  class BaseVertexShader : public BaseShader
  {
   public:
    //Constructor
    BaseVertexShader() = default;

    //Destructor
    virtual
    ~BaseVertexShader() {};


  };
}
