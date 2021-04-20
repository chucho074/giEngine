/**
* @file		CObjectLoader.h
* @author	Jesús Alberto Del Moral Cupil
* @e	    idv18c.jmoral@uartesdigitales.edu.mx
* @date		11/11/2020
* @brief	This class read info from a .obj file.
* @bug		No known Bugs.
**/
#pragma once
#include "giPrerequisitesCore.h"
#include <giVector2.h>
#include <giVector3.h>
#include <giStdHeaders.h>
#include "giMesh.h"
#include <fstream>

namespace giEngineSDK {
  
  struct SimpleVertex {
    Vector3 Pos;
    Vector2 Tex;
    Vector3 Nor;
  };

  /**
  * @class    CObjectLoader.
  * @brief    This class read info from a .obj file.
  * @bug      No known Bugs.
  **/
  class CObjectLoader {
   public:
    CObjectLoader();
    ~CObjectLoader();

    bool loadObject(String inFileName);

    Vector<Vector<float>>& getVertex() { return m_VertexList; }
    Vector<Vector<float>>& getTextureCoords() { return m_TextureCoordsList; }
    Vector<Vector<float>>& getVertexNormal() { return m_VertexNormalList; }
    Vector<Vector<unsigned short>>& getFaces() { return m_FacesList; }

    int getNumVertex() { return m_VertexList.size(); }
    int getNumUV() { return m_TextureCoordsList.size(); }
    int getNumNormals() { return m_VertexNormalList.size(); }
    int getNumFaces() { return m_FacesList.size(); }

    Vector<String>& getTextureName() { return m_TextureFiles; }

    Vector<SimpleVertex> getVertBuffer() { return m_VertexBuffer; }

    Map<String, CMesh*> getMapMesh() { return m_Meshes; }
   private:
    bool readLineObj(String inLine);
    bool readLineMtl(String inLine);

    Vector<String> m_TextureFiles;
    String m_MTLFile = " ";

    Vector<Vector<float>> m_VertexList;
    Vector<Vector<float>> m_TextureCoordsList;
    Vector<Vector<float>> m_VertexNormalList;
    Vector<Vector<unsigned short>> m_FacesList;
    Vector<SimpleVertex> m_VertexBuffer;

    Map<String, CMesh*> m_Meshes;

    String m_ActualName;

    //friend class CMesh;
  };
}