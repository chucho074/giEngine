/**
 * @file   CDepthStencilViewDX.h
 * @author Jesus Alberto Del Moral Cupil
 * @e      idv18c.jmoral@uartesdigitales.edu.mx
 * @date   05/03/2021
 * @brief  Management of the graphics APIs.
 * @bug    No known Bugs.
 */

/**
 * @include
 */
#pragma once
#include "giPrerequisitesDX.h"
#include <giDepthStencilView.h>

namespace giEngineSDK {
  /**
   * @class    CDepthStencilViewDX.
   * @brief    Manage the graphics of DirectX.   
   */
  class CDepthStencilViewDX final : public DepthStencilView
  {
   public:
    ///Default constructor
    CDepthStencilViewDX() = default;

    ///Destructor
    ~CDepthStencilViewDX() = default;

    //Reference to DirectX Depth Stencil View
    ID3D11DepthStencilView* m_depthStencilView;

    //Reference to Depth Stencil View Desc
    DepthStencilViewDesc m_descDepthStencilView;
  };
}