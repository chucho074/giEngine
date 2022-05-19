/**
 * @file    giModel.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/04/2021
 * @brief   For load models.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giModel.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags



namespace giEngineSDK {

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

  Vector<Texture>
  loadMaterialTextures(Model inModel,
                       aiMaterial* mat, 
                       aiTextureType type, 
                       String typeName) {

    auto& GAPI = g_graphicsAPI();
    Vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
      aiString str;
      mat->GetTexture(type, i, &str);
      String path = str.C_Str();
      path = getPathCorrectly(path);
      bool skip = false;
      for (unsigned int j = 0; j < inModel.m_texturesLoaded.size(); j++) {
        if (std::strcmp(inModel.m_texturesLoaded[j].path.data(), path.c_str()) == 0) {
          textures.push_back(inModel.m_texturesLoaded[j]);
          skip = true;
          break;
        }
      }
      if (!skip)  {   // if texture hasn't been loaded already, load it
        Texture texture;
        texture.texture = GAPI.TextureFromFile(path, inModel.m_directory);
        texture.type = typeName;
        texture.path = path;

        SamplerDesc sampDesc;
        sampDesc.filter = 21;
        sampDesc.addressU = 1;
        sampDesc.addressV = 1;
        sampDesc.addressW = 1;
        sampDesc.comparisonFunc = 1;
        sampDesc.minLOD = 0;
        sampDesc.maxLOD = 3.402823466e+38f;
        texture.samplerState = GAPI.createSampler(sampDesc);

        textures.push_back(texture);
        inModel.m_texturesLoaded.push_back(texture); // add to loaded textures
      }
    }
    return textures;
  }


  void
  processNode(Model &inModel, aiNode* node, const aiScene* inScene);

  Mesh 
  processMesh(Model &inModel, aiMesh* mesh, const aiScene* scene);

  Model::~Model() {
    unload();
  }

  bool 
  Model::loadFromFile(const Path& inFileName) {

    // Create an instance of the Importer class
    Assimp::Importer importer;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    importer.ReadFile(inFileName.string(),
                      aiProcessPreset_TargetRealtime_MaxQuality |
                      aiProcess_TransformUVCoords|
                      aiProcess_ConvertToLeftHanded |
                      aiProcess_Triangulate);

    const aiScene * tmpScene = importer.GetOrphanedScene();

    if (!tmpScene || 
        tmpScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE 
        || !tmpScene->mRootNode) {
      g_logger().SetError(ERROR_TYPE::kModelLoading, "Failed to load a model");
      return false;
    }

    m_directory = inFileName.string().substr(0, inFileName.string().find_last_of('/') + 1);

    processNode(*this, tmpScene->mRootNode, tmpScene);
  }

  bool 
  Model::loadFromMemory(const char* inData, size_T inSizeOfData) {
    return false;
  }

  void 
  Model::unload() {

  }

  void 
  Model::saveToFile(const String& inFile) {

  }

  

  void 
  processNode(Model &inModel, aiNode* node, const aiScene* inScene) {
    ////Check if has meshes
    //if (!inScene->HasMeshes()) return;
    //
    ////Model resize the meshes
    //inModel.m_meshes.resize(inScene->mNumMeshes);

    ////
    //for (uint32 i = 0; i < inScene->mNumMeshes; ++i) {
    //  auto assimpMesh = inScene->mMeshes[i];
    //  auto& myMesh = inModel.m_meshes[i];
    //  
    //  
    //  
    //  inModel.m_meshes.push_back(processMesh(inModel, mesh, inScene));
    //}
    //// then do the same for each of its children
    //for (uint32 i = 0; i < node->mNumChildren; i++) {
    //  processNode(inModel, node->mChildren[i], inScene);
    //}
    

    // process all the node's meshes (if any)
    for (uint32 i = 0; i < node->mNumMeshes; i++) {
      aiMesh* mesh = inScene->mMeshes[node->mMeshes[i]];
      inModel.m_meshes.push_back(processMesh(inModel, mesh, inScene));
    }
    // then do the same for each of its children
    for (uint32 i = 0; i < node->mNumChildren; i++) {
      processNode(inModel, node->mChildren[i], inScene);
    }
  }


  Mesh 
  processMesh(Model &inModel, aiMesh* mesh, const aiScene* scene) {
    auto& GAPI = g_graphicsAPI();
    Vector<SimpleVertex> vertices;
    Vector<uint32> indices;
    Vector<Texture> textures;

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
      //Texture
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
      //bitangentes
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
    // process indices
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



    // process material
    if(mesh->mMaterialIndex >= 0) {
      aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

      Vector<Texture> diffuseMaps = loadMaterialTextures(inModel,
                                                         material,
                                                         aiTextureType_DIFFUSE, 
                                                         "texture_diffuse");

      textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

      Vector<Texture> normalMaps = loadMaterialTextures(inModel,
                                                         material,
                                                         aiTextureType_NORMALS, 
                                                         "texture_normal");

      textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

      Vector<Texture> specularMaps = loadMaterialTextures(inModel,
                                                          material,
                                                          aiTextureType_SPECULAR, 
                                                          "texture_specular");

      textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

      Vector<Texture> roughnessMaps = loadMaterialTextures(inModel,
                                                          material,
                                                          aiTextureType_SHININESS, 
                                                          "texture_shininess");

      textures.insert(textures.end(), roughnessMaps.begin(), roughnessMaps.end());

    }
    else {
      
      Texture texture;
      texture.texture = GAPI.TextureFromFile("Resources/", "missingtexture.png");
      textures.push_back(texture);
    }

    return Mesh(vertices, 
                indices, 
                textures);
  }


  

  void 
  Model::drawModel() {

    //Draw every mesh into the map
    for (uint32 i = 0; i < m_meshes.size(); i++) {
      m_meshes[i].drawMesh();
    }
  }
}