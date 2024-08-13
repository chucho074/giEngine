/**
 * @file    giDecoder.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    08/07/2022
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giDecoder.h"
#include <giModel.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <yaml-cpp/yaml.h>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "giResourceManager.h"
#include "giSceneGraph.h"
#include "giModel.h"
#include "giMesh.h"
#include "giTexture.h"
#include "giBaseConfig.h"

namespace giEngineSDK {

  void 
  Decoder::decodeFile(FILE& inFileData) {
    if (EXTENSION_TYPE::kgiScene == inFileData.m_extension) {
      Decoder::decodeGiScene(inFileData);

    }

    if (EXTENSION_TYPE::kgiProject == inFileData.m_extension) {
      decodeGiProject(inFileData);
    }
  }

  void
  Decoder::decodeGiProject(FILE& inFileData) {
    //auto& logger = g_logger();
    //auto& configs = g_engineConfigs();
    //auto& sgraph = g_sceneGraph();


    //ifstream tmpStream(inFileData.m_path);
    //std::stringstream tmpStr;
    //tmpStr << tmpStream.rdbuf();

    //YAML::Node tmpData = YAML::Load(tmpStr.str());
    ////Validate if is the file with the firts data in it
    //if (!tmpData["Project Name"]) {
    //  logger.SetError(ERROR_TYPE::kDecodingFile, 
    //                  "Can't open the file or the file is corrupted");
    //  return;
    //}

    ////Show the Save as window in case there are any changes to save.
    ////Close the actual project instances
    //sgraph.clearGraph();
    //RM.clearLoadedResources();

    ////Save the Project Name
    //String tmpProjectName = tmpData["Project Name"].as<String>();
    //ConsoleOut << "Deserializing " << tmpProjectName << " project." << ConsoleLine;
    //configs.s_projectName = tmpProjectName;

    ////Save the Project Path
    //Path tmpProjectPath = tmpData["Project Path"].as<String>();
    //configs.s_projectPath = tmpProjectPath;

    ////Save the active Graphics API
    //GIENGINE_API::E tmpActiveAPI = (GIENGINE_API::E)tmpData["Active Graphic API"].as<int32>();
    //configs.s_activeGraphicApi = tmpActiveAPI;

    ////Save the Omniverse Stage
    //String tmpStage = tmpData["Omniverse stage"].as<String>();
    //configs.s_existingStage = tmpStage;


    ////Sets the shadow camera                                                                       TO CHANGE
    //SharedPtr<Camera> shadowCamera = make_shared<Camera>();
    //shadowCamera->init(Degrees(75.0f).getRadians(),
    //                   1280.f / 720.f,
    //                   0.01f,
    //                   100000.0f);
    //
    //shadowCamera->setPosition({ 360.0f, 280.0f, -200.0f, 0.0f },
    //                          { 0.0f,   1.0f,    0.0f,   0.0f },
    //                          { 0.0f,   1.0f,    0.0f,   0.0f });
    //
    //SharedPtr<Actor> lightActor = make_shared<Actor>();
    //lightActor->m_actorName = "Light";
    //lightActor->addComponent(shadowCamera, COMPONENT_TYPE::kCamera);
    //sgraph.addActor(lightActor, sgraph.getRoot());



  }


  void 
  Decoder::decodeGiScene(FILE& inFileData) {
    //auto& SG = g_sceneGraph();

    //ifstream tmpStream(inFileData.m_path);
    //std::stringstream tmpStr;
    //tmpStr << tmpStream.rdbuf();

    //YAML::Node tmpData = YAML::Load(tmpStr.str());
    //if (!tmpData["Scene Name"]) {
    //  return;
    //}
    //
    //String tmpSceneName = tmpData["Scene Name"].as<String>();
    //ConsoleOut << "Deserializing " << tmpSceneName << " scene." << ConsoleLine;

    ////Getting the number of actors in the scene.
    //auto tmpNumActors = tmpData["Number of actors in scene"];

    ////There's actors in the scene.
    //if (tmpNumActors) {
    //  //Clears the scene Graph and sets the new information with the
    //  //given information from the readed file.
    //  SG.clearGraph();

    //  auto tmpActors = tmpData["Actors in Scene"];

    //  if(tmpActors) {
    //    for(auto actor : tmpActors) {
    //      auto tmpActor = make_shared<Actor>();
    //      auto tmpSceneNode = make_shared<SceneNode>();
    //      //Get the scene node ID.
    //      tmpSceneNode->m_nodeId = actor["SceneNode"].as<uint64>();
    //      //Parent
    //      if("None" != actor["Parent"].as<String>()) {
    //        auto tmpParent = actor["Parent"].as<uint64>();

    //      }
    //      //Actor name
    //      auto tmpActorName = actor["Actor Name"].as<String>();
    //      //Actor ID
    //      auto tmpActorID = actor["Actor ID"].as<int32>();
    //      //Transform
    //      auto tmpTransform = actor["Transform"];
    //      for(auto iterTransform : tmpTransform) {
    //        iterTransform["Translation"];
    //      }
    //      //Components
    //      
    //      //Childs
    //      
    //    }
    //  }

    //}
  }

  
  void
  processData(ModelInfo& inInfo, 
              aiNode* node,
              const aiScene* inScene) {
    for (uint32 i = 0; i < node->mNumMeshes; ++i) {
      aiMesh* mesh = inScene->mMeshes[node->mMeshes[i]];
      inInfo.totalVertices += mesh->mNumVertices;
      inInfo.totalFaces += mesh->mNumFaces;
      for (uint32 i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        inInfo.totalIndex += face.mNumIndices;
      }
    }
    // then do the same for each of its children
    for (uint32 i = 0; i < node->mNumChildren; i++) {
      processData(inInfo, node->mChildren[i], inScene);
    }
  }

  void 
  Decoder::readBasicModel(FILE& inFile, ModelInfo& inInfo) {
     Assimp::Importer importer;

    importer.ReadFile(inFile.m_path.string(),
                      aiProcessPreset_TargetRealtime_MaxQuality |
                      aiProcess_TransformUVCoords|
                      aiProcess_ConvertToLeftHanded |
                      aiProcess_Triangulate);

    const aiScene* tmpScene = importer.GetOrphanedScene();

    if (!tmpScene 
        || tmpScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE
        || !tmpScene->mRootNode) {
      g_logger().SetError(ERROR_TYPE::kModelLoading, "Failed to load a model");
    }

    inInfo.totalMeshes = tmpScene->mRootNode->mNumMeshes;
    inInfo.totalAnimations = tmpScene->mNumAnimations;
    inInfo.totalMaterials = tmpScene->mNumMaterials;

    processData(inInfo, tmpScene->mRootNode, tmpScene);

    inInfo.totalTriangles = inInfo.totalIndex/3;
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

  ModelInfo 
  Decoder::decodeGiData(FILE& inFile) {
    ifstream tmpStream(inFile.m_path);
    ModelInfo tmpInfo;
    std::stringstream tmpStr;
    tmpStr << tmpStream.rdbuf();

    YAML::Node tmpData = YAML::Load(tmpStr.str());
    if (tmpData["Model data"]) {
      auto tmpModelData = tmpData["Model data"];
      for (auto iterData : tmpModelData) {
        if (iterData["Triangles"]) {
          tmpInfo.totalTriangles = iterData["Triangles"].as<uint32>();
        }
        if (iterData["Vertices"]) {
          tmpInfo.totalVertices = iterData["Vertices"].as<uint32>();
        }
        if (iterData["Index"]) {
          tmpInfo.totalIndex = iterData["Index"].as<uint32>();
        }
        if (iterData["Faces"]) {
          tmpInfo.totalFaces = iterData["Faces"].as<uint32>();
        }
        if (iterData["Meshes"]) {
          tmpInfo.totalMeshes = iterData["Meshes"].as<uint32>();
        }
        if (iterData["Materials"]) {
          tmpInfo.totalMaterials = iterData["Materials"].as<uint32>();
        }
        if (iterData["Animations"]) {
          tmpInfo.totalAnimations = iterData["Animations"].as<uint32>();
        }
      }
    }
    return tmpInfo;
  }



  
}