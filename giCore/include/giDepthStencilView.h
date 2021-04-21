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
    uint32 format;
    uint32 viewDimension;
    uint32 mipSlice;
  };

  /**
   * @brief  Abstraction for DepthStencilView.
   * @bug    No Bugs Known.
   */
  class CDepthStencilView {
   public:

    ///Default constructor
    CDepthStencilView() = default;

    ///Destructor
    virtual 
    ~CDepthStencilView() = default;


  };
}