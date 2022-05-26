/**
 * @file    giViewportDX.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    27/11/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include <giBaseViewport.h>

#include "giPrerequisitesDX.h"

namespace giEngineSDK {
  /**
   * @class    ViewportDX.
   * @brief    .
   * @bug      No known Bugs.
   */
  class ViewportDX final : public BaseViewport
  {
   public:
    //Default Constructor.
    ViewportDX() = default;

    //Destructor.
    ~ViewportDX() {
      SAFE_RELEASE(m_viewport);
    };
    
   private:
     CD3D11_VIEWPORT * m_viewport = nullptr;
  };
  
  

}