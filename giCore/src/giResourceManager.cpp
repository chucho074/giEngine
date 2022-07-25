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

#include "stb_image.h"


namespace giEngineSDK {

  SharedPtr<Resource> 
  ResourceManager::readFromFile(FILE inFile) {

    readFile(inFile);

    //Decide the type of file and send to the correct function.


  }

  WeakPtr<Resource>
  ResourceManager::getResource(uint32 inID) {
    return m_loadedResources.find(inID)->second;
  }

  uint32 
  ResourceManager::createTextureFromMem(String inData) {
    
    auto &gapi = g_graphicsAPI().instance();

    int32 w, h, comp;

    comp = 4;
    
    //Save the information of the readed data.
    uint8 tmpData = (uint8)inData.c_str();
    
    //Get the information of the image loadead.
    uint8 * tmpImg = stbi_load_from_memory(&tmpData, 
                                           inData.length(), 
                                           &w, 
                                           &h, 
                                           &comp, 
                                           0);

    //Create the texture with the information.
    if (tmpImg) {
      SharedPtr<Texture> tmpTexture;
      tmpTexture->texture = gapi.createTex2D(w,
                                             h,
                                             1,
                                             GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                                             GI_BIND_FLAG::kBIND_SHADER_RESOURCE);
      
      //
      m_loadedResources.insert({m_nextID, tmpTexture});
    }

    //Unload Data
    stbi_image_free(tmpImg);

  }

  uint32
  ResourceManager::createTextureFromFile(FILE inFileData) {
    readFile(inFileData);
    
    createTextureFromMem(inFileData.m_data);

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

}