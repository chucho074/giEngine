/**
 * @file    giComputeShaderDX.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/10/2021
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesDX.h"
#include <giBaseComputeShader.h>

namespace giEngineSDK {
  class ComputeShaderDX : public BaseComputeShader
  {
   public:
    //Default Constructor
  	ComputeShaderDX() = default;

    //Destructor
  	~ComputeShaderDX() = default;

   /**
     * @brief    .
     * @param    inFileName
     * @param    inEntryPoint
     * @param    inShaderModel
     * @return   .
     */
    bool
    init(wString inFileName,
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
    CompileShaderFromFile(wString szFileName,
                          String szEntryPoint,
                          String szShaderModel,
                          ID3DBlob** ppBlobOut);

    ID3D11ComputeShader * m_computeShader;

    ID3DBlob* m_compiledCShader;
  };
}