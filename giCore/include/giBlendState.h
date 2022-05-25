/**
 * @file    giBlendState.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    04/11/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"

namespace giEngineSDK {

  class GI_CORE_EXPORT BaseBlendState
  {
   public:
    //Default constructor
     BaseBlendState() = default;

    //Destructor
  	~BaseBlendState() = default;
  };
}