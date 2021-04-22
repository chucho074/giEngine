/**
 * @file    giPixelShaderDX.h
 * @author  Jes�s Alberto Del Moral Cupil
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
#include <giBasePixelShader.h>

namespace giEngineSDK {
  class PixelShaderDX : public BasePixelShader
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
    init(lpcstr inFileName,
    /***/lpcstr inEntryPoint,
    /***/lpcstr inShaderModel) override;

    /**
     * @brief    .
     * @param    szFileName      .
     * @param    szEntryPoint    .
     * @param    szShaderModel   .
     * @param    ppBlobOut       .
     * @return   .
     */
    bool
    CompileShaderFromFile(lpcstr szFileName,
    /********************/lpcstr szEntryPoint,
    /********************/lpcstr szShaderModel,
    /********************/ID3DBlob** ppBlobOut);


    ID3D11PixelShader* m_PS;

    ID3DBlob* m_CompiledPShader;
  };
}