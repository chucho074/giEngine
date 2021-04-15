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
  class BaseShader 
  {
   public:
     BaseShader() = default;

    virtual 
    ~BaseShader() = 0;

    bool
    loadFromfile(char * file);

    void 
    setSourceCode(String inCode);

    virtual bool 
    compile() = 0;

    void 
    link();

    void 
    setShader();

    

    /*bool 
    CompileShaderFromFile(WCHAR* szFileName,
      LPCSTR szEntryPoint,
      LPCSTR szShaderModel,
      ID3DBlob** ppBlobOut);*/

  };
}