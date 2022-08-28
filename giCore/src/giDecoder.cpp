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


  SharedPtr<Resource>
  Decoder::decodeData(FILE &inFileData) {
    //Verify if the FILE is not empty.
    if (!inFileData.m_data.empty()) {
      //Use the data to decode it.
      switch (inFileData.m_extension) {

        case EXTENSION_TYPE::E::kBMP: {
          return decodeImage(inFileData);
        }

        case EXTENSION_TYPE::E::kJPEG: {
          return decodeImage(inFileData);
        }

        case EXTENSION_TYPE::E::kPNG: {
          return decodeImage(inFileData);
        }

        case EXTENSION_TYPE::E::kTGA: {
          return decodeImage(inFileData);
        }

        case EXTENSION_TYPE::E::kFBX: {
          return decodeModel(inFileData);
        }

        case EXTENSION_TYPE::E::kOBJ: {
          return decodeModel(inFileData);
        }
        case EXTENSION_TYPE::E::kHLSL: {}

        case EXTENSION_TYPE::E::kgiTEX2D: {}

        case EXTENSION_TYPE::E::kgiModel: {}

        case EXTENSION_TYPE::E::kgiShader: {}

      default:
        break;
      }
    }
    //If the file is empty.
    else {
      //Read the FILE and get the data.
      readFile(inFileData);
      //Decode the data.
      return decodeData(inFileData);

    }

    return SharedPtr<Resource>();
  }

  SharedPtr<Resource>
  Decoder::decodeGiProject(FILE &inFileData) {

    return SharedPtr<Resource>();
  }

  SharedPtr<Resource>
  Decoder::decodeImage(FILE &inFileData) {
    auto& gapi = g_graphicsAPI().instance();

    int32 w, h, comp;

    comp = 4;

    SharedPtr<Texture> tmpTexture;
    
    //Save the information of the readed data.
    uint8 tmpData = (uint8)inFileData.m_data.c_str();
    
    //Get the information of the image loadead.
    uint8 * tmpImg = stbi_load_from_memory(&tmpData, 
                                           inFileData.m_data.length(), 
                                           &w, 
                                           &h, 
                                           &comp, 
                                           0);

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

    return SharedPtr<Texture>();
  }

  SharedPtr<Resource>
  Decoder::decodeModel(FILE &inFileData) {
    
    Assimp::Importer importer;

    size_T tmpSize(inFileData.m_data.size());
    importer.ReadFileFromMemory(&inFileData.m_data,
                                  tmpSize,
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

    SharedPtr<Model> tmpModel;

    processNode(tmpModel, tmpScene->mRootNode, tmpScene);
    return SharedPtr<Resource>();
  }


  void
  Decoder::readFile(FILE& inFile) {
    
    ifstream tmpFile(inFile.m_path);
    
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
    //Get the number of textures in assimp in the material.
    for (uint32 i = 0; i < mat->GetTextureCount(type); i++) {
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

      if (!skip)  {   // if texture hasn't been loaded already, load it
        FILE tmpFile(inModel.lock()->m_directory.string() + tmpTextureName);

        tmpTextureRef.m_id = UUID();

        RM.m_loadedResources.insert({tmpTextureRef.m_id,
                                     Decoder::decodeData(tmpFile)});

        auto tmpResource = RM.getResource(tmpTextureRef.m_id);


        auto tmpTexture = static_pointer_cast<Texture>(tmpResource.lock());
        
        tmpTexture->m_type = typeName;
      }
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