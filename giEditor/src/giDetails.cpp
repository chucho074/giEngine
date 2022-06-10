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

Details::Details() {
  
}

void 
Details::init() {
  
}

void 
Details::update(float inDeltaTime) {
  
}

void 
Details::render() {
  auto& sg = SceneGraph::instance();
  ImGui::Begin("Details", nullptr, m_windowFlags);
  if (ImGui::CollapsingHeader("Transform", ImGuiWindowFlags_NoNav)) {
    float pos[3];
    float rot[3];
    float sca[3];
    if(sg.getSelectedActor() != nullptr) {
      auto tmpTransoform = sg.getSelectedActor()->m_transform;
      pos[0] = tmpTransoform.m_translation.x;
      pos[1] = tmpTransoform.m_translation.y;
      pos[2] = tmpTransoform.m_translation.z;

      rot[0] = tmpTransoform.m_rotation.x;
      rot[1] = tmpTransoform.m_rotation.y;
      rot[2] = tmpTransoform.m_rotation.z;

      sca[0] = tmpTransoform.m_scale.x;
      sca[1] = tmpTransoform.m_scale.y;
      sca[2] = tmpTransoform.m_scale.z;

    }
    
    else {
      pos[0] = 0.f;
      pos[1] = 0.f;
      pos[2] = 0.f;

      rot[0] = 0.f;
      rot[1] = 0.f;
      rot[2] = 0.f;

      sca[0] = 0.f;
      sca[1] = 0.f;
      sca[2] = 0.f;
    }
    ImGui::DragFloat3("Position", pos);
    ImGui::DragFloat3("Rotation", rot);
    ImGui::DragFloat3("Scale",    sca);
  }
  ImGui::End();
}

void 
Details::destroy() {
  
}
