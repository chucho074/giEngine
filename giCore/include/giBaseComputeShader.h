/**
 * @file    giBaseComputeShader.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/10/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giBaseShader.h"

namespace giEngineSDK {
  /**
   * @class     BaseComputeShader.
   * @brief     A base shader for Compute.
   */
   class BaseComputeShader : public BaseShader
   {
    public:
     //Default Costructor
     BaseComputeShader() {}

     //Destructor
     virtual
     ~BaseComputeShader() {}
   };

}