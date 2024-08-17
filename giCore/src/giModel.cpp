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
#include "giTexture.h"
#include "giBaseConfig.h"
#include "giEncoder.h"
#include "giBaseGraphicsAPI.h"

#include <pmp/surface_mesh.h>
#include <pmp/algorithms/subdivision.h>
#include <pmp/io/write_giAMR.h>

#include <giStdHeaders.h>
#include <giVector2.h>
#include <giVector3.h>



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

  Vector<SharedPtr<Texture>>
  loadMaterialTextures(Model inModel,
                       aiMaterial* mat, 
                       aiTextureType type, 
                       TEXTURE_TYPE::E textureType) {

    auto& GAPI = g_graphicsAPI();
    Vector<SharedPtr<Texture>> textures;
    for (uint32 i = 0; i < mat->GetTextureCount(type); i++) {
      aiString str;
      mat->GetTexture(type, i, &str);
      String path = str.C_Str();
      path = getPathCorrectly(path);
      bool skip = false;
      for (uint32 j = 0; j < inModel.m_texturesLoaded.size(); j++) {
        if (std::strcmp(inModel.m_texturesLoaded[j]->m_path.string().c_str(), path.c_str()) == 0) {
          textures.push_back(inModel.m_texturesLoaded[j]);
          skip = true;
          break;
        }
      }
      if (!skip)  {   // if texture hasn't been loaded already, load it
        SharedPtr<Texture> texture = GAPI.TextureFromFile(path, inModel.m_directory);

        textures.push_back(texture);
        inModel.m_texturesLoaded.push_back(texture); // add to loaded textures
      }
    }
    return textures;
  }


  void
  processNode(Model &inModel, aiNode* node, const aiScene* inScene);

  SharedPtr<Mesh> 
  processMesh(Model &inModel, aiMesh* mesh, const aiScene* scene);

  Model::Model(Vector<SharedPtr<Mesh>> inMeshes, Vector<SharedPtr<Texture>> inMaterials) {
    
    this->m_meshes = inMeshes;
    
    if (!inMaterials.empty()) {
      this->m_texturesLoaded = inMaterials;
    }
    
  }

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


  SharedPtr<Mesh> 
  processMesh(Model &inModel, aiMesh* mesh, const aiScene* scene) {
    auto& GAPI = g_graphicsAPI();
    Vector<SimpleVertex> vertices;
    Vector<uint32> indices;
    Vector<SharedPtr<Texture>> textures;

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

      Vector<SharedPtr<Texture>> diffuseMaps = loadMaterialTextures(inModel,
                                                         material,
                                                         aiTextureType_DIFFUSE, 
                                                         TEXTURE_TYPE::kDiffuse);

      textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

      Vector<SharedPtr<Texture>> normalMaps = loadMaterialTextures(inModel,
                                                         material,
                                                         aiTextureType_NORMALS, 
                                                         TEXTURE_TYPE::kNormal);

      textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

      Vector<SharedPtr<Texture>> specularMaps = loadMaterialTextures(inModel,
                                                          material,
                                                          aiTextureType_SPECULAR, 
                                                          TEXTURE_TYPE::kSpecular);

      textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

      Vector<SharedPtr<Texture>> roughnessMaps = loadMaterialTextures(inModel,
                                                          material,
                                                          aiTextureType_SHININESS, 
                                                          TEXTURE_TYPE::kShininess);

      textures.insert(textures.end(), roughnessMaps.begin(), roughnessMaps.end());

    }
    else {
      //Assign the missing texture.
      SharedPtr<Texture> tmpTexture;
      tmpTexture = GAPI.TextureFromFile("Resources/", "missingTexture.png");
      textures.push_back(tmpTexture);
    }

    return make_shared<Mesh>(vertices, 
                indices, 
                textures);
  }


  void 
  Model::drawModel() {

    //Draw every mesh into the map
    for (uint32 i = 0; i < m_meshes.size(); i++) {
      m_meshes[i]->drawMesh();
    }
  }


#define MIN_SPHERE_SECTOR 3
#define MIN_SPHERE_STACK 2

  struct Triangle {
    int32 v1, v2, v3;
  };

  void 
  Subdivide(Vector<SimpleVertex> & inVertices, Vector<Triangle> & inTriangles) {
    Vector<Triangle> newTriangles;
    Vector<SimpleVertex> newVertices;

    for (const auto & triangle : inTriangles) {
      int32 v1 = triangle.v1;
      int32 v2 = triangle.v2;
      int32 v3 = triangle.v3;

      int32 v4 = newVertices.size();
      int32 v5 = v4 + 1;
      int32 v6 = v4 + 2;

      // Calcula los puntos medios de los lados
      SimpleVertex midPoint1, midPoint2, midPoint3;

      midPoint1.Pos.x = (inVertices[v1].Pos.x + inVertices[v2].Pos.x) / 2.0f;
      midPoint1.Pos.y = (inVertices[v1].Pos.y + inVertices[v2].Pos.y) / 2.0f;
      midPoint1.Pos.z = (inVertices[v1].Pos.z + inVertices[v2].Pos.z) / 2.0f;

      midPoint2.Pos.x = (inVertices[v2].Pos.x + inVertices[v3].Pos.x) / 2.0f;
      midPoint2.Pos.y = (inVertices[v2].Pos.y + inVertices[v3].Pos.y) / 2.0f;
      midPoint2.Pos.z = (inVertices[v2].Pos.z + inVertices[v3].Pos.z) / 2.0f;
      
      midPoint3.Pos.x = (inVertices[v3].Pos.x + inVertices[v1].Pos.x) / 2.0f;
      midPoint3.Pos.y = (inVertices[v3].Pos.y + inVertices[v1].Pos.y) / 2.0f;
      midPoint3.Pos.z = (inVertices[v3].Pos.z + inVertices[v1].Pos.z) / 2.0f;

      // Normaliza los puntos medios
      float length = sqrt(midPoint1.Pos.x * midPoint1.Pos.x + midPoint1.Pos.y * midPoint1.Pos.y + midPoint1.Pos.z * midPoint1.Pos.z);
      midPoint1.Pos.x /= length;
      midPoint1.Pos.y /= length;
      midPoint1.Pos.z /= length;

      length = sqrt(midPoint2.Pos.x * midPoint2.Pos.x + midPoint2.Pos.y * midPoint2.Pos.y + midPoint2.Pos.z * midPoint2.Pos.z);
      midPoint2.Pos.x /= length;
      midPoint2.Pos.y /= length;
      midPoint2.Pos.z /= length;

      length = sqrt(midPoint3.Pos.x * midPoint3.Pos.x + midPoint3.Pos.y * midPoint3.Pos.y + midPoint3.Pos.z * midPoint3.Pos.z);
      midPoint3.Pos.x /= length;
      midPoint3.Pos.y /= length;
      midPoint3.Pos.z /= length;

      // Agrega los nuevos vertices al vector de v�rtices
      newVertices.push_back(midPoint1);
      newVertices.push_back(midPoint2);
      newVertices.push_back(midPoint3);

      // Crea los nuevos triangulos
      newTriangles.push_back({ v1, v4, v6 });
      newTriangles.push_back({ v4, v2, v5 });
      newTriangles.push_back({ v4, v5, v6 });
      newTriangles.push_back({ v6, v5, v3 });
    }

    // Reemplaza los vertices y triangulos originales con los nuevos
    inVertices = newVertices;
    inTriangles = newTriangles;
  }

  SharedPtr<Model>
  Model::createSphere(int32 numTriangles) {
    
    float radius = 1;
    uint32 sectors = MIN_SPHERE_SECTOR;
    for (int32 i = MIN_SPHERE_SECTOR; (((numTriangles) % i) == 0); i += 3) {
      sectors = i;
    }
    
    uint32 stacks = ((numTriangles) / sectors) / 2;

    uint32 sphereSectors = sectors < MIN_SPHERE_SECTOR ? MIN_SPHERE_SECTOR : sectors;
    uint32 sphereStacks = stacks < MIN_SPHERE_STACK ? MIN_SPHERE_STACK : stacks;

    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / radius;
    float s, t;

    float sectorStep = 2 * Math::PI / sphereSectors;
    float sectorAngle, stackAngle;

    Vector<SimpleVertex> sphereVertices;
    Vector<uint32> sphereIndices;
    Vector<SharedPtr<Texture>> sphereTextures;
    SimpleVertex vertex;
    vertex.Tang = Vector3(1.0f, 1.0f, 1.0f);
    vertex.BiNor = Vector3(1.0f, 1.0f, 1.0f);

    sphereVertices.resize((sphereSectors * (sphereStacks-1))+2);
    uint32 tmpIter = 0;
    tmpIter++;

    //First Vertex data.
    SimpleVertex tmpVertex;
    tmpVertex.Pos = {0, 1, 0};
    tmpVertex.Nor = {0, 1, 0};
    tmpVertex.Tex = {0.f, 1.f};
    sphereVertices[0] = tmpVertex;

    //Vertices
    for (uint32 i = 0; i < sphereStacks - 1; ++i) {
      auto phi = Math::PI * double(i + 1) / double(sphereStacks);
      for (uint32 j = 0; j < sphereSectors; ++j) {
        sectorAngle = 2.0 * Math::PI * double(j) / double(sphereSectors);

        //Vertex
        x = sin(phi) * cos(sectorAngle);
        y = cos(phi);
        z = sin(phi) * sin(sectorAngle);
        vertex.Pos = Vector3(x, y, z);
        //Normal
        nx = x * lengthInv;
        ny = y * lengthInv;
        nz = z * lengthInv;
        vertex.Nor = Vector3(nx, ny, nz);
        //Texcoords
        s = (float)j / sphereSectors;
        t = (float)i / sphereStacks;
        vertex.Tex = Vector2(s, t);

        vertex.Tex.normalize();
        if(tmpIter >= ((sphereSectors * (sphereStacks - 1)) + 2)){
          __debugbreak();
          tmpIter = tmpIter - 1;
          break;
        }
        else {
          sphereVertices[tmpIter] = vertex;
          tmpIter++;
        }
      }
    }
    //Last vertex data.
    tmpVertex.Pos = { 0, -1, 0};
    tmpVertex.Nor = { 0, -1, 0};
    tmpVertex.Tex = { 0.5f, 0.5f };
    sphereVertices[tmpIter++] = tmpVertex;
     
    //Indices

    //Triangles with the first Vertex.
    for(int32 i = 0; i < sphereSectors; ++i) {
      auto i0 = i + 1;
      auto i1 = (i + 1) % sphereSectors + 1;
      sphereIndices.push_back(0);
      sphereIndices.push_back(i0);
      sphereIndices.push_back(i1);
      i0 = i + sphereSectors * (sphereStacks - 2) + 1;
      i1 = (i + 1) % sphereSectors + sphereSectors * (sphereStacks-2) + 1;
      sphereIndices.push_back(tmpIter++);
      sphereIndices.push_back(i0);
      sphereIndices.push_back(i1);
    } 

    //Middle triangles
    for(int32 i = 0; i < sphereStacks - 2; ++i) {
      auto i0 = i * sphereSectors + 1;
      auto i1 = (i + 1) * sphereSectors + 1;
      for(int32 j = 0; j < sphereSectors; ++j){
        auto j0 = i0 + j;
        auto j1 = i0 + (j + 1) % sphereSectors;
        auto j2 = i1 + (j + 1) % sphereSectors;
        auto j3 = i1 + j;
        sphereIndices.push_back(j0);
        sphereIndices.push_back(j1);
        sphereIndices.push_back(j2);
        
        sphereIndices.push_back(j0);
        sphereIndices.push_back(j2);
        sphereIndices.push_back(j3);

      }
    }

    SharedPtr<Texture> tmpTexture;
    tmpTexture = g_graphicsAPI().TextureFromFile("/missingTexture.png", "Resources/");

    sphereTextures.push_back(tmpTexture);
    Vector<SharedPtr<Mesh>> tmpMeshes;
    tmpMeshes.reserve(1);
    SharedPtr<Mesh> tmpMesh = make_shared<Mesh>(sphereVertices, sphereIndices, sphereTextures);
    tmpMeshes.emplace(tmpMeshes.end(), tmpMesh);

    Vector<SharedPtr<Texture>> tmpMaterials;
    tmpMaterials.reserve(1);
    tmpMaterials.emplace(tmpMaterials.end(), tmpTexture);

    SharedPtr<Model> tmpRef = make_shared<Model>(tmpMeshes, tmpMaterials);

    return tmpRef;

  }

  void
  Model::createQuadSphere(int32 inNumSubdivisions) {
    auto& configs = g_engineConfigs();
    // choose coordinates on the unit sphere
    float a = 1.0f / sqrt(3.0f);

    pmp::SurfaceMesh tmpPMPMesh;
    
    // add the 8 vertices
    auto v0 = tmpPMPMesh.add_vertex(pmp::Point(-a, -a, -a));
    tmpPMPMesh.add_vertex_property("v:normal", pmp::Normal(1.f, 1.f, 1.f));
    tmpPMPMesh.add_halfedge_property("h:tex", pmp::TexCoord(1.f, 1.f));

    auto v1 = tmpPMPMesh.add_vertex(pmp::Point(a, -a, -a));
    auto v2 = tmpPMPMesh.add_vertex(pmp::Point(a, a, -a));
    auto v3 = tmpPMPMesh.add_vertex(pmp::Point(-a, a, -a));
    auto v4 = tmpPMPMesh.add_vertex(pmp::Point(-a, -a, a));
    auto v5 = tmpPMPMesh.add_vertex(pmp::Point(a, -a, a));
    auto v6 = tmpPMPMesh.add_vertex(pmp::Point(a, a, a));
    auto v7 = tmpPMPMesh.add_vertex(pmp::Point(-a, a, a));

    tmpPMPMesh.add_quad(v3, v2, v1, v0);
    tmpPMPMesh.add_quad(v2, v6, v5, v1);
    tmpPMPMesh.add_quad(v5, v6, v7, v4);
    tmpPMPMesh.add_quad(v0, v4, v7, v3);
    tmpPMPMesh.add_quad(v3, v7, v6, v2);
    tmpPMPMesh.add_quad(v1, v5, v4, v0);


    for(int32 i = 1; i <= inNumSubdivisions; i++){
      pmp::catmull_clark_subdivision(tmpPMPMesh);
    }

    pmp::IOFlags tmpFlags;
    tmpFlags.use_vertex_texcoords = true;
    tmpFlags.use_vertex_normals = true;
    tmpFlags.use_halfedge_texcoords = true;

    Path tmpPath = configs.s_generatedPath.string() + "sphere.obj";
    
    pmp::write_giAMR(tmpPMPMesh, tmpPath, tmpFlags);
    Encoder::exportMtl(tmpPath);

  }

}