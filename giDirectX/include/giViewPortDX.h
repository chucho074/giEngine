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
  class CViewPortDX : public CViewPort
  {
   public:
    /**
     * @brief  Constructor.
     * @bug    No Bugs known.
     */
    CViewPortDX() = default;
    /**
     * @brief    Constructor.
     * @bug      No Bugs known.
     */
    ~CViewPortDX() = default;


    D3D11_VIEWPORT m_VP;
  
  };
}