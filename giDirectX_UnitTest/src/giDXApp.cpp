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
#include "giDXApp.h"
#include <giObjectLoader.h>

DirectXApp::DirectXApp() {
  //Set the window size
  m_width = 1280;
  m_height = 720;
  m_World = Matrix4::IDENTITY;
  
}


void 
DirectXApp::onCreate() {

  //Create Vertex Shader 
  m_VertexShader = m_GAPI->createVS("Resources/MyShader.fx", "VS", "vs_4_0");

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

  m_InputLayout = m_GAPI->createIL(layoutDesc, m_VertexShader);

  //Create Pixel Shader
  m_PixelShader = m_GAPI->createPS("Resources/MyShader.fx", "PS", "ps_4_0");

  //Create vertex for the cube 
  SimpleVertex vertices[] = {
    { Vector3(-1.0f, 1.0f, -1.0f), Vector2(0.0f, 0.0f),Vector3(0.f,0.f,0.f)},
    { Vector3(1.0f, 1.0f, -1.0f), Vector2(1.0f, 0.0f) ,Vector3(0.f,0.f,0.f)},
    { Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f)  ,Vector3(0.f,0.f,0.f)},
    { Vector3(-1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f) ,Vector3(0.f,0.f,0.f)},
  
    { Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f, 0.0f) ,Vector3(0.f,0.f,0.f)},
    { Vector3(1.0f, -1.0f, -1.0f), Vector2(1.0f, 0.0f)  ,Vector3(0.f,0.f,0.f)},
    { Vector3(1.0f, -1.0f, 1.0f), Vector2(1.0f, 1.0f)   ,Vector3(0.f,0.f,0.f)},
    { Vector3(-1.0f, -1.0f, 1.0f), Vector2(0.0f, 1.0f)  ,Vector3(0.f,0.f,0.f)},
  
    { Vector3(-1.0f, -1.0f, 1.0f), Vector2(0.0f, 0.0f)  ,Vector3(0.f,0.f,0.f)},
    { Vector3(-1.0f, -1.0f, -1.0f), Vector2(1.0f, 0.0f) ,Vector3(0.f,0.f,0.f)},
    { Vector3(-1.0f, 1.0f, -1.0f), Vector2(1.0f, 1.0f)  ,Vector3(0.f,0.f,0.f)},
    { Vector3(-1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f)   ,Vector3(0.f,0.f,0.f)},
  
    { Vector3(1.0f, -1.0f, 1.0f), Vector2(0.0f, 0.0f)  ,Vector3(0.f,0.f,0.f)},
    { Vector3(1.0f, -1.0f, -1.0f), Vector2(1.0f, 0.0f) ,Vector3(0.f,0.f,0.f)},
    { Vector3(1.0f, 1.0f, -1.0f), Vector2(1.0f, 1.0f)  ,Vector3(0.f,0.f,0.f)},
    { Vector3(1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f)   ,Vector3(0.f,0.f,0.f)},
  
    { Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f, 0.0f) ,Vector3(0.f,0.f,0.f)},
    { Vector3(1.0f, -1.0f, -1.0f), Vector2(1.0f, 0.0f)  ,Vector3(0.f,0.f,0.f)},
    { Vector3(1.0f, 1.0f, -1.0f), Vector2(1.0f, 1.0f)   ,Vector3(0.f,0.f,0.f)},
    { Vector3(-1.0f, 1.0f, -1.0f), Vector2(0.0f, 1.0f)  ,Vector3(0.f,0.f,0.f)},
  
    { Vector3(-1.0f, -1.0f, 1.0f), Vector2(0.0f, 0.0f) ,Vector3(0.f,0.f,0.f)},
    { Vector3(1.0f, -1.0f, 1.0f), Vector2(1.0f, 0.0f)  ,Vector3(0.f,0.f,0.f)},
    { Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f)   ,Vector3(0.f,0.f,0.f)},
    { Vector3(-1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f)  ,Vector3(0.f,0.f,0.f)},
  };

  //Create VertexBuffer
  m_vertexBuffer = m_GAPI->createBuffer(sizeof(giEngineSDK::SimpleVertex) * 24, 
  /************************************/0x1L, 
  /************************************/0, 
  /************************************/vertices);

  //Create index for the cube
  WORD indices[] = {
    3,1,0,
    2,1,3,
  
    6,4,5,
    7,4,6,
  
    11,9,8,
    10,9,11,
  
    14,12,13,
    15,12,14,
  
    19,17,16,
    18,17,19,
  
    22,20,21,
    23,20,22
  };

  //Create Index Buffer
  m_indexBuffer = m_GAPI->createBuffer(sizeof(WORD) * 36, 
  /***********************************/GI_BIND_FLAG::E::kBIND_INDEX_BUFFER, 
  /***********************************/0,
  /***********************************/indices);


  ImageLoader imgLoader;
  imgLoader.clearData();

           //Load Models

  //Load Yoshi model
  m_Yoshi.loadModel("yoshipirate.obj");

  //Load the Yoshi textures
  for (int i = 0; i < m_Yoshi.getNumTextures(); i++) {
    imgLoader.loadBMP(m_Yoshi.getTextures()[i]);
  }
  imgLoader.clearData();
  imgLoader.loadBMP("Test.bmp");

  m_ColorTexture = m_GAPI->createTex2D(imgLoader.getWidth(),
  /********************************/imgLoader.getHeight(),
  /********************************/0,
  /********************************/GI_FORMAT::E::kFORMAT_R8G8B8A8_UNORM,
  /********************************/GI_BIND_FLAG::E::kBIND_SHADER_RESOURCE);

  m_GAPI->updateTexture(m_ColorTexture, 
  /*****************/imgLoader.getImgData(), 
  /*****************/imgLoader.getPitch(), 
  /*****************/imgLoader.getImgSize());
          

  //Set Topology
  m_GAPI->setTopology(GI_PRIMITIVE_TOPOLOGY::E::kPRIMITIVE_TOPOLOGY_TRIANGLELIST);

  //Create Constant Buffer for Never Change
  m_ConstantBuffer_NC = m_GAPI->createBuffer(sizeof(CBNeverChanges), 0x4L, 0, nullptr);

  //Create Constant Buffer for Change on Resize
  m_ConstantBuffer_COR = m_GAPI->createBuffer(sizeof(CBChangeOnResize), 0x4L, 0, nullptr);

  //Create Constant Buffer for Change Every Frame
  m_ConstantBuffer_CEF = m_GAPI->createBuffer(sizeof(CBChangesEveryFrame), 0x4L, 0, nullptr);

  //Create the texture
  m_ColorTexture = m_GAPI->createTex2D(imgLoader.getWidth(),
  /********************************/imgLoader.getHeight(),
  /********************************/0,
  /********************************/GI_FORMAT::E::kFORMAT_R8G8B8A8_UNORM,
  /********************************/GI_BIND_FLAG::E::kBIND_SHADER_RESOURCE); //0xaabbggrr

  //Update the texture
  m_GAPI->updateTexture(m_ColorTexture, 
  /*****************/imgLoader.getImgData(), 
  /*****************/imgLoader.getPitch(), 
  /*****************/imgLoader.getImgSize());

  //Clear the image loader
  imgLoader.clearData();

  

  //Create Sampler
  SamplerDesc sampDesc;
  sampDesc.filter = 21;
  sampDesc.addressU = 1;
  sampDesc.addressV = 1;
  sampDesc.addressW = 1;
  sampDesc.comparisonFunc = 1;
  sampDesc.minLOD = 0;
  sampDesc.maxLOD = 3.402823466e+38f;
  m_Sampler = m_GAPI->createSampler(sampDesc);

  //Initialize world matrix
  m_World = Matrix4::IDENTITY;

  //Initialize Camera
  m_MainCamera.init(180, static_cast<float>((m_width/m_height)), 0.0001f, 10000.0f);
  
  //Sets the view matrix
  CBNeverChanges tmpNC;
  tmpNC.mView = m_MainCamera.getViewMatrix();
  m_GAPI->updateSubresource(m_ConstantBuffer_NC, &tmpNC, sizeof(tmpNC));

  //Sets the projection matrix
  CBChangeOnResize tmpCOR;
  tmpCOR.mProjection = m_MainCamera.getProyectionMatrix();
  m_GAPI->updateSubresource(m_ConstantBuffer_COR, &tmpCOR, sizeof(tmpCOR));
  
}


void 
DirectXApp::onDestroy() {

}


void 
DirectXApp::onUpdate(float inDeltaTime) {
  GI_UNREFERENCED_PARAMETER(inDeltaTime);
  //World rotation
  //m_World = XMMatrixRotationY(inDeltaTime);
}


void 
DirectXApp::onRender() {

  //Set Render Target & Depth Stencil
  m_GAPI->omSetRenderTarget(static_cast<Texture2D*>(m_GAPI->getDefaultRenderTarget()), 
  /*********************/static_cast<Texture2D*>(m_GAPI->getDefaultDephtStencil()));

  //Set Input Layout
  m_GAPI->aiSetInputLayout(m_InputLayout);

  //Clear the back buffer
  float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
  m_GAPI->clearRTV(static_cast<Texture2D*>(m_GAPI->getDefaultRenderTarget()), 
  /************/ClearColor);

  //Clear the depth buffer to 1.0 (max depth)
  m_GAPI->clearDSV(static_cast<Texture2D*>(m_GAPI->getDefaultDephtStencil()));

  //Update variables that change once per frame
  CBChangesEveryFrame cb;
  cb.mWorld = m_World.transpose();
  cb.vMeshColor = m_MeshColor;
  m_GAPI->updateSubresource(m_ConstantBuffer_CEF, &cb, sizeof(cb));

  //Render the cube/sets values
  m_GAPI->vsSetShader(m_VertexShader);
  m_GAPI->vsSetConstantBuffer(0, m_ConstantBuffer_NC);
  m_GAPI->vsSetConstantBuffer(1, m_ConstantBuffer_COR);
  m_GAPI->vsSetConstantBuffer(2, m_ConstantBuffer_CEF);
  m_GAPI->psSetShader(m_PixelShader);
  m_GAPI->psSetConstantBuffer(2, m_ConstantBuffer_CEF);
  m_GAPI->psSetShaderResource(0, m_ColorTexture);
  m_GAPI->psSetSampler(0, 1, m_Sampler);
  
  //Set Vertex Buffer
  uint32 stride = sizeof(giEngineSDK::SimpleVertex);
  m_GAPI->setVertexBuffer(m_vertexBuffer, stride);

  //Set Index Buffer
  m_GAPI->setIndexBuffer(m_indexBuffer, GI_FORMAT::E::kFORMAT_R16_UINT);


  //Sets the render target and depth Stencil
  //m_GAPI->omSetRenderTarget(static_cast<Texture2D*>(m_GAPI->getDefaultRenderTarget()),
  //*********************/static_cast<Texture2D*>(m_GAPI->getDefaultDephtStencil()));

  //Draw the cube
  m_GAPI->drawIndexed(36, 0);

    
}


void 
DirectXApp::onEvent(Event inEvent) {
  
  if (inEvent.type == Event::KeyPressed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
    /**/sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      Vector4 tmpVect = { 0.f, 0.f, 0.1f, 0.0f };
      m_MainCamera.move(tmpVect);
      CBNeverChanges tmpNC;
      tmpNC.mView = m_MainCamera.getViewMatrix();
      m_GAPI->updateSubresource(m_ConstantBuffer_NC, &tmpNC, sizeof(tmpNC));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
    /**/sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      Vector4 tmpVect = { 0.f, 0.f, -0.1f, 0.0f };
      m_MainCamera.move(tmpVect);
      CBNeverChanges tmpNC;
      tmpNC.mView = m_MainCamera.getViewMatrix();
      m_GAPI->updateSubresource(m_ConstantBuffer_NC, &tmpNC, sizeof(tmpNC));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
    /**/sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      Vector4 tmpVect = { -0.1f, 0.f, 0.f, 0.0f };
      m_MainCamera.move(tmpVect);
      CBNeverChanges tmpNC;
      tmpNC.mView = m_MainCamera.getViewMatrix();
      m_GAPI->updateSubresource(m_ConstantBuffer_NC, &tmpNC, sizeof(tmpNC));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
    /**/sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      Vector4 tmpVect = { 0.1f, 0.f, 0.f, 0.0f };
      m_MainCamera.move(tmpVect);
      CBNeverChanges tmpNC;
      tmpNC.mView = m_MainCamera.getViewMatrix();
      m_GAPI->updateSubresource(m_ConstantBuffer_NC, &tmpNC, sizeof(tmpNC));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
      Vector4 tmpVect = { 0.f, 0.1f, 0.1f, 0.0f };
      m_MainCamera.move(tmpVect);
      CBNeverChanges tmpNC;
      tmpNC.mView = m_MainCamera.getViewMatrix();
      m_GAPI->updateSubresource(m_ConstantBuffer_NC, &tmpNC, sizeof(tmpNC));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
      Vector4 tmpVect = { 0.f, -0.1f, 0.1f, 0.0f };
      m_MainCamera.move(tmpVect);
      CBNeverChanges tmpNC;
      tmpNC.mView = m_MainCamera.getViewMatrix();
      m_GAPI->updateSubresource(m_ConstantBuffer_NC, &tmpNC, sizeof(tmpNC));
    }
    //CBNeverChanges tmpNC;
    //tmpNC.mView = m_MainCamera.getViewMatrix();
    //m_GAPI->updateSubresource(m_ConstantBuffer_NC, &tmpNC, sizeof(tmpNC));
  }
}