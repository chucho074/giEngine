/**
 * @file    giBaseShader.h
 * @author  Jes�s Alberto Del Moral Cupil
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
     //Constructor
     BaseShader() = default;

     //Destructor
    virtual 
    ~BaseShader() = 0;

    ///**
    // * @brief 
    // * @param    inFile 
    // * @return 
    // */
    //bool
    //loadFromfile(char * inFile);

    ///**
    // * @brief 
    // * @param inCode 
    //*/
    //void 
    //setSourceCode(String inCode);

    ///**
    // * @brief 
    // * @return 
    // */
    //virtual bool 
    //compile() = 0;

    ///**
    // * @brief 
    // * @return
    // */
    //virtual bool 
    //link() = 0;

    ///**
    // * @brief 
    // */
    //void 
    //setShader();

    virtual bool 
    init(wchar* inFileName,
    /***/lpcstr inEntryPoint,
    /***/lpcstr inShaderModel) = 0;

    


    //String m_code;

  };
}