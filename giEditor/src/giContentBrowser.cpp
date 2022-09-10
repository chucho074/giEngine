/**
 * @file    giContentBrowser.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    01/06/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giContentBrowser.h"
#include "giResourceManager.h"
#include <giTexture.h>


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
  
}

void 
ContentBrowser::render() {

  auto& RM = g_resourceManager().instance();

  ImGui::Begin("Content Browser", nullptr, m_windowFlags);

  //Back Button
  if (m_workingDirectory.string() != m_currentDirectory.string()) {
    if (ImGui::Button("<-")) {
      m_currentDirectory = m_currentDirectory.parent_path();
    }
  }


  if (ImGui::BeginTable("BrowserTable", 2, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_Resizable)) {

    ImGui::TableNextColumn();
    ImGui::Text("Holis, soy la columna 0");



    ImGui::TableNextColumn();
    static float tmpPadding = 16.0f;
    static float tmpThumbnailSize = 74;
    float tmpCellSize = tmpThumbnailSize + tmpPadding;
    float tmpPanelWidth = ImGui::GetContentRegionAvail().x;
    int32 tmpColumnCount = (int32)(tmpPanelWidth / tmpCellSize);

    if (ImGui::BeginTable("Browser", tmpColumnCount, ImGuiTableFlags_None)) {

      
      //ImGui::Columns(tmpColumnCount, 0, false);
      ImGui::TableNextColumn();

      //Iterate in directory
      for (auto& tmpIterator : fsys::directory_iterator(m_currentDirectory)) {

        const auto& tmpPath = tmpIterator.path();
        auto relativePath = fsys::relative(tmpPath, m_workingDirectory);
        String relativePathString = relativePath.filename().string();

        //Show Folders
        SharedPtr<Texture> tmpFolderTexture = static_pointer_cast<Texture>(RM.getResource(RM.m_folderIcon.m_id).lock());
        if (ImGui::ImageButton(tmpFolderTexture->m_texture->getApiTexture(), 
                               { tmpThumbnailSize, tmpThumbnailSize })) {
          if (tmpIterator.is_directory()) {
            m_currentDirectory /= tmpPath.filename();
          }
        }
        ImGui::Text(relativePathString.c_str());
        //Show files
        //else {
          /*if (ImGui::Button(relativePathString.c_str())) {

          }*/
        //}
        ImGui::TableNextColumn();

      }

      ImGui::Columns(1);
      ImGui::EndTable();
    }
    //Status bar
    ImGui::SliderFloat("Thumbnail Size", &tmpThumbnailSize, 16, 100);
    //ImGui::SliderFloat("Padding", &tmpPadding, 0, 32);

    ImGui::EndTable();
  }

  ImGui::End();
}

void 
ContentBrowser::destroy() {
  
}
