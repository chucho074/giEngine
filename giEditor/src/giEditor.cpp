/**
 * @file    giEditor.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    01/06/2022
 * @brief   A basic implementation of the editor of the engine.
 */
 
/**
 * @include
 */
#include "giEditor.h"
#include <giModel.h>
#include <giSceneGraph.h>
#include <giBaseGraphicsAPI.h>
#include <giBaseConfig.h>
#include <giTexture.h>
#include <giTexture2D.h>
#include <giResourceManager.h>
#include <giPrerequisitesCore.h>
#include <giCamera.h>
#include <giStdHeaders.h>
#include <giFile.h>
#include <giFileSystem.h>
#include <giBaseAMR.h>

using giEngineSDK::FILE;

void 
Editor::init(void* inHandler, Vector2 inWindowSize) {

  auto& configs = g_engineConfigs().instance();

  m_ui = make_shared<UI>();

  m_ui->init(inHandler, inWindowSize);

  m_windowHandle = inHandler;

  m_contentBrowser = make_shared<ContentBrowser>(configs.s_contentPath);

  m_hierarchy = make_shared<Hierarchy>();

  m_details = make_shared<Details>();
}

void 
Editor::update(float inDeltaTime) {
  m_ui->update(m_windowHandle, inDeltaTime);
  
  m_contentBrowser->update(inDeltaTime);

  m_hierarchy->update(inDeltaTime);

  m_details->update(inDeltaTime);

}

void 
Editor::render() {
  
  auto& amr = g_AMR();


  ImGui::BeginMainMenuBar(); {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::BeginMenu("New")) {
        if (ImGui::MenuItem("Project")) {
          m_renderProjectSelection = !m_renderProjectSelection;
        }
        ImGui::EndMenu();
      }
      if (ImGui::MenuItem("Open...", "Ctrl+O")) {
        openFileDilog();
      }
      if (ImGui::MenuItem("Save", "Ctrl+S")) {}
      if (ImGui::MenuItem("Save As...")) {
        saveFileDilog();
      }
      if (ImGui::MenuItem("Import")) {
        renderImport();
      }
      if (ImGui::MenuItem("Export")) {}

      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit")) {
      if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
      if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}
      ImGui::Separator();
      if (ImGui::MenuItem("Cut", "CTRL+X")) {}
      if (ImGui::MenuItem("Copy", "CTRL+C")) {}
      if (ImGui::MenuItem("Paste", "CTRL+V")) {}
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Window")) {
      if (ImGui::MenuItem("Performance")) {
        m_renderPerformance = !m_renderPerformance;
      }
      if (ImGui::MenuItem("Camera movement")) {
        m_renderCamera = !m_renderCamera;
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help")) {
      if (ImGui::MenuItem("About")) {
        m_renderAbout = !m_renderAbout;
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }

  //Imgui docking space for windows
  ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

  //Renders the performance window if is active.
  if (m_renderPerformance) {
    renderPerformanceWindow();
  }

  //Renders the about window if is active.
  if (m_renderAbout) {
    renderAboutWindow();
  }

  //Renders the camera movement window if is active.
  if (m_renderCamera) {
    renderCameraMovementWindow();
  }

  //Renders the camera movement window if is active.
  if (m_renderProjectSelection) {
    renderProjectCreationSelection();
  }

  //Renders the giAMR window if is active.
  if (amr.m_renderWindow && !amr.m_processWindow) {
    renderAMR();
  }

  //Renders the giAMR window if is active.
  if (amr.m_processWindow) {
    renderAMRprocess();
  }

  //Render the hierarchy of the scene.
  m_hierarchy->render();

  //Render the Details of the actor.
  m_details->render();

  //Render the viewport window.
  ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoNav 
                                  | ImGuiWindowFlags_NoCollapse 
                                  | ImGuiWindowFlags_NoScrollbar); {
    void * tmpTexture = g_graphicsAPI().getViewportTex()->getApiTexture();
    ImGui::Image(tmpTexture, ImGui::GetWindowSize());
    ImGui::End();
  }

  //Render the content Browser.
  m_contentBrowser->render();

  //After the own editor ui objects, call the render of ImGui.
  m_ui->render();
  
}

void 
Editor::destroy() {
  m_details->destroy();
  m_hierarchy->destroy();
  m_contentBrowser->destroy();
  m_ui->shutDown();
}

void 
Editor::callBack() {
  m_ui->callBack();
}

void 
Editor::renderPerformanceWindow() {

  bool * tmpValue = &m_renderPerformance;

  ImGui::Begin("Performance", tmpValue, ImGuiWindowFlags_NoScrollbar 
                                        | ImGuiWindowFlags_NoCollapse);

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f 
              / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

  ImGui::End();
}

void 
Editor::renderAboutWindow() {
  bool* tmpValue = &m_renderAbout;
  ImGui::Begin("About giEngine", tmpValue, ImGuiWindowFlags_NoScrollbar 
                                           | ImGuiWindowFlags_NoDocking
                                           | ImGuiWindowFlags_NoCollapse);

  ImGui::Text("Gioco Engine developed by: Jesus Alberto Del Moral Cupil");
  ImGui::Separator();
  ImGui::Text("Contact: idv18c.jmoral@uartesdigitales.edu.mx");
  ImGui::Separator();

  ImGui::End();
}

ResourceRef
Editor::openFileDilog() {
  auto& RM = g_resourceManager().instance();

  if (auto tmpPath = FileDialogs::openFileDialog(m_windowHandle); !tmpPath.empty()) {
    giEngineSDK::FILE tmpOpenFile(tmpPath);
    RM.readFromFile(tmpOpenFile);
    return ResourceRef();
  }

  return ResourceRef();
}

void 
Editor::saveFileDilog() {
  auto& RM = g_resourceManager();
  auto tmpPath = FileDialogs::saveFileDialog(m_windowsHandle);
  giEngineSDK::FILE tmpFileToOpen(tmpPath);
  RM.saveFile(tmpFileToOpen);

}

void 
Editor::renderCameraMovementWindow() {
  bool * tmpValue = &m_renderCamera;
  auto& sgraph = g_sceneGraph();

  ImGui::Begin("Editor camera movement", tmpValue, ImGuiWindowFlags_NoScrollbar 
                                                   | ImGuiWindowFlags_NoDocking
                                                   | ImGuiWindowFlags_NoResize
                                                   | ImGuiWindowFlags_NoCollapse);
  auto tmpMainCamera = sgraph.m_editorCamera;

  String tmpX = toString(tmpMainCamera->m_viewMatrix.m_wColumn.x);
  String tmpY = toString(tmpMainCamera->m_viewMatrix.m_wColumn.y);
  String tmpZ = toString(tmpMainCamera->m_viewMatrix.m_wColumn.z);

  ImGui::Text("Pos: ");
  ImGui::SameLine();
  ImGui::TextColored({0.91f, 0.07f, 0.14f, 1.f}, tmpX.substr(0, tmpX.find(".")+3).c_str());
  ImGui::SameLine();
  ImGui::TextColored({0.05f, 0.76f, 0.26f, 1.f}, tmpY.substr(0, tmpY.find(".")+3).c_str());
  ImGui::SameLine();
  ImGui::TextColored({0.f, 0.48f, 0.8f, 1.f},    tmpZ.substr(0, tmpZ.find(".")+3).c_str());
  

  ImGui::SliderFloat("Speed", &tmpMainCamera->m_speed, 0, 250);

  ImGui::End();
}

void 
Editor::renderProjectCreationSelection() {

  auto& configs = g_engineConfigs();
  auto& RM = g_resourceManager();
  
  bool* tmpValue = &m_renderProjectSelection;
  
  ImGui::Begin("Project Creation/Selection", tmpValue, ImGuiWindowFlags_NoScrollbar 
                                                       | ImGuiWindowFlags_NoDocking
                                                       | ImGuiWindowFlags_NoCollapse);
  
  ImGui::Text("Actual Path for Save:");

  ImGui::SameLine();

  ImGui::Text(m_savingPath.string().c_str());
  
  ImGui::SameLine();

  if(ImGui::Button("Search", {55, 25})) {
    m_savingPath = FileDialogs::saveFileDialog(m_windowsHandle, 
                                               "giEngine Projects\0*.giProject\0");
    
    if (!m_savingPath.empty()) {
      configs.s_projectName = m_savingPath.stem().string().c_str();
      configs.s_projectPath = m_savingPath;
    }
  }

  //Create a new file // when is a class, make this a function to create the file type.
  //if(!FileSystem::exist(m_savingPath)){
    if(ImGui::Button("Create", {55, 25})) {
      if (!m_savingPath.empty()) {
        FILE tmpFile(m_savingPath);
        RM.saveFile(tmpFile);
        m_contentBrowser->changeWorkingDir(m_savingPath.parent_path());
        m_renderProjectSelection = !m_renderProjectSelection;
      }
    }
  //}

  //Opens a file.
  if(ImGui::Button("Open", {55, 25})) {
    if (!m_savingPath.empty()) {
      FILE tmpFile(m_savingPath);
      RM.readFromFile(tmpFile);
      m_contentBrowser->changeWorkingDir(m_savingPath.parent_path());
      m_renderProjectSelection = !m_renderProjectSelection;

    }
  }

  //Save & save as
  //Verify if the project is created.
  //If the project is created, search for the scene with a same name in the folder.
  //If the project is not created & there is no saving path, create the project file and
  //present the save dialog for the actual scene.

  //Set as a modal in the engine.

  ImGui::End();
}

void
Editor::renderImport() {
  //Open the dialog of open file and save the information of the loaded resource
  //into the current path in the content browser or in the base path of the project content.
  //Sends the data to the decoder to decode the file to import and save the data into the
  //project path.
  

  
  //Create a folder for models, materials, textures is a good idea?
}

void
Editor::renderAMR() {
  auto& amr = g_AMR();
  auto& RM = g_resourceManager();
  auto& configs = g_engineConfigs();

  bool* tmpValue = &amr.m_renderWindow;

   
  ImGui::Begin("giAMR", tmpValue, ImGuiWindowFlags_NoScrollbar
                                  | ImGuiWindowFlags_NoDocking
                                  | ImGuiWindowFlags_NoCollapse);

  //
  ImGui::BeginTable("giAMRTable", 1, ImGuiTableFlags_ScrollY);
  ImGui::TableNextColumn();
  

  //Ref mesh
  ImGui::Text("Ref Mesh:\t");
  ImGui::SameLine();
  ImGui::Text(amr.m_savedData.m_refMesh.relative_path().string().c_str());

  ImGui::Separator();

  //Base mesh
  ImGui::Text("Base Mesh:\t");
  ImGui::SameLine();
  ImGui::Text(amr.m_savedData.m_baseMesh.relative_path().string().c_str());

  ImGui::Separator();

  //Train resolution
  ImGui::SliderInt("Train resolution", &amr.m_savedData.m_trainResolution, 64, 512);

  ImGui::Separator();

  //Learning rate
  ImGui::SliderFloat("Learning Rate", &amr.m_savedData.m_learningRate, 0.003, 0.05);

  ImGui::Separator();

  //Iterations
  ImGui::SliderInt("Iterations", &amr.m_savedData.m_iterations, 4000, 15000);
  
  ImGui::Separator();

  //Generate Button
  if (ImGui::Button("Generate")) {
    amr.run();
    amr.m_renderWindow = false;
    amr.m_processWindow = true;
  }


  ImGui::EndTable();

  ImGui::End();

}

void
Editor::renderAMRprocess() { 

  auto& amr = g_AMR();
  auto& RM = g_resourceManager();
  auto& configs = g_engineConfigs();

  amr.m_AMRprocess.reserve(25);

  bool* tmpValue = &amr.m_processWindow;
  ImGui::Begin("giAMRprocess", tmpValue, ImGuiWindowFlags_NoScrollbar
                                         | ImGuiWindowFlags_NoDocking
                                         | ImGuiWindowFlags_NoCollapse);
  if(ImGui::BeginTable("giAMRProcessTable", 1, ImGuiTableFlags_ScrollY)) { //1
    ImGui::TableNextColumn();

    //Read every new image, if exist any new, load it and present it.
    SharedPtr<Texture> tmpTexture;
    String tmpImgName = ("/img" + toString(amr.m_processImg) + ".png");
    String tmpNextImgName = ("/img" + toString(amr.m_processImg+1) + ".png");
    Path tmpImgPath = configs.s_contentPath.string() + "/giAMR/"
                       + amr.m_savedData.m_refMesh.filename().string() + tmpImgName;
    Path tmpNextImgPath = configs.s_contentPath.string() + "/giAMR/"
                       + amr.m_savedData.m_refMesh.filename().string() + tmpNextImgName;
    
    Path tmpPath = amr.m_savedData.m_outputDir.string() + "/mesh/mesh.obj";
    if (fsys::exists(tmpNextImgPath)) {
      FILE tmpFile(tmpImgPath);
      amr.m_AMRprocess.push_back(RM.resourceFromFile(tmpFile));
      ++amr.m_processImg;
      amr.m_showingImg = amr.m_processImg;
    }

    if(!amr.m_AMRprocess.empty()) {
      if (UUID::ZERO != amr.m_AMRprocess.at(amr.m_showingImg-1).m_id) {
        tmpTexture = static_pointer_cast<Texture>(RM.getResource(amr.m_AMRprocess.at(amr.m_showingImg-1).m_id).lock());
        if(nullptr != tmpTexture->m_texture) {
          ImGui::Image(tmpTexture->m_texture->getApiTexture(), { ImGui::GetWindowContentRegionMax().x / 1,
                                                                 ImGui::GetWindowContentRegionMax().y / 2 });
        }
      }
    }
    ImGui::SliderInt("", &amr.m_showingImg, 1, amr.m_processImg);
    ImGui::Text(String("Image: "+ toString(amr.m_showingImg)).c_str());
    ImGui::Separator();

    if(ImGui::BeginTable("ComparasionTable", 2, ImGuiTableFlags_ScrollY)) {//2
      ImGui::TableNextColumn();
      
      if (0 == amr.m_outInfo.totalTriangles) {
        if (fsys::exists(tmpPath.string()+ ".giData")) {
          FILE tmpOutFile(tmpPath.string() + ".giData");
          amr.m_outInfo = RM.getFromFile(tmpOutFile);
        }
      }

      ImGui::Text("Output Model: ");
      ImGui::Text(String("Triangles: " + toString(amr.m_outInfo.totalTriangles)).c_str());
      ImGui::Text(String("Vertex: " + toString(amr.m_outInfo.totalVertices)).c_str());
      ImGui::Text(String("Index: " + toString(amr.m_outInfo.totalIndex)).c_str());

      ImGui::TableNextColumn();

      if (0 == amr.m_refInfo.totalTriangles) {
        FILE tmpRefFile(amr.m_savedData.m_refMesh.string() + ".giData");
        amr.m_refInfo = RM.getFromFile(tmpRefFile);
      }

      ImGui::Text("Reference Model: ");
      ImGui::Text(String("Triangles: " + toString(amr.m_refInfo.totalTriangles)).c_str());
      ImGui::Text(String("Vertex: " + toString(amr.m_refInfo.totalVertices)).c_str());
      ImGui::Text(String("Index: " + toString(amr.m_refInfo.totalIndex)).c_str());

      ImGui::EndTable();//2

    }
    ImGui::EndTable();//1
  }
  ImGui::End();
}