/**
 * @file    giBasePixelShader.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/04/2021
 * @brief   A basic Pixel Shader.
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
   * @class     BasePixelShader.
   * @brief     A base shader for pixel.
   */
  class BasePixelShader : public BaseShader
  {
  public:
    //Constructor
    BasePixelShader() {};

    //Destructor
    virtual
    ~BasePixelShader() {};




  };
}
