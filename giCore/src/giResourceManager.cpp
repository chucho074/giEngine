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

  class giIter {
   public:
    giIter() =default;
    ~giIter() =default;

    uint32 iter = 0;

    void
    incrementIter() {
      this->iter++;
    }

    uint32
    getIter(){
      return this->iter;
    }
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
    
    /*Vector<Vector3> subdivision_0_positions{
        Vector3 {  0.0000000e+00,  0.0000000e+00,  1.0000000e+00 },
        Vector3 {  8.9442718e-01,  0.0000000e+00,  4.4721359e-01 },
        Vector3 {  2.7639320e-01,  8.5065079e-01,  4.4721359e-01 },
        Vector3 { -7.2360682e-01,  5.2573109e-01,  4.4721359e-01 },
        Vector3 { -7.2360682e-01, -5.2573109e-01,  4.4721359e-01 },
        Vector3 {  2.7639320e-01, -8.5065079e-01,  4.4721359e-01 },
        Vector3 {  7.2360682e-01,  5.2573109e-01, -4.4721359e-01 },
        Vector3 { -2.7639320e-01,  8.5065079e-01, -4.4721359e-01 },
        Vector3 { -8.9442718e-01,  1.0953574e-16, -4.4721359e-01 },
        Vector3 { -2.7639320e-01, -8.5065079e-01, -4.4721359e-01 },
        Vector3 {  7.2360682e-01, -5.2573109e-01, -4.4721359e-01 },
        Vector3 {  0.0000000e+00,  0.0000000e+00, -1.0000000e+00 }
    };

    Vector<Vector3> subdivision_0_indices {
        Vector3 {  0,  1,  2 },
        Vector3 {  0,  2,  3 },
        Vector3 {  0,  3,  4 },
        Vector3 {  0,  4,  5 },
        Vector3 {  0,  5,  1 },
        Vector3 {  1,  6,  2 },
        Vector3 {  2,  7,  3 },
        Vector3 {  3,  8,  4 },
        Vector3 {  4,  9,  5 },
        Vector3 {  5, 10,  1 },
        Vector3 {  2,  6,  7 },
        Vector3 {  3,  7,  8 },
        Vector3 {  4,  8,  9 },
        Vector3 {  5,  9, 10 },
        Vector3 {  1, 10,  6 },
        Vector3 {  6, 11,  7 },
        Vector3 {  7, 11,  8 },
        Vector3 {  8, 11,  9 },
        Vector3 {  9, 11, 10 },
        Vector3 { 10, 11,  6 }
    };*/


    //Sectors = slices of the sphere.
    //Stacks  = divisions of the slices.

    float radius = 1;
    uint32 sectors = MIN_SPHERE_SECTOR;
    for (int32 i = MIN_SPHERE_SECTOR; (((numTriangles) % i) == 0); i += 3) {
      sectors = i;
    }
    
    //uint32 stacks = (((numTriangles / sectors) - 2) / 2) + 2;
    uint32 stacks = ((numTriangles) / sectors) / 2;

    uint32 sphereSectors = sectors < MIN_SPHERE_SECTOR ? MIN_SPHERE_SECTOR : sectors;
    uint32 sphereStacks = stacks < MIN_SPHERE_STACK ? MIN_SPHERE_STACK : stacks;

    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / radius;
    float s, t;

    float sectorStep = 2 * Math::PI / sphereSectors;
    //float stackStep = Math::PI / sphereStacks;
    float sectorAngle, stackAngle;

    Vector<SimpleVertex> sphereVertices;
    Vector<uint32> sphereIndices;
    Vector<ResourceRef> sphereTextures;
    SimpleVertex vertex;
    vertex.Tang = Vector3(1.0f, 1.0f, 1.0f);
    vertex.BiNor = Vector3(1.0f, 1.0f, 1.0f);

    //sphereVertices.resize((numTriangles*3) +1);
    sphereVertices.resize((sphereSectors * (sphereStacks-1))+2);
    SharedPtr<giIter> tmpIter = make_shared<giIter>();
    tmpIter->incrementIter();

    //First Vertex data.
    SimpleVertex tmpVertex;
    tmpVertex.Pos = {0, 1, 0};
    tmpVertex.Nor = {0, 1, 0};
    tmpVertex.Tex = {0.f, 1.f};
    sphereVertices[0] = tmpVertex;

    //Vertices
    for (uint32 i = 0; i < sphereStacks - 1; ++i) {
      auto phi = Math::PI * double(i + 1) / double(sphereStacks);
      
      /*stackAngle = Math::PI / 2 - i * stackStep;
      xy = radius * Math::cos(stackAngle);
      z = radius * Math::sin(stackAngle);*/

      for (uint32 j = 0; j < sphereSectors; ++j) {
        //sectorAngle = j * sectorStep;

        sectorAngle = 2.0 * Math::PI * double(j) / double(sphereSectors);
        x = sin(phi) * cos(sectorAngle);
        y = cos(phi);
        z = sin(phi) * sin(sectorAngle);

        //Vertex
        //x = xy * Math::cos(sectorAngle);
        //y = xy * Math::sin(sectorAngle);
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
        if(tmpIter->getIter() >= ((sphereSectors * (sphereStacks - 1)) + 2)){
          __debugbreak();
          tmpIter->iter = tmpIter->iter - 1;
          break;
        }
        else {
          sphereVertices[tmpIter->getIter()] = vertex;
          tmpIter->incrementIter();
        }
      }
    }
    //Last vertex data.
    tmpVertex.Pos = { 0, -1, 0};
    tmpVertex.Nor = { 0, -1, 0};
    tmpVertex.Tex = { 0.5f, 0.5f };
    sphereVertices[tmpIter->getIter()] = tmpVertex;
     
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
      sphereIndices.push_back(tmpIter->getIter());
      sphereIndices.push_back(i0);
      sphereIndices.push_back(i1);
    }
    /*for(int32 i = 1; i <= sphereSectors; ++i) {
      if (i < sphereSectors) {
        sphereIndices.push_back(1);
        sphereIndices.push_back(1 + i);
        sphereIndices.push_back(2 + i);
      }
      else {
        sphereIndices.push_back(1);
        sphereIndices.push_back(1 + sphereSectors);
        sphereIndices.push_back(2);
      }
    }

    sphereIndices.push_back(sphereSectors + 2);
    sphereIndices.push_back(sphereSectors + 1);
    sphereIndices.push_back(2);*/


    //Middle triangles
    int32 tmpSize = sphereVertices.size();


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

    //uint32 tmpIndex = tmpSize - sphereSectors;

    //for(int32 i = 0; i < tmpIndex; ++i) {
    //  
    //  sphereIndices.push_back(i + 3);
    //  sphereIndices.push_back(i + 2);
    //  sphereIndices.push_back(i + sphereSectors + 2);

    //  sphereIndices.push_back(i + 3);
    //  sphereIndices.push_back(i + sphereSectors + 2);
    //  sphereIndices.push_back(i + sphereSectors + 3);


    //              // IDK WTF IS IT
    //  //sphereIndices.push_back(i + 1);
    //  //sphereIndices.push_back(sphereSectors + 2 + 1);
    //  //sphereIndices.push_back(sphereSectors + i);
    //  //sphereIndices.push_back(sphereSectors + 1 + i);
    //  //sphereIndices.push_back(sphereSectors + 2 + i);
    //  //sphereIndices.push_back((sphereSectors *2) + 1 + i);
    //}

    //uint32 k1,k2;
    //for(int32 i = 0; i < sphereStacks - 1; ++i) {
    //  k1 = (i * sphereSectors);
    //  k2 = k1 + sphereSectors;
    //  for(int32 j = 0; j < sphereSectors; ++j, ++k1, ++k2) { 
    //    //if (i != 0) {
    //      sphereIndices.push_back(k1);
    //      sphereIndices.push_back(k2);
    //      sphereIndices.push_back(k1 + 1);
    //    //}
    //    //if (i != (sphereStacks)) {
    //      sphereIndices.push_back(k1 + 1);
    //      sphereIndices.push_back(k2);
    //      sphereIndices.push_back(k2 + 1);
    //    //}
    //  }
    //}

    /*
    uint32 k1,k2;
    for(int32 i = 0; i < sphereStacks - 1; ++i) {
      k1 = (i * sphereSectors) + 1;
      k2 = k1 + sphereSectors;
      for(int32 j = 0; j < sphereSectors; ++j, ++k1, ++k2) { 
        if (i != 0) {
          sphereIndices.push_back(k1);
          sphereIndices.push_back(k2);
          sphereIndices.push_back(k1 + 1);
        }

        if (i != (sphereStacks)) {
          sphereIndices.push_back(k1 + 1);
          sphereIndices.push_back(k2);
          sphereIndices.push_back(k2 + 1);
        }
      }
    }
    */
    /*uint32 k1, k2;
    for (uint32 i = 1; i < sphereStacks-1; ++i) {
      k1 = i * (sphereSectors + 1);
      k2 = k1 + sphereSectors + 1;

      for (uint32 j = 1; j < sphereSectors-1; ++j, ++k1, ++k2) {
        if (i != 0) {
          sphereIndices.push_back(k1);
          sphereIndices.push_back(k2);
          sphereIndices.push_back(k1 + 1);
        }

        if (i != (sphereStacks - 1)) {
          sphereIndices.push_back(k1 + 1);
          sphereIndices.push_back(k2);
          sphereIndices.push_back(k2 + 1);
        }
      }*/


    
    //int32 tmpSize = sphereVertices.size();

    //Last triangles with the last vertex.
    /*for(int32 i = 1; i <= sphereSectors; ++i) {
      if (i < sphereSectors) {
        sphereIndices.push_back(tmpSize);
        sphereIndices.push_back(tmpSize - i);
        sphereIndices.push_back(tmpSize - i - 1);
      }
      else {
        sphereIndices.push_back(tmpSize);
        sphereIndices.push_back(tmpSize - sphereSectors);
        sphereIndices.push_back(tmpSize - 1);
      }
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