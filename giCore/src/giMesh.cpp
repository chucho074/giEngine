/**
* @file    Mesh.cpp
* @author  Jesús Alberto Del Moral Cupil
* @e       idv18c.jmoral@uartesdigitales.edu.mx
* @date    28/11/2020
* @brief   This class have the funtionality for load models.
* @bug     No known Bugs.
**/

#include "giMesh.h"
#include "giBaseGraphicsAPI.h"

namespace giEngineSDK {
  Mesh::Mesh(Vector<SimpleVertex> inVertex, 
             Vector<uint32> inIndex, 
             Vector<Texture> inTextures) {
    this->m_vertexVector = inVertex;
    this->m_facesList = inIndex;
    this->m_textures = inTextures;

    loadMesh();
  }
  
  Mesh::~Mesh() {
    
  }

  void 
  Mesh::loadMesh() {

    auto& GAPI = g_graphicsAPI();

    m_vertexBuffer = GAPI.createBuffer(sizeof(SimpleVertex) * 
                                       static_cast<int32>(m_vertexVector.size()),
                                       0x1L,
                                       0,
                                       m_vertexVector.data());

    

    m_indexBuffer = GAPI.createBuffer(sizeof(uint32) * m_facesList.size(),
                                      0x2L,
                                      0,
                                      m_facesList.data());


  }

  void 
  Mesh::drawMesh() {
    auto& GAPI = g_graphicsAPI();

    for(uint32 i = 0; i < m_textures.size(); i++) {
      GAPI.psSetShaderResource(i, m_textures[i].texture);
      //GAPI.psSetSampler(i, 1, m_textures[i].samplerState);
    }


    uint32 stride = sizeof(SimpleVertex);

    //Set vertex buffer
    GAPI.setVertexBuffer(m_vertexBuffer, stride);

    //Set IB
    GAPI.setIndexBuffer(m_indexBuffer, GI_FORMAT::kFORMAT_R32_UINT);

    //Draw
    GAPI.drawIndexed(m_facesList.size(), 0);
  }
}