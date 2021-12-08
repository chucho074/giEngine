/**
 * @file    giDepthStateDX
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/08/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesDX.h"
#include <giDepthState.h>
namespace giEngineSDK {

  class DepthStateDX final : public BaseDepthStencilState
  {
   public:
    //Default constructor
    DepthStateDX() = default;

    //Destructor
    ~DepthStateDX() {
      SAFE_RELEASE(m_State);
    }

    

    //Depth Stencil State
    ID3D11DepthStencilState * m_State;
  };
}