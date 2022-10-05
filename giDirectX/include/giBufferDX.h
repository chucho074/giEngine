/**
 * @file    giBufferDX.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    05/03/2021
 * @brief   Everything about buffers for DX.
 */

/**
 * @include
 */
#pragma once
#include "giPrerequisitesDX.h"
#include <giBuffer.h>

/**
 * @class    BufferDX.
 * @brief    A buffer interface for own buffers for DX. 
 */
namespace giEngineSDK {
  class BufferDX final : public Buffer
  {
   public:
    ///Specific constructor
    BufferDX() {
    
    };
  
    ///Destructor
    ~BufferDX() {
      SAFE_RELEASE(m_buffer);
    };
  
   
    //Access to the DirectX Buffers
    ID3D11Buffer * m_buffer = nullptr;
    //UAV
    ID3D11UnorderedAccessView * m_UAV;
  };
}