/**
 * @file    giDXApp.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include <giDegrees.h>
#include "giDXApp.h"

DirectXApp::DirectXApp() {
  //Set the window size
  m_width = 1280;
  m_height = 720;
  m_world = Matrix4::IDENTITY;
  
}


void 
DirectXApp::onCreate() {


  SharedPtr<Model> tmpModel = make_shared<Model>();

  tmpModel->loadFromFile("Resources/Models/Vela2/Vela2.fbx");

  SharedPtr<StaticMesh> modelComponent = make_shared<StaticMesh>();

  modelComponent->setModel(tmpModel);

  SharedPtr<Actor> tmpActor = make_shared<Actor>();

  tmpActor->addComponent(modelComponent, COMPONENT_TYPE::kStaticMesh);

  m_sceneGraph->addActor(tmpActor, m_sceneGraph->getRoot());


  //Set Topology
  m_gapi->setTopology(GI_PRIMITIVE_TOPOLOGY::kPRIMITIVE_TOPOLOGY_TRIANGLELIST);

  //Create Constant Buffer for Never Change
  m_cBufferCamera = m_gapi->createBuffer(sizeof(CameraConstantBuffer),
                                         4, 
                                         0, 
                                         nullptr);

  //Create Constant Buffer for Change Every Frame
  m_cBufferChangeEveryFrame = m_gapi->createBuffer(sizeof(CBChangesEveryFrame), 
                                                   4, 
                                                   0, 
                                                   nullptr);


  //Initialize world matrix
  m_world = Matrix4::IDENTITY;

  
  
}


void 
DirectXApp::onDestroy() {

}


void 
DirectXApp::onUpdate(float inDeltaTime) {
  GI_UNREFERENCED_PARAMETER(inDeltaTime);
  //World rotation
  //m_world = XMMatrixRotationY(inDeltaTime);
}


void 
DirectXApp::onRender() {

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
  //m_gapi->psSetSampler(0, 1, m_sampler);
  
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
  
  //g_

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
