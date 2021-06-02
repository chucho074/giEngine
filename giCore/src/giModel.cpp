/**
 * @file    giModel.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/04/2021
 * @brief   For load models.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giModel.h"

namespace giEngineSDK {

  Model::Model() {
    m_indexNum = 0;
    m_vertexNum = 0;
  }


  Model::~Model() {

  }


  void 
  Model::loadModel(String inFileName) {

    //auto& GAPI = g_GraphicsAPI();

    ObjectLoader tmpObjectLoader;
    tmpObjectLoader.loadObject(inFileName);

    //Texture name
    m_texturesNames = tmpObjectLoader.getTextureName();


    auto numVertex = tmpObjectLoader.getNumVertex();
    auto& faces = tmpObjectLoader.getFaces();
    auto numIndices = faces.size() * 3;


    m_meshes = tmpObjectLoader.getMapMesh();

    //Load every mesh into the map
    for (auto iter : m_meshes) {
      iter.second->loadMesh();
    }


    m_vertexNum = numVertex;
    m_indexNum = static_cast<int32>(numIndices);


  }


  void 
  Model::drawModel() {

    //auto& GAPI = g_GraphicsAPI();

    //Draw every mesh into the map
    for (auto iter : m_meshes) {
      iter.second->drawMesh();
    }
  }
}