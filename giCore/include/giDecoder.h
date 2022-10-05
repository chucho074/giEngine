/**
 * @file    giDecoder.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    08/07/2022
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giFile.h"
#include "giResource.h"


namespace giEngineSDK {

  struct ResourceRef;

  class Decoder
  {
  public:

    Decoder() = default;

    ~Decoder() = default;

    /**
     * @brief    Decode data of the given file and create a resource.
     * @param    inFileData    The file data structure.
     */
    static ResourceRef
    decodeData(FILE& inFileData);

    /**
     * @brief    Decode files than don't need to create a resource.
     */
    static void
    decodeFile(FILE& inFileData);

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
    static void
    decodeGiProject(FILE &inFileData);

    /**
     * @brief    Decode any image type.
     * @param    inFileData    The file data structure.
     */
    static SharedPtr<Resource>
    decodeImage(FILE &inFileData);
    
    /**
     * @brief    Decode the information of any kind of model files.
     * @param    inFileData    The file data structure.
     * @return   Returns the model as a Shared Pointer of Resource .
     */
    static SharedPtr<Resource>
    decodeModel(FILE &inFileData);

    /**
     * @brief    Decode the information of any kind of scene files.
     * @param    inFileData    The file data structure.
     */
    static void
    decodeGiScene(FILE &inFileData);


    
   protected:
    friend class FILE;
  };

}