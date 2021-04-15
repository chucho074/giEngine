/**
 * @file    giRenderTargetViewDX.h
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
#include <giRenderTargetView.h>

namespace giEngineSDK {
  /**
   * @brief   Abstraction for Render targets.
   * @bug     No Bugs known.
   */
  class CRenderTargetViewDX : public CRenderTargetView
  {
   public:
    /**
     * @brief    Constructor.
     * @bug      No Bugs known.
     */
    CRenderTargetViewDX();

    /**
    * @brief	: Destructor.
    * @bug		: No Bugs known.
    **/
    ~CRenderTargetViewDX();


    ID3D11RenderTargetView* m_RTV;

  };
}