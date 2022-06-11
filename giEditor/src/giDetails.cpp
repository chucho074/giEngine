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
  if (sg.getSelectedActor() != nullptr) {

    if (ImGui::CollapsingHeader("Transform", ImGuiWindowFlags_NoNav)) {
    
      ImGui::DragFloat3("Position", &sg.getSelectedActor()->m_transform.m_translation.x);
      ImGui::DragFloat3("Rotation", &sg.getSelectedActor()->m_transform.m_rotation.x);
      ImGui::DragFloat3("Scale",    &sg.getSelectedActor()->m_transform.m_scale.x);
    }
  }
  ImGui::End();
}

void 
Details::destroy() {
  
}
