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
#include <giSceneGraph.h>
#include <giBaseGraphicsAPI.h>
#include <giBaseConfig.h>
#include <giTexture.h>
#include <giTexture2D.h>
#include <giResourceManager.h>
#include <giPrerequisitesCore.h>
#include <giCamera.h>
#include <giStdHeaders.h>
#include <memory>

void 
Editor::init(void* inHandler, Vector2 inWindowSize) {

  auto& configs = g_engineConfigs().instance();

  m_ui = make_shared<UI>();

  m_ui->init(inHandler, inWindowSize);

  m_windowHandle = inHandler;

  m_contentBrowser.reset(new ContentBrowser(configs.s_projectPath));

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
  
  ImGui::BeginMainMenuBar(); {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("New")) {
        
      }
      if (ImGui::MenuItem("Open...", "Ctrl+O")) {
        openFileDilog();
      }
      if (ImGui::MenuItem("Save", "Ctrl+S")) {}
      if (ImGui::MenuItem("Save As...")) {
        saveFileDilog();
      }
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
        m_renderPerformance = true;
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help")) {
      if (ImGui::MenuItem("About")) {
        m_renderAbout = true;
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
  auto& RM = g_resourceManager().instance();
  auto tmpPath = FileDialogs::saveFileDialog(m_windowsHandle);
  giEngineSDK::FILE tmpFileToOpen(tmpPath);
  RM.saveFile(tmpFileToOpen);

}

void 
Editor::renderCameraMovementWindow() {
  bool * tmpValue = &m_renderCamera;
  auto& sgraph = g_sceneGraph().instance();

  ImGui::Begin("Editor camera movement", tmpValue, ImGuiWindowFlags_NoScrollbar 
                                                   | ImGuiWindowFlags_NoDocking
                                                   | ImGuiWindowFlags_NoResize
                                                   | ImGuiWindowFlags_NoCollapse);
  
  auto& tmpCamera = sgraph.getActorByName("MainCamera")->getComponent(COMPONENT_TYPE::kCamera);
  auto tmpMainCamera = static_pointer_cast<Camera>(tmpCamera);

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