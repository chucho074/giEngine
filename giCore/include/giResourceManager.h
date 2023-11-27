/**
 * @file    giResourceManager.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/05/2022
 * @brief   A basic description of the what do the doc.
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
  struct ModelInfo;

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
     * @brief    Function to read a file and create a resource.
     * @param    inFile        The file to read.
     * @return   Returns the reference of the resource created by reading the file.
     */
    ResourceRef
    resourceFromFile(FILE& inFile, 
                     DECODER_FLAGS::E inFlags = DECODER_FLAGS::kNoFlags);

    /**
     * @brief    Function to read a file and make internal changes in the engine.
     * @param    inFile        The file to read.
     */
    void
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

    /**
     * @brief 
     * @param inMeshes 
     * @param inMaterials 
     * @return 
     */
    ResourceRef
    createModelFromMem(Vector<SharedPtr<Mesh>> inMeshes,
                       Vector<ResourceRef> inMaterials = Vector<ResourceRef>());

    /**
     * @brief    Renders a Resource by the reference.
     * @param    inReference   The reference of the resource to Render.
     */
    void
    renderResource(ResourceRef inReference);

    /**
     * @brief    .
     * @param    inFile        .
     */
    void 
    createData(FILE& inFile);

    /**
     * @brief    .
     * @param    inPath        .
     * @param    inModel       .
     */
    void
    exportModel(Path inPath, ResourceRef inModel);

    //THIS MAY BE IN ANOTHER CLASS
    
    /**
     * @brief    Saving files of the engine types.
     * @param    inFile        .
     */
    void
    saveFile(FILE& inFile);
    
    /**
     * @brief 
     * @param    inFile 
     * @return   Returns .
     */
    ModelInfo
    getFromFile(FILE& inFile);

    /**
     * @brief 
     * @param    numTriangles 
     * @return   Returns .
     */
    ResourceRef
    createSphere(int32 numTriangles);

    /**
     * @brief    .
     * @return   Returns .
     */
    void
    createQuadSphere(int32 inNumSubdivisions);

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

    //The reference to the obj icon texture.
    ResourceRef m_objIcon;

    //The reference to the FBX icon texture.
    ResourceRef m_fbxIcon;

    //The reference to the mdl icon texture.
    ResourceRef m_mtlIcon;

    //The reference to the PNG icon texture.
    ResourceRef m_pngIcon;

    //The reference to the JPG icon texture.
    ResourceRef m_jpgIcon;

    //SAQ
    ResourceRef m_SAQ;

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


   protected:
    /**
     * @brief    Clear the map of resources loaded.
     */
    void 
    clearLoadedResources();

    friend class Decoder;
    friend class Encoder;
  };

  GI_CORE_EXPORT ResourceManager&
  g_resourceManager();

}