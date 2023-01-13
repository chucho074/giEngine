/**
 * @file    giContentBrowser.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    01/06/2022
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include <giBaseConfig.h>
#include <giResourceManager.h>
#include <giTexture.h>
#include "giContentBrowser.h"


ContentBrowser::ContentBrowser(Path inWorkingDir) {
  m_workingDirectory = inWorkingDir;
  m_currentDirectory = m_workingDirectory;
  init();
}

void
ContentBrowser::init() {
  m_windowFlags |= ImGuiWindowFlags_NoCollapse;
}

void 
ContentBrowser::update(float inDeltaTime) {
  GI_UNREFERENCED_PARAMETER(inDeltaTime);
}

void 
ContentBrowser::render() {

  auto& configs = g_engineConfigs().instance();
  auto& RM = g_resourceManager().instance();

  ImGui::Begin("Content Browser", nullptr, m_windowFlags);


  static float tmpThumbnailSize = 74;

  //Back table
  if (ImGui::BeginTable("Base table", 1, ImGuiTableFlags_BordersInnerH 
                                         | ImGuiTableFlags_PreciseWidths)) {
    ImGui::TableNextColumn();
    //Back Button

    SharedPtr<Texture>tmpLArrrow =
      static_pointer_cast<Texture>(RM.getResource(RM.m_leftArrow.m_id).lock());

    if (ImGui::ImageButton(tmpLArrrow->m_texture->getApiTexture(),
      { 15, 15 })) {
      m_currentDirectory = m_currentDirectory.parent_path();
    }
    
    ImGui::TableNextColumn();
    //Left Panel
    if (ImGui::BeginTable("BrowserTable", 2, ImGuiTableFlags_BordersInnerV 
                                             | ImGuiTableFlags_Resizable
                                             | ImGuiTableFlags_ScrollY)) {
  
      ImGui::TableNextColumn();
      
      if (ImGui::BeginTable("Left Table", 1, ImGuiTableFlags_ScrollY)) {
        ImGui::TableNextColumn();
        int32 tmpTreeCount = 0;
        //int selection_mask = (1 << 2);
        ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow 
                                        | ImGuiTreeNodeFlags_OpenOnDoubleClick 
                                        | ImGuiTreeNodeFlags_SpanAvailWidth;
    
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        //Create the root folder for the project.
        bool root_open = ImGui::TreeNodeEx((void*)(intptr_t)tmpTreeCount, 
                                           base_flags,
                                           configs.s_projectName.c_str());
        tmpTreeCount++;
        //if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
          if(root_open) {
            for(auto& tmpIterator : fsys::directory_iterator(m_workingDirectory)) {
              auto& tmpPath = tmpIterator.path();
              String tmpName = tmpPath.stem().string();
              if (tmpIterator.is_directory()) {
                bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)tmpTreeCount, 
                                                   base_flags, 
                                                   tmpName.c_str());
    
                GI_UNREFERENCED_PARAMETER(node_open);
    
                //ImGui::TreePop();
    
              }
              tmpTreeCount++;
            }
          }
        //}
        ImGui::TreePop();
        ImGui::EndTable();
      }
  
      //Right Panel
      ImGui::TableNextColumn();
      static float tmpPadding = 16.0f;
      //static float tmpThumbnailSize = 74;
      float tmpCellSize = tmpThumbnailSize + tmpPadding;
      float tmpPanelWidth = ImGui::GetContentRegionAvail().x;
      int32 tmpColumnCount = (int32)(tmpPanelWidth / tmpCellSize);
  
      if (ImGui::BeginTable("Browser", tmpColumnCount, ImGuiTableFlags_ScrollY)) {
  
        ImGui::TableNextColumn();
  
        //Iterate in directory
        for (auto& tmpIterator : fsys::directory_iterator(m_currentDirectory)) {
  
          const auto& tmpPath = tmpIterator.path();
          auto relativePath = fsys::relative(tmpPath, m_workingDirectory);
          String relativePathString = relativePath.filename().string();
          bool tmpIsDir = false;
          SharedPtr<Texture> tmpTexture;
          //Show Folders
          if (tmpIterator.is_directory()) {
            tmpTexture = static_pointer_cast<Texture>(RM.getResource(RM.m_folderIcon.m_id).lock());
            tmpIsDir = true;
          }
  
          //Show files
          else {
            if (false) {
              //Verify if is another type of file, as a material, texture, model, script...   
            }
  
            else {
              tmpTexture = static_pointer_cast<Texture>(RM.getResource(RM.m_fileIcon.m_id).lock());
            }
          }
  
          //Shows the data if its sets any image
          if (tmpTexture) {
            if (ImGui::ImageButton(tmpTexture->m_texture->getApiTexture(),
                { tmpThumbnailSize, tmpThumbnailSize })) {
              if (tmpIsDir) {  
                m_currentDirectory /= tmpPath.filename();
              }
            }
            ImGui::Text(relativePathString.c_str());
          }
          ImGui::TableNextColumn();
  
        }
  
        ImGui::Columns(1);
        ImGui::EndTable();
      }
      //Status bar
      //ImGui::SliderFloat("Thumbnail Size", &tmpThumbnailSize, 16, 100);
      //ImGui::SliderFloat("Padding", &tmpPadding, 0, 32);
  
      ImGui::EndTable();
    }
    ImGui::TableNextColumn();
    ImGui::PushItemWidth(100);
    ImGui::SliderFloat("Thumbnail Size", &tmpThumbnailSize, 16, 100);
    ImGui::EndTable();
  }

  ImGui::End();
}

void 
ContentBrowser::destroy() {
  
}

void 
ContentBrowser::changeWorkingDir(Path inWorkingDir) {
  m_workingDirectory = inWorkingDir;
  m_currentDirectory = m_workingDirectory;
}
