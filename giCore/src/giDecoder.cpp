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

namespace giEngineSDK {
  
  void
  processNode(WeakPtr<Model> inModel, aiNode* node, const aiScene* inScene);

  Mesh 
  processMesh(WeakPtr<Model> inModel, aiMesh* mesh, const aiScene* scene);


  SharedPtr<Resource> 
  Decoder::decodeData(FILE &inFileData) {

    return SharedPtr<Resource>();
  }

  SharedPtr<Resource> 
  Decoder::decodeGiProject(FILE &inFileData) {

    return SharedPtr<Resource>();
  }

  SharedPtr<Resource> 
  Decoder::decodePNG(FILE &inFileData) {

    return SharedPtr<Resource>();
  }

  SharedPtr<Resource> 
  Decoder::decodeModel(FILE &inFileData) {
    
    size_T tmpSize(inFileData.m_data.size());
    m_importer.ReadFileFromMemory(&inFileData.m_data,
                                  tmpSize,
                                  aiProcessPreset_TargetRealtime_MaxQuality |
                                  aiProcess_TransformUVCoords|
                                  aiProcess_ConvertToLeftHanded |
                                  aiProcess_Triangulate);

    const aiScene* tmpScene = m_importer.GetOrphanedScene();

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
  processNode(WeakPtr<Model>inModel, aiNode* node, const aiScene* inScene) {
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
      inModel.lock()->m_meshes.push_back(processMesh(inModel, mesh, inScene));
    }
    // then do the same for each of its children
    for (uint32 i = 0; i < node->mNumChildren; i++) {
      processNode(inModel, node->mChildren[i], inScene);
    }
  }


  Mesh 
  processMesh(WeakPtr<Model>inModel, aiMesh* mesh, const aiScene* scene) {
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
      //To change for the creation of the textures in the resource Manager.
      Vector<Texture> diffuseMaps = loadMaterialTextures(inModel,
                                                         material,
                                                         aiTextureType_DIFFUSE, 
                                                         "texture_diffuse");

      textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
      //To change for the creation of the textures in the resource Manager.
      Vector<Texture> normalMaps = loadMaterialTextures(inModel,
                                                         material,
                                                         aiTextureType_NORMALS, 
                                                         "texture_normal");

      textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
      //To change for the creation of the textures in the resource Manager.
      Vector<Texture> specularMaps = loadMaterialTextures(inModel,
                                                          material,
                                                          aiTextureType_SPECULAR, 
                                                          "texture_specular");

      textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
      //To change for the creation of the textures in the resource Manager.
      Vector<Texture> roughnessMaps = loadMaterialTextures(inModel,
                                                          material,
                                                          aiTextureType_SHININESS, 
                                                          "texture_shininess");

      textures.insert(textures.end(), roughnessMaps.begin(), roughnessMaps.end());

    }
    else {
      //To change for the creation of the textures in the resource Manager.
      Texture texture;
      texture.texture = GAPI.TextureFromFile("Resources/", "missingTexture.png");
      textures.push_back(texture);
    }

    return Mesh(vertices, 
                indices, 
                textures);
  }

}