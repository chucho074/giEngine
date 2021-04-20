/**
 * @file    giDepthStencilView.h
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

namespace giEngineSDK {
  /**
   * @brief  DepthStencilViewDesc.
   * @bug    No Bugs Known.
   */
  struct DepthStencilViewDesc {
    unsigned int format;
    unsigned int viewDimension;
    unsigned int mipSlice;
  };

  /**
   * @brief  Abstraction for DepthStencilView.
   * @bug    No Bugs Known.
   */
  class GI_CORE_EXPORT CDepthStencilView {
   public:

    ///Default constructor
    CDepthStencilView() = default;

    ///Destructor
    ~CDepthStencilView() = default;


  };
}