/**
 * @file    giModel.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/04/2021
 * @brief   For load models.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giModel.h"

namespace giEngineSDK {

  Model::Model(String inFileName) {
    loadModel(inFileName);
  }


  Model::~Model() {

  }

  void 
  Model::loadModel(String inFileName) {

    // Create an instance of the Importer class
    Assimp::Importer importer;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    importer.ReadFile(inFileName,
                      aiProcessPreset_TargetRealtime_MaxQuality |
                      aiProcess_ConvertToLeftHanded |
                      aiProcess_Triangulate);

    m_scene = importer.GetOrphanedScene();

    if (!m_scene || m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_scene->mRootNode) {
      g_logger().SetError(ERROR_TYPE::kModelLoading, "Failed to load a model");
      return;
    }

    m_directory = inFileName.substr(0, inFileName.find_last_of('/') + 1);

    processNode(m_scene->mRootNode, m_scene);
  }

  void 
  Model::update(float inDeltaTime, Vector<Matrix4>& inTransforms) {
    
    for(auto mesh : m_meshes) {
      mesh.update(inDeltaTime, inTransforms, m_globalInverseTransform);
    }
  }


  void 
  Model::processNode(aiNode* node, const aiScene* scene) {
    // process all the node's meshes (if any)
    for (uint32 i = 0; i < node->mNumMeshes; i++) {
      aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
      m_meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (uint32 i = 0; i < node->mNumChildren; i++)  {
      processNode(node->mChildren[i], scene);
    }

  }


  Mesh 
  Model::processMesh(aiMesh* mesh, const aiScene* scene) {
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

      //


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
    if(mesh->mNumBones) {
      for (uint32 i = 0 ; i < mesh->mNumBones ; i++) {
        uint32 BoneIndex = 0;
        String BoneName(mesh->mBones[i]->mName.data);

        if (m_boneMapping.find(BoneName) == m_boneMapping.end()) {
            BoneIndex = m_numBones;
            m_numBones++;
            BoneInfo bi;
            m_boneInfo.push_back(bi);
        }
        else {
            BoneIndex = m_boneMapping[BoneName];
        }

        m_boneMapping[BoneName] = BoneIndex;

        memcpy(&m_boneInfo[BoneIndex].offset, &mesh->mBones[i]->mOffsetMatrix, sizeof(Matrix4));

        for (uint32 j = 0 ; j < mesh->mBones[i]->mNumWeights ; j++) {
            uint32 VertexID = mesh->mBones[i]->mWeights[j].mVertexId;
            float Weight = mesh->mBones[i]->mWeights[j].mWeight;
            

            for (uint32 k = 0; k < 4; k++) {
              if (m_weights[k] == 0.0) {
                m_ids[i] = BoneIndex;
                m_weights[i] = Weight;
                
              }
            }
        }
    }
    }



    // process material
    if(mesh->mMaterialIndex >= 0) {
      aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

      Vector<Texture> diffuseMaps = loadMaterialTextures(material,
                                                         aiTextureType_DIFFUSE, 
                                                         "texture_diffuse");

      textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

      Vector<Texture> specularMaps = loadMaterialTextures(material,
                                                          aiTextureType_SPECULAR, 
                                                          "texture_specular");

      textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    }

    return Mesh(vertices, 
                indices, 
                textures, 
                m_scene, 
                m_numBones, 
                m_boneInfo, 
                m_boneMapping);
  }


  Vector<Texture>
  Model::loadMaterialTextures(aiMaterial* mat, 
                              aiTextureType type, 
                              String typeName) {

    auto& GAPI = g_graphicsAPI();
    Vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
      aiString str;
      mat->GetTexture(type, i, &str);
      bool skip = false;
      for (unsigned int j = 0; j < m_texturesLoaded.size(); j++) {
        if (std::strcmp(m_texturesLoaded[j].path.data(), str.C_Str()) == 0) {
          textures.push_back(m_texturesLoaded[j]);
          skip = true;
          break;
        }
      }
      if (!skip)  {   // if texture hasn't been loaded already, load it
        Texture texture;
        texture.texture = GAPI.TextureFromFile(str.C_Str(), m_directory);
        texture.type = typeName;
        texture.path = str.C_Str();

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
        m_texturesLoaded.push_back(texture); // add to loaded textures
      }
    }
    return textures;
  }


  void 
  Model::drawModel() {

    //Draw every mesh into the map
    for (uint32 i = 0; i < m_meshes.size(); i++) {
      m_meshes[i].drawMesh();
    }
  }
}