/**
 * @file    giResourceManager.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/05/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
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

  SharedPtr<Resource> 
  ResourceManager::readFromFile(FILE inFile) {

    readFile(inFile);

    //Decide the type of file and send to the correct function.


  }

  WeakPtr<Resource>
  ResourceManager::getResource(UUID inID) {
    return m_loadedResources.find(inID)->second;
  }

  ResourceRef
  ResourceManager::createTextureFromMem(String inData) {
    
    

  }

  ResourceRef
  ResourceManager::createTextureFromFile(FILE inFileData) {
    readFile(inFileData);
    
    createTextureFromMem(inFileData.m_data);

  }

  ResourceRef 
  ResourceManager::createMaterialFromTexRef(Vector<ResourceRef> inReferences) {
    SharedPtr<Material> newMaterial;

    newMaterial->m_textures = inReferences;

    m_loadedResources.insert({UUID(), newMaterial});
  }

  ResourceRef 
  ResourceManager::createMaterialFromFile(FILE inFileData) {
    
  }

  String
  ResourceManager::getTextureName(ResourceRef& inRef) {
    auto tmpVal = m_loadedResources.find(inRef.m_id)->second;
    if (RESOURCE_TYPE::kTexture == inRef.m_type) {
      static_pointer_cast<Texture>(tmpVal);
    }
  }

  void
  ResourceManager::readFile(FILE& inFile) {
    
    ifstream tmpFile(inFile.m_path);
    
    String tmpData;
    while (getline(tmpFile, tmpData)) {
      inFile.m_data += tmpData;
    }

    tmpFile.close();
  }

  ResourceManager&
  g_resourceManager() {
    return ResourceManager::instance();
  }

}