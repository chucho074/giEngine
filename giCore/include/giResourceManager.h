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
#include "giModule.h"
#include "giUUID.h"


namespace giEngineSDK {

  /**
   * @brief    Type for save a reference of a resource.
   */
  struct ResourceRef {
    UUID m_id = UUID::ZERO;
    RESOURCE_TYPE::E m_type = RESOURCE_TYPE::E::kUnknown;
  };

  /**
   * @brief    The Class in charge to manage the creation of the resources.
   */
  class ResourceManager : public Module<ResourceManager> 
  {
   public:
    //Default Constructor.
    ResourceManager() = default;

    //Default destructor.
    ~ResourceManager() = default;

    /**
     * @brief    Prepare the Module.
     * @bug      No known Bugs.
     */
    void 
    onStartUp() override {};
    
    /**
     * @brief    Clear the Module.
     * @bug      No known Bugs.
     */
    void 
    onShutDown() override {};
    
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
    getResource(UUID inID);

    /**
     * @brief    Creates a texture from memory data.
     * @return   Returns the reference of the resource.
     */
    ResourceRef
    createTextureFromMem(String inData);

    /**
     * @brief    Creates a texture from a readed file data.
     * @param    inFileData    The data to use as a texture.
     * @return   Returns the reference of the resource.
     */
    ResourceRef
    createTextureFromFile(FILE inFileData);

    /**
     * @brief    .
     * @param    inReferences  .
     * @return   .
     */
    ResourceRef
    createMaterialFromTexRef(Vector<ResourceRef> inReferences);

    /**
     * @brief    .
     * @param    inFileData    .
     * @return   .
     */
    ResourceRef
    createMaterialFromFile(FILE inFileData);



    /**
     * @brief    .
     * @param    inRef 
     * @return   .
     */
    String
    getTextureName(ResourceRef & inRef);

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

    ////Reference of the Decoder.
    SharedPtr<Decoder> m_decoder;

    //The map of resources loaded.
    Map<UUID, SharedPtr<Resource>> m_loadedResources;


    friend class Decoder;
    friend class Encoder;
  };

  GI_CORE_EXPORT ResourceManager&
  g_resourceManager();

}