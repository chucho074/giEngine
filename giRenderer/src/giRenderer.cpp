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
#include <giBaseVertexShader.h>
#include <giBasePixelShader.h>

#include "giRenderer.h"

namespace giEngineSDK {

  void 
  Renderer::create() {
    auto& gapi = g_graphicsAPI();
    
    //Create Vertex Shader 
    m_vertexShader = gapi.createVS("Resources/MyShader.fx", "VS", "vs_4_0");
    
    //Create Input Layout
    Vector<InputLayoutDesc> layoutDesc;
    
    //Set the size for the inputLayout
    layoutDesc.resize(3);
    
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
    layoutDesc[2].format = GI_FORMAT::kFORMAT_R32G32_FLOAT;
    layoutDesc[2].inputSlot = 0;
    layoutDesc[2].alignedByteOffset = ALIGN_ELEMENT;
    layoutDesc[2].inputSlotClass = GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
    layoutDesc[2].instanceDataStepRate = 0;
    
    //Create the Input Layout
    m_inputLayout = gapi.createIL(layoutDesc, m_vertexShader);
    
    //Create Pixel Shader
    m_pixelShader = gapi.createPS("Resources/MyShader.fx", "PS", "ps_4_0");
  }
  
  void 
  Renderer::render() {

    auto& gapi = g_graphicsAPI();
    auto& sgraph = SceneGraph::instance();

    //Clear the back buffer
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
    gapi.clearRTV(gapi.getDefaultRenderTarget(),
                     ClearColor);

    //Set Input Layout
    gapi.aiSetInputLayout(m_inputLayout);

    //Clear the depth buffer to 1.0 (max depth)
    gapi.clearDSV(gapi.getDefaultDephtStencil());


    gapi.vsSetShader(m_vertexShader);

    gapi.psSetShader(m_pixelShader);

    sgraph.draw();
  }
  
  void 
  Renderer::setModels(Vector<SharedPtr<Model>> inModelList) {
    
  }



  Renderer& g_Renderer() {
    return Renderer::instance();
  }
}