/**
 * @file    giDXApp.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include <giDegrees.h>
//#include <giGraphicsDX.h>
#include <giCamera.h>
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
#include <giStaticMesh.h>
#include <giSceneGraph.h>
#include <SFML/Window.hpp>
#include <SFML/Window/WindowBase.hpp>
#include "giDXApp.h"

DirectXApp::DirectXApp() {
  //Set the window size
  //m_width = EngineConfigs::s_resolution.x;
  m_width = 1280;
  //m_height = EngineConfigs::s_resolution.y;
  m_height = 720;
  m_world = Matrix4::IDENTITY;
  m_editorUI.reset(new Editor);
}


void 
DirectXApp::onCreate() {

  Vector2 tmpSize(m_window.getSize().x, m_window.getSize().y);
  
  m_editorUI->init(m_window.getSystemHandle(), tmpSize);

  //Sets the main camera
  SharedPtr<Camera> mainCamera = make_shared<Camera>();
  mainCamera->init(Degrees(75.0f).getRadians(),
                   1280.f / 720.f,
                   0.01f,
                   1000.0f);
  SharedPtr<Actor> cameraActor = make_shared<Actor>();
  cameraActor->m_actorName = "MainCamera";
  cameraActor->addComponent(mainCamera, COMPONENT_TYPE::kCamera);
  m_sceneGraph->addActor(cameraActor, m_sceneGraph->getRoot());

  //Sets Vela's model
  SharedPtr<Model> tmpModel = make_shared<Model>();
  tmpModel->loadFromFile("Resources/Models/Vela2/Vela2.fbx");
  //tmpModel->loadFromFile("Resources/Models/cube.fbx");
  SharedPtr<StaticMesh> modelComponent = make_shared<StaticMesh>();
  modelComponent->setModel(tmpModel);
  SharedPtr<Actor> tmpActor = make_shared<Actor>();
  tmpActor->addComponent(modelComponent, COMPONENT_TYPE::kStaticMesh);
  tmpActor->m_actorName = "Vela";
  m_sceneGraph->addActor(tmpActor, m_sceneGraph->getRoot());

  //Sets plane model
  //SharedPtr<Model> tmpModelPlane = make_shared<Model>();
  //tmpModelPlane->loadFromFile("Resources/Models/plano.fbx");
  //SharedPtr<StaticMesh> modelComponentPlane = make_shared<StaticMesh>();
  //modelComponentPlane->setModel(tmpModelPlane);
  //SharedPtr<Actor> tmpActorPlane = make_shared<Actor>();
  //tmpActorPlane->addComponent(modelComponentPlane, COMPONENT_TYPE::kStaticMesh);
  //tmpActorPlane->m_actorName = "Plane";
  //m_sceneGraph->addActor(tmpActorPlane, m_sceneGraph->getRoot());

  //Sets the shadow camera
  SharedPtr<Camera> shadowCamera = make_shared<Camera>();
  shadowCamera->init(Degrees(75.0f).getRadians(),
                     1280.f / 720.f,
                     0.01f,
                     1000.0f);

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
  GI_UNREFERENCED_PARAMETER(inDeltaTime);
  //World rotation
  //m_world = XMMatrixRotationY(inDeltaTime);


  auto& cameraRef = m_sceneGraph->getActorByName("MainCamera")->getComponent(COMPONENT_TYPE::kCamera);

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
  
  //g_inputManager().sendEvent(inMsg);

  m_editorUI->callBack();

  //Vector4 tmpVect;
  //if (inEvent.type == Event::KeyPressed) {
  //  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
  //      sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
  //    tmpVect = { 0.f, 0.f, 0.1f, 0.0f };
  //  }
  //  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
  //      sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
  //    tmpVect = { 0.f, 0.f, -0.1f, 0.0f };
  //  }
  //  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
  //      sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
  //    tmpVect = { -0.1f, 0.f, 0.f, 0.0f };
  //  }
  //  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
  //      sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
  //    tmpVect = { 0.1f, 0.f, 0.f, 0.0f };
  //  }
  //  if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
  //    tmpVect = { 0.f, 0.1f, 0.f, 0.0f };
  //  }
  //  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
  //    tmpVect = { 0.f, -0.1f, 0.f, 0.0f };
  //  }
  //  m_mainCamera.move(tmpVect);
  //  //Sets the view matrix
  //  CameraConstantBuffer tmpConstantCamera;
  //  tmpConstantCamera.mView = m_mainCamera.getViewMatrix();
  //  m_gapi->updateSubresource(m_cBufferCamera, 
  //                            &tmpConstantCamera, 
  //                            sizeof(tmpConstantCamera));
  //}
  //if (inEvent.type == Event::Resized) {    
  //  CameraConstantBuffer tmpConstantCamera;
  //  //Sets the projection matrix
  //  tmpConstantCamera.mProjection = m_mainCamera.getProyectionMatrix();
  //  m_gapi->updateSubresource(m_cBufferCamera, 
  //                            &tmpConstantCamera, 
  //                            sizeof(tmpConstantCamera));
  //}
}
