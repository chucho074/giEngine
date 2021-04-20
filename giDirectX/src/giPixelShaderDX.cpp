/**
 * @file    giPixelShaderDX.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    16/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giPixelShaderDX.h"

namespace giEngineSDK {

  PixelShaderDX::PixelShaderDX() {
    m_PS = nullptr;
    m_CompiledPShader = nullptr;
  }

  PixelShaderDX::~PixelShaderDX() {

  }

  bool
  PixelShaderDX::init(lpcstr inFileName, 
  /******************/lpcstr inEntryPoint, 
  /******************/lpcstr inShaderModel) {

     return CompileShaderFromFile(inFileName, 
     /***************************/inEntryPoint, 
     /***************************/inShaderModel, 
     /***************************/&m_CompiledPShader);
  }

  bool 
  PixelShaderDX::CompileShaderFromFile(lpcstr szFileName, 
  /***********************************/lpcstr szEntryPoint, 
  /***********************************/lpcstr szShaderModel, 
  /***********************************/ID3DBlob** ppBlobOut) {
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
    hr = D3DX11CompileFromFile(szFileName,
    /*************************/NULL,
    /*************************/NULL,
    /*************************/szEntryPoint,
    /*************************/szShaderModel,
    /*************************/dwShaderFlags,
    /*************************/0,
    /*************************/NULL,
    /*************************/ppBlobOut,
    /*************************/&pErrorBlob,
    /*************************/NULL);

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