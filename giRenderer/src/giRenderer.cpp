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
#include <giBaseComputeShader.h>
#include <giDegrees.h>
#include "giRenderer.h"

namespace giEngineSDK {

  void 
  Renderer::create() {
    auto& gapi = g_graphicsAPI();
    auto& sgraph = SceneGraph::instance();
    
    //Get the main camera
    auto& camera = sgraph.getActorByName("MainCamera")->getComponent(COMPONENT_TYPE::kCamera);
    m_mainCamera = static_pointer_cast<Camera>(camera);
    //Get the Shadow Camera
    
    auto& lightCamera = sgraph.getActorByName("Light")->getComponent(COMPONENT_TYPE::kCamera);
    m_ShadowCamera = static_pointer_cast<Camera>(lightCamera);

    //Create SamplerState
    SamplerDesc sampDesc;
    sampDesc.filter = GI_FILTER::kFILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
    sampDesc.addressU = GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
    sampDesc.addressV = GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
    sampDesc.addressW = GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
    sampDesc.comparisonFunc = 1;
    sampDesc.minLOD = 0;
    sampDesc.maxLOD = 3.402823466e+38f;
    m_sampler = gapi.createSampler(sampDesc);

    //Main Camera
    //Sets the view matrix
    CameraConstantBuffer tmpConstantCamera;
    tmpConstantCamera.mView = m_mainCamera->getViewMatrix().transpose();

    //Sets the projection matrix
    tmpConstantCamera.mProjection = m_mainCamera->getProyectionMatrix().transpose();

    //Create Constant Buffer for Camera
    m_cBufferCamera = gapi.createBuffer(sizeof(CameraConstantBuffer),
                                        GI_BIND_FLAG::kBIND_CONSTANT_BUFFER,
                                        nullptr);
    //Update the Camera Constant Buffer 
    gapi.updateSubresource(m_cBufferCamera, 
                           &tmpConstantCamera, 
                           sizeof(tmpConstantCamera));
    //Shadow Camera
    
    //Sets the view matrix
    CameraConstantBuffer tmpConstantShadowCamera;
    tmpConstantShadowCamera.mView = m_ShadowCamera->getViewMatrix().transpose();

    //Sets the projection matrix
    tmpConstantShadowCamera.mProjection = m_ShadowCamera->getProyectionMatrix().transpose();

    //Create Constant Buffer for Camera
    m_cBufferShadow = gapi.createBuffer(sizeof(CameraConstantBuffer),
                                        GI_BIND_FLAG::kBIND_CONSTANT_BUFFER,
                                        nullptr);
    //Update the Camera Constant Buffer 
    gapi.updateSubresource(m_cBufferShadow,
                           &tmpConstantShadowCamera,
                           sizeof(tmpConstantShadowCamera));

    // Update variables that change once per frame
    CBChangesEveryFrame tmpConstantEveryFrame;
    tmpConstantEveryFrame.mWorld = Matrix4::IDENTITY;
    //tmpConstantEveryFrame.vMeshColor = m_meshColor;


    //Create Constant Buffer for Change Every Frame
    m_cBufferChangeEveryFrame = gapi.createBuffer(sizeof(CBChangesEveryFrame), 
                                                  GI_BIND_FLAG::kBIND_CONSTANT_BUFFER,
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
    m_vertexShader = gapi.createVShaderFromFile(L"Resources/gBuffer.hlsl", "VS_GBUFFER", "vs_4_0");

    //Create Pixel Shader
    m_pixelShader = gapi.createPShaderFromFile(L"Resources/gBuffer.hlsl", "PS_GBUFFER", "ps_4_0");
    
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
    m_inputLayout = gapi.createInputLayout(layoutDesc, m_vertexShader);
    
    
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
    m_vertexShaderSSAO = gapi.createVShaderFromFile(L"Resources/SSAO.hlsl", "VS_SSAO", "vs_4_0");

    //Create Pixel Shader
    m_pixelShaderSSAO = gapi.createPShaderFromFile(L"Resources/SSAO.hlsl", "PS_SSAO", "ps_4_0");

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
    m_inputLayoutSSAO = gapi.createInputLayout(layoutDescSSAO, m_vertexShaderSSAO);

    m_SSAOTexture.push_back(gapi.createTex2D(1280,
                                             720, 
                                             1,
                                             GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                                             GI_BIND_FLAG::kBIND_RENDER_TARGET 
                                             | GI_BIND_FLAG::kBIND_SHADER_RESOURCE
                                             | GI_BIND_FLAG::kBIND_UNORDERED_ACCESS));

    SSAOConstantBuffer SSAOcb;
    SSAOcb.Intensity = 2.0f;
    SSAOcb.SampleRadius = 0.800f;
    SSAOcb.Scale = 1.0f;
    SSAOcb.Bias = 0.0800f;
    SSAOcb.TextureSize = Vector2(1280, 720);


    m_cBufferSSAO = gapi.createBuffer(sizeof(SSAOConstantBuffer),
                                      GI_BIND_FLAG::kBIND_CONSTANT_BUFFER,
                                      &SSAOcb);


    /************************************************************************/
    /*                               BLUR                                   */
    /************************************************************************/
    //Create Vertex Shader 
    m_vertexShaderBlur = gapi.createVShaderFromFile(L"Resources/Blur.hlsl", "vs_blur", "vs_4_0");

    //Create Pixel Shader
    m_pixelShaderBlurH = gapi.createPShaderFromFile(L"Resources/Blur.hlsl", "ps_gaussian_blurH", "ps_4_0");

    //Create Pixel Shader
    m_pixelShaderBlurV = gapi.createPShaderFromFile(L"Resources/Blur.hlsl", "ps_gaussian_blurV", "ps_4_0");


    //Create the texture
    m_BlurTexture.push_back(gapi.createTex2D(1280,
                                             720,
                                             1,
                                             GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                                             GI_BIND_FLAG::kBIND_RENDER_TARGET 
                                             | GI_BIND_FLAG::kBIND_SHADER_RESOURCE
                                             | GI_BIND_FLAG::kBIND_UNORDERED_ACCESS));

    //Set the Constant buffer data
    BlurConstantBuffer Blurcb;
    Blurcb.Gamma = 1;
    Blurcb.Viewport.x = 1280;
    Blurcb.Viewport.y = 720;
    Blurcb.TextureSize = Vector2(1280, 720);
    m_cBufferBlur = gapi.createBuffer(sizeof(BlurConstantBuffer),
                                      GI_BIND_FLAG::kBIND_CONSTANT_BUFFER, 
                                      &Blurcb);

    /************************************************************************/
    /*                              SHADOWS                                 */
    /************************************************************************/
    //Create Vertex Shader
    m_vertexShaderShadow = gapi.createVShaderFromFile(L"Resources/Shadow.hlsl", "vs_Shadow", "vs_4_0");
    
    //Create Pixel Shader
    m_pixelShaderShadow = gapi.createPShaderFromFile(L"Resources/Shadow.hlsl", "ps_Shadow", "ps_4_0");

    //Create the texture
    m_ShadowTexture.push_back(gapi.createTex2D(1024, 
                                               1024, 
                                               1, 
                                               GI_FORMAT::kFORMAT_R16_FLOAT, 
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
    m_vertexShaderLight = gapi.createVShaderFromFile(L"Resources/Light.hlsl", "vs_main", "vs_4_0");

    //Create Pixel Shader
    m_pixelShaderLight = gapi.createPShaderFromFile(L"Resources/Light.hlsl", "ps_main", "ps_4_0");

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
    m_inputLayoutLight = gapi.createInputLayout(layoutDescLight, m_vertexShaderLight);

    LightConstantBuffer Lightcb;
    Lightcb.LightIntensity = 2;
    Lightcb.LightPos.x = 360;
    Lightcb.LightPos.y = 280;
    Lightcb.LightPos.z = -200;
    Lightcb.ViewPos = m_mainCamera->m_viewMatrix.m_zColumn;
    Lightcb.InverseView = m_mainCamera->m_viewMatrix.inverse();
    m_cBufferLight = gapi.createBuffer(sizeof(LightConstantBuffer),
                                      GI_BIND_FLAG::kBIND_CONSTANT_BUFFER,
                                      &Lightcb);
    
    
    m_SAQ = make_shared<Model>();

    m_SAQ->loadFromFile("Resources/Models/ScreenAlignedQuad.3ds");


  }

  void
  Renderer::update() {
    
  }
  
  void 
  Renderer::render() {

    auto& gapi = g_graphicsAPI();
    auto& sgraph = SceneGraph::instance();

    /************************************************************************/
    /*                           GBUFFER                                    */
    /************************************************************************/
    Vector<SharedPtr<Buffer>> tmpGbufferConstants;

    tmpGbufferConstants.push_back(m_cBufferCamera);
    tmpGbufferConstants.push_back(m_cBufferChangeEveryFrame);

    renderData(m_renderTargets, 
               gapi.getDefaultDephtStencil(),
               m_inputLayout,
               m_vertexShader,
               m_pixelShader,
               m_sampler,
               tmpGbufferConstants);

    /************************************************************************/
    /*                           SSAO                                       */
    /************************************************************************/
    Vector<SharedPtr<Buffer>> tmpSSAOConstants;
    tmpSSAOConstants.push_back(m_cBufferSSAO);
    Vector<SharedPtr<Texture2D>> tmpSSAOShaderResources;
    tmpSSAOShaderResources.push_back(m_renderTargets[0]);
    tmpSSAOShaderResources.push_back(m_renderTargets[1]);

    renderData(m_SSAOTexture,
               nullptr,
               m_inputLayoutSSAO,
               m_vertexShaderSSAO,
               m_pixelShaderSSAO,
               nullptr,
               tmpSSAOConstants,
               tmpSSAOShaderResources,
               true);

    /************************************************************************/
    /*                           BlurH                                      */
    /************************************************************************/
    Vector<SharedPtr<Buffer>> tmpBlurHConstants;
    tmpBlurHConstants.push_back(m_cBufferBlur);

    renderData(m_BlurTexture,
               nullptr,
               nullptr,
               nullptr,
               m_pixelShaderBlurH,
               nullptr,
               tmpBlurHConstants,
               m_SSAOTexture,
               true);

    /************************************************************************/
    /*                           BlurV                                      */
    /************************************************************************/
    Vector<SharedPtr<Buffer>> tmpBlurVConstants;
    tmpBlurVConstants.push_back(m_cBufferBlur);

    renderData(m_SSAOTexture,
               nullptr,
               nullptr,
               nullptr,
               m_pixelShaderBlurV,
               nullptr,
               tmpBlurVConstants,
               m_BlurTexture,
               true, 
               false);

    /************************************************************************/
    /*                           Shadow                                     */
    /************************************************************************/
    Vector<SharedPtr<Buffer>> tmpShadowConstants;
    tmpShadowConstants.push_back(m_cBufferShadow);

    renderData(m_ShadowTexture,
               nullptr,
               m_inputLayout,
               m_vertexShaderShadow,
               m_pixelShaderShadow,
               nullptr,
               tmpShadowConstants);
    

    /************************************************************************/
    /*                           Light                                      */
    /************************************************************************/
    Vector<SharedPtr<Texture2D>> tmpVector;
    tmpVector.push_back(gapi.getViewportTex());
    Vector<SharedPtr<Buffer>> tmpLightConstants;
    tmpLightConstants.push_back(m_cBufferCamera);
    tmpLightConstants.push_back(m_cBufferShadow);
    tmpLightConstants.push_back(m_cBufferChangeEveryFrame);
    tmpLightConstants.push_back(m_cBufferLight);

    Vector<SharedPtr<Texture2D>> tmpLightShaderResources;
    for(auto RT : m_renderTargets) {
      tmpLightShaderResources.push_back(RT);
    }
    tmpLightShaderResources.push_back(m_SSAOTexture[0]);
    tmpLightShaderResources.push_back(m_ShadowTexture[0]);

    renderData(tmpVector,
               gapi.getDefaultDephtStencil(),
               m_inputLayoutLight,
               m_vertexShaderLight,
               m_pixelShaderLight,
               nullptr,
               tmpLightConstants,
               tmpLightShaderResources,
               true);


    Vector<SharedPtr<Texture2D>> tmpVectorForClear;
    tmpVectorForClear.push_back(gapi.getDefaultRenderTarget());
    //Render in a diferent texture for the viewport in editor.
    gapi.omSetRenderTarget(tmpVectorForClear, gapi.getDefaultDephtStencil());

  }

  void
  Renderer::renderData(Vector<SharedPtr<Texture2D>> inRenderTarget,
                       SharedPtr<Texture2D> inDS, 
                       SharedPtr<InputLayout> inInputLayout,
                       SharedPtr<BaseVertexShader> inVertexShader,
                       SharedPtr<BasePixelShader> inPixelShader,
                       SharedPtr<SamplerState> inSampler, 
                       Vector<SharedPtr<Buffer>> inConstantBuffers,
                       Vector<SharedPtr<Texture2D>> inShaderResources,
                       bool inDrawSAQ, 
                       bool inClear) {

    auto& gapi = g_graphicsAPI();

    auto& sgraph = SceneGraph::instance();

    gapi.omSetRenderTarget(inRenderTarget, inDS);

    if(inClear) {
      for (auto tmpRTV : inRenderTarget) {
        gapi.clearRTV(tmpRTV, ClearColor);
      }
    }

    if(nullptr != inDS && inClear) {
      gapi.clearDSV(inDS);
    }

    if (nullptr != inInputLayout) {
      gapi.aiSetInputLayout(inInputLayout);
    }

    if(nullptr != inVertexShader) {
      gapi.vsSetShader(inVertexShader);
    }

    if(nullptr != inPixelShader) {
      gapi.psSetShader(inPixelShader);
    }

    if(nullptr != inSampler) {
      gapi.psSetSamplerState(0, 1, inSampler);
    }

    for (int i = 0; i < inConstantBuffers.size(); ++i) {
      gapi.vsSetConstantBuffer(i, inConstantBuffers[i]);
      gapi.psSetConstantBuffer(i, inConstantBuffers[i]);
    }

    int j = 0;
    for (; j < inShaderResources.size(); ++j) {
      gapi.psSetShaderResource(j, inShaderResources[j]);
    }

    //Draw
    if(inDrawSAQ) {
      m_SAQ->drawModel();
    } 
    else {
      sgraph.draw();
    }

    if(0 < j) {
      for(int k = 0; k <= j; ++k) {
        gapi.psSetShaderResource(k, nullptr);
      }
    }
    gapi.unbindRenderTarget();
  }

  void 
  Renderer::dispatchData(Vector<SharedPtr<Buffer>> inConstantBuffers,
                         SharedPtr<BaseComputeShader> inCS,
                         Vector<SharedPtr<Texture2D>> inShaderResources,
                         Vector<SharedPtr<Texture2D>> inUAVS,
                         SharedPtr<SamplerState> inSampler,
                         Vector3 inDispatch) {
    //Get the Gapi
    auto& gapi = g_graphicsAPI();
    //Set Compute
    gapi.csSetShader(inCS);
    //Set samplers
    if (nullptr != inSampler) {
      gapi.csSetSampler(0, 1, inSampler);
    }
    //Set Constant Buffers
    for (int32 i = 0; i < inConstantBuffers.size(); ++i) {
      gapi.csSetConstantBuffer(i, inConstantBuffers[i]);
    }
    //Set UAVs
    size_T tmpSize = inUAVS.size();
    int32 j = 0;
    for(; j < tmpSize; ++j) {
      //gapi.setUAV(j, inUAVS[j]);
    }
    //Set Shader Resources
    int32 k = 0;
    for (; k < inShaderResources.size(); ++k) {
      gapi.csSetShaderResource(k, inShaderResources[k]);
    }
    //Dispatch
    gapi.dispatch(inDispatch.x, inDispatch.y, inDispatch.z);
    //Unbind UAVs
    if (0 < j) {
      for(int32 i = 0; i < j; ++i) {
        gapi.setUAV(i, nullptr);
      }
    }
    //Unbind Shader Resources
    if (0 < k) {
      for (int32 l = 0; l < k; ++l) {
        gapi.csSetShaderResource(l, nullptr);
      }
    }
  }
  
  void 
  Renderer::setModels(Vector<SharedPtr<Model>> inModelList) {
    
  }

  void
  Renderer::updateTextureSizes(Vector2i inSize) {
    
  }

  void 
  Renderer::setTransform(Matrix4 inTransformation) {

    g_graphicsAPI().updateSubresource(m_cBufferChangeEveryFrame,
                                      &inTransformation, 
                                      0);
  }

}