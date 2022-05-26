/**
* @file    Mesh.cpp
* @author  Jesus Alberto Del Moral Cupil
* @e       idv18c.jmoral@uartesdigitales.edu.mx
* @date    28/11/2020
* @brief   This class have the funtionality for load models.
* @bug     No known Bugs.
**/

#include "giMesh.h"
#include "giBaseGraphicsAPI.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace giEngineSDK {
  Mesh::Mesh(Vector<SimpleVertex> inVertex, 
             Vector<uint32> inIndex, 
             Vector<Texture> inTextures) {
    m_vertexVector = inVertex;
    m_facesList = inIndex;
    m_textures = inTextures;

    loadMesh();
  }
  
  Mesh::~Mesh() {
    
  }

  void 
  Mesh::loadMesh() {

    auto& GAPI = g_graphicsAPI();

    m_vertexBuffer = GAPI.createBuffer(sizeof(SimpleVertex) * 
                                         static_cast<int32>(m_vertexVector.size()),
                                       GI_BIND_FLAG::kBIND_VERTEX_BUFFER,
                                       m_vertexVector.data());

    

    m_indexBuffer = GAPI.createBuffer(sizeof(uint32) * m_facesList.size(),
                                      GI_BIND_FLAG::kBIND_INDEX_BUFFER,
                                      m_facesList.data());


  }

  void
  Mesh::drawMesh() {
    auto& GAPI = g_graphicsAPI();

    for(uint32 i = 0; i < m_textures.size(); i++) {
      GAPI.psSetShaderResource(i, m_textures[i].texture);
      GAPI.psSetSamplerState(i, 1, m_textures[i].samplerState);
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