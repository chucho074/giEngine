/**
 * @file    giVertexShaderDX.h
 * @author  Jes�s Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    07/04/2021
 * @brief   A basic Vertex shader for DirectX.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesDX.h"
#include <giBaseVertexShader.h>

namespace giEngineSDK {
  class VertexShaderDX final : public BaseVertexShader
  {
   public:
     //Constructor
    VertexShaderDX();

    //Destructor
    ~VertexShaderDX();

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


    ID3D11VertexShader* m_VS;

    ID3DBlob* m_CompiledVShader;
  };
}