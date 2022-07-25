/**
 * @file    giDecoder.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    08/07/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giFile.h"
#include "giResource.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace giEngineSDK {

  class Decoder
  {
  public:

    Decoder() = default;

    ~Decoder() = default;

    /**
     * @brief    .
     * @param    inFileData    .
     */
    SharedPtr<Resource>
    decodeData(FILE &inFileData);


  private:

    /**
     * @brief    Encode the information for the giProject Files.
     * @param    inFileData    The file data structure.
     */
    SharedPtr<Resource>
    decodeGiProject(FILE &inFileData);

    /**
     * @brief    .
     * @param    inFileData    .
     */
    SharedPtr<Resource> 
    decodePNG(FILE &inFileData);
    
    /**
     * @brief    Decode the information of any kind of model files.
     * @param    inFileData    .
     * @return   Returns the model as a Shared Pointer of Resource .
     */
    SharedPtr<Resource>
    decodeModel(FILE &inFileData);

    Assimp::Importer m_importer;
  protected:
  };

}