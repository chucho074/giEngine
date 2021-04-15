/**
 * @file    CBufferDX.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    05/03/2021
 * @brief   Everything about buffers for DX.
 * @bug     No known Bugs.
 */

/**
 * @include
 */
#pragma once
#include "giPrerequisitesDX.h"
#include <giBuffer.h>

/**
 * @class    CBufferDX.
 * @brief    A buffer interface for own buffers for DX.
 * @bug      No known Bugs.
 */
namespace giEngineSDK {
  class CBufferDX final : public CBuffer
  {
   public:
    ///Specific constructor
    CBufferDX() = default;
  
    ///Destructor
    ~CBufferDX() {
      SAFE_RELEASE(m_Buffer);
    };
  
   
    //Access to the DirectX Buffers
    ID3D11Buffer * m_Buffer = nullptr;
  };
}