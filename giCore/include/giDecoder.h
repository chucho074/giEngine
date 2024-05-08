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
  struct ModelInfo;

  namespace DECODER_FLAGS {
    enum E {
      kNoFlags,
      kNoMaterial,
      kBothSides
    };
  }

  class Decoder
  {
  public:

    Decoder() = default;

    ~Decoder() = default;

    /**
     * @brief    Decode data of the given file and create a resource.
     * @param    inFileData    The file data structure.
     * @param    inFlags       Flags for read the file.
     */
    static ResourceRef
    decodeData(FILE& inFileData, 
               DECODER_FLAGS::E inFlags = DECODER_FLAGS::kNoFlags);

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

    static ModelInfo
    decodeGiData(FILE& inFile);
    

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
    decodeImage(FILE &inFileData, DECODER_FLAGS::E inFlags);
    
    /**
     * @brief    Decode the information of any kind of model files.
     * @param    inFileData    The file data structure.
     * @return   Returns the model as a Shared Pointer of Resource .
     */
    static SharedPtr<Resource>
    decodeModel(FILE &inFileData, DECODER_FLAGS::E inFlags);

    /**
     * @brief    Decode the information of any kind of scene files.
     * @param    inFileData    The file data structure.
     */
    static void
    decodeGiScene(FILE &inFileData);


    
   protected:
    /**
     * @brief    Reads the basic information of a model and returns it.
     */
    static void
    readBasicModel(FILE& inFile, ModelInfo& inInfo);

    friend class FILE;
    friend class Encoder;
  };

}