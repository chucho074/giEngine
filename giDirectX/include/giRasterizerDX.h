/**
 * @file    giRasterizerDX
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
#include <giRasterizer.h>

namespace giEngineSDK {
  class RasterizerDX final : public Rasterizer
  {
   public:
    //Default constructor
  	RasterizerDX() = default;

    //Destructor
  	~RasterizerDX() {
      SAFE_RELEASE(m_rasterizerState);
    }

    
    ID3D11RasterizerState * m_rasterizerState;
  };
}