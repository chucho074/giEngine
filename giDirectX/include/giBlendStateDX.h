/**
 * @file    giBlendStateDX.h
 * @author  Jes�s Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    04/11/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include <giBlendState.h>
#include "giPrerequisitesDX.h"

namespace giEngineSDK {
  class BlendStateDX : public BlendState
  {
   public:
    //Default Constructor
  	BlendStateDX() = default;

    //Destructor
  	~BlendStateDX() {
      SAFE_RELEASE(m_blendState);
    };

    ID3D11BlendState * m_blendState;
  };
}