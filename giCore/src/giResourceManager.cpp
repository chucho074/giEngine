/**
 * @file    giResourceManager.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/05/2022
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giResourceManager.h"
#include "giBaseGraphicsAPI.h"
#include "giStdHeaders.h"
#include "giTexture.h"
#include "giMaterial.h"
#include "giModel.h"


namespace giEngineSDK {

  void 
  ResourceManager::init() {
    createEditorIconsTextures();
    createMissingTexture();

    //Load the Screen Aligned Quad
    FILE tmpFile("Resources/Models/ScreenAlignedQuad.3ds");
    m_SAQ = resourceFromFile(tmpFile, DECODER_FLAGS::kNoMaterial);

  }

  ResourceRef
  ResourceManager::resourceFromFile(FILE& inFile, DECODER_FLAGS::E inFlags) {

    //Send to read the file.
    Decoder::readFile(inFile);

    //Creates the References of the Resource.
    ResourceRef tmpRef = Decoder::decodeData(inFile, inFlags);
    
    //Return the reference.
    return tmpRef;

  }

  void 
  ResourceManager::readFromFile(FILE& inFile) {
    Decoder::decodeFile(inFile);
  }

  WeakPtr<Resource>
  ResourceManager::getResource(UUID inID) {
    return m_loadedResources.find(inID)->second;
  }

  ResourceRef 
  ResourceManager::createMaterialFromTexRef(Vector<ResourceRef> inReferences) {
    SharedPtr<Material> newMaterial;

    ResourceRef tmpMaterialRef;

    tmpMaterialRef.m_id = UUID();

    tmpMaterialRef.m_type = RESOURCE_TYPE::kMaterial;

    newMaterial->m_textures = inReferences;

    m_loadedResources.insert({tmpMaterialRef.m_id, newMaterial});

    return tmpMaterialRef;
  }

  Vector<StringView>
  ResourceManager::getTextureNameFromMaterial(ResourceRef& inRef) {
    Vector<StringView> tmpNames;
    //Get the resource of the Material.
    if (auto tmpResource = m_loadedResources.find(inRef.m_id)->second; 
        RESOURCE_TYPE::kMaterial == inRef.m_type) {
      //Get the material.
      auto tmpMaterial = static_pointer_cast<Material>(tmpResource);
      //Iterate into the textures.
      for(auto iterTex : tmpMaterial->m_textures) {
        if (RESOURCE_TYPE::kTexture == iterTex.m_type) {
          //Get the resource of the texture.
          auto tmpRef = m_loadedResources.find(iterTex.m_id)->second;
          //Get the texture.
          auto tmpTexture = static_pointer_cast<Texture>(tmpRef);
          //Save the name of the texture.
          tmpNames.push_back(tmpTexture->m_name);
        }
      }
    }
    return tmpNames;
  }

  ResourceRef 
  ResourceManager::getReferenceByNameInMaterial(ResourceRef& inMaterialRef, 
                                                StringView inTextureName) {
    //Get the resource of the Material.
    if (auto tmpResource = m_loadedResources.find(inMaterialRef.m_id)->second; 
        RESOURCE_TYPE::kMaterial == inMaterialRef.m_type) {
      //Get the material.
      auto tmpMaterial = static_pointer_cast<Material>(tmpResource);
      for (auto iterTex : tmpMaterial->m_textures) {
        //Get the resource of the texture.
        auto tmpRef = m_loadedResources.find(iterTex.m_id)->second;
        //Get the texture.
        if(auto tmpTexture = static_pointer_cast<Texture>(tmpRef); 
           inTextureName == tmpTexture->m_name) {
          return iterTex;
        }
      }

      return ResourceRef();
    }
    return ResourceRef();
  }

  ResourceRef 
  ResourceManager::createModelFromMem(Vector<SharedPtr<Mesh>> inMeshes, 
                                      Vector<ResourceRef> inMaterials) {
    //Create the reference of the resource.
    ResourceRef tmpRef;
    tmpRef.m_id = UUID();
    tmpRef.m_type = RESOURCE_TYPE::kModel;

    //Create the resource (The model).
    SharedPtr<Model> tmpModel = make_shared<Model>();

    tmpModel->m_meshes = inMeshes;
    
    if (!inMaterials.empty()) {
      tmpModel->m_materialsLoaded = inMaterials;
    }
    
    //Insert the model in the resources list
    m_loadedResources.insert({tmpRef.m_id, tmpModel});

    return tmpRef;
  }

  void
  ResourceManager::renderResource(ResourceRef inReference) {
    
     auto& tmpRes = m_loadedResources.find(inReference.m_id)->second;
     if(RESOURCE_TYPE::kModel == inReference.m_type) {
       static_pointer_cast<Model>(tmpRes)->drawModel();
     }
  }

  void 
  ResourceManager::saveFile(FILE& inFile) {
    Encoder::encodeData(inFile);
  }

  void
  ResourceManager::createMissingTexture() {

    FILE tmpMissingTextureFile("Resources/missingTexture.png");

    m_missingTextureRef = Decoder::decodeData(tmpMissingTextureFile);

  }

  void 
  ResourceManager::createEditorIconsTextures() {
    //Left Arrow Icon.
    FILE tmpLeftArrowIcon("Resources/Icons/leftArrow.png");
    m_leftArrow = Decoder::decodeData(tmpLeftArrowIcon);

    //Right Arrow Icon.
    FILE tmpRightArrowIcon("Resources/Icons/rightArrow.png");
    m_rightArrow = Decoder::decodeData(tmpRightArrowIcon);

    //Folder Icon.
    FILE tmpFolderIcon("Resources/Icons/folderIcon.png");
    m_folderIcon = Decoder::decodeData(tmpFolderIcon);

    //File icon.
    FILE tmpFileIcon("Resources/Icons/fileIcon.png");
    m_fileIcon = Decoder::decodeData(tmpFileIcon);
  }

  void 
  ResourceManager::clearLoadedResources() {
    for(auto resources : m_loadedResources) {
      if(!resources.first == m_missingTextureRef.m_id 
         || !resources.first == m_leftArrow.m_id
         || !resources.first == m_rightArrow.m_id
         || !resources.first == m_folderIcon.m_id
         || !resources.first == m_fileIcon.m_id
         || !resources.first == m_SAQ.m_id){
        resources.second->unload();
        m_loadedResources.erase(m_loadedResources.find(resources.first));
      }
    }
  }

  ResourceManager&
  g_resourceManager() {
    return ResourceManager::instance();
  }

}