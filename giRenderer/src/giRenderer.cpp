/**
 * @file    giRenderer.cpp
 * @author  Jesús Alberto Del Moral Cupil
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

#include "giRenderer.h"

namespace giEngineSDK {

  void 
  Renderer::create() {
    auto& gapi = g_graphicsAPI();
    auto& sgraph = SceneGraph::instance();
    
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
                                               GI_BIND_FLAG::kBIND_RENDER_TARGET & GI_BIND_FLAG::kBIND_SHADER_RESOURCE));
    //Normales
    m_renderTargets.push_back(gapi.createTex2D(1280, 
                                               720, 
                                               1,
                                               GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                                               GI_BIND_FLAG::kBIND_RENDER_TARGET & GI_BIND_FLAG::kBIND_SHADER_RESOURCE));
    //Albedo
    m_renderTargets.push_back(gapi.createTex2D(1280, 
                                               720, 
                                               1,
                                               GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                                               GI_BIND_FLAG::kBIND_RENDER_TARGET & GI_BIND_FLAG::kBIND_SHADER_RESOURCE));


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
    layoutDescSSAO[0].format = GI_FORMAT::kFORMAT_R32G32B32A32_FLOAT;
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
                            GI_BIND_FLAG::kBIND_RENDER_TARGET & GI_BIND_FLAG::kBIND_SHADER_RESOURCE));

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
    //Se agarra del SSAO

    //Create Pixel Shader
    m_pixelShaderBlurH = gapi.createPS("Resources/Blur.hlsl", "ps_gaussian_blurH", "ps_4_0");

    //Create Pixel Shader
    m_pixelShaderBlurV = gapi.createPS("Resources/Blur.hlsl", "ps_gaussian_blurV", "ps_4_0");

    //Create Input Layout
    Vector<InputLayoutDesc> layoutDescBlur;

    //Set the size for the inputLayout
    layoutDescBlur.resize(1);

    //Sets the input Layout values

    //Texcoords
    layoutDescBlur[0].semanticName = "TEXCOORD";
    layoutDescBlur[0].semanticIndex = 0;
    layoutDescBlur[0].format = GI_FORMAT::kFORMAT_R32G32_FLOAT;
    layoutDescBlur[0].inputSlot = 0;
    layoutDescBlur[0].alignedByteOffset = ALIGN_ELEMENT;
    layoutDescBlur[0].inputSlotClass = GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
    layoutDescBlur[0].instanceDataStepRate = 0;

    //Create the Input Layout
    m_inputLayoutBlur = gapi.createIL(layoutDescBlur, m_vertexShaderSSAO);

    //Create the texture
    m_BlurTexture.push_back(gapi.createTex2D(1280,
                            720, 
                            1,
                            GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                            GI_BIND_FLAG::kBIND_RENDER_TARGET & GI_BIND_FLAG::kBIND_SHADER_RESOURCE));

    BlurConstantBuffer Blurcb;

    m_cBufferBlur = gapi.createBuffer(sizeof(BlurConstantBuffer),
                                      4, 
                                      0, 
                                      &Blurcb);

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

    //Set Input Layout
    gapi.aiSetInputLayout(m_inputLayout);

    //Set Shaders
    gapi.vsSetShader(m_vertexShader);
    gapi.psSetShader(m_pixelShader);

    //Set Constant Buffers

    
    //Clear the back buffer
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
    gapi.clearRTV(gapi.getDefaultRenderTarget(), 
                     ClearColor);
    
    //Clear the depth buffer to 1.0 (max depth)
    gapi.clearDSV(gapi.getDefaultDephtStencil());

    //Set Render Targets
    gapi.omSetRenderTarget(m_renderTargets,
                           gapi.getDefaultDephtStencil());
    
    

    //Draw models
    sgraph.draw();

    /************************************************************************/
    /*                           SSAO                                       */
    /************************************************************************/
    
    //Set Input Layout
    gapi.aiSetInputLayout(m_inputLayoutSSAO);

    //Set Shaders
    gapi.vsSetShader(m_vertexShaderSSAO);
    gapi.psSetShader(m_pixelShaderSSAO);

    //Set Constant Buffers
    gapi.vsSetConstantBuffer(0, m_cBufferSSAO);
    gapi.psSetConstantBuffer(0, m_cBufferSSAO);

    //Clear the texture to draw
    //gapi.clearRTV(m_SSAOTexture,
    //              ClearColor);

    //Clear the depth buffer to 1.0 (max depth)
    
    //Set Render Targets
    gapi.omSetRenderTarget(m_SSAOTexture,
                           gapi.getDefaultDephtStencil());

    gapi.psSetShaderResource(0, m_renderTargets[0]);
    gapi.psSetShaderResource(1, m_renderTargets[1]);


    m_SAQ->drawModel();

    /************************************************************************/
    /*                           BlurH                                       */
    /************************************************************************/

    //Set Input Layout
    gapi.aiSetInputLayout(m_inputLayoutSSAO);

    //Set Shaders
    gapi.vsSetShader(m_vertexShaderSSAO);
    gapi.psSetShader(m_pixelShaderBlurH);

    //Set Constant Buffers
    gapi.vsSetConstantBuffer(0, m_cBufferBlur);
    gapi.psSetConstantBuffer(0, m_cBufferBlur);

    //Clear the texture to draw
    //gapi.clearRTV(m_SSAOTexture,
    //              ClearColor);

    //Clear the depth buffer to 1.0 (max depth)

    //Set Render Targets
    gapi.omSetRenderTarget(m_BlurTexture,
                           gapi.getDefaultDephtStencil());

    gapi.psSetShaderResource(0, m_SSAOTexture[0]);
    m_SAQ->drawModel();
    /************************************************************************/
    /*                           BlurV                                      */
    /************************************************************************/

    //Set Input Layout
    gapi.aiSetInputLayout(m_inputLayoutSSAO);

    //Set Shaders
    gapi.vsSetShader(m_vertexShaderSSAO);
    gapi.psSetShader(m_pixelShaderBlurV);

    //Set Constant Buffers
    gapi.vsSetConstantBuffer(0, m_cBufferBlur);
    gapi.psSetConstantBuffer(0, m_cBufferBlur);

    //Clear the texture to draw
    //gapi.clearRTV(m_SSAOTexture,
    //              ClearColor);

    //Clear the depth buffer to 1.0 (max depth)

    //Set Render Targets
    gapi.omSetRenderTarget(m_BlurTexture,
                           gapi.getDefaultDephtStencil());

    gapi.psSetShaderResource(0, m_BlurTexture[0]);
    m_SAQ->drawModel();

  }
  
  void 
  Renderer::setModels(Vector<SharedPtr<Model>> inModelList) {
    
  }

}