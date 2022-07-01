/**
 * @file    giEditor.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    01/06/2022
 * @brief   A basic implementation of the editor of the engine.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giEditor.h"
#include <giBaseGraphicsAPI.h>
#include <giBaseConfig.h>
#include <giTexture2D.h>

void 
Editor::init(void* inHandler, Vector2 inWindowSize) {
  m_ui.reset(new UI);
  m_ui->init(inHandler, inWindowSize);

  //m_contentBrowser.reset(new ContentBrowser(EngineConfigs::s_projectPath));
  m_contentBrowser.reset(new ContentBrowser("E:/Dev/giTestProject"));

  m_hierarchy.reset(new Hierarchy());

  m_details.reset(new Details());
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
      if (ImGui::MenuItem("New")) {}
      if (ImGui::MenuItem("Open", "Ctrl+O")) {}
      if (ImGui::MenuItem("Save", "Ctrl+S")) {}
      if (ImGui::MenuItem("Save As..")) {}
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
      if (ImGui::MenuItem("Browser")) {}
      if (ImGui::MenuItem("Details")) {}
      if (ImGui::MenuItem("Viewport")) {}
      if (ImGui::MenuItem("Scene")) {}
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help")) {
      if (ImGui::MenuItem("About")) {}
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }

  //Imgui docking space for windows
  ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
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
