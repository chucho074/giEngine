/**
 * @file    giResourceManager.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/05/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giEncoder.h"
#include "giDecoder.h"
#include "giMaterial.h"
#include "giModule.h"
#include "giModel.h"

namespace giEngineSDK {

  class ResourceManager : Module<ResourceManager> 
  {
   public:
  	//Default Constructor.
    ResourceManager() = default;
  	//Default destructor.
    ~ResourceManager() = default;

    /**
     * @brief    Function to read a file.
     * @param    inFile        The file to read.
     * @return   Returns the result from the reading file.
     */
    SharedPtr<Resource>
    readFromFile(FILE inFile);

    /**
     * @brief    Getter for the resources by an a ID.
     * @param    inID          The ID of the resource wanted.
     * @return   A reference of the resource as a Weak Pointer.
     */
    WeakPtr<Resource>
    getResource(uint32 inID);

    /**
     * @brief    .
     * @return 
     */
    uint32
    createTextureFromMem(String inData);

    /**
     * @brief    .
     * @param    inFileData 
     * @return   Returns the ID of the created texture.
     */
    uint32
    createTextureFromFile(FILE inFileData);


   protected:
  	
    /**
     * @brief    Read file information and save it in File type.
     * @param    inFile        File type to read and save the information.
     */
    void
    readFile(FILE & inFile);

   private:
    //Reference of the encoder.
    SharedPtr<Encoder> m_encoder;

    //Reference of the Decoder.
    SharedPtr<Decoder> m_decoder;

    //The map of resources loaded.
    Map<uint32, SharedPtr<Resource>> m_loadedResources;

    //Temporal solution for UUIDs.
    uint32 m_nextID = 0;

  };

}