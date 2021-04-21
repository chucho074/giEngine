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
    uint32 filter;
    uint32 addressU;
    uint32 addressV;
    uint32 addressW;
    uint32 comparisonFunc;
    float minLOD;
    float maxLOD;
  };
  
  /**
   * @class    CSampler.
   * @brief    Manage the Sampler State.
   * @bug      No known Bugs.
   */
  class CSampler {
   public:
  
     CSampler() = default;
  
     virtual
     ~CSampler() = default;
  
     virtual void 
     init(SamplerDesc inDesc) {};
  };
}