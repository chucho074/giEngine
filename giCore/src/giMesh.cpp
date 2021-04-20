/**
* @file		CMesh.cpp
* @author	Jesús Alberto Del Moral Cupil
* @e	    idv18c.jmoral@uartesdigitales.edu.mx
* @date		28/11/2020
* @brief	This class have the funtionality for load models.
* @bug		No known Bugs.
**/

#include "giMesh.h"
#include "giObjectLoader.h"
#include "giBaseGraphicsAPI.h"

namespace giEngineSDK {
  CMesh::~CMesh() {

  }

  void CMesh::loadMesh() {

    auto& GAPI = g_GraphicsAPI();

    m_VertexBuffer = GAPI.createBuffer(sizeof(SimpleVertex) * m_VertexVector.size(),
    /*********************************/0x1L,
    /*********************************/0,
    /*********************************/m_VertexVector.data());

    auto numIndices = m_FacesList.size() * 3;
    Vector<unsigned short> tmpIndices;
    tmpIndices.reserve(numIndices);
    int tmpIndexCount = 0;
    for (auto& face : m_FacesList) {
      tmpIndices.push_back(tmpIndexCount * 3 + 0);
      tmpIndices.push_back(tmpIndexCount * 3 + 1);
      tmpIndices.push_back(tmpIndexCount * 3 + 2);
      ++tmpIndexCount;
    }

    m_IndexBuffer = GAPI.createBuffer(sizeof(unsigned short) * tmpIndices.size(),
    /********************************/0x2L,
    /********************************/0,
    /********************************/tmpIndices.data());


    m_IndexNum = numIndices;

  }

  void CMesh::drawMesh() {
    auto& GAPI = g_GraphicsAPI();

    uint32 stride = sizeof(SimpleVertex);

    //Set vertex buffer
    GAPI.setVertexBuffer(m_VertexBuffer, stride);

    //Set IB
    GAPI.setIndexBuffer(m_IndexBuffer, GI_FORMAT::E::kFORMAT_R16_UINT);

    //Draw
    GAPI.draw(m_IndexNum, 0);
  }
}