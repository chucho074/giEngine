/**
 * @file    giVertexShaderDX.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    16/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giVertexShaderDX.h"

namespace giEngineSDK {

  VertexShaderDX::VertexShaderDX() {
    m_vertexShader = nullptr;
    m_compiledVShader = nullptr;
  }

  VertexShaderDX::~VertexShaderDX() {

  }

  bool 
  VertexShaderDX::init(String inFileName,
                       String inEntryPoint, 
                       String inShaderModel) {

    return CompileShaderFromFile(inFileName, 
                                 inEntryPoint, 
                                 inShaderModel, 
                                 &m_compiledVShader);
  }

  bool 
  VertexShaderDX::CompileShaderFromFile(String szFileName,
                                        String szEntryPoint, 
                                        String szShaderModel, 
                                        ID3DBlob** ppBlobOut) {

    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob = nullptr;
    hr = D3DX11CompileFromFileA(szFileName.c_str(),
                                NULL,
                                NULL,
                                szEntryPoint.c_str(),
                                szShaderModel.c_str(),
                                dwShaderFlags,
                                0,
                                NULL,
                                ppBlobOut,
                                &pErrorBlob,
                                NULL);

    if (FAILED(hr)) {
      if (pErrorBlob != NULL) {
        OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
      }
      if (pErrorBlob) {
        pErrorBlob->Release();
        return false;
      }
      return hr;
    }
    if (pErrorBlob) {
      pErrorBlob->Release();
    }
    return true;
  }

}