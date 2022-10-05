/**
 * @file    giDepthStencilView.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    15/04/2021
 * @brief   A Depth Stencil View object.
 */
 
/**
 * @include
 */
#pragma once

namespace giEngineSDK {
  /**
   * @struct  DepthStencilViewDesc.
   * @brief   Basics for the Depth stencil.
   * @bug     No Bugs Known.
   */
  struct DepthStencilViewDesc {
    uint32 format;
    uint32 viewDimension;
    uint32 mipSlice;
  };

  /**
   * @class  DepthStencilView 
   * @brief  Abstraction for DepthStencilView.
   * @bug    No Bugs Known.
   */
  class DepthStencilView {
   public:

    ///Default constructor
    DepthStencilView() = default;

    ///Destructor
    virtual 
    ~DepthStencilView() = default;


  };
}