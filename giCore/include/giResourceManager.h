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

  class Mesh;

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
  class GI_CORE_EXPORT ResourceManager : public Module<ResourceManager> 
  {
   public:
    //Default Constructor.
    ResourceManager() = default;

    //Default destructor.
    ~ResourceManager() = default;

    /**
     * @brief    Prepare the Module.
     */
    void 
    onStartUp() override {};
    
    /**
     * @brief    Clear the Module.
     */
    void 
    onShutDown() override {};
    
    /**
     * @brief    Initialize the Resource Manager info.
     */
    void
    init();

    /**
     * @brief    Function to read a file.
     * @param    inFile        The file to read.
     * @return   Returns the reference of the resource created by reading the file.
     */
    ResourceRef
    readFromFile(FILE& inFile);

    /**
     * @brief    Getter for the resources by an a ID.
     * @param    inID          The ID of the resource wanted.
     * @return   A reference of the resource as a Weak Pointer.
     */
    WeakPtr<Resource>
    getResource(UUID inID);

    /**
     * @brief    .
     * @param    inReferences  .
     * @return   .
     */
    ResourceRef
    createMaterialFromTexRef(Vector<ResourceRef> inReferences);

    /**
     * @brief    Get the name of the textures used in a material.
     * @param    inRef         The reference of the material.
     * @return   Returns the Vector of names of the textures.
     */
    Vector<StringView>
    getTextureNameFromMaterial(ResourceRef& inRef);

    /**
     * @brief    .
     * @param    inMaterialRef 
     * @param    inTextureName 
     * @return   .
     */
    ResourceRef
    getReferenceByNameInMaterial(ResourceRef& inMaterialRef, 
                                 StringView inTextureName);


    ResourceRef
    createModelFromMem(Vector<SharedPtr<Mesh>> inMeshes,
                       Vector<ResourceRef> inMaterials = Vector<ResourceRef>());

    /**
     * @brief    .
     * @param    inReference   .
     */
    void
    renderResource(ResourceRef inReference);

   public:

    //The map of resources loaded.
    Map<UUID, SharedPtr<Resource>> m_loadedResources;

    //The reference to the missing texture.
    ResourceRef m_missingTextureRef;

    //The reference to the left arrow texture.
    ResourceRef m_leftArrow;

    //The reference to the right arrow texture.
    ResourceRef m_rightArrow;

    //The reference to the folder icon texture.
    ResourceRef m_folderIcon;

    //The reference to the file icon texture.
    ResourceRef m_fileIcon;

   private:

    /**
     * @brief    Creates a texture and bind it as a missingTexture.
     */
    void
    createMissingTexture();

    /**
     * @brief    Creates the textures for the icons used for the editor.
     */
    void
    createEditorIconsTextures();



    friend class Decoder;
    friend class Encoder;
  };

  GI_CORE_EXPORT ResourceManager&
  g_resourceManager();

}