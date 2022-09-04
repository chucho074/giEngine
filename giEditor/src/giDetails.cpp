/**
 * @file    giDetails.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/06/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giDetails.h"
#include <giSceneGraph.h>
#include <giTransform.h>
#include <giBaseOmniverse.h>
#include <giBaseConfig.h>

Details::Details() {
  
}

void 
Details::init() {
  
}

void 
Details::update(float inDeltaTime) {
  GI_UNREFERENCED_PARAMETER(inDeltaTime);
}

void 
Details::render() {
  auto& sg = SceneGraph::instance();
  ImGui::Begin("Details", nullptr, m_windowFlags);
  if (sg.getSelectedActor() != nullptr) {
    auto tmpActor = sg.getSelectedActor();

    ImGui::Text(String("Selected Actor: " + tmpActor->m_actorName).c_str());

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

    //Verify if the actor has this information, if not, don't present this header.
    if (ImGui::CollapsingHeader("Materials", ImGuiWindowFlags_NoNav)) {
      
    }
  }
  ImGui::End();
}

void 
Details::destroy() {
  
}
