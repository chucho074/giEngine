/**
 * @file    giPixelShaderDX.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    16/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesDX.h"
#include <giBaseShader.h>

namespace giEngineSDK {
  class PixelShaderDX final : public BaseShader
  {
  public:
    //Constructor
    PixelShaderDX();

    //Destructor
    ~PixelShaderDX();

    /**
     * @brief    .
     * @param    inFileName
     * @param    inEntryPoint
     * @param    inShaderModel
     * @return   .
     */
    bool
    init(WCHAR* inFileName,
    /***/LPCSTR inEntryPoint,
    /***/LPCSTR inShaderModel) override;

    /**
     * @brief    .
     * @param    szFileName      .
     * @param    szEntryPoint    .
     * @param    szShaderModel   .
     * @param    ppBlobOut       .
     * @return   .
     */
    bool
    CompileShaderFromFile(WCHAR* szFileName,
    /********************/LPCSTR szEntryPoint,
    /********************/LPCSTR szShaderModel,
    /********************/ID3DBlob** ppBlobOut);


    ID3D11PixelShader* m_PS;

    ID3DBlob* m_CompiledPShader;
  };
}