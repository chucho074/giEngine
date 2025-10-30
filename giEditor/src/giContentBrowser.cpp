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
#include <giBaseAMR.h>
#include <giFile.h>
#include <giExporter.h>
#include <giStaticMesh.h>
#include <giActor.h>
#include <giSceneGraph.h>
#include "giContentBrowser.h"

using giEngineSDK::FILE;

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
  //auto& configs = g_engineConfigs();
  //auto& RM = g_resourceManager();

  GI_UNREFERENCED_PARAMETER(inDeltaTime);

  //Quitar de aqui, ponerlo maybe en el viewport, idk, app?

  /*for(auto& tmpIterator : fsys::directory_iterator(configs.s_contentPath)) {
    const auto& tmpPath = tmpIterator.path();

    if (!tmpIterator.is_directory() 
        || tmpPath.extension() != ".giData") {
        if(!fsys::exists(tmpPath.string()+".giData")) {
          FILE tmpFile(tmpPath);
          RM.saveFile(tmpFile);
        }
    }

  }*/
}

void 
ContentBrowser::render() {

  auto& configs = g_engineConfigs().instance();
  auto& RM = g_resourceManager().instance();
  auto& amr = g_AMR();

  ImGui::Begin("Content Browser", nullptr, m_windowFlags);

  static float tmpThumbnailSize = 74;

  ImGui::BeginChild("LeftSide", 
                    {ImGui::GetContentRegionAvail().x * 0.15f, 
                     ImGui::GetContentRegionAvail().y - (ImGui::GetFontSize()*1.8f)},
                    false, 
                    ImGuiChildFlags_None);
  if(ImGui::BeginTable("Left Table", 1, ImGuiTableFlags_ScrollY)) {
    ImGui::TableNextColumn();
    int32 tmpTreeCount = 0;
    int32 tmpSelectedNode = 0;

    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    //Create the root folder for the project.
    bool root_open = ImGui::TreeNodeEx((void*)(intptr_t)tmpTreeCount,
                                       m_treeFolders,
                                       //configs.s_projectName.c_str());
                                       "Content");
    tmpTreeCount++;
    if(root_open) {
      if(!m_workingDirectory.empty()) {
        
        drawFolders(m_workingDirectory, tmpTreeCount, tmpSelectedNode);
        /*for(auto& tmpIterator : fsys::directory_iterator(m_workingDirectory)) {
          if(tmpIterator.is_directory()) {
            drawFolders(tmpIterator, tmpTreeCount, tmpSelectedNode);
          }
        }*/
      }


      ImGui::TreePop();
    }


    ImGui::EndTable();
  }
  ImGui::EndChild();

  ImGui::SameLine();
  
  ImGui::BeginChild("RightSide", 
                    {0, 
                    ImGui::GetContentRegionAvail().y - (ImGui::GetFontSize() * 1.8f)}, 
                    true, 
                    ImGuiWindowFlags_None);
  //Top bar
  auto tmpSize = ImGui::CalcTextSize("Import");

  if(ImGui::Button("Import", {(tmpSize.x * ImGui::GetFontSize()) / 10, 
                              (tmpSize.y * ImGui::GetFontSize()) / 10})) {
    //TODO: Open the import dialog.

  }

  ImGui::SameLine();

  SharedPtr<Texture>tmpLArrrow = static_pointer_cast<Texture>(RM.getResource(RM.m_leftArrow.m_id).lock());
  if(ImGui::ImageButton("Image", tmpLArrrow->m_texture->getApiTexture(),
                        {18, 18})) {
    m_currentDirectory = m_currentDirectory.parent_path();
  }
  
  //////////////////////////////////////////////////////////////////////////
  if(ImGui::BeginTable("RightSide", 1, ImGuiTableFlags_BordersInnerH
                                       | ImGuiTableFlags_PreciseWidths
                                       | ImGuiTableColumnFlags_NoClip)) {

    ImGui::TableNextColumn();

    static float tmpPadding = 16.0f;
    float tmpCellSize = tmpThumbnailSize + tmpPadding;
    float tmpPanelWidth = ImGui::GetContentRegionAvail().x;
    int32 tmpColumnCount = (int32)(tmpPanelWidth / tmpCellSize);

    if(ImGui::BeginTable("Browser", tmpColumnCount, ImGuiTableFlags_ScrollY)) {

      ImGui::TableNextColumn();

      //Iterate in directory
      if(!m_currentDirectory.empty()) {
        bool tmpIsDir = false;
        SharedPtr<Texture> tmpTexture;

        for(auto& tmpIterator : fsys::directory_iterator(m_currentDirectory)) {

          const auto& tmpPath = tmpIterator.path();
          auto relativePath = fsys::relative(tmpPath, m_workingDirectory);
          String relativePathString = relativePath.filename().string();
          String tmpExtension = tmpPath.extension().string();
          //Show Folders
          if(tmpIterator.is_directory()) {
            tmpTexture = static_pointer_cast<Texture>(RM.getResource(RM.m_folderIcon.m_id).lock());
            tmpIsDir = true;
          }

          //Show files
          else {
            if(tmpExtension == ".obj") {
              tmpTexture = static_pointer_cast<Texture>(RM.getResource(RM.m_objIcon.m_id).lock());
            }

            else if(tmpExtension == ".fbx") {
              tmpTexture = static_pointer_cast<Texture>(RM.getResource(RM.m_fbxIcon.m_id).lock());
            }

            else if(tmpExtension == ".mtl") {
              tmpTexture = static_pointer_cast<Texture>(RM.getResource(RM.m_mtlIcon.m_id).lock());
            }

            else if(tmpExtension == ".png") {
              tmpTexture = static_pointer_cast<Texture>(RM.getResource(RM.m_pngIcon.m_id).lock());
            }

            else if(tmpExtension == ".jpg") {
              tmpTexture = static_pointer_cast<Texture>(RM.getResource(RM.m_jpgIcon.m_id).lock());
            }

            else {
              tmpTexture = static_pointer_cast<Texture>(RM.getResource(RM.m_fileIcon.m_id).lock());
            }

          }
          //Shows the data if its sets any image
          if(tmpTexture) {
            if(ImGui::ImageButton("Image2", tmpTexture->m_texture->getApiTexture(),
               {tmpThumbnailSize, tmpThumbnailSize})) {
              //Enter to the folder
              m_currentDirectory = m_workingDirectory;
              if(tmpIsDir) {
                m_currentDirectory /= tmpPath.filename();
              }
            }

            //Pop up menus for files.
            if(tmpExtension == ".obj") {
              if(ImGui::BeginPopupContextItem("file popup")) {
                if(ImGui::Button("Create actor from model / JUST TESTING")) {
                  auto& sg = g_sceneGraph();
                  ResourceRef tmpModel;
                  FILE tmpFileModel(tmpPath);
                  tmpModel = RM.resourceFromFile(tmpFileModel);
                  SharedPtr<StaticMesh> modelComponent = make_shared<StaticMesh>(tmpModel);
                  SharedPtr<Actor> tmpActor = make_shared<Actor>();
                  tmpActor->addComponent(modelComponent, COMPONENT_TYPE::kStaticMesh);
                  tmpActor->m_actorName = tmpPath.filename().stem().string();
                  sg.addActor(tmpActor, sg.getRoot());
                }
                if(ImGui::Button("Use giAMR in this model")) {
                  FILE tmpFile(tmpPath);
                  RM.createData(tmpFile);
                  amr.setRefMesh(tmpPath);
                }
                ImGui::EndPopup();
              }
            }
            if(tmpExtension == ".fbx") {
              if(ImGui::BeginPopupContextItem("file popup fbx")) {
                if(ImGui::Button("Create actor from model / JUST TESTING")) {
                  auto& sg = g_sceneGraph();
                  ResourceRef tmpModel;
                  FILE tmpFileModel(tmpPath);
                  tmpModel = RM.resourceFromFile(tmpFileModel);
                  SharedPtr<StaticMesh> modelComponent = make_shared<StaticMesh>(tmpModel);
                  SharedPtr<Actor> tmpActor = make_shared<Actor>();
                  tmpActor->addComponent(modelComponent, COMPONENT_TYPE::kStaticMesh);
                  tmpActor->m_actorName = tmpPath.filename().stem().string();
                  sg.addActor(tmpActor, sg.getRoot());
                }
                if(ImGui::Button("Use giAMR in this model")) {
                  //Path tmpNewPath = Exporter::ExportAsObj(tmpPath, "obj");
                  //FILE tmpFile(tmpNewPath);

                  ResourceRef tmpResource;
                  FILE tmpFileModel(tmpPath);
                  tmpResource = RM.resourceFromFile(tmpFileModel);
                  SharedPtr<Model> tmpModel = dynamic_pointer_cast<Model>(RM.getResource(tmpResource.m_id).lock());
                  Path tmpNewPath = tmpPath;
                  tmpNewPath.replace_extension("obj");
                  Exporter::ExportObj(tmpNewPath, tmpModel);
                  FILE tmpNewFileModel(tmpNewPath);
                  RM.createData(tmpNewFileModel);
                  amr.setRefMesh(tmpNewPath);
                }
                ImGui::EndPopup();
              }
            }
            ImGui::Text(relativePathString.c_str());
          }
          ImGui::TableNextColumn();

        }

      }//

      ImGui::Columns(1);
      ImGui::EndTable();
    }
    ImGui::TableNextColumn();
    ImGui::EndTable();

  }
  ImGui::EndChild();

  ImGui::PushItemWidth(100);
  ImGui::SliderFloat("Thumbnail Size", &tmpThumbnailSize, 16, 100);
  
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

void 
ContentBrowser::drawFolders(Path& inIter,
                            int32& inTreeCount, 
                            int32& inSelectedNode) {
  for (auto& tmpIterator : fsys::directory_iterator(inIter)) {
    Path tmpPath = tmpIterator.path();
    String tmpName = tmpPath.stem().string();
    if(tmpIterator.is_directory()) {
      //ImGui::SetNextItemOpen(true, ImGuiCond_Once);
      bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)inTreeCount,
                                         fsys::is_empty(tmpPath) ? m_treeEmpty : m_treeFolders,
                                         tmpName.c_str());

      inTreeCount++;
      if(ImGui::IsItemClicked()) {
        inSelectedNode = inTreeCount;
      }
      if(node_open && !fsys::is_empty(tmpPath)) {
        drawFolders(tmpPath, inTreeCount, inSelectedNode);
        ImGui::TreePop();
      }
    }
  }
}
