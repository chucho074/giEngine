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
    uint32 filter = 0;
    uint32 addressU = 0;
    uint32 addressV = 0;
    uint32 addressW = 0;
    uint32 comparisonFunc = 0;
    float minLOD = 0.f;
    float maxLOD = 0.f;
  };
  
  /**
   * @class    Sampler.
   * @brief    Manage the Sampler State.
   * @bug      No known Bugs.
   */
  class Sampler {
   public:
     //Constructor
     Sampler() = default;

     //Destructor  
     virtual
     ~Sampler() = default;
  
     /**
      * @brief     Initialize the sampler.
      * @param     inDesc    The description of the sampler.
      */
     virtual void 
     init(SamplerDesc) {};
  };
}