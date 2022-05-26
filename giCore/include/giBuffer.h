/**
 * @file    giBuffer.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/03/2021
 * @brief   Everything about buffers.
 * @bug     No known Bugs.
 */

/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"

namespace giEngineSDK {
  /**
   * @struct   BufferDesc.
   * @brief    For the buffer information.
   * @bug      No known Bugs.
   */
  struct BufferDesc {
    uint32 byteWidth = 0;
    unsigned short usage = 0;
    uint32 bindFlags = 0;
    uint32 startSlot = 0;
    uint32 numBuffers = 0;
    uint32 CPUAccessFlags = 0;
    uint32 stride = 0;
    uint32 offset = 0;
    void* SRD = nullptr;
    uint32 memPitch = 0;
    uint32 memSlicePitch = 0;
  };

  
  /**
   * @class    Buffer.
   * @brief    A buffer interface for own buffers.
   * @bug      No known Bugs.
   */
  class Buffer {
  public:
    ///Specific constructor
    Buffer() = default;
  
    ///Destructor
    virtual 
    ~Buffer() = default;
  
  };
}