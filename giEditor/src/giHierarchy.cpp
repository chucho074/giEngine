/**
 * @file    giHierarchy.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/06/2022
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giHierarchy.h"
#include <giSceneNode.h>
#include <giSceneGraph.h>


Hierarchy::Hierarchy() {
  
  init();
}

void
Hierarchy::init() {
  m_windowFlags = ImGuiWindowFlags_NoNav
                  | ImGuiWindowFlags_NoCollapse;


  m_rootFlags = ImGuiTreeNodeFlags_OpenOnArrow
                | ImGuiTreeNodeFlags_OpenOnDoubleClick 
                | ImGuiTreeNodeFlags_SpanFullWidth;

  m_treeSelectableFlags = m_rootFlags | ImGuiTreeNodeFlags_Selected;


  m_leafFlags = m_treeSelectableFlags |= ImGuiTreeNodeFlags_Leaf
                                      | ImGuiTreeNodeFlags_Bullet
                                      | ImGuiTreeNodeFlags_NoTreePushOnOpen;
}

void 
Hierarchy::update(float inDeltaTime) {
  GI_UNREFERENCED_PARAMETER(inDeltaTime);
}

void
Hierarchy::render() {
  auto& sg = SceneGraph::instance();
  auto root = sg.getRoot();
  auto tmpNodes = sg.getNodesByParent(root);

  ImGui::Begin("Hierarchy", nullptr, m_windowFlags); {
    
    if(ImGui::BeginTable("Hierarchy List", 3, ImGuiTableFlags_Resizable | 
                                              ImGuiTableFlags_NoBordersInBody |
                                              ImGuiTableFlags_BordersV)) {
      ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
      ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_NoHide);
      ImGui::TableSetupColumn("Active", ImGuiTableColumnFlags_NoHide);
      ImGui::TableHeadersRow();
      for (auto& nodes : sg.getRoot()->m_childs) {
        renderNode(nodes);
      }
    }
    ImGui::EndTable();

    ImGui::End();
  }
}

void 
Hierarchy::destroy() {
  
}

void 
Hierarchy::renderNode(SharedPtr<SceneNode> inNode) {

  auto& sg = SceneGraph::instance();

  ImGui::TableNextRow();
  ImGui::TableNextColumn();

  bool tmpOpenNode = false;

  if (0 < inNode->m_childs.size()) {  //It has a child
    tmpOpenNode = ImGui::TreeNodeEx(inNode->m_actor->m_actorName.c_str(), m_rootFlags);
  }
  else {  //It hasn't childs
    ImGui::TreeNodeEx(inNode->m_actor->m_actorName.c_str(), m_leafFlags);
  }

  if (ImGui::IsItemClicked()) {
    sg.setSelectedActor(inNode->m_actor);
  }

  ImGui::TableNextColumn();
  ImGui::TextDisabled("Actor");

  if (0 < inNode->m_childs.size() && tmpOpenNode) {
    for (auto& nodes : sg.getRoot()->m_childs) {
      renderNode(nodes);
    }
    ImGui::TreePop();
  }
}