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
#include "giExporter.h"


namespace giEngineSDK {

#define MIN_SPHERE_SECTOR 3
#define MIN_SPHERE_STACK 2

  struct Triangle {
    int v1, v2, v3;
  };

  void 
  ResourceManager::init() {
    createEditorIconsTextures();
    createMissingTexture();

    //Load the Screen Aligned Quad
    FILE tmpFile("Resources/Models/ScreenAlignedQuad.3ds");
    m_SAQ = resourceFromFile(tmpFile, DECODER_FLAGS::kNoMaterial);

  }

  ResourceRef
  ResourceManager::resourceFromFile(FILE& inFile, 
                                    DECODER_FLAGS::E inFlags) {

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
  ResourceManager::createData(FILE& inFile) {
    Encoder::encodeData(inFile);
  }

  void 
  ResourceManager::exportModel(Path inPath, ResourceRef inModel) {
    if (L".obj" == inPath.extension()) {
      auto tmpModel = getResource(inModel.m_id).lock();
      Exporter::ExportObj(inPath, static_pointer_cast<Model>(tmpModel));
      //Encoder::exportModelFromMem(inPath, inModel);
    }
    else {
      Encoder::exportFromFile(inPath, "obj");
    }
  }

  void
  ResourceManager::saveFile(FILE& inFile) {
    Encoder::encodeFile(inFile);
  }

  ModelInfo 
  ResourceManager::getFromFile(FILE& inFile) {
    return Decoder::decodeGiData(inFile);
  }


  void 
  Subdivide(Vector<SimpleVertex> & inVertices, Vector<Triangle> & inTriangles) {
    Vector<Triangle> newTriangles;
    Vector<SimpleVertex> newVertices;

    for (const auto & triangle : inTriangles) {
      int v1 = triangle.v1;
      int v2 = triangle.v2;
      int v3 = triangle.v3;

      int v4 = newVertices.size();
      int v5 = v4 + 1;
      int v6 = v4 + 2;

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

      // Agrega los nuevos vértices al vector de vértices
      newVertices.push_back(midPoint1);
      newVertices.push_back(midPoint2);
      newVertices.push_back(midPoint3);

      // Crea los nuevos triángulos
      newTriangles.push_back({ v1, v4, v6 });
      newTriangles.push_back({ v4, v2, v5 });
      newTriangles.push_back({ v4, v5, v6 });
      newTriangles.push_back({ v6, v5, v3 });
    }

    // Reemplaza los vértices y triángulos originales con los nuevos
    inVertices = newVertices;
    inTriangles = newTriangles;
  }


  ResourceRef
  ResourceManager::createSphere(int32 numTriangles) {
    float radius = 1;
    uint32 sectors = MIN_SPHERE_SECTOR;
    for (int32 i = MIN_SPHERE_SECTOR; ((numTriangles % i) == 0); i += 3) {
      sectors = i;
    }
    sectors = 9;
    uint32 stacks = (((numTriangles / sectors) - 2) / 2) + 2;

    uint32 sphereSectors = sectors < MIN_SPHERE_SECTOR ? MIN_SPHERE_SECTOR : sectors;
    uint32 spehereStacks = stacks < MIN_SPHERE_STACK ? MIN_SPHERE_STACK : stacks;

    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / radius;
    float s, t;

    float sectorStep = 2 * Math::PI / sphereSectors;
    float stackStep = Math::PI / spehereStacks;
    float sectorAngle, stackAngle;

    Vector<SimpleVertex> sphereVertices;
    Vector<uint32> sphereIndices;
    Vector<ResourceRef> sphereTextures;
    SimpleVertex vertex;
    vertex.Tang = Vector3(1.0f, 1.0f, 1.0f);
    vertex.BiNor = Vector3(1.0f, 1.0f, 1.0f);

    //Vertices
    for (uint32 i = 1; i < spehereStacks-2; ++i) {
      stackAngle = Math::PI / 2 - i * stackStep;
      xy = radius * Math::cos(stackAngle);
      z = radius * Math::sin(stackAngle);

      for (uint32 j = 1; j <= sphereSectors; ++j) {
        sectorAngle = j * sectorStep;
        //Vertex
        x = xy * Math::cos(sectorAngle);
        y = xy * Math::sin(sectorAngle);
        vertex.Pos = Vector3(x, y, z);
        //Normal
        nx = x * lengthInv;
        ny = y * lengthInv;
        nz = z * lengthInv;
        vertex.Nor = Vector3(nx, ny, nz);
        //Texcoords
        s = (float)j / sphereSectors;
        t = (float)i / spehereStacks;
        vertex.Tex = Vector2(s, t);

        //vertex.Pos.normalize();
        //vertex.Nor.normalize();
        vertex.Tex.normalize();
        sphereVertices.push_back(vertex);
      }
    }

    //Indices
    uint32 k1, k2;
    for (uint32 i = 1; i < spehereStacks-2; ++i) {
      k1 = i * (sphereSectors + 1);
      k2 = k1 + sphereSectors + 1;

      for (uint32 j = 1; j < sphereSectors; ++j, ++k1, ++k2) {
        if (i != 0) {
          sphereIndices.push_back(k1);
          sphereIndices.push_back(k2);
          sphereIndices.push_back(k1 + 1);
        }

        if (i != (spehereStacks - 1)) {
          sphereIndices.push_back(k1 + 1);
          sphereIndices.push_back(k2);
          sphereIndices.push_back(k2 + 1);
        }
      }

    }

    /*const float X = 0.525731112119133606;
    const float Z = 0.850650808352039932;

    Vector<SimpleVertex> sphereVertices;
    Vector<Triangle> sphereTriangles;
    Vector<ResourceRef> sphereTextures;
    SimpleVertex vertex;
    vertex.Tang = Vector3(1.0f, 1.0f, 1.0f);
    vertex.BiNor = Vector3(1.0f, 1.0f, 1.0f);*/

    //1
    //vertex.Pos = { -X, 0.0f, Z  };
    //sphereVertices.push_back(vertex);
    ////2
    //vertex.Pos = { X, 0.0f, Z   };
    //vertex.Nor = { 1.0f, 0.0f, 0.0f };
    //sphereVertices.push_back(vertex);
    ////3
    //vertex.Pos = { -X, 0.0f, -Z };
    //vertex.Nor = { 0.0f, 1.0f, 0.0f };
    //sphereVertices.push_back(vertex);
    ////4
    //vertex.Pos = { X, 0.0f, -Z  };
    //vertex.Nor = { 1.0f, 1.0f, 0.0f};
    //sphereVertices.push_back(vertex);
    ////5
    //vertex.Pos = { 0.0f, Z, X   };
    //sphereVertices.push_back(vertex);
    ////6
    //vertex.Pos = { 0.0f, Z, -X  };
    //vertex.Nor = { 1.0f, 0.0f, 0.0f};
    //sphereVertices.push_back(vertex);
    ////7
    //vertex.Pos = { 0.0f, -Z, X  };
    //vertex.Nor = { 0.0f, 1.0f, 0.0f };
    //sphereVertices.push_back(vertex);
    ////8
    //vertex.Pos = { 0.0f, -Z, -X };
    //vertex.Nor = { 1.0f, 1.0f, 0.0f };
    //sphereVertices.push_back(vertex);
    ////9
    //vertex.Pos = { Z, X, 0.0f   };
    //sphereVertices.push_back(vertex);
    ////10
    //vertex.Pos = { -Z, X, 0.0f  };
    //vertex.Nor = { 1.0f, 0.0f, 0.0f };
    //sphereVertices.push_back(vertex);
    ////11
    //vertex.Pos = { Z, -X, 0.0f  };
    //vertex.Nor = { 0.0f, 1.0f, 0.0f };
    //sphereVertices.push_back(vertex);
    ////12
    //vertex.Pos = { -Z, -X, 0.0f };
    //vertex.Nor = { 1.0f, 1.0f, 0.0f };
    //sphereVertices.push_back(vertex);

    /*sphereTriangles.push_back({0, 1, 4});
    sphereTriangles.push_back({1, 9, 4});
    sphereTriangles.push_back({4, 9, 5});
    sphereTriangles.push_back({5, 9, 3});
    sphereTriangles.push_back({2, 3, 7});
    sphereTriangles.push_back({3, 2, 5});
    sphereTriangles.push_back({7, 10,2 });
    sphereTriangles.push_back({0, 8, 10});
    sphereTriangles.push_back({0, 4, 8 });
    sphereTriangles.push_back({8, 2, 10});
    sphereTriangles.push_back({8, 4, 5 });
    sphereTriangles.push_back({8, 5, 2 });
    sphereTriangles.push_back({1, 0, 6 });
    sphereTriangles.push_back({11, 1, 6});
    sphereTriangles.push_back({3, 9, 11});
    sphereTriangles.push_back({6, 10, 7});
    sphereTriangles.push_back({3, 11, 7});
    sphereTriangles.push_back({11, 6, 7});
    sphereTriangles.push_back({6, 0, 10});
    sphereTriangles.push_back({9, 1, 11}); */
     
    /*sphereTriangles.push_back({0, 4, 1});
    sphereTriangles.push_back({ 0,9,4 });
    sphereTriangles.push_back({ 9,5,4 });
    sphereTriangles.push_back({ 4,5,8 });
    sphereTriangles.push_back({ 4,8,1 });
    sphereTriangles.push_back({ 8,10,1});
    sphereTriangles.push_back({ 8,3,10});
    sphereTriangles.push_back({ 5,3,8 });
    sphereTriangles.push_back({ 5,2,3 });
    sphereTriangles.push_back({ 2,7,3 });
    sphereTriangles.push_back({ 7,10,3});
    sphereTriangles.push_back({ 7,6,10});
    sphereTriangles.push_back({ 7,11,6});
    sphereTriangles.push_back({ 11,0,6});
    sphereTriangles.push_back({ 0,1,6 });
    sphereTriangles.push_back({ 6,1,10});
    sphereTriangles.push_back({ 9,0,11});
    sphereTriangles.push_back({ 9,11,2});
    sphereTriangles.push_back({ 9,2,5 });
    sphereTriangles.push_back({ 7,2,11});

    int currentTriangleCount = sphereTriangles.size();*/

    // Realiza subdivisiones hasta alcanzar el número deseado de triángulos
    //while (currentTriangleCount < numTriangles) {
    //    Subdivide(sphereVertices, sphereTriangles);
    //    currentTriangleCount = sphereTriangles.size();
    //}

    // Calcular las normales
    /*for (const auto & triangle : sphereTriangles) {
      SimpleVertex & v1 = sphereVertices[triangle.v1];
      SimpleVertex & v2 = sphereVertices[triangle.v2];
      SimpleVertex & v3 = sphereVertices[triangle.v3];

      float ux = v2.Pos.x - v1.Pos.x;
      float uy = v2.Pos.y - v1.Pos.y;
      float uz = v2.Pos.z - v1.Pos.z;

      float vx = v3.Pos.x - v1.Pos.x;
      float vy = v3.Pos.y - v1.Pos.y;
      float vz = v3.Pos.z - v1.Pos.z;

      float nx = uy * vz - uz * vy;
      float ny = uz * vx - ux * vz;
      float nz = ux * vy - uy * vx;

      v1.Pos.normalize();
      v2.Pos.normalize();
      v3.Pos.normalize();

      v1.Nor.x += nx;
      v1.Nor.y += ny;
      v1.Nor.z += nz;

      v2.Nor.x += nx;
      v2.Nor.y += ny;
      v2.Nor.z += nz;

      v3.Nor.x += nx;
      v3.Nor.y += ny;
      v3.Nor.z += nz;
    }*/

    // Normalizar las normales
    /*for (auto & vertex : sphereVertices) {
      vertex.Nor.normalize();
    }*/

    // Calcular las coordenadas de textura
    /*for (auto & vertex : sphereVertices) {
      float theta = std::atan2(vertex.Pos.x, vertex.Pos.z);
      float phi = std::acos(vertex.Pos.y);

      vertex.Tex.x = theta / (2 * M_PI) + 0.5f;
      vertex.Tex.y = phi / M_PI;
    }*/


    /*Vector<uint32> sphereIndices;

    for (auto tmpIter : sphereTriangles) {
      sphereIndices.push_back(tmpIter.v1);
      sphereIndices.push_back(tmpIter.v2);
      sphereIndices.push_back(tmpIter.v3);
    }*/

    sphereTextures.push_back(m_missingTextureRef);
    Vector<SharedPtr<Mesh>> tmpMeshes;
    tmpMeshes.reserve(1);
    auto tmpMesh = make_shared<Mesh>(sphereVertices, sphereIndices, sphereTextures);
    tmpMeshes.emplace(tmpMeshes.end(), tmpMesh);

    Vector<ResourceRef> tmpMaterials;
    tmpMaterials.reserve(1);
    tmpMaterials.emplace(tmpMaterials.end(), m_missingTextureRef);

    auto tmpRef = createModelFromMem(tmpMeshes, tmpMaterials);

    return tmpRef;

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

    //Obj icon.
    FILE tmpObjIcon("Resources/Icons/FileModelOBJ.png");
    m_objIcon = Decoder::decodeData(tmpObjIcon);

    //FBX icon.
    FILE tmpFbxIcon("Resources/Icons/FileModelFBX.png");
    m_fbxIcon = Decoder::decodeData(tmpFbxIcon);

    //Mtl icon.
    FILE tmpMtlIcon("Resources/Icons/FileMaterialMtl.png");
    m_mtlIcon = Decoder::decodeData(tmpMtlIcon);

    //PNG icon.
    FILE tmpPNGIcon("Resources/Icons/FileTexturePNG.png");
    m_pngIcon = Decoder::decodeData(tmpPNGIcon);

    //JPG icon.
    FILE tmpJPGIcon("Resources/Icons/FileTextureJPG.png");
    m_jpgIcon = Decoder::decodeData(tmpJPGIcon);


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