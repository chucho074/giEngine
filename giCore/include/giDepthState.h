/**
 * @file    giDepthState
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/08/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"

namespace giEngineSDK {

  class DepthState
  {
  public:
    //Default constructor
    DepthState() = default;

    //Destructor
    virtual
    ~DepthState() = default;
  };
}