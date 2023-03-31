/**
 * @file    giDXApp.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/04/2021
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giDXApp.h"
#include <giMatrix4.h>
#include <giVector4.h>
#include <giVector3.h>
#include <giVector2.h>
#include <giTexture2D.h>
#include <giDepthStencilView.h>
#include <giRenderTargetView.h>
#include <giVertexShaderDX.h>
#include <giPixelShaderDX.h>
#include <giBuffer.h>
#include <giInputLayout.h>
#include <giSampler.h>
#include <giMesh.h>
#include <giModel.h>
#include <giFile.h>
#include <giStaticMesh.h>
#include <giSceneGraph.h>
#include <SFML/Window.hpp>
#include <SFML/Window/WindowBase.hpp>

DirectXApp::DirectXApp() {
  //Set the window size
  m_width = 1280;
  //m_width = EngineConfigs::s_resolution.x;
  m_height = 720;
  //m_height = EngineConfigs::s_resolution.y;
  m_world = Matrix4::IDENTITY;
  m_editorUI = make_shared<Editor>();
}

void 
DirectXApp::onCreate() {
  auto& RM = g_resourceManager();

  Vector2 tmpSize(m_width, m_height);
  
  m_editorUI->init(m_window.getSystemHandle(), tmpSize);

  //Sets Vela's model
  //ResourceRef tmpModel;
  //FILE tmpFileModel("Resources/Models/Vela2/Vela2.fbx");
  ////FILE tmpFileModel("Resources/Models/Sponza/Sponza.fbx");
  ////FILE tmpFileModel("G:/Dev/giTestProject/content/spot.obj");
  //tmpModel = RM.resourceFromFile(tmpFileModel);
  //SharedPtr<StaticMesh> modelComponent = make_shared<StaticMesh>(tmpModel);
  //SharedPtr<Actor> tmpActor = make_shared<Actor>();
  //tmpActor->addComponent(modelComponent, COMPONENT_TYPE::kStaticMesh);
  //tmpActor->m_actorName = "Vela2";
  //m_sceneGraph->addActor(tmpActor, m_sceneGraph->getRoot());

  //Sets the shadow camera
  SharedPtr<Camera> shadowCamera = make_shared<Camera>();
  shadowCamera->init(Degrees(75.0f).getRadians(),
                     1280.f / 720.f,
                     0.01f,
                     100000.0f);

  shadowCamera->setPosition({ 360.0f, 280.0f, -200.0f, 0.0f },
                            { 0.0f,   1.0f,    0.0f,   0.0f },
                            { 0.0f,   1.0f,    0.0f,   0.0f });

  SharedPtr<Actor> lightActor = make_shared<Actor>();
  lightActor->m_actorName = "Light";
  lightActor->addComponent(shadowCamera, COMPONENT_TYPE::kCamera);
  m_sceneGraph->addActor(lightActor, m_sceneGraph->getRoot());

  //Set Topology
  m_gapi->setTopology(GI_PRIMITIVE_TOPOLOGY::kPRIMITIVE_TOPOLOGY_TRIANGLELIST);

  //Create Constant Buffer for Never Change
  m_cBufferCamera = m_gapi->createBuffer(sizeof(CameraConstantBuffer),
                                         GI_BIND_FLAG::kBIND_CONSTANT_BUFFER, 
                                         nullptr);

  //Create Constant Buffer for Change Every Frame
  m_cBufferChangeEveryFrame = m_gapi->createBuffer(sizeof(CBChangesEveryFrame), 
                                                   GI_BIND_FLAG::kBIND_CONSTANT_BUFFER, 
                                                   nullptr);

  //Initialize world matrix
  m_world = Matrix4::IDENTITY;
}

void 
DirectXApp::onDestroy() {
  m_editorUI->destroy();
}

void 
DirectXApp::onUpdate(float inDeltaTime) {

  auto& cameraRef = m_sceneGraph->m_editorCamera;

  if(cameraRef) {
    SharedPtr<Camera> tmpCamera = static_pointer_cast<Camera>(cameraRef);
    //Get forward input
    if (g_inputManager().isKeyPressed(KEYBOARD_KEYS::kW)) {
      tmpCamera->m_front = true;
    }
    else if (g_inputManager().isKeyReleassed(KEYBOARD_KEYS::kW)) {
      tmpCamera->m_front = false;
    }
    //Get backard input
    if (g_inputManager().isKeyPressed(KEYBOARD_KEYS::kS)) {
      tmpCamera->m_back = true;
    }
    else if (g_inputManager().isKeyReleassed(KEYBOARD_KEYS::kS)) {
      tmpCamera->m_back = false;
    }
    //Get left input
    if (g_inputManager().isKeyPressed(KEYBOARD_KEYS::kA)) {
      tmpCamera->m_left = true;
    }
    else if (g_inputManager().isKeyReleassed(KEYBOARD_KEYS::kA)) {
      tmpCamera->m_left = false;
    }
    //Get right input
    if (g_inputManager().isKeyPressed(KEYBOARD_KEYS::kD)) {
      tmpCamera->m_right = true;
    }
    else if (g_inputManager().isKeyReleassed(KEYBOARD_KEYS::kD)) {
      tmpCamera->m_right = false;
    }
    //Get up input
    if (g_inputManager().isKeyPressed(KEYBOARD_KEYS::kQ)) {
      tmpCamera->m_up = true;
    }
    else if (g_inputManager().isKeyReleassed(KEYBOARD_KEYS::kQ)) {
      tmpCamera->m_up = false;
    }
    //Get down input
    if (g_inputManager().isKeyPressed(KEYBOARD_KEYS::kE)) {
      tmpCamera->m_down = true;
    }
    else if (g_inputManager().isKeyReleassed(KEYBOARD_KEYS::kE)) {
      tmpCamera->m_down = false;
    }
  }

  m_sceneGraph->update(inDeltaTime);
  
  m_editorUI->update(inDeltaTime);
  
}

void 
DirectXApp::onRender() {
  
  m_editorUI->render();

}

void 
DirectXApp::onEvent(MSG inMsg) {
  
  GI_UNREFERENCED_PARAMETER(inMsg);


  m_editorUI->callBack();

  
}

void 
DirectXApp::resize(int32 inW, int32 inH) {
  //Set the new size to the camera.
  auto& SG = g_sceneGraph();
  SG.resizeMainCamera(inW, inH);

  //Set the new size to ImGui.
  ImGuiIO& io = ImGui::GetIO();
  io.DisplaySize = { static_cast<float>(inW), static_cast<float>(inH) };
  
  //Set the new size to the textures.
  g_graphicsAPI().getViewportTex().reset();

}
