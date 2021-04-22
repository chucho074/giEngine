/**
 * @file    giSamplerDX.h
 * @author  Jes�s Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    15/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesDX.h"
#include <giSampler.h>

namespace giEngineSDK {
  
  class CSamplerDX : public Sampler
  {
   public:
    //Constructor
    CSamplerDX();

    //Destructor
    ~CSamplerDX();
    
    /**
     * @brief 
     * @param inDesc 
     */
    void 
    init(SamplerDesc inDesc);


    ID3D11SamplerState* m_Sampler;

    D3D11_SAMPLER_DESC m_Desc;
   
  };
}