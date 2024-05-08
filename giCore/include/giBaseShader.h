/**
 * @file    giBaseShader.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    02/02/2021
 * @brief   A basic shader class.
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
    //Constructor
    BaseShader() = default;

    //Destructor
    virtual 
    ~BaseShader() {};

    
    /**
     * @brief     Init the shader.
     * @param     inFileName      The shader file name.
     * @param     inEntryPoint    The point of entry.
     * @param     inShaderModel   The model of the shader.
     * @return    Returns if it can be readed.
     */
    virtual bool 
    init(wString inFileName,
         String inEntryPoint,
         String inShaderModel) = 0;

  };
}