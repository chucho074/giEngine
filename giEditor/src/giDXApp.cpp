/**
 * @file    giDXApp.cpp
 * @author  Jes�s Alberto Del Moral Cupil
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
#include "giImGui.h"

DirectXApp::DirectXApp() {
  //Set the window size
  //m_width = EngineConfigs::s_resolution.x;
  m_width = 1280;
  //m_height = EngineConfigs::s_resolution.y;
  m_height = 720;
  m_world = Matrix4::IDENTITY;
  
}


void 
DirectXApp::onCreate() {

  Vector2 tmpSize(m_window.getSize().x, m_window.getSize().y);

  ImGui::init(&m_window, tmpSize);

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
  ImGui::shutDown();
}


void 
DirectXApp::onUpdate(float inDeltaTime) {
  GI_UNREFERENCED_PARAMETER(inDeltaTime);
  //World rotation
  //m_world = XMMatrixRotationY(inDeltaTime);


  auto& camera = m_sceneGraph->getActorByName("MainCamera")->getComponent(COMPONENT_TYPE::kCamera);

  if(camera) {
    //static_cast<Camera>();
  }

  m_sceneGraph->update(inDeltaTime);
  
  ImGui::NewFrame();
  ImGui::update(m_window.getSystemHandle(), inDeltaTime);
  ImGui::ShowDemoWindow();
}


void 
DirectXApp::onRender() {

  ImGui::render();

  //Update variables that change once per frame
  //CBChangesEveryFrame cb;
  //cb.mWorld = m_world.transpose();
  //cb.vMeshColor = m_meshColor;
  //m_gapi->updateSubresource(m_cBufferChangeEveryFrame, &cb, sizeof(cb));

  //Render the cube/sets values
  //m_gapi->vsSetConstantBuffer(0, m_cBufferCamera);
  //m_gapi->vsSetConstantBuffer(1, m_cBufferChangeEveryFrame);
  //m_gapi->psSetConstantBuffer(1, m_cBufferChangeEveryFrame);
  //m_gapi->psSetShaderResource(0, m_colorTexture);
  //m_gapi->psSetSamplerState(0, 1, m_sampler);
  
  //Apply a rotation
  //static float tmpRotation = Math::PI / 550.0f;
  //tmpRotation += Math::PI / 550.0f;

  //Sets values to the world
  //m_world = Matrix4::IDENTITY;
  //m_world *= matrixTranslation({60.f, -10.0f, 50.f});
  //m_world *= matrixRotationY(180);
  //m_world *= matrixRotationZ(180);
  //m_world *= matrixRotationY(tmpRotation);
  //m_world *= XMMatrixScaling(0.1f, 0.1f, 0.1f);

  //cb.mWorld = m_world.transpose();
  //cb.vMeshColor = m_meshColor;
  
}


void 
DirectXApp::onEvent(MSG inMsg) {
  
  //g_inputManager().sendEvent(inMsg);

  ImGui::callBack();

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
