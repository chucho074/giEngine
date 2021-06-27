/**
 * @file    giInputLayoutDX.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    15/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giInputLayoutDX.h"

namespace giEngineSDK {

  CInputLayoutDX::CInputLayoutDX() {
    m_inputLayout = nullptr;
  }

  CInputLayoutDX::~CInputLayoutDX() {
    SAFE_RELEASE(m_inputLayout);
  }

  void 
  CInputLayoutDX::init(const Vector<InputLayoutDesc>& inDesc) {
    for (int i = 0; i < inDesc.size(); ++i) {
      D3D11_INPUT_ELEMENT_DESC layout;
      layout.SemanticName = inDesc[i].semanticName.c_str();
      layout.SemanticIndex = inDesc[i].semanticIndex;
      layout.Format = (DXGI_FORMAT)inDesc[i].format;
      layout.InputSlot = inDesc[i].inputSlot;
      layout.AlignedByteOffset = inDesc[i].alignedByteOffset;
      layout.InputSlotClass = (D3D11_INPUT_CLASSIFICATION)inDesc[i].inputSlotClass;
      layout.InstanceDataStepRate = inDesc[i].instanceDataStepRate;
      m_descriptors.push_back(layout);
    }
  }
}