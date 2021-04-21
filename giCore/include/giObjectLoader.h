/**
 * @file    ObjectLoader.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    11/11/2020
 * @brief   This class read info from a .obj file.
 * @bug     No known Bugs.
 */

/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include <giVector2.h>
#include <giVector3.h>
#include <giStdHeaders.h>
#include "giMesh.h"
#include <fstream>
#include <iostream>
#include <stdio.h>

namespace giEngineSDK {

  class Mesh;
  
  /**
   * @struct    SimpleVertex.
   * @brief     Basic struc for my vertex.
   */
  struct SimpleVertex {
    Vector3 Pos;
    Vector2 Tex;
    Vector3 Nor;
    
  };

  /**
   * @class    ObjectLoader.
   * @brief    This class read info from a .obj file.
   * @bug      No known Bugs.
   */
  class GI_CORE_EXPORT ObjectLoader {
   public:
    //Constructor.
    ObjectLoader();

    //Destructor.
    ~ObjectLoader();

    /**
     * @brief    Load an object from file.
     * @param    inFileName   The name of the file to read.
     * @return   Returns a true if the file can be readed. 
     */
    bool 
    loadObject(String inFileName);

    /**
     * @brief   Getter for the Vertex List.
     * @return  Returns the list of vertex.
     */
    Vector<Vector<float>>& 
    getVertex() { 
      return m_VertexList; 
    }
    
    /**
     * @brief     Getter for the Texture coords.
     * @return    Returns a list with Texture coords.
     */
    Vector<Vector<float>>& 
    getTextureCoords() { 
      return m_TextureCoordsList; 
    }
    
    /**
     * @brief    Getter for the Normal Vertexes.
     * @return   Returns a list with Normal Vertex.
     */
    Vector<Vector<float>>& 
    getVertexNormal() { 
      return m_VertexNormalList; 
    }
    
    /**
     * @brief     Getter for the faces list.
     * @return    Returns the faces list.
     */
    Vector<Vector<unsigned short>>& 
    getFaces() { 
      return m_facesList; 
    }

    /**
     * @brief     Getter for the num of vertex.
     * @return    Return the name of vertex in the object loaded.
     */
    int 
    getNumVertex() { 
      return static_cast<int32>(m_VertexList.size()); 
    }
    
    /**
     * @brief     Gettter for the num of the UVs.
     * @return    Returns the num of UVs in the object loaded.
     */
    int 
    getNumUV() { 
      return static_cast<int32>(m_TextureCoordsList.size());
    }
    
    /**
     * @brief     Getter for the num of normals.
     * @return    Returns the num of Vertex normal.
     */
    int 
    getNumNormals() { 
      return static_cast<int32>(m_VertexNormalList.size());
    }
    
    /**
     * @brief     Getter for the num of faces.
     * @return    Returns the num of faces in list.
     */
    int 
    getNumFaces() { 
      return static_cast<int32>(m_facesList.size());
    }

    /**
     * @brief     Getter for the list of texture names.
     * @return    Returns a list whit names.
     */
    Vector<String>& 
    getTextureName() { 
      return m_TextureFiles;
    }

    /**
     * @brief      Getter for the Vertex buffer.
     * @return     Returns a list with SimpleVertex.
     */
    Vector<SimpleVertex> 
    getVertBuffer() { 
      return m_vertexBuffer; 
    }

    /**
     * @brief    Getter for the map of meshes.
     * @return   Returns the map of meshes.
     */
    Map<String, Mesh*> 
    getMapMesh() { 
      return m_meshes; 
    }

   private:

    /**
     * @brief    Read lines in obj files.
     * @param    inLine   The line to read.
     * @return   Returns a true if can be parsed.
     */
    bool 
    readLineObj(String inLine);

    /**
     * @brief     Read lines in a MTL files.
     * @param     inLine  The line to read.
     * @return    Returns a true if can be parsed.
     */
    bool 
    readLineMtl(String inLine);

    Vector<String> m_TextureFiles;
    String m_MTLFile = " ";

    Vector<Vector<float>> m_VertexList;
    Vector<Vector<float>> m_TextureCoordsList;
    Vector<Vector<float>> m_VertexNormalList;
    Vector<Vector<unsigned short>> m_facesList;
    Vector<SimpleVertex> m_vertexBuffer;

    Map<String, Mesh*> m_meshes;

    String m_ActualName;

    //friend class Mesh;
  };
}