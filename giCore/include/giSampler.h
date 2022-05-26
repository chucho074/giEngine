/**
 * @file     giSampler.h
 * @author   Jesus Alberto Del Moral Cupil
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
   * @brief    Manage the information for the SamplerState.
   * @bug      No known Bugs.
   */
  struct SamplerDesc {
    GI_FILTER::E filter = GI_FILTER::kFILTER_MIN_MAG_MIP_POINT;
    GI_TEXTURE_ADDRESS_MODE::E addressU;
    GI_TEXTURE_ADDRESS_MODE::E addressV;
    GI_TEXTURE_ADDRESS_MODE::E addressW;
    uint32 comparisonFunc = 0;
    float minLOD = 0.f;
    float maxLOD = 0.f;
  };
  
  /**
   * @class    SamplerState.
   * @brief    Manage the SamplerState State.
   * @bug      No known Bugs.
   */
  class SamplerState {
   public:
     //Constructor
     SamplerState() = default;

     //Destructor  
     virtual
     ~SamplerState() = default;
  
     /**
      * @brief     Initialize the sampler.
      * @param     inDesc    The description of the sampler.
      */
     virtual void 
     init(SamplerDesc) {};
  };
}