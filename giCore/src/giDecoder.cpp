/**
 * @file    giDecoder.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    08/07/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giDecoder.h"
#include "giResourceManager.h"
#include "giModel.h"
#include "giMesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace giEngineSDK {
  
  void
  processNode(WeakPtr<Model> inModel, aiNode* node, const aiScene* inScene);

  SharedPtr<Mesh>
  processMesh(WeakPtr<Model> inModel, aiMesh* mesh, const aiScene* scene);


  ResourceRef
  Decoder::decodeData(FILE &inFileData) {

    auto& RM = g_resourceManager();

    ResourceRef tmpRef;
    tmpRef.m_id = UUID();
    
    if(EXTENSION_TYPE::E::kBMP == inFileData.m_extension
      || EXTENSION_TYPE::E::kJPEG == inFileData.m_extension
      || EXTENSION_TYPE::E::kPNG == inFileData.m_extension
      || EXTENSION_TYPE::E::kTGA == inFileData.m_extension) {

      RM.m_loadedResources.insert({tmpRef.m_id,
                                   Decoder::decodeImage(inFileData)});

      tmpRef.m_type = RESOURCE_TYPE::kTexture;
      return tmpRef;
    }

        

    if(EXTENSION_TYPE::E::kFBX == inFileData.m_extension
      || EXTENSION_TYPE::E::k3DS == inFileData.m_extension
      || EXTENSION_TYPE::E::kOBJ == inFileData.m_extension) {

      RM.m_loadedResources.insert({ tmpRef.m_id,
                                   Decoder::decodeModel(inFileData) });

      tmpRef.m_type = RESOURCE_TYPE::kModel;

      return tmpRef;
    }

    //case EXTENSION_TYPE::E::kHLSL: {}
    
    //case EXTENSION_TYPE::E::kgiTEX2D: {}
    
    //case EXTENSION_TYPE::E::kgiModel: {}
    
    //case EXTENSION_TYPE::E::kgiShader: {}

      
  }

  SharedPtr<Resource>
  Decoder::decodeGiProject(FILE &inFileData) {

    return SharedPtr<Resource>();
  }

  SharedPtr<Resource>
  Decoder::decodeImage(FILE &inFileData) {
    auto& gapi = g_graphicsAPI().instance();

    int32 w = 0, h = 0, comp = 0;

    comp = 4;

    SharedPtr<Texture> tmpTexture = make_shared<Texture>();

    //Save the information of the readed data.
    //uint8 tmpData = (uint8)inFileData.m_data.c_str();
    
    //Get the information of the image loadead.
    uint8 * tmpImg = stbi_load(inFileData.m_path.string().c_str(),
                               &w, 
                               &h, 
                               &comp, 4);

    //Create the texture with the information.
    if (tmpImg) {
      tmpTexture->m_texture = gapi.createTex2D(w,
                                               h,
                                               1,
                                               GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                                               GI_BIND_FLAG::kBIND_SHADER_RESOURCE);
      
      //Unload Data
      stbi_image_free(tmpImg);
      tmpTexture->m_path = inFileData.m_path;
      tmpTexture->m_name = inFileData.m_name;

      SamplerDesc sampDesc;
      sampDesc.filter = GI_FILTER::kFILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
      sampDesc.addressU = GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
      sampDesc.addressV = GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
      sampDesc.addressW = GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
      sampDesc.comparisonFunc = 1;
      sampDesc.minLOD = 0;
      sampDesc.maxLOD = 3.402823466e+38f;
      tmpTexture->m_samplerState = gapi.createSampler(sampDesc);

      return tmpTexture;
    }

    //Unload Data
    stbi_image_free(tmpImg);

    return tmpTexture;
  }

  SharedPtr<Resource>
  Decoder::decodeModel(FILE &inFileData) {
    
    Assimp::Importer importer;

    size_T tmpSize(inFileData.m_data.size());
    importer.ReadFile(inFileData.m_path.string(),
                      aiProcessPreset_TargetRealtime_MaxQuality |
                      aiProcess_TransformUVCoords|
                      aiProcess_ConvertToLeftHanded |
                      aiProcess_Triangulate);

    const aiScene* tmpScene = importer.GetOrphanedScene();

    if (!tmpScene 
        || tmpScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE
        || !tmpScene->mRootNode) {
      g_logger().SetError(ERROR_TYPE::kModelLoading, "Failed to load a model");
      return SharedPtr<Resource>();
    }

    SharedPtr<Model> tmpModel = make_shared<Model>();

    tmpModel->m_directory = inFileData.m_path;

    tmpModel->m_resourceType = RESOURCE_TYPE::kModel;

    processNode(tmpModel, tmpScene->mRootNode, tmpScene);
    return tmpModel;
  }


  void
  Decoder::readFile(FILE& inFile) {
    
    ifstream tmpFile(inFile.m_path.c_str());
    
    String tmpData;
    while (getline(tmpFile, tmpData)) {
      inFile.m_data += tmpData;
    }

    tmpFile.close();
  }

  //

  String 
  getPathCorrectly(String inFile) {
    size_T realPos = 0;
    size_T posInvSlash = inFile.rfind('\\');
    size_T posSlash = inFile.rfind('/');

    if(posInvSlash == String::npos) {
      if(posSlash != String::npos) {
        realPos = posSlash;
      }
    }
    else {
      realPos = posInvSlash;
      if (posSlash == String::npos) {
        if (posSlash > realPos) {
          posSlash = realPos;
        }
      }
    }
    if (realPos == 0) {
      return "/" + inFile;
    }
    return "/" + inFile.substr(realPos + 1, inFile.length() - realPos);
  }


  ResourceRef
  loadMaterialTextures(WeakPtr<Model> inModel,
                       aiMaterial* mat, 
                       aiTextureType type, 
                       TEXTURE_TYPE::E typeName) {

    auto& GAPI = g_graphicsAPI();
    auto& RM = g_resourceManager();
    ResourceRef tmpTextureRef;
    bool noTexture = true;
    //Get the number of textures in assimp in the material.
    for (uint32 i = 0; i < mat->GetTextureCount(type); i++) {
      noTexture = false;
      aiString str;
      mat->GetTexture(type, i, &str);
      String tmpTextureName = str.C_Str();
      //Get just the name of the texture.
      tmpTextureName = getPathCorrectly(tmpTextureName);
      bool skip = false;

      for (uint32 j = 0; j < inModel.lock()->m_materialsLoaded.size(); j++) {
        //Get the list of names of textures in the material.
        auto tmpNames = RM.getTextureNameFromMaterial(inModel.lock()->m_materialsLoaded[j]);
        //Compare if the texture is already in any material by it name.
        auto tmpIterNames = find(tmpNames.begin(), tmpNames.end(), tmpTextureName);
        //If the Texture exist, get the reference of that texture.
        if (tmpIterNames != tmpNames.end()) {
          //Get the reference of the texture.
          tmpTextureRef = RM.getReferenceByNameInMaterial(inModel.lock()->m_materialsLoaded[j], 
                                                          tmpIterNames->data());
          skip = true;
          break;
        }
      }

      if (!skip)  {   // if texture hasn't been loaded already, load it.

        //Get the path without the name of the model name.

        FILE tmpFile(inModel.lock()->m_directory.parent_path().string() + tmpTextureName);

        tmpTextureRef = Decoder::decodeData(tmpFile);

        auto tmpResource = RM.getResource(tmpTextureRef.m_id);

        auto tmpTexture = static_pointer_cast<Texture>(tmpResource.lock());
        
        tmpTexture->m_type = typeName;
      }
    }

    if (noTexture) {
      tmpTextureRef = RM.m_missingTextureRef;
    }

    return tmpTextureRef;
  }


  void 
  processNode(WeakPtr<Model>inModel, aiNode* node, const aiScene* inScene) {
    // process all the node's meshes (if any)
    for (uint32 i = 0; i < node->mNumMeshes; i++) {
      aiMesh* mesh = inScene->mMeshes[node->mMeshes[i]];
      inModel.lock()->m_meshes.push_back(processMesh(inModel, mesh, inScene));
    }
    // then do the same for each of its children
    for (uint32 i = 0; i < node->mNumChildren; i++) {
      processNode(inModel, node->mChildren[i], inScene);
    }
  }


  SharedPtr<Mesh>
  processMesh(WeakPtr<Model>inModel, aiMesh* mesh, const aiScene* scene) {
    auto& GAPI = g_graphicsAPI();
    auto& RM = g_resourceManager();
    Vector<SimpleVertex> vertices;
    Vector<uint32> indices;
    Vector<ResourceRef> textures;

    for(uint32 i = 0; i < mesh->mNumVertices; i++) {
      SimpleVertex vertex;
      // process vertex positions, normals and texture coordinates
      //Pos
      vertex.Pos.x = mesh->mVertices[i].x;
      vertex.Pos.y = mesh->mVertices[i].y;
      vertex.Pos.z = mesh->mVertices[i].z;
      //Normals
      if(mesh->mNormals) {
        vertex.Nor.x = mesh->mNormals[i].x;
        vertex.Nor.y = mesh->mNormals[i].y;
        vertex.Nor.z = mesh->mNormals[i].z;
      }
      else {
        vertex.Nor.x = 0.0f;
        vertex.Nor.y = 0.0f;
        vertex.Nor.z = 0.0f;
      }
      //Texture / UVs
      if (mesh->mTextureCoords[0]) {
        vertex.Tex.x = mesh->mTextureCoords[0][i].x;
        vertex.Tex.y = mesh->mTextureCoords[0][i].y;
      }
      else {
        vertex.Tex.x = 0.f;
        vertex.Tex.y = 0.f;
      }

      //Tangentes
      if(mesh->mTangents) {
        vertex.Tang.x = mesh->mTangents[i].x;
        vertex.Tang.y = mesh->mTangents[i].y;
        vertex.Tang.z = mesh->mTangents[i].z;
      }
      else {
        vertex.Tang.x = 0.0f;
        vertex.Tang.y = 0.0f;
        vertex.Tang.z = 0.0f;
      }
      //Bitangentes
      if (mesh->mBitangents) {
        vertex.BiNor.x = mesh->mBitangents[i].x;
        vertex.BiNor.y = mesh->mBitangents[i].y;
        vertex.BiNor.z = mesh->mBitangents[i].z;
      }
      else {
        vertex.BiNor.x = 0.0f;
        vertex.BiNor.y = 0.0f;
        vertex.BiNor.z = 0.0f;
      }

      vertices.push_back(vertex);
    }
    // Process indices
    for (uint32 i = 0; i < mesh->mNumFaces; ++i) {
      aiFace face = mesh->mFaces[i];
      for (uint32 j = 0; j < face.mNumIndices; ++j) {
        indices.push_back(face.mIndices[j]);
      }
    }

    //Bones
    /*if(mesh->mNumBones) {
      for (uint32 i = 0 ; i < mesh->mNumBones ; i++) {
        uint32 BoneIndex = 0;
        String BoneName(mesh->mBones[i]->mName.data);

        if (inModel.m_boneMapping.find(BoneName) == inModel.m_boneMapping.end()) {
            BoneIndex = inModel.m_numBones;
            inModel.m_numBones++;
            BoneInfo bi;
            inModel.m_boneInfo.push_back(bi);
        }
        else {
            BoneIndex = inModel.m_boneMapping[BoneName];
        }

        inModel.m_boneMapping[BoneName] = BoneIndex;

        memcpy(&inModel.m_boneInfo[BoneIndex].offset, &mesh->mBones[i]->mOffsetMatrix, sizeof(Matrix4));

        for (uint32 j = 0 ; j < mesh->mBones[i]->mNumWeights ; j++) {
            uint32 VertexID = mesh->mBones[i]->mWeights[j].mVertexId;
            float Weight = mesh->mBones[i]->mWeights[j].mWeight;
            

            for (uint32 k = 0; k < 4; k++) {
              if (inModel.m_weights[k] == 0.0) {
                inModel.m_ids[i] = BoneIndex;
                inModel.m_weights[i] = Weight;
                
              }
            }
        }
      }
    }*/



    // Process material
    if(mesh->mMaterialIndex >= 0) {
      aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
      //To change for the creation of the textures in the resource Manager.
      textures.push_back(loadMaterialTextures(inModel,
                                              material,
                                              aiTextureType_DIFFUSE, 
                                              TEXTURE_TYPE::kAlbedo));

      

      //To change for the creation of the textures in the resource Manager.
      textures.push_back(loadMaterialTextures(inModel,
                                              material,
                                              aiTextureType_NORMALS, 
                                              TEXTURE_TYPE::kNormal));


      //To change for the creation of the textures in the resource Manager.
      textures.push_back(loadMaterialTextures(inModel,
                                              material,
                                              aiTextureType_SPECULAR, 
                                              TEXTURE_TYPE::kSpecular));


      //To change for the creation of the textures in the resource Manager.
      textures.push_back(loadMaterialTextures(inModel,
                                              material,
                                              aiTextureType_SHININESS, 
                                              TEXTURE_TYPE::kGloss));

    }
    else {
      //To change for the Setting the reference of the missingTexture only.
      
      textures.push_back(RM.m_missingTextureRef);
    }

    SharedPtr<Mesh> tmpMesh = make_shared<Mesh>(vertices, indices, textures);

    return tmpMesh;
  }

}