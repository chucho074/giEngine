#pragma once
#include "giPrerequisitesCore.h"

namespace giEngineSDK {
  class CShader {
   public:
    CShader() = default;
    ~CShader() = default;

    virtual void
    init(WCHAR* inFileName,
    /***/LPCSTR inEntryPoint,
    /***/LPCSTR inShaderModel) = 0;

    /*bool 
    CompileShaderFromFile(WCHAR* szFileName,
      LPCSTR szEntryPoint,
      LPCSTR szShaderModel,
      ID3DBlob** ppBlobOut);*/

  };
}