/**
 * @file    giModel.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giModel.h"

namespace giEngineSDK {

  CModel::CModel()
  {
  }


  CModel::~CModel()
  {
  }


  void 
  CModel::loadModel(String inFileName) {

    auto& GAPI = g_GraphicsAPI();

    CObjectLoader tmpObjectLoader;
    tmpObjectLoader.loadObject(inFileName);

    //Texture name
    m_TexturesNames = tmpObjectLoader.getTextureName();


    auto numVertex = tmpObjectLoader.getNumVertex();
    auto& faces = tmpObjectLoader.getFaces();
    auto numIndices = faces.size() * 3;


    m_Meshes = tmpObjectLoader.getMapMesh();

    //Load every mesh into the map
    for (auto iter : m_Meshes) {
      iter.second->loadMesh();
    }


    m_VertexNum = numVertex;
    m_IndexNum = numIndices;


  }


  void 
  CModel::drawModel() {

    auto& GAPI = g_GraphicsAPI();

    //Draw every mesh into the map
    for (auto iter : m_Meshes) {
      iter.second->drawMesh();
    }
  }
}