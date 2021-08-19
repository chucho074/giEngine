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

  //Create Vertex Shader 
  m_vertexShader = m_gapi->createVS("Resources/MyShader.fx", "VS", "vs_4_0");

  //Create Input Layout
  Vector<InputLayoutDesc> layoutDesc;

  //Set the size for the inputLayout
  layoutDesc.resize(3);

          //Sets the input Layout values

  //Positions
  layoutDesc[0].semanticName = "POSITION";
  layoutDesc[0].semanticIndex = 0;
  layoutDesc[0].format = DXGI_FORMAT_R32G32B32_FLOAT;
  layoutDesc[0].inputSlot = 0;
  layoutDesc[0].alignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
  layoutDesc[0].inputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  layoutDesc[0].instanceDataStepRate = 0;

  //texcoords
  layoutDesc[1].semanticName = "TEXCOORD";
  layoutDesc[1].semanticIndex = 0;
  layoutDesc[1].format = DXGI_FORMAT_R32G32_FLOAT;
  layoutDesc[1].inputSlot = 0;
  layoutDesc[1].alignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
  layoutDesc[1].inputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  layoutDesc[1].instanceDataStepRate = 0;
  
  //normals
  layoutDesc[2].semanticName = "NORMAL";
  layoutDesc[2].semanticIndex = 0;
  layoutDesc[2].format = DXGI_FORMAT_R32G32_FLOAT;
  layoutDesc[2].inputSlot = 0;
  layoutDesc[2].alignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
  layoutDesc[2].inputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  layoutDesc[2].instanceDataStepRate = 0;

  //Create the Input Layout
  m_inputLayout = m_gapi->createIL(layoutDesc, m_vertexShader);

  //Create Pixel Shader
  m_pixelShader = m_gapi->createPS("Resources/MyShader.fx", "PS", "ps_4_0");

  //Create the resource (The model)
  //Create & assign to the component (StaticMesh)
  //Assign the component to the actor
  //Add the actor to the scene graph

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
  m_cBufferNeverChange = m_gapi->createBuffer(sizeof(CBNeverChanges), 
                                              4, 
                                              0, 
                                              nullptr);

  //Create Constant Buffer for Change on Resize
  m_cBufferChangeOnResize = m_gapi->createBuffer(sizeof(CBChangeOnResize), 
                                                 4, 
                                                 0, 
                                                 nullptr);

  //Create Constant Buffer for Change Every Frame
  m_cBufferChangeEveryFrame = m_gapi->createBuffer(sizeof(CBChangesEveryFrame), 
                                                   4, 
                                                   0, 
                                                   nullptr);

 
  //Create Sampler
  SamplerDesc sampDesc;
  sampDesc.filter = 21;
  sampDesc.addressU = 1;
  sampDesc.addressV = 1;
  sampDesc.addressW = 1;
  sampDesc.comparisonFunc = 1;
  sampDesc.minLOD = 0;
  sampDesc.maxLOD = 3.402823466e+38f;
  m_sampler = m_gapi->createSampler(sampDesc);

  //Initialize world matrix
  m_world = Matrix4::IDENTITY;

  //Initialize Camera
  m_mainCamera.init(Degrees(75.0f).getRadians(), 
                    (m_width/m_height), 
                    0.01f, 
                    1000.0f);

  //Sets the view matrix
  CBNeverChanges tmpNC;
  tmpNC.mView = m_mainCamera.getViewMatrix();
  m_gapi->updateSubresource(m_cBufferNeverChange, &tmpNC, sizeof(tmpNC));

  //Sets the projection matrix
  CBChangeOnResize tmpCOR;
  tmpCOR.mProjection = m_mainCamera.getProyectionMatrix();
  m_gapi->updateSubresource(m_cBufferChangeOnResize, &tmpCOR, sizeof(tmpCOR));
  
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

  //Set Render Target & Depth Stencil
  Vector<Texture2D*> tmpVector;
  tmpVector.push_back(m_gapi->getDefaultRenderTarget());
  m_gapi->omSetRenderTarget(tmpVector,
                            m_gapi->getDefaultDephtStencil());

  //Set Input Layout
  m_gapi->aiSetInputLayout(m_inputLayout);

  //Clear the back buffer
  float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
  m_gapi->clearRTV(m_gapi->getDefaultRenderTarget(), 
                   ClearColor);

  //Clear the depth buffer to 1.0 (max depth)
  m_gapi->clearDSV(m_gapi->getDefaultDephtStencil());

  //Update variables that change once per frame
  CBChangesEveryFrame cb;
  cb.mWorld = m_world.transpose();
  cb.vMeshColor = m_meshColor;
  m_gapi->updateSubresource(m_cBufferChangeEveryFrame, &cb, sizeof(cb));

  //Render the cube/sets values
  m_gapi->vsSetShader(m_vertexShader);
  m_gapi->vsSetConstantBuffer(0, m_cBufferNeverChange);
  m_gapi->vsSetConstantBuffer(1, m_cBufferChangeOnResize);
  m_gapi->vsSetConstantBuffer(2, m_cBufferChangeEveryFrame);
  m_gapi->psSetShader(m_pixelShader);
  m_gapi->psSetConstantBuffer(2, m_cBufferChangeEveryFrame);
  m_gapi->psSetShaderResource(0, m_colorTexture);
  m_gapi->psSetSampler(0, 1, m_sampler);
  
  //Apply a rotation
  static float tmpRotation = Math::PI / 550.0f;
  tmpRotation += Math::PI / 550.0f;

  //Sets values to the world
  m_world = Matrix4::IDENTITY;
  m_world *= matrixTranslation({60.f, -10.0f, 50.f});
  m_world *= matrixRotationY(180);
  //m_world *= matrixRotationZ(180);
  //m_world *= matrixRotationY(tmpRotation);
  //m_world *= XMMatrixScaling(0.1f, 0.1f, 0.1f);

  cb.mWorld = m_world.transpose();
  cb.vMeshColor = m_meshColor;

  //Update the Change Every Frame Buffer
  m_gapi->updateSubresource(m_cBufferChangeEveryFrame, &cb, sizeof(cb));
  m_gapi->vsSetConstantBuffer(2, m_cBufferChangeEveryFrame);
  m_gapi->psSetConstantBuffer(2, m_cBufferChangeEveryFrame);

  //Draw the Yoshi model
  //m_yoshi.drawModel();

  m_sceneGraph->draw();

  //Sets values to the world
  m_world = Matrix4::IDENTITY;
  //m_world = XMMatrixRotationY(tmpRotation);
  //m_world *= XMMatrixScaling(0.1f, 0.1f, 0.1f);
  //m_world *= XMMatrixTranslation(0.f, 1.5f, 0.f);

  cb.mWorld = m_world.transpose();
  cb.vMeshColor = m_meshColor;
  
  //Update the Change Every Frame Buffer
  m_gapi->updateSubresource(m_cBufferChangeEveryFrame, &cb, sizeof(cb));
  m_gapi->vsSetConstantBuffer(2, m_cBufferChangeEveryFrame);
  m_gapi->psSetConstantBuffer(2, m_cBufferChangeEveryFrame);
  
  //Sets the texture
  //m_gapi->psSetShaderResource(0, m_peachTexture);

  //Draw the model
  //m_peach.drawModel();
  
}


void 
DirectXApp::onEvent(Event inEvent) {
  
  Vector4 tmpVect;
  if (inEvent.type == Event::KeyPressed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      tmpVect = { 0.f, 0.f, 0.1f, 0.0f };
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      tmpVect = { 0.f, 0.f, -0.1f, 0.0f };
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      tmpVect = { -0.1f, 0.f, 0.f, 0.0f };
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      tmpVect = { 0.1f, 0.f, 0.f, 0.0f };
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
      tmpVect = { 0.f, 0.1f, 0.f, 0.0f };
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
      tmpVect = { 0.f, -0.1f, 0.f, 0.0f };
    }
    m_mainCamera.move(tmpVect);
    CBNeverChanges tmpNC;
    tmpNC.mView = m_mainCamera.getViewMatrix();
    m_gapi->updateSubresource(m_cBufferNeverChange, &tmpNC, sizeof(tmpNC));
  }
  if (inEvent.type == Event::Resized) {    
    CBChangeOnResize tmpCOR;
    tmpCOR.mProjection = m_mainCamera.getProyectionMatrix();
    m_gapi->updateSubresource(m_cBufferChangeOnResize, &tmpCOR, sizeof(tmpCOR));
  }
}
