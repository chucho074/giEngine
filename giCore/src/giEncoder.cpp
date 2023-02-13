/**
 * @file    giEncoder.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/05/2022
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giEncoder.h"
#include <yaml-cpp/yaml.h>
#include "giBaseConfig.h"
#include "giSceneGraph.h"
#include "giSceneNode.h"
#include "giStaticMesh.h"
#include "giModel.h"
#include "giMesh.h"
#include "giCamera.h"

namespace giEngineSDK {

  static void
  encodeNode(YAML::Emitter& inEmitter, SharedPtr<SceneNode> inNode);

  void 
  Encoder::encodeFile(FILE& inFileData) {
    switch (inFileData.m_extension) {
    case EXTENSION_TYPE::kgiProject: {
      encodeGiProject(inFileData);
      break;
    }
    case EXTENSION_TYPE::kgiScene: {
      encodeGiScene(inFileData);
      break;
    }
    case EXTENSION_TYPE::kOBJ: {
      encodeData(inFileData);
      break;
    }


    default: {
      break;
    }
    }
  }
  
  void 
  Encoder::encodeGiProject(FILE& inFileData) {
    auto& configs = g_engineConfigs();
    YAML::Emitter tmpOutput;
    tmpOutput << YAML::BeginMap;
    tmpOutput << YAML::Key << "Project Name";
    tmpOutput << YAML::Value << configs.s_projectName;

    tmpOutput << YAML::Key << "Project Path";
    tmpOutput << YAML::Value << configs.s_projectPath.string();

    tmpOutput << YAML::Key << "Content Path";
    tmpOutput << YAML::Value << configs.s_contentPath.string();

    tmpOutput << YAML::Key << "Active Graphic API";
    tmpOutput << YAML::Value << configs.s_activeGraphicApi;

    tmpOutput << YAML::Key << "Omniverse stage";
    tmpOutput << YAML::Value << configs.s_existingStage;

    tmpOutput << YAML::EndMap;

    ofstream fout(inFileData.m_path);
    fout << tmpOutput.c_str();

  }

  void 
  Encoder::encodeGiScene(FILE& inFileData)  {

    auto& SG = g_sceneGraph();

    YAML::Emitter tmpOut;

    tmpOut << YAML::BeginMap;

    tmpOut << YAML::Key << "Scene Name";
    tmpOut << YAML::Value << SG.m_sceneName;

    tmpOut << YAML::Key << "Number of actors in scene";
    tmpOut << YAML::Value << SG.m_numActors;

    tmpOut << YAML::Key << "Actors in Scene" << YAML::Value << YAML::BeginSeq;

    encodeNode(tmpOut, SG.getRoot());

    tmpOut << YAML::EndSeq;
    tmpOut << YAML::EndMap;

    ofstream fout(inFileData.m_path);
    fout << tmpOut.c_str();
  }

  void 
  Encoder::encodeData(FILE& inFile) {
    
    YAML::Emitter tmpOut;


    //Models
    if (EXTENSION_TYPE::E::kFBX == inFile.m_extension
      || EXTENSION_TYPE::E::k3DS == inFile.m_extension
      || EXTENSION_TYPE::E::kOBJ == inFile.m_extension) {

      tmpOut << YAML::BeginMap;
      tmpOut << YAML::Key << "Model data" << YAML::Value << YAML::BeginSeq;
      tmpOut << YAML::BeginMap;

      //Search for data.
      ModelInfo tmpData; 
      Decoder::readBasicModel(inFile, tmpData);

      //Triangles data
      tmpOut << YAML::Key << "Triangles";
      tmpOut << YAML::Value << tmpData.totalTriangles;

      tmpOut << YAML::Key << "Vertices";
      tmpOut << YAML::Value << tmpData.totalVertices;
      
      tmpOut << YAML::Key << "Index";
      tmpOut << YAML::Value << tmpData.totalIndex;
      
      tmpOut << YAML::Key << "Faces";
      tmpOut << YAML::Value << tmpData.totalFaces;
      
      tmpOut << YAML::Key << "Meshes";
      tmpOut << YAML::Value << tmpData.totalMeshes;
      
      tmpOut << YAML::Key << "Materials";
      tmpOut << YAML::Value << tmpData.totalMaterials;
      
      tmpOut << YAML::Key << "Animations";
      tmpOut << YAML::Value << tmpData.totalAnimations;


      tmpOut << YAML::EndMap;
      tmpOut << YAML::EndSeq;
      tmpOut << YAML::EndMap;
    }

    else {
      tmpOut << YAML::BeginMap;
      tmpOut << YAML::Key << "Default data";
      tmpOut << YAML::EndMap;
    }

    ofstream fout(inFile.m_path.string()+ ".giData");
    fout << tmpOut.c_str();

  }

  static void
  encodeNode(YAML::Emitter& inEmitter, SharedPtr<SceneNode> inNode) {
    auto& configs = g_engineConfigs();
    auto& RM = g_resourceManager();

    inEmitter << YAML::BeginMap;
    // Scene Node: 1203912021441
    inEmitter << YAML::Key << "Scene Node";
    inEmitter << YAML::Value << inNode->m_nodeId;
    //Parent: 1203912021442 / None (None in case of root)
    inEmitter << YAML::Key << "Parent";
    //Verify the parent
    if((nullptr != inNode->m_parent.lock().get())) { //Has a parent
      inEmitter << YAML::Value << inNode->m_parent.lock()->m_nodeId;
    }
    else { //Doesn't have a parent
      inEmitter << YAML::Value << "None";
    }
    //Actor: 
    auto& tmpActor = inNode->m_actor;
    // Actor Name: Tree1
    inEmitter << YAML::Key << "Actor Name";
    inEmitter << YAML::Value << tmpActor->m_actorName;
    // Actor ID: 12353512331
    inEmitter << YAML::Key << "Actor ID";
    inEmitter << YAML::Value << tmpActor->m_actorId;
    // Transform: 
    inEmitter << YAML::Key << "Transform" << YAML::BeginSeq; {
      //Translation
      inEmitter << YAML::BeginMap; {
        inEmitter << YAML::Key << "Translation" << YAML::Value;
        inEmitter << YAML::BeginMap; {
          inEmitter << YAML::Flow << YAML::BeginMap; {
            inEmitter << YAML::Key << "X";
            inEmitter << YAML::Value << tmpActor->m_transform.m_translation.x;
            inEmitter << YAML::Key << "Y";
            inEmitter << YAML::Value << tmpActor->m_transform.m_translation.y;
            inEmitter << YAML::Key << "Z";
            inEmitter << YAML::Value << tmpActor->m_transform.m_translation.z;
          }
          inEmitter << YAML::EndMap;
        }
        inEmitter << YAML::EndMap;
      }
      inEmitter << YAML::EndMap;
      //Scale
      inEmitter << YAML::BeginMap; {
        inEmitter << YAML::Key << "Scale" << YAML::Value;
        inEmitter << YAML::BeginMap; {
          inEmitter << YAML::Flow << YAML::BeginMap; {
            inEmitter << YAML::Key << "X";
            inEmitter << YAML::Value << tmpActor->m_transform.m_scale.x;
            inEmitter << YAML::Key << "Y";
            inEmitter << YAML::Value << tmpActor->m_transform.m_scale.y;
            inEmitter << YAML::Key << "Z";
            inEmitter << YAML::Value << tmpActor->m_transform.m_scale.z;
          }
          inEmitter << YAML::EndMap;
        }
        inEmitter << YAML::EndMap;
      }
      inEmitter << YAML::EndMap;
      //Rotation
      inEmitter << YAML::BeginMap; {
        inEmitter << YAML::Key << "Rotation in Quaternion" << YAML::Value;
        inEmitter << YAML::BeginMap; {
          inEmitter << YAML::Flow << YAML::BeginMap; {
            inEmitter << YAML::Key << "X";
            inEmitter << YAML::Value << tmpActor->m_transform.m_rotationQuat.x;
            inEmitter << YAML::Key << "Y";
            inEmitter << YAML::Value << tmpActor->m_transform.m_rotationQuat.y;
            inEmitter << YAML::Key << "Z";
            inEmitter << YAML::Value << tmpActor->m_transform.m_rotationQuat.z;
            inEmitter << YAML::Key << "W";
            inEmitter << YAML::Value << tmpActor->m_transform.m_rotationQuat.w;
          }
          inEmitter << YAML::EndMap;
        }
        inEmitter << YAML::EndMap;
      }
      inEmitter << YAML::EndMap;
    }
    inEmitter << YAML::EndSeq;
    //OmniPath
    auto iter = configs.s_activePlugins.find(GIPLUGINS::kOmniverse);
    if (iter != configs.s_activePlugins.end()) {
      inEmitter << YAML::Key << "OmniPath";
      inEmitter << YAML::Value << tmpActor->m_omniRefPath;
    }
    //Components
    inEmitter << YAML::Key << "Components" << YAML::Value << YAML::BeginSeq;
    if(tmpActor->m_components.empty()) {
      inEmitter << YAML::Key << "None";
    }
    else {
      for(auto& iterComp : tmpActor->m_components) {
        if(COMPONENT_TYPE::E::kStaticMesh == iterComp.first) {
          inEmitter << YAML::BeginMap; {
            auto tmpStaticMesh = static_pointer_cast<StaticMesh>(iterComp.second);
            inEmitter << YAML::Key << "Model";
            inEmitter << YAML::Value << tmpStaticMesh->getModel().m_id;
            auto tmpResource = static_pointer_cast<Model>(RM.getResource(tmpStaticMesh->getModel().m_id).lock());
            inEmitter << YAML::Key << "Number of Materials in the model";
            inEmitter << YAML::Value << tmpResource->getNumTextures();
            inEmitter << YAML::Key << "Number of meshes in the model";
            inEmitter << YAML::Value << tmpResource->m_meshes.size();
            inEmitter << YAML::Key << "Path to original model";
            inEmitter << YAML::Value << tmpResource->m_directory.string();
          }
          inEmitter << YAML::EndMap;
        }
        else if(COMPONENT_TYPE::E::kCamera == iterComp.first) {
          inEmitter << YAML::BeginMap; {
            //Camera Type
            inEmitter << YAML::Key << "Camera Type";
            auto tmpCamera = static_pointer_cast<Camera>(iterComp.second);
            inEmitter << YAML::Value << tmpCamera->m_cameraType;
            //Eye Vector
            inEmitter << YAML::Key << "Eye";
            inEmitter << YAML::Flow << YAML::BeginMap; {
              inEmitter << YAML::Key << "X";
              inEmitter << YAML::Value << tmpCamera->m_eye.x;
              inEmitter << YAML::Key << "Y";
              inEmitter << YAML::Value << tmpCamera->m_eye.y;
              inEmitter << YAML::Key << "Z";
              inEmitter << YAML::Value << tmpCamera->m_eye.z;
            }
            inEmitter << YAML::EndMap;
            //At Vector
            inEmitter << YAML::Key << "At";
            inEmitter << YAML::Flow << YAML::BeginMap; {
              inEmitter << YAML::Key << "X";
              inEmitter << YAML::Value << tmpCamera->m_at.x;
              inEmitter << YAML::Key << "Y";
              inEmitter << YAML::Value << tmpCamera->m_at.y;
              inEmitter << YAML::Key << "Z";
              inEmitter << YAML::Value << tmpCamera->m_at.z;
            }
            inEmitter << YAML::EndMap;
            //Up Vector
            inEmitter << YAML::Key << "Up";
            inEmitter << YAML::Flow << YAML::BeginMap; {
              inEmitter << YAML::Key << "X";
              inEmitter << YAML::Value << tmpCamera->m_upVect.x;
              inEmitter << YAML::Key << "Y";
              inEmitter << YAML::Value << tmpCamera->m_upVect.y;
              inEmitter << YAML::Key << "Z";
              inEmitter << YAML::Value << tmpCamera->m_upVect.z;
            }
            inEmitter << YAML::EndMap;
            //Speed 
            inEmitter << YAML::Key << "Speed";
            inEmitter << YAML::Value << tmpCamera->m_speed;
          }
          inEmitter << YAML::EndMap;
        }
      }
    }
    inEmitter << YAML::EndSeq;

    //Childs
    inEmitter << YAML::Key << "Childs" << YAML::Value << YAML::BeginSeq;

    if (inNode->m_childs.empty()) {
      inEmitter << YAML::Key << "None";
    }
    else {
      for (auto iterChilds : inNode->m_childs) {
        encodeNode(inEmitter, iterChilds);
      }
    }

    inEmitter << YAML::EndSeq;
    inEmitter << YAML::EndMap;
  }
}