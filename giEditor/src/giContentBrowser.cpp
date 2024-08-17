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
#include <giBaseConfig.h>
#include <giTexture.h>
#include <giBaseAMR.h>
#include <giFile.h>
#include <giEncoder.h>
#include "giContentBrowser.h"

using giEngineSDK::FILE;

ContentBrowser::ContentBrowser(Path inWorkingDir) {
  m_workingDirectory = inWorkingDir;
  m_currentDirectory = m_workingDirectory;

  objIcon = make_shared<Texture>();
  fbxIcon = make_shared<Texture>();
  mtlIcon = make_shared<Texture>();
  pngIcon = make_shared<Texture>();
  jpgIcon = make_shared<Texture>();
  fileIcon = make_shared<Texture>();
  folderIcon = make_shared<Texture>();
  sceneIcon = make_shared<Texture>();

  init();
}

void
ContentBrowser::init() {
  auto& gapi = g_graphicsAPI();
  m_windowFlags |= ImGuiWindowFlags_NoCollapse;

  objIcon    = gapi.TextureFromFile("/FileModelOBJ.png", "Resources/Icons/");
  fbxIcon    = gapi.TextureFromFile("/FileModelFBX.png", "Resources/Icons/");
  mtlIcon    = gapi.TextureFromFile("/FileMaterialMtl.png", "Resources/Icons/");
  pngIcon    = gapi.TextureFromFile("/FileTexturePNG.png", "Resources/Icons/");
  jpgIcon    = gapi.TextureFromFile("/FileTextureJPG.png", "Resources/Icons/");
  fileIcon   = gapi.TextureFromFile("/fileIcon.png", "Resources/Icons/");
  folderIcon = gapi.TextureFromFile("/folderIcon.png", "Resources/Icons/");
}

void 
ContentBrowser::update(float inDeltaTime) {
  GI_UNREFERENCED_PARAMETER(inDeltaTime);
}

void 
ContentBrowser::render() {
  
  auto& configs = g_engineConfigs();
  auto& amr = g_AMR();

  ImGui::Begin("Content Browser", nullptr, m_windowFlags);
  
  //Left panel
  if (ImGui::BeginTable("BrowserTable", 2, ImGuiTableFlags_BordersInnerV
                                           | ImGuiTableFlags_Resizable
                                           | ImGuiTableFlags_ScrollY)) {
    ImGui::TableNextColumn();
    if (ImGui::BeginTable("LeftTable", 1, ImGuiTableFlags_ScrollY)) {
      ImGui::TableNextColumn();
      int32 tmpTreeCount = 0;
      ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_OpenOnArrow 
                                     | ImGuiTreeNodeFlags_OpenOnDoubleClick 
                                     | ImGuiTreeNodeFlags_SpanAvailWidth;

      ImGui::SetNextItemOpen(true, ImGuiCond_Once);
      //Create the root folder for the project.
      bool rootOpen = ImGui::TreeNodeEx((void*)(intptr_t)tmpTreeCount, 
                                        baseFlags, 
                                        configs.s_projectName.c_str());
      tmpTreeCount++;
      if (rootOpen) {
        for (auto& tmpIter : fsys::directory_iterator(m_workingDirectory)) {
          auto tmpPath = tmpIter.path();
          String tmpName = tmpPath.stem().string();
          if (tmpIter.is_directory()) {
            bool nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)tmpTreeCount, 
                                              baseFlags, 
                                              tmpName.c_str());
            GI_UNREFERENCED_PARAMETER(nodeOpen);
          }
          tmpTreeCount++;
        }
      }
      ImGui::TreePop();
      ImGui::EndTable();
    }

    //Right panel
    ImGui::TableNextColumn();

    if (ImGui::BeginTable("RightSide", 1, ImGuiTableFlags_BordersInnerH 
                                          | ImGuiTableFlags_PreciseWidths)) {
      ImGui::TableNextColumn();
      //Back Button
      if (m_workingDirectory.string() != m_currentDirectory.string()) {
        if (ImGui::Button("<-")) {                                                            //Change for the texture
          m_currentDirectory = m_currentDirectory.parent_path();
        }
      }

      ImGui::TableNextColumn();
      static float tmpPadding = 16.0f;
      static float tmpThumbnailSize = 74;
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
          SharedPtr<Texture> tmpTexture = make_shared<Texture>();
          String tmpExtension = tmpPath.extension().string();

          //Setting the texture depending on the file type or folders.
          
          //Show Folders
          if (tmpIterator.is_directory()) {
            tmpTexture = folderIcon;
            tmpIsDir = true;
          }
          //Show Files
          else {
            if (tmpExtension == ".obj") {
              tmpTexture = objIcon;
            }
            else if (tmpExtension == ".fbx") {
              tmpTexture = fbxIcon;
            }
            else if (tmpExtension == ".mtl") {
              tmpTexture = mtlIcon;
            }
            else if (tmpExtension == ".png") {
              tmpTexture = pngIcon;
            }
            else if (tmpExtension == ".jpg") {
              tmpTexture = jpgIcon;
            }
            else {
              tmpTexture = fileIcon;
            }
          }

          //Shows the data if its sets any image
          if (tmpTexture) {
            if (ImGui::ImageButton(tmpTexture->m_texture->getApiTexture(),
                                   { tmpThumbnailSize, tmpThumbnailSize })) {
              //Enter to the folder
              if (tmpIsDir) {
                m_currentDirectory /= tmpPath.filename();
              }
              //If is a file
              else if (tmpExtension == ".obj") {
                ImGui::OpenPopupOnItemClick("file popup", ImGuiPopupFlags_MouseButtonRight);
              }
              //ToDo: Create the fbx popup to create the obj files.                           <----------
            }

            //Pop up menus for files.
            if (tmpExtension == ".obj") {
              if (ImGui::BeginPopupContextItem("file popup")) {
                if (ImGui::Button("Create data / JUST TESTING")) {
                  FILE tmpFile(tmpPath);
                  Encoder::encodeData(tmpFile);
                }
                if (ImGui::Button("Use giAMR in this model")) {
                  amr.setRefMesh(tmpPath);
                  //RM.exportModel(tmpPath, ResourceRef());
                }
                ImGui::EndPopup();
              }
            }
            ImGui::Text(relativePathString.c_str());
          }
          ImGui::TableNextColumn();

        }
        
        ImGui::Columns(1);
        ImGui::EndTable();
      }
      //Thumbnail size slider.
      ImGui::TableNextColumn();
      ImGui::PushItemWidth(100);
      ImGui::SliderFloat("Thumbnail Size", &tmpThumbnailSize, 16, 100);
    }
    ImGui::EndTable();
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
