/**
* @file    Mesh.cpp
* @author  Jesús Alberto Del Moral Cupil
* @e       idv18c.jmoral@uartesdigitales.edu.mx
* @date    28/11/2020
* @brief   This class have the funtionality for load models.
* @bug     No known Bugs.
**/

#include "giMesh.h"
#include "giObjectLoader.h"
#include "giBaseGraphicsAPI.h"

namespace giEngineSDK {
  Mesh::~Mesh() {

  }

  void 
  Mesh::loadMesh() {

    auto& GAPI = g_GraphicsAPI();

    m_vertexBuffer = GAPI.createBuffer(sizeof(SimpleVertex) * 
    /**********************************/static_cast<int32>(m_vertexVector.size()),
    /*********************************/0x1L,
    /*********************************/0,
    /*********************************/m_vertexVector.data());

    auto numIndices = m_facesList.size() * 3;
    Vector<unsigned short> tmpIndices;
    tmpIndices.reserve(numIndices);
    int tmpIndexCount = 0;
    for (int i = 0; m_facesList.size() >= i; i++) {
      tmpIndices.push_back(tmpIndexCount * 3 + 0);
      tmpIndices.push_back(tmpIndexCount * 3 + 1);
      tmpIndices.push_back(tmpIndexCount * 3 + 2);
      ++tmpIndexCount;
    }

    m_indexBuffer = GAPI.createBuffer(sizeof(unsigned short) * 
    /*********************************/static_cast<int32>(tmpIndices.size()),
    /********************************/0x2L,
    /********************************/0,
    /********************************/tmpIndices.data());


    m_indexNum = static_cast<int32>(numIndices);

  }

  void 
  Mesh::drawMesh() {
    auto& GAPI = g_GraphicsAPI();

    uint32 stride = sizeof(SimpleVertex);

    //Set vertex buffer
    GAPI.setVertexBuffer(m_vertexBuffer, stride);

    //Set IB
    GAPI.setIndexBuffer(m_indexBuffer, GI_FORMAT::E::kFORMAT_R16_UINT);

    //Draw
    GAPI.drawIndexed(m_indexNum, 0);
  }
}