/**
 * @file    giDetails.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/06/2022
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giDetails.h"
#include <giSpecificImplementations.h>
#include <giResource.h>
#include <giSceneGraph.h>
#include <giTransform.h>
#include <giBaseOmniverse.h>
#include <giBaseConfig.h>
#include <giResourceManager.h>
#include <giModel.h>
#include <giStaticMesh.h>
#include <giEditor.h>
#include <giDecoder.h>


Details::Details() {
  
}

void 
Details::init(void* inHandler) {
  m_windowHandle = inHandler;
}

void 
Details::update(float inDeltaTime) {
  GI_UNREFERENCED_PARAMETER(inDeltaTime);
}

void 
Details::render() {
  auto& sg = g_sceneGraph();
  auto& RM = g_resourceManager();
  //auto& gapi = g_graphicsAPI();
  ImGui::Begin("Details", nullptr, m_windowFlags);

  if (sg.getSelectedActor() != nullptr) { 
    auto tmpActor = sg.getSelectedActor();
    //Actor name
    ImGui::Text("Actor name: ");
    ImGui::SameLine();
    ImGui::InputText(" ", tmpActor->m_actorName.data(), tmpActor->m_actorName.size()+1);

    ImGui::Separator();
    if (ImGui::CollapsingHeader("Transform", ImGuiWindowFlags_NoNav)) {
    
      ImGui::DragFloat3("Position", &sg.getSelectedActor()->m_transform.m_translation.x);
      if(ImGui::IsItemEdited()) {
        auto iter = EngineConfigs::s_activePlugins.find(GIPLUGINS::kOmniverse);
        if (iter != EngineConfigs::s_activePlugins.end()) {

          if (g_omniverse().m_liveEditActivation && !tmpActor->m_omniRefPath.empty()) {
            g_omniverse().setTransformOp(tmpActor->m_transform.m_translation, 
                                         GI_OMNI_OP::kTRANSLATE,
                                         GI_OMNI_PRECISION::kDOUBLE,
                                         tmpActor->m_omniRefPath);
          }
        }
      }

      ImGui::DragFloat3("Rotation", &sg.getSelectedActor()->m_transform.m_rotation.x);
      if(ImGui::IsItemEdited()) {
        auto iter = EngineConfigs::s_activePlugins.find(GIPLUGINS::kOmniverse);
        if (iter != EngineConfigs::s_activePlugins.end()) {
          if (g_omniverse().m_liveEditActivation && !tmpActor->m_omniRefPath.empty()) {
            g_omniverse().setTransformOp(tmpActor->m_transform.m_rotation, 
                                         GI_OMNI_OP::kROTATE,
                                         GI_OMNI_PRECISION::kFLOAT,
                                         tmpActor->m_omniRefPath);
          }
        }
      }

      if(!m_scaleBlock) {
        ImGui::DragFloat3("Scale",    &sg.getSelectedActor()->m_transform.m_scale.x);
        if(ImGui::IsItemEdited()) {
          auto iter = EngineConfigs::s_activePlugins.find(GIPLUGINS::kOmniverse);
          if (iter != EngineConfigs::s_activePlugins.end()) {
            if (g_omniverse().m_liveEditActivation && !tmpActor->m_omniRefPath.empty()) {
              g_omniverse().setTransformOp(tmpActor->m_transform.m_scale, 
                                           GI_OMNI_OP::kSCALE,
                                           GI_OMNI_PRECISION::kFLOAT,
                                           tmpActor->m_omniRefPath);
            }
          }
        }
      }

      else if (m_scaleBlock) {
        ImGui::DragFloat("Scale", &sg.getSelectedActor()->m_transform.m_scale.x);
        sg.getSelectedActor()->m_transform.m_scale.y = sg.getSelectedActor()->m_transform.m_scale.x;
        sg.getSelectedActor()->m_transform.m_scale.z = sg.getSelectedActor()->m_transform.m_scale.x;
        if(ImGui::IsItemEdited()) {
          auto iter = EngineConfigs::s_activePlugins.find(GIPLUGINS::kOmniverse);
          if (iter != EngineConfigs::s_activePlugins.end()) {
            if (g_omniverse().m_liveEditActivation && !tmpActor->m_omniRefPath.empty()) {
              g_omniverse().setTransformOp(tmpActor->m_transform.m_scale, 
                                           GI_OMNI_OP::kSCALE,
                                           GI_OMNI_PRECISION::kFLOAT,
                                           tmpActor->m_omniRefPath);
            }
          }
        }
      }

      ImGui::SameLine();
      ImGui::Checkbox(" ", &m_scaleBlock);
    }
    ImGui::Separator();
    //Static Mesh
    //Verify if the actor has this information, if not, don't present this header.
    if(tmpActor->isStaticMesh) {
      if (ImGui::CollapsingHeader("Static Mesh", ImGuiWindowFlags_NoNav)) {
        SharedPtr<StaticMesh> tmpComponent = dynamic_pointer_cast<StaticMesh>(tmpActor->getComponent(COMPONENT_TYPE::kStaticMesh));
        SharedPtr<Model> tmpModel = dynamic_pointer_cast<Model>(RM.getResource(tmpComponent->getModel().m_id).lock());

        ImGui::Text(String("Path: " + tmpModel->m_directory.string()).c_str());
       
      }
    }
    ImGui::Separator();
    //Materials
    if (tmpActor->isStaticMesh) {
      if(ImGui::CollapsingHeader("Materials", ImGuiWindowFlags_NoNav)) {
        SharedPtr<StaticMesh> tmpComponent = dynamic_pointer_cast<StaticMesh>(tmpActor->getComponent(COMPONENT_TYPE::kStaticMesh));
        SharedPtr<Model> tmpModel = dynamic_pointer_cast<Model>(RM.getResource(tmpComponent->getModel().m_id).lock());
        for (auto mesh : tmpModel->m_meshes) {
          for (int32 i = 0; i < mesh->m_textures.size(); ++i) {
            auto tmpTexture = dynamic_pointer_cast<Texture>(RM.getResource(mesh->m_textures[i].m_id).lock());
            ImGui::Text(String("Path: " + tmpTexture->m_name).c_str());
            ImGui::SameLine();
            if (ImGui::Button("Change")) {
              //Create a new texture
              giEngineSDK::FILE tmpFile(FileDialogs::openFileDialog(m_windowHandle, FileDialogs::m_fileFiltersImage));
              ResourceRef tmpRef = RM.resourceFromFile(tmpFile);
              //Change the ResourceRef for the new texture.
              mesh->m_textures[i] = tmpRef;
            }
          }
          ImGui::Separator();
        }
      }
    }
    ImGui::Separator();
    if(ImGui::Button("Add")) {
      ImGui::OpenPopup("Adding component");
      if(ImGui::BeginPopup("Adding component")) {
        
      }
    }

  }
  ImGui::End();
}

void 
Details::destroy() {
  
}
