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
#include "giResourceManager.h"


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
    static SharedPtr<Resource>
    decodeData(FILE &inFileData);

    /**
     * @brief    Read file information and save it in File type.
     * @param    inFile        File type to read and save the information.
     */
    static void
    readFile(FILE& inFile);

  private:

    /**
     * @brief    Encode the information for the giProject Files.
     * @param    inFileData    The file data structure.
     */
    static SharedPtr<Resource>
    decodeGiProject(FILE &inFileData);

    /**
     * @brief    Decode any image type.
     * @param    inFileData    .
     */
    static SharedPtr<Resource>
    decodeImage(FILE &inFileData);
    
    /**
     * @brief    Decode the information of any kind of model files.
     * @param    inFileData    .
     * @return   Returns the model as a Shared Pointer of Resource .
     */
    static SharedPtr<Resource>
    decodeModel(FILE &inFileData);

    
   protected:
    friend class FILE;
  };

}