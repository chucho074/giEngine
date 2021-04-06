/**
* @file    giBuffer.h
* @author  Jesús Alberto Del Moral Cupil
* @e      idv18c.jmoral@uartesdigitales.edu.mx
* @date    18/03/2021
* @brief  Everything about buffers.
* @bug    No known Bugs.
**/

/**
* @include
**/
#pragma once
#include "giPrerequisitesCore.h"

namespace giEngineSDK {
  /**
  * @struct   BufferDesc.
  * @brief    For the buffer information.
  * @bug      No known Bugs.
  **/
  struct BufferDesc {
    unsigned int byteWidth = 0;
    unsigned short usage = 0;
    unsigned int bindFlags = 0;
    unsigned int startSlot = 0;
    unsigned int numBuffers = 0;
    unsigned int CPUAccessFlags = 0;
    unsigned int stride = 0;
    unsigned int offset = 0;
    void* SRD = nullptr;
    unsigned int memPitch = 0;
    unsigned int memSlicePitch = 0;
  };
  
  /**
  * @class    CBuffer.
  * @brief    A buffer interface for own buffers.
  * @bug      No known Bugs.
  **/
  class CBuffer {
  public:
    ///Specific constructor
    CBuffer() = default;
  
    ///Destructor
    virtual ~CBuffer() = 0;
  
  };
}