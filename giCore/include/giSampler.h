/**
 * @file     giSampler.h
 * @author   Jesús Alberto Del Moral Cupil
 * @e        idv18c.jmoral@uartesdigitales.edu.mx
 * @date     10/03/2021
 * @brief    Management of the SamplerState.
 * @bug      No known Bugs.
 */

/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"

namespace giEngineSDK {
  /**
   * @struct   SamplerDesc.
   * @brief    Manage the information for the Sampler.
   * @bug      No known Bugs.
   */
  struct SamplerDesc {
    unsigned int filter;
    unsigned int addressU;
    unsigned int addressV;
    unsigned int addressW;
    unsigned int comparisonFunc;
    float minLOD;
    float maxLOD;
  };
  
  /**
   * @class    CSampler.
   * @brief    Manage the Sampler State.
   * @bug      No known Bugs.
   */
  class GI_CORE_EXPORT CSampler {
   public:
  
     CSampler() {}
  
     ~CSampler() {}
  
     virtual void 
     init(SamplerDesc inDesc) {};
  };
}