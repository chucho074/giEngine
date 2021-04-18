/**
 * @file    giSamplerDX.cpp
 * @author  Jesús Alberto Del Moral Cupil
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
  CSamplerDX::CSamplerDX() {
    m_Sampler = nullptr;
    memset(&m_Desc, 0, sizeof(m_Desc));
  }

  CSamplerDX::~CSamplerDX() {
    SAFE_RELEASE(m_Sampler);
  }

  void
  CSamplerDX::init(SamplerDesc inDesc) {
    m_Desc.Filter = (D3D11_FILTER)inDesc.filter;
    m_Desc.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)inDesc.addressU;
    m_Desc.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)inDesc.addressV;
    m_Desc.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)inDesc.addressW;
    m_Desc.ComparisonFunc = (D3D11_COMPARISON_FUNC)inDesc.comparisonFunc;
    m_Desc.MinLOD = inDesc.minLOD;
    m_Desc.MaxLOD = inDesc.maxLOD;
  }
}