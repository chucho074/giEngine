/**
 * @file    giSamplerDX.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giSamplerDX.h"

namespace giEngineSDK {
  SamplerDX::SamplerDX() {
    m_sampler = nullptr;
    memset(&m_desc, 0, sizeof(m_desc));
  }

  SamplerDX::~SamplerDX() {
    SAFE_RELEASE(m_sampler);
  }

  void
  SamplerDX::init(SamplerDesc inDesc) {
    m_desc.Filter = (D3D11_FILTER)inDesc.filter;
    m_desc.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)inDesc.addressU;
    m_desc.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)inDesc.addressV;
    m_desc.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)inDesc.addressW;
    m_desc.ComparisonFunc = (D3D11_COMPARISON_FUNC)inDesc.comparisonFunc;
    m_desc.MinLOD = inDesc.minLOD;
    m_desc.MaxLOD = inDesc.maxLOD;
  }
}