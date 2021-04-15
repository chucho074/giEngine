/**
 * @file    giViewPortDX.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    15/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesDX.h"
#include <giViewPort.h>

namespace giEngineSDK {
  class CViewPort : public CViewPort
  {
   public:
    /**
     * @brief  Constructor.
     * @bug    No Bugs known.
     */
    CViewPort() = default;
    /**
     * @brief    Constructor.
     * @bug      No Bugs known.
     */
    ~CViewPort() = default;


    D3D11_VIEWPORT m_VP;
  
  };
}