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
    init(String inFileName,
         String inEntryPoint,
         String inShaderModel) override;

    /**
     * @brief    .
     * @param    szFileName      .
     * @param    szEntryPoint    .
     * @param    szShaderModel   .
     * @param    ppBlobOut       .
     * @return   .
     */
    bool
    CompileShaderFromFile(String szFileName,
                          String szEntryPoint,
                          String szShaderModel,
                          ID3DBlob** ppBlobOut);


    ID3D11PixelShader* m_pixelShader;

    ID3DBlob* m_compiledPShader;
  };
}