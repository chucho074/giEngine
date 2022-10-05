/**
 * @file    giBaseDepthStencilState.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/08/2021
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"

namespace giEngineSDK {

  class BaseDepthStencilState
  {
  public:
    //Default constructor
    BaseDepthStencilState() = default;

    //Destructor
    virtual
    ~BaseDepthStencilState() = default;
  };
}