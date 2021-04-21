/**
* @file    ObjectLoader.cpp
* @author  Jesús Alberto Del Moral Cupil
* @e      idv18c.jmoral@uartesdigitales.edu.mx
* @date    11/11/2020
* @brief  This class read info from a .obj file.
* @bug    No known Bugs.
**/
#include "giObjectLoader.h"
#include <sstream>

namespace giEngineSDK {

  ObjectLoader::ObjectLoader() {

  }

  ObjectLoader::~ObjectLoader() {

  }

  bool 
  ObjectLoader::loadObject(String inFileName) {
    bool tmpIsReaded = true;
    int tmpLineIter = 0;
    std::ifstream FS;
    String tmpLine;
    FS.open(inFileName, std::ios::in);

    while (!FS.eof()) {
      std::getline(FS, tmpLine);
      tmpLineIter++;

      if (!readLineObj(tmpLine)) {
        tmpIsReaded = false;
        break;
      }

    }

    FS.close();

    if (" " != m_MTLFile) {
      FS.open(m_MTLFile, std::ios::in);
      while (!FS.eof()) {
        std::getline(FS, tmpLine);
        tmpLineIter++;

        if (!readLineMtl(tmpLine)) {
          tmpIsReaded = false;
          break;
        }

      }

      FS.close();
    }


    return tmpIsReaded;
  }

  bool 
  ObjectLoader::readLineObj(String inLine) {

    //Comentary & spaces
    if ("#" == inLine.substr(0, 1)
      || "o " == inLine.substr(0, 2)
      || "g " == inLine.substr(0, 2)
      || "s " == inLine.substr(0, 2)
      || "" == inLine.substr(0, 1)) {

      return true;
    }

    //Material File
    if ("mtllib " == inLine.substr(0, 7)) {
      std::stringstream tmpBuffer(inLine.substr(7));
      m_MTLFile = tmpBuffer.str();
      return true;
    }
    if ("usemtl " == inLine.substr(0, 7)) {

      //Save the actual mesh name
      m_ActualName = inLine.substr(7);

      //Verify if that mesh exist in map
      auto comp_func = m_meshes.key_comp();
      for (auto iter : m_meshes) {
        if (comp_func(m_ActualName, iter.first)
          && comp_func(iter.first, m_ActualName)) {

        }
      }

      //Add a new Mesh to the map
      auto tmpMesh = new Mesh();
      m_meshes.insert({ inLine.substr(7), tmpMesh });
      return true;
    }

    //Vertex
    if ("v " == inLine.substr(0, 2)) {
      Vector<float> tmpArrayData;
      float tmpData = 0;
      std::stringstream tmpBuffer(inLine.substr(2));

      unsigned short tmpIter = 0;
      while (tmpBuffer >> tmpData) {
        tmpArrayData.push_back(tmpData);
        if (2 == tmpIter) {
          m_VertexList.push_back(tmpArrayData);
          tmpIter = 0;
        }
        ++tmpIter;
      }
      return true;
    }

    //Texture coords
    if ("vt " == inLine.substr(0, 3)) {
      Vector<float> tmpArrayData;
      float tmpData;
      std::stringstream tmpBuffer(inLine.substr(3));

      unsigned short tmpIter = 0;
      while (tmpBuffer >> tmpData) {
        tmpArrayData.push_back(tmpData);
        if (1 == tmpIter) {
          m_TextureCoordsList.push_back(tmpArrayData);
          tmpIter = 0;
        }
        ++tmpIter;
      }
      return true;
    }

    //Vertex Normals
    if ("vn " == inLine.substr(0, 3)) {
      Vector<float> tmpArrayData;
      float tmpData;
      std::stringstream tmpBuffer(inLine.substr(3));

      unsigned short tmpIter = 0;
      while (tmpBuffer >> tmpData) {
        tmpArrayData.push_back(tmpData);
        if (2 == tmpIter) {
          m_VertexNormalList.push_back(tmpArrayData);
          tmpIter = 0;
        }
        ++tmpIter;
      }
      return true;
    }

    //Faces

    Vector<Vector<float>> tmpTexCordsList = m_TextureCoordsList;
    if ("f " == inLine.substr(0, 2)) {
      Vector<unsigned short> tmpArrayData;
      //int tmpData;

      int a, b, c;
      int A1, B1, C1;
      int A2, B2, C2;
      const char* chh = inLine.c_str();
      sscanf_s(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i",
        &a, &A1, &A2, &b, &B1, &B2, &c, &C1, &C2);
      if (0 > C2) {
        sscanf_s(chh, "f %i/%i %i/%i %i/%i",
          &a, &A1, &b, &B1, &c, &C1);

        tmpArrayData.push_back(a - 1);
        tmpArrayData.push_back(A1 - 1);
        tmpArrayData.push_back(b - 1);
        tmpArrayData.push_back(B1 - 1);
        tmpArrayData.push_back(c - 1);
        tmpArrayData.push_back(C1 - 1);
      }
      else {

        tmpArrayData.push_back(a - 1);
        tmpArrayData.push_back(A1 - 1);
        tmpArrayData.push_back(A2 - 1);
        tmpArrayData.push_back(b - 1);
        tmpArrayData.push_back(B1 - 1);
        tmpArrayData.push_back(B2 - 1);
        tmpArrayData.push_back(c - 1);
        tmpArrayData.push_back(C1 - 1);
        tmpArrayData.push_back(C2 - 1);
      }
      m_facesList.push_back(tmpArrayData);

      SimpleVertex tmpVertex;

      auto tmpActualMesh = (m_meshes.find(m_ActualName));

      tmpVertex.Pos = Vector3(m_VertexList[a - 1][0], m_VertexList[a - 1][1], m_VertexList[a - 1][2]);
      tmpVertex.Tex = Vector2(m_TextureCoordsList[A1 - 1][0], m_TextureCoordsList[A1 - 1][1]);
      tmpActualMesh->second->m_vertexVector.push_back(tmpVertex);
      //m_vertexBuffer.push_back(tmpVertex);

      tmpVertex.Pos = Vector3(m_VertexList[b - 1][0], m_VertexList[b - 1][1], m_VertexList[b - 1][2]);
      tmpVertex.Tex = Vector2(m_TextureCoordsList[B1 - 1][0], m_TextureCoordsList[B1 - 1][1]);
      tmpActualMesh->second->m_vertexVector.push_back(tmpVertex);
      //m_vertexBuffer.push_back(tmpVertex);

      tmpVertex.Pos = Vector3(m_VertexList[c - 1][0], m_VertexList[c - 1][1], m_VertexList[c - 1][2]);
      tmpVertex.Tex = Vector2(m_TextureCoordsList[C1 - 1][0], m_TextureCoordsList[C1 - 1][1]);
      tmpActualMesh->second->m_vertexVector.push_back(tmpVertex);
      //m_vertexBuffer.push_back(tmpVertex);

      //se le daria valor a Actual mesh cuando se encuentre el usemtl
      //Por cada usemtl mandar buffer al mesh que corresponda con el nombre
      //Mandar al actualMesh el buffer
      tmpActualMesh->second->m_facesList.push_back(tmpArrayData);
      return true;
    }



    return false;
  }

  bool 
  ObjectLoader::readLineMtl(String inLine) {
    //map_Kd
    if ("\t" == inLine.substr(0, 1)) {
      inLine.erase(inLine.begin());
    }

    if ("Ns " == inLine.substr(0, 3)
      || "d " == inLine.substr(0, 2)
      || "illum " == inLine.substr(0, 6)
      || "newmtl " == inLine.substr(0, 7)
      || "Kd " == inLine.substr(0, 3)
      || "Ks " == inLine.substr(0, 3)
      || "Ni " == inLine.substr(0, 3)
      || "Ka " == inLine.substr(0, 3)
      || "#" == inLine.substr(0, 1)
      || "" == inLine.substr(0, 1)) {

      return true;
    }
    else if ("map_Kd " == inLine.substr(0, 7)) {
      std::string tmpString;
      std::stringstream tmpBuffer(inLine.substr(7));
      tmpString = tmpBuffer.str();
      //Check if the name exist
      int tmpSize = static_cast<int32>(m_TextureFiles.size());
      if (0 != tmpSize) {
        for (int i = 0; i < tmpSize; i++) {
          if (tmpString == m_TextureFiles[i]) {
            return true;
          }
          if (i == (tmpSize - 1)) {
            m_TextureFiles.push_back(tmpString);
          }
        }
      }
      else if (0 == tmpSize) {
        m_TextureFiles.push_back(tmpString);
      }
      return true;
    }
    return false;
  }
}