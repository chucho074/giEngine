/**
 * @file    giRenderer.cpp
 * @author  Jes�s Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/08/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include <giInputLayout.h>

#include <giSceneGraph.h>
#include <giModel.h>
#include <giStaticMesh.h>
#include <giBaseVertexShader.h>
#include <giBasePixelShader.h>
#include <giDegrees.h>
#include "giRenderer.h"

namespace giEngineSDK {

  void 
  Renderer::create() {
    auto& gapi = g_graphicsAPI();
    auto& sgraph = SceneGraph::instance();
    
    //Initialize Camera
    m_mainCamera.init(Degrees(75.0f).getRadians(), 
                      1280.f / 720.f, 
                      0.01f, 
                      1000.0f);

    //Initialize Shadow Camera
    m_ShadowCamera.init(Degrees(75.0f).getRadians(), 
                        1920 / 1080, 
                        0.01f, 
                        1000.0f);

    m_ShadowCamera.setPosition({ 360.0f, 280.0f, -200.0f, 0.0f },
                               { 0.0f, 1.0f, 0.0f, 0.0f },
                               { 0.0f, 1.0f,  0.0f, 0.0f });

    //Create Sampler
    SamplerDesc sampDesc;
    sampDesc.filter = 21;
    sampDesc.addressU = 1;
    sampDesc.addressV = 1;
    sampDesc.addressW = 1;
    sampDesc.comparisonFunc = 1;
    sampDesc.minLOD = 0;
    sampDesc.maxLOD = 3.402823466e+38f;
    m_sampler = gapi.createSampler(sampDesc);

    //Main Camera
    //Sets the view matrix
    CameraConstantBuffer tmpConstantCamera;
    tmpConstantCamera.mView = m_mainCamera.getViewMatrix().transpose();

    //Sets the projection matrix
    tmpConstantCamera.mProjection = m_mainCamera.getProyectionMatrix().transpose();

    //Create Constant Buffer for Camera
    m_cBufferCamera = gapi.createBuffer(sizeof(CameraConstantBuffer),
                                        4,
                                        0,
                                        nullptr);
    //Update the Camera Constant Buffer 
    gapi.updateSubresource(m_cBufferCamera, 
                           &tmpConstantCamera, 
                           sizeof(tmpConstantCamera));

    //Shadow Camera
    
    //Sets the view matrix
    CameraConstantBuffer tmpConstantShadowCamera;
    tmpConstantShadowCamera.mView = m_ShadowCamera.getViewMatrix().transpose();

    //Sets the projection matrix
    tmpConstantShadowCamera.mProjection = m_ShadowCamera.getProyectionMatrix().transpose();

    //Create Constant Buffer for Camera
    m_cBufferShadow = gapi.createBuffer(sizeof(CameraConstantBuffer),
                                        4,
                                        0,
                                        nullptr);
    //Update the Camera Constant Buffer 
    gapi.updateSubresource(m_cBufferShadow,
                           &tmpConstantShadowCamera,
                           sizeof(tmpConstantShadowCamera));

    // Update variables that change once per frame
    CBChangesEveryFrame tmpConstantEveryFrame;
    tmpConstantEveryFrame.mWorld = Matrix4::IDENTITY;/*
    tmpConstantEveryFrame.mWorld.m_xColumn.x = 0.05f;
    tmpConstantEveryFrame.mWorld.m_yColumn.y = 0.05f;
    tmpConstantEveryFrame.mWorld.m_zColumn.z = 0.05f;*/
    tmpConstantEveryFrame.vMeshColor = m_meshColor;


    //Create Constant Buffer for Change Every Frame
    m_cBufferChangeEveryFrame = gapi.createBuffer(sizeof(CBChangesEveryFrame), 
                                                  4,
                                                  0,
                                                  nullptr);


    //Update the Camera Constant Buffer 
    gapi.updateSubresource(m_cBufferChangeEveryFrame,
                           &tmpConstantEveryFrame,
                           sizeof(tmpConstantEveryFrame));
    
    

    /************************************************************************/
    /*                           GBUFFER                                    */
    /************************************************************************/
    //Raster


    //Create Vertex Shader 
    m_vertexShader = gapi.createVS("Resources/gBuffer.hlsl", "VS_GBUFFER", "vs_4_0");

    //Create Pixel Shader
    m_pixelShader = gapi.createPS("Resources/gBuffer.hlsl", "PS_GBUFFER", "ps_4_0");
    
    //Create Input Layout
    Vector<InputLayoutDesc> layoutDesc;
    
    //Set the size for the inputLayout
    layoutDesc.resize(5);
    
            //Sets the input Layout values
    
    //Positions
    layoutDesc[0].semanticName = "POSITION";
    layoutDesc[0].semanticIndex = 0;
    layoutDesc[0].format = GI_FORMAT::kFORMAT_R32G32B32_FLOAT;
    layoutDesc[0].inputSlot = 0;
    layoutDesc[0].alignedByteOffset = ALIGN_ELEMENT;
    layoutDesc[0].inputSlotClass = GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
    layoutDesc[0].instanceDataStepRate = 0;

    //texcoords
    layoutDesc[1].semanticName = "TEXCOORD";
    layoutDesc[1].semanticIndex = 0;
    layoutDesc[1].format = GI_FORMAT::kFORMAT_R32G32_FLOAT;
    layoutDesc[1].inputSlot = 0;
    layoutDesc[1].alignedByteOffset = ALIGN_ELEMENT;
    layoutDesc[1].inputSlotClass = GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
    layoutDesc[1].instanceDataStepRate = 0;

    //normals
    layoutDesc[2].semanticName = "NORMAL";
    layoutDesc[2].semanticIndex = 0;
    layoutDesc[2].format = GI_FORMAT::kFORMAT_R32G32B32_FLOAT;
    layoutDesc[2].inputSlot = 0;
    layoutDesc[2].alignedByteOffset = ALIGN_ELEMENT;
    layoutDesc[2].inputSlotClass = GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
    layoutDesc[2].instanceDataStepRate = 0;

    //tangents
    layoutDesc[3].semanticName = "TANGENT";
    layoutDesc[3].semanticIndex = 0;
    layoutDesc[3].format = GI_FORMAT::kFORMAT_R32G32B32_FLOAT;
    layoutDesc[3].inputSlot = 0;
    layoutDesc[3].alignedByteOffset = ALIGN_ELEMENT;
    layoutDesc[3].inputSlotClass = GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
    layoutDesc[3].instanceDataStepRate = 0;

    //binormals
    layoutDesc[4].semanticName = "BINORMAL";
    layoutDesc[4].semanticIndex = 0;
    layoutDesc[4].format = GI_FORMAT::kFORMAT_R32G32B32_FLOAT;
    layoutDesc[4].inputSlot = 0;
    layoutDesc[4].alignedByteOffset = ALIGN_ELEMENT;
    layoutDesc[4].inputSlotClass = GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
    layoutDesc[4].instanceDataStepRate = 0;
    
    //Create the Input Layout
    m_inputLayout = gapi.createIL(layoutDesc, m_vertexShader);
    
    
    //Create the textures
    
    //Positions
    m_renderTargets.push_back(gapi.createTex2D(1280, 
                                               720, 
                                               1,
                                               GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                                               GI_BIND_FLAG::kBIND_RENDER_TARGET 
                                               | GI_BIND_FLAG::kBIND_SHADER_RESOURCE));
    //Normales
    m_renderTargets.push_back(gapi.createTex2D(1280, 
                                               720, 
                                               1,
                                               GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                                               GI_BIND_FLAG::kBIND_RENDER_TARGET 
                                               | GI_BIND_FLAG::kBIND_SHADER_RESOURCE));
    //Albedo
    m_renderTargets.push_back(gapi.createTex2D(1280, 
                                               720, 
                                               1,
                                               GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                                               GI_BIND_FLAG::kBIND_RENDER_TARGET 
                                               | GI_BIND_FLAG::kBIND_SHADER_RESOURCE));


    /************************************************************************/
    /*                               SSAO                                   */
    /************************************************************************/
    //Create Vertex Shader 
    m_vertexShaderSSAO = gapi.createVS("Resources/SSAO.hlsl", "VS_SSAO", "vs_4_0");

    //Create Pixel Shader
    m_pixelShaderSSAO = gapi.createPS("Resources/SSAO.hlsl", "PS_SSAO", "ps_4_0");

    //Create Input Layout
    Vector<InputLayoutDesc> layoutDescSSAO;

    //Set the size for the inputLayout
    layoutDescSSAO.resize(2);

    //Sets the input Layout values

    //Positions
    layoutDescSSAO[0].semanticName = "POSITION";
    layoutDescSSAO[0].semanticIndex = 0;
    layoutDescSSAO[0].format = GI_FORMAT::kFORMAT_R32G32B32_FLOAT;
    layoutDescSSAO[0].inputSlot = 0;
    layoutDescSSAO[0].alignedByteOffset = ALIGN_ELEMENT;
    layoutDescSSAO[0].inputSlotClass = GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
    layoutDescSSAO[0].instanceDataStepRate = 0;

    //Texcoords
    layoutDescSSAO[1].semanticName = "TEXCOORD";
    layoutDescSSAO[1].semanticIndex = 0;
    layoutDescSSAO[1].format = GI_FORMAT::kFORMAT_R32G32_FLOAT;
    layoutDescSSAO[1].inputSlot = 0;
    layoutDescSSAO[1].alignedByteOffset = ALIGN_ELEMENT;
    layoutDescSSAO[1].inputSlotClass = GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
    layoutDescSSAO[1].instanceDataStepRate = 0;

    //Create the Input Layout
    m_inputLayoutSSAO = gapi.createIL(layoutDescSSAO, m_vertexShaderSSAO);

    m_SSAOTexture.push_back(gapi.createTex2D(1280,
                                             720, 
                                             1,
                                             GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                                             GI_BIND_FLAG::kBIND_RENDER_TARGET 
                                             | GI_BIND_FLAG::kBIND_SHADER_RESOURCE));

    
    for (int32 i = 0; i < 7; ++i) {
      m_SSAOTexture.push_back(nullptr);
    }
    SSAOConstantBuffer SSAOcb;
    SSAOcb.Intensity = 2.0f;
    SSAOcb.SampleRadius = 0.800f;
    SSAOcb.Scale = 1.0f;
    SSAOcb.Bias = 0.0800f;

    m_cBufferSSAO = gapi.createBuffer(sizeof(SSAOConstantBuffer),
                                      4, 
                                      0, 
                                      &SSAOcb);


    /************************************************************************/
    /*                               BLUR                                   */
    /************************************************************************/
    //Create Vertex Shader 
    m_vertexShaderBlur = gapi.createVS("Resources/Blur.hlsl", "vs_blur", "vs_4_0");

    //Create Pixel Shader
    m_pixelShaderBlurH = gapi.createPS("Resources/Blur.hlsl", "ps_gaussian_blurH", "ps_4_0");

    //Create Pixel Shader
    m_pixelShaderBlurV = gapi.createPS("Resources/Blur.hlsl", "ps_gaussian_blurV", "ps_4_0");


    //Create the texture
    m_BlurTexture.push_back(gapi.createTex2D(1280,
                                             720,
                                             1,
                                             GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                                             GI_BIND_FLAG::kBIND_RENDER_TARGET 
                                             | GI_BIND_FLAG::kBIND_SHADER_RESOURCE));

    //Set the Constant buffer data
    BlurConstantBuffer Blurcb;
    Blurcb.Gamma = 1;
    Blurcb.Viewport.x = 1280;
    Blurcb.Viewport.y = 720;
    m_cBufferBlur = gapi.createBuffer(sizeof(BlurConstantBuffer),
                                      4, 
                                      0, 
                                      &Blurcb);

    /************************************************************************/
    /*                              SHADOWS                                 */
    /************************************************************************/
    //Create Vertex Shader
    m_vertexShaderShadow = gapi.createVS("Resources/Shadow.hlsl", "vs_Shadow", "vs_4_0");
    
    //Create Pixel Shader
    m_pixelShaderShadow = gapi.createPS("Resources/Shadow.hlsl", "ps_Shadow", "ps_4_0");

    //Create the texture
    m_ShadowTexture.push_back(gapi.createTex2D(1920, 
                                               1080, 
                                               1, 
                                               GI_FORMAT::kFORMAT_R8_UNORM, 
                                               GI_BIND_FLAG::kBIND_RENDER_TARGET 
                                               | GI_BIND_FLAG::kBIND_SHADER_RESOURCE));

    //Pasar la textura al pase de iluminacion o textura de sombras, pasar la info de la camara de vista y la camara de sombras para 
    //pasar la inversa de la matriz de vista de la camara de sombras, agarrar las posiciones, convertirlas a espacio de vista de la luz
    //y luego pasarlos a espacio de proyeccion (multiplicar por sus matrices, clip) sacar las coords de textura y ponerlas en terminos de entre 0 y 1
    //Operacion -> 0.5+ Posiciones * 0.5, samplear la textura, pasar el sampler y poner en X y Y con los valores de la operacion


    /************************************************************************/
    /*                               LIGHT                                  */
    /************************************************************************/
    //Create Vertex Shader 
    m_vertexShaderLight = gapi.createVS("Resources/Light.hlsl", "vs_main", "vs_4_0");

    //Create Pixel Shader
    m_pixelShaderLight = gapi.createPS("Resources/Light.hlsl", "ps_main", "ps_4_0");

    //Create Input Layout
    Vector<InputLayoutDesc> layoutDescLight;

    //Set the size for the inputLayout
    layoutDescLight.resize(2);

    //Sets the input Layout values
    //Positions
    layoutDescLight[0].semanticName = "SV_POSITION";
    layoutDescLight[0].semanticIndex = 0;
    layoutDescLight[0].format = GI_FORMAT::kFORMAT_R32G32B32A32_FLOAT;
    layoutDescLight[0].inputSlot = 0;
    layoutDescLight[0].alignedByteOffset = ALIGN_ELEMENT;
    layoutDescLight[0].inputSlotClass = GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
    layoutDescLight[0].instanceDataStepRate = 0;
    //Texcoords
    layoutDescLight[1].semanticName = "TEXCOORD";
    layoutDescLight[1].semanticIndex = 0;
    layoutDescLight[1].format = GI_FORMAT::kFORMAT_R32G32_FLOAT;
    layoutDescLight[1].inputSlot = 0;
    layoutDescLight[1].alignedByteOffset = ALIGN_ELEMENT;
    layoutDescLight[1].inputSlotClass = GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
    layoutDescLight[1].instanceDataStepRate = 0;

    //Create the Input Layout
    m_inputLayoutLight = gapi.createIL(layoutDescLight, m_vertexShaderLight);

    //Create the texture
    m_BlurTexture.push_back(gapi.createTex2D(1280,
                                             720, 
                                             1,
                                             GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                                             GI_BIND_FLAG::kBIND_RENDER_TARGET 
                                             | GI_BIND_FLAG::kBIND_SHADER_RESOURCE));

    LightConstantBuffer Lightcb;
    Lightcb.LightIntensity = 2;
    Lightcb.LightPos.x = 360;
    Lightcb.LightPos.y = 280;
    Lightcb.LightPos.z = -200;
    Lightcb.ViewPos = m_mainCamera.m_viewMatrix.m_zColumn;
    Lightcb.InverseView = m_mainCamera.m_viewMatrix.inverse();
    m_cBufferLight = gapi.createBuffer(sizeof(LightConstantBuffer),
                                      4,
                                      0,
                                      &Lightcb);
    
    
    m_SAQ = make_shared<Model>();

    m_SAQ->loadFromFile("Resources/Models/ScreenAlignedQuad.3ds");


  }
  
  void 
  Renderer::render() {

    auto& gapi = g_graphicsAPI();
    auto& sgraph = SceneGraph::instance();

    /************************************************************************/
    /*                           GBUFFER                                    */
    /************************************************************************/
    //Set Render Targets
    gapi.omSetRenderTarget(m_renderTargets,
                           gapi.getDefaultDephtStencil());

    //Set Input Layout
    gapi.aiSetInputLayout(m_inputLayout);

    //Set Shaders
    gapi.vsSetShader(m_vertexShader);
    gapi.psSetShader(m_pixelShader);

    gapi.psSetSampler(0, 1, m_sampler);

    //Set Constant Buffers
    gapi.vsSetConstantBuffer(0, m_cBufferCamera);
    gapi.vsSetConstantBuffer(1, m_cBufferChangeEveryFrame);
    gapi.psSetConstantBuffer(1, m_cBufferChangeEveryFrame);

    //Clear the back buffer
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
    gapi.clearRTV(gapi.getDefaultRenderTarget(), 
                     ClearColor);
    
    //Clear the depth buffer to 1.0 (max depth)
    gapi.clearDSV(gapi.getDefaultDephtStencil());

    //Draw models
    sgraph.draw();

    /************************************************************************/
    /*                           SSAO                                       */
    /************************************************************************/
    //Set Render Targets
    gapi.omSetRenderTarget(m_SSAOTexture,
                           nullptr);

     //Clear the texture to draw
    gapi.clearRTV(m_SSAOTexture[0],
                  ClearColor);

    //Set Input Layout
    gapi.aiSetInputLayout(m_inputLayoutSSAO);

    //Set Shaders
    gapi.vsSetShader(m_vertexShaderSSAO);
    gapi.psSetShader(m_pixelShaderSSAO);

    //Set Constant Buffers
    gapi.vsSetConstantBuffer(0, m_cBufferSSAO);
    gapi.psSetConstantBuffer(0, m_cBufferSSAO);

    //Clear the depth buffer to 1.0 (max depth)
    
    gapi.psSetShaderResource(0, m_renderTargets[0]);
    gapi.psSetShaderResource(1, m_renderTargets[1]);


    m_SAQ->drawModel();

    /************************************************************************/
    /*                           BlurH                                      */
    /************************************************************************/
    //Set Render Targets
    gapi.omSetRenderTarget(m_BlurTexture,
                           nullptr);

    //Clear the texture to draw
    gapi.clearRTV(m_BlurTexture[0],
                  ClearColor);

    //Set Input Layout
    //gapi.aiSetInputLayout(m_inputLayoutBlur);

    //Set Shaders
    //gapi.vsSetShader(m_vertexShaderSSAO);
    gapi.psSetShader(m_pixelShaderBlurH);

    //Set Constant Buffers
    gapi.vsSetConstantBuffer(0, m_cBufferBlur);
    gapi.psSetConstantBuffer(0, m_cBufferBlur);

    //Clear the depth buffer to 1.0 (max depth)

    gapi.psSetShaderResource(0, m_SSAOTexture[0]);
    m_SAQ->drawModel();

    gapi.psSetShaderResource(0, nullptr);


    /************************************************************************/
    /*                           BlurV                                      */
    /************************************************************************/
    //Set Render Targets
    gapi.omSetRenderTarget(m_SSAOTexture,
                           nullptr);

    //Clear the texture to draw
    //gapi.clearRTV(m_SSAOTexture[0],
    //              ClearColor);

    //Set Input Layout
    //gapi.aiSetInputLayout(m_inputLayoutBlur);

    //Set Shaders
    //gapi.vsSetShader(m_vertexShaderSSAO);
    gapi.psSetShader(m_pixelShaderBlurV);

    //Set Constant Buffers
    gapi.vsSetConstantBuffer(0, m_cBufferBlur);
    gapi.psSetConstantBuffer(0, m_cBufferBlur);

    //Clear the depth buffer to 1.0 (max depth)

    gapi.psSetShaderResource(0, m_BlurTexture[0]);
    m_SAQ->drawModel();

    gapi.psSetShaderResource(0, nullptr);
    gapi.psSetShaderResource(1, nullptr);

    /************************************************************************/
    /*                           Shadow                                     */
    /************************************************************************/

    //gapi.createVP();

    //Set Render Targets
    gapi.omSetRenderTarget(m_ShadowTexture,
                           nullptr);

     //Clear the texture to draw
    gapi.clearRTV(m_ShadowTexture[0],
                  ClearColor);

    //Set Input Layout
    gapi.aiSetInputLayout(m_inputLayout);

    //Set Shaders
    gapi.vsSetShader(m_vertexShaderShadow);
    gapi.psSetShader(m_pixelShaderShadow);

    //Set Constant Buffers
    gapi.vsSetConstantBuffer(0, m_cBufferShadow);
    gapi.psSetConstantBuffer(0, m_cBufferShadow);

    //Clear the depth buffer to 1.0 (max depth)
    
    //gapi.psSetShaderResource(0, m_renderTargets[0]);
    //gapi.psSetShaderResource(1, m_renderTargets[1]);


    sgraph.draw();
    //m_SAQ->drawModel();

    /************************************************************************/
    /*                           Light                                      */
    /************************************************************************/

    //Set Render Targets
    Vector<Texture2D*> tmpVector;
    tmpVector.push_back(gapi.getDefaultRenderTarget());

    gapi.omSetRenderTarget(tmpVector,
                           gapi.getDefaultDephtStencil());

    //Set Input Layout
    gapi.aiSetInputLayout(m_inputLayoutLight);

    //Set Shaders
    gapi.vsSetShader(m_vertexShaderLight);
    gapi.psSetShader(m_pixelShaderLight);

    //Set Constant Buffers
    gapi.vsSetConstantBuffer(0, m_cBufferCamera);
    gapi.vsSetConstantBuffer(1, m_cBufferChangeEveryFrame);
    gapi.psSetConstantBuffer(1, m_cBufferChangeEveryFrame);
    gapi.vsSetConstantBuffer(2, m_cBufferLight);
    gapi.psSetConstantBuffer(2, m_cBufferLight);

    for (int32 i = 0; i < m_renderTargets.size(); ++i) {
      gapi.psSetShaderResource(i, m_renderTargets[i]);
    }

    gapi.psSetShaderResource(3, m_SSAOTexture[0]);
    gapi.psSetShaderResource(4, m_ShadowTexture[0]);

    //Clear the texture to draw
    gapi.clearRTV(gapi.getDefaultRenderTarget(),
                  ClearColor);

    //Clear the depth buffer to 1.0 (max depth)
    gapi.clearDSV(gapi.getDefaultDephtStencil());
    

    //gapi.psSetShaderResource(0, m_BlurTexture[0]);
    m_SAQ->drawModel();
    

    for (int32 i = 0; i < m_renderTargets.size(); ++i) {
      gapi.psSetShaderResource(i, nullptr);
    }

    gapi.psSetShaderResource(3, nullptr);

  }
  
  void 
  Renderer::setModels(Vector<SharedPtr<Model>> inModelList) {
    
  }

}