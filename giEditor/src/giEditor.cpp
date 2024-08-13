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
#include <giFile.h>
#include <giBaseAMR.h>
#include <giDecoder.h>
#include <giEncoder.h>
#include <giModel.h>
#include <giUUID.h>
#include <giSceneGraph.h>

void 
Editor::init(void* inHandler, Vector2 inWindowSize) {
  m_ui = make_shared<UI>();
  m_ui->init(inHandler, inWindowSize);

  m_contentBrowser = make_shared<ContentBrowser>(ContentBrowser(EngineConfigs::s_contentPath));

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
  //auto& sg = g_sceneGraph();

  //Imgui docking space for windows
  ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

  //The docking space ID.
  static ImGuiID dockspaceID = 0;

  //The main bar of the app
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
Editor::renderAMR() {
  auto& amr = g_AMR();
  auto& configs = g_engineConfigs();

  bool* tmpValue = &amr.m_renderWindow;

  if(0 == amr.m_refInfo.totalTriangles){
    giEngineSDK::FILE tmpRefFile(amr.m_savedData.m_refMesh.string() + ".giData");
    amr.m_refInfo = Decoder::decodeGiData(tmpRefFile);
    //Get the minimun number of triangles possible.

    if (amr.minimunTriang < amr.m_refInfo.totalTriangles) {
      amr.minimunTriang = amr.m_refInfo.totalTriangles * 0.25f;

      amr.halfTriang = amr.m_refInfo.totalTriangles * 0.50f;

      amr.partialTriang = amr.m_refInfo.totalTriangles * 0.75f;
    }
    else {
      //Error: there is no enought data to work.
    }
  }

  bool useSphere = true;

  ImGui::Begin("giAMR", tmpValue, ImGuiWindowFlags_NoScrollbar
                                  | ImGuiWindowFlags_NoDocking
                                  | ImGuiWindowFlags_NoCollapse);

  //
  ImGui::BeginTable("giAMRTable", 1, ImGuiTableFlags_ScrollY);
  ImGui::TableNextColumn();
  
  ImGui::Text("Generate from a Sphere");

  ImGui::SameLine();

  if(ImGui::Button(toString(amr.minimunTriang).c_str())) {
    amr.finalTriang = amr.minimunTriang;
  }

  ImGui::SameLine();

  if(ImGui::Button(toString(amr.halfTriang).c_str())) {
    amr.finalTriang = amr.halfTriang;
  }

  ImGui::SameLine();

  if(ImGui::Button(toString(amr.partialTriang).c_str())) {
    amr.finalTriang = amr.partialTriang;
  }
  ImGui::Text("By Triangles (uses uv Sphere)");
  ImGui::SliderInt("Triangles", 
                   &amr.finalTriang, 
                   amr.minimunTriang, 
                   amr.m_refInfo.totalTriangles);

  ImGui::Text("By Subdivisions (uses Quad Sphere)");
  ImGui::SliderInt("Subdivisions",
                   &m_Subdiv,
                   1, 
                   6);

  ImGui::Text("Total Triangles: ");
  
  ImGui::SameLine();

  ImGui::Text(toString(pow(4, m_Subdiv+1) * 6 / 2).c_str());
  ImGui::Separator();
  
  ImGui::Text("Generate form a base model");
  
  ImGui::Separator();

  //Ref mesh
  ImGui::Text("Ref Mesh:\t");
  ImGui::SameLine();
  ImGui::Text(amr.m_savedData.m_refMesh.filename().string().c_str());
  ImGui::SameLine();

  //ImGui::Separator();
  ImGui::Text(" | ");
  ImGui::SameLine();

  //Base mesh
  ImGui::Text("Base Mesh:\t");
  ImGui::SameLine();
  ImGui::Text(amr.m_savedData.m_baseMesh.filename().string().c_str());

  ImGui::Separator();

  ImGui::Text("AMR configuration");
  ImGui::Separator();

  //Train resolution
  ImGui::SliderInt("Train resolution", &amr.m_savedData.m_trainResolution, 64, 2048);

  ImGui::Separator();

  //Learning rate
  ImGui::SliderFloat("Learning Rate", &amr.m_savedData.m_learningRate, 0.003, 0.10);

  ImGui::Separator();

  //Iterations
  ImGui::SliderInt("Iterations", &amr.m_savedData.m_iterations, 4000, 25000);
  
  ImGui::Separator();

  //Batch
  ImGui::SliderInt("Batch", &amr.m_savedData.m_batch, 2, 10);
  
  ImGui::Separator();

  //Generate Button
  if (ImGui::Button("Generate (uv sphere)")) {
    Encoder::exportObj({configs.s_generatedPath.string() + "sphere.obj"}, 
                  Model::createSphere(amr.finalTriang));
                    
    amr.run();
    amr.m_renderWindow = false;
    amr.m_processWindow = true;
  }

  ImGui::SameLine();

  if (ImGui::Button("Generate (quad sphere)")) {
    
    Model::createQuadSphere(m_Subdiv);
  
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
      giEngineSDK::FILE tmpFile(tmpImgPath);
      //Creates the next texture
      SharedPtr<Texture> tmpImage = make_shared<Texture>();
      tmpImage = g_graphicsAPI().TextureFromFile(tmpNextImgName, tmpImgPath.parent_path().string());

      amr.m_AMRprocess.push_back(tmpImage);
      ++amr.m_processImg;
      amr.m_showingImg = amr.m_processImg;
    }

    if(!amr.m_AMRprocess.empty()) {
      
      tmpTexture = amr.m_AMRprocess.at(amr.m_showingImg-1);
      if(nullptr != tmpTexture->m_texture) {
        ImGui::Image(tmpTexture->m_texture->getApiTexture(), { ImGui::GetWindowContentRegionMax().x / 1,
                                                               ImGui::GetWindowContentRegionMax().y / 2 });
      }
      
    }
    ImGui::SliderInt("", &amr.m_showingImg, 1, amr.m_processImg);
    ImGui::Text(String("Image: "+ toString(amr.m_showingImg)).c_str());
    ImGui::Separator();

    if(ImGui::BeginTable("ComparasionTable", 2, ImGuiTableFlags_ScrollY)) {//2
      ImGui::TableNextColumn();
      
      if (0 == amr.m_outInfo.totalTriangles) {
        if (fsys::exists(tmpPath.string()+ ".giData")) {
          giEngineSDK::FILE tmpOutFile(tmpPath.string() + ".giData");
          amr.m_outInfo = Decoder::decodeGiData(tmpOutFile);
        }
      }

      ImGui::Text("Output Model: ");
      ImGui::Text(String("Triangles: " + toString(amr.m_outInfo.totalTriangles)).c_str());
      ImGui::Text(String("Vertex: " + toString(amr.m_outInfo.totalVertices)).c_str());
      ImGui::Text(String("Index: " + toString(amr.m_outInfo.totalIndex)).c_str());

      ImGui::TableNextColumn();

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