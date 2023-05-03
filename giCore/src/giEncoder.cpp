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
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/Exporter.hpp>      // C++ exporter interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <OpenMesh/Core/IO/Options.hh>
#include <OpenMesh/Core/IO/OMFormat.hh>
#include <OpenMesh/Core/IO/writer/OMWriter.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

#include "giBaseConfig.h"
#include "giSceneGraph.h"
#include "giSceneNode.h"
#include "giStaticMesh.h"
#include "giModel.h"
#include "giMesh.h"
#include "giCamera.h"

typedef OpenMesh::TriMesh_ArrayKernelT<>  MyMesh;

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
      
      break;
    }


    default: {
      break;
    }
    }
  }
  
  void 
  Encoder::encodeOBJ(Path inPath, ResourceRef inModel) {
    
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

  void 
  Encoder::exportFromFile(Path inPath, String inFileType) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(inPath.string(), 
                                             aiProcess_Triangulate   
                                             | aiProcess_FlipUVs);

    // Exportar el modelo
    Assimp::Exporter exporter;
    inPath.replace_extension(inFileType);
    exporter.Export(scene, inFileType, inPath.string());
  }

  void 
  Encoder::exportModelFromMem(Path inPath, ResourceRef inModel) {
    auto& RM = g_resourceManager();

    MyMesh outMesh;

    //Get the geometry.

    auto tmpResource = RM.getResource(inModel.m_id);

    auto tmpModel = static_pointer_cast<Model>(tmpResource.lock());

    auto& tmpVertex = tmpModel->m_meshes.at(0)->m_vertexVector;

    auto& tmpIndex = tmpModel->m_meshes.at(0)->m_facesList;
    
    outMesh.request_vertex_texcoords2D();
    outMesh.request_vertex_normals();
    outMesh.request_face_colors();

    //OpenMesh::HPropHandleT<String> MyMaterial;
    //outMesh.add_property(MyMaterial, "MyMaterial");

    //Set the vertex data.
    const int32 a = tmpVertex.size();
    Vector<MyMesh::VertexHandle> vhadle;
    vhadle.reserve(a);

    for (int32 i = 0; i < a; ++i) {
      vhadle.push_back(outMesh.add_vertex(MyMesh::Point(tmpVertex[i].Pos.x, 
                                                        tmpVertex[i].Pos.y, 
                                                        tmpVertex[i].Pos.z)));
    }

    for (int32 i = 0; i < a; ++i) {
      //Add the normals 
      outMesh.set_normal(vhadle.at(i), MyMesh::Normal(tmpVertex[i].Nor.x, tmpVertex[i].Nor.y, tmpVertex[i].Nor.z));
    }

    for (int32 i = 0; i < a; ++i) {
      //Add the Texcoords 
      outMesh.set_texcoord2D(vhadle.at(i), MyMesh::TexCoord2D(tmpVertex[i].Tex.x, tmpVertex[i].Tex.y));
    }

    //Set the indices data
    Vector<MyMesh::VertexHandle> faceVhandles;
    for(int32 i = 0; i+3 <= tmpIndex.size(); i += 3) {
      faceVhandles.clear();
      faceVhandles.push_back(vhadle.at(tmpIndex.at(i)));
      faceVhandles.push_back(vhadle.at(tmpIndex.at(i+1)));
      faceVhandles.push_back(vhadle.at(tmpIndex.at(i+2)));
      outMesh.add_face(faceVhandles);
    }

    //outMesh.update_normals();
    
    //Add the mtl file
    MyMesh::FaceIter f_it, f_end = outMesh.faces_end();
    for (f_it = outMesh.faces_begin(); f_it != f_end; ++f_it) {
      outMesh.set_color(*f_it, MyMesh::Color(255, 255, 255));
    }


    OpenMesh::IO::Options opt;
    opt += OpenMesh::IO::Options::VertexNormal;
    opt += OpenMesh::IO::Options::VertexTexCoord;
    opt += OpenMesh::IO::Options::FaceColor;


    OpenMesh::IO::write_mesh(outMesh, inPath.string(), opt);


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