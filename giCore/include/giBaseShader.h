/**
 * @file    giBaseShader.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    02/02/2021
 * @brief   A basic shader class.
 * @bug     No known Bugs.
 */

 /**
   * @include
   */
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