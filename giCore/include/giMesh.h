/**
 * @file    Mesh.cpp
 * @author  Jes�s Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    28/11/2020
 * @brief   This class have the funtionality for load models.
 * @bug     No known Bugs.
 */

/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giBaseGraphicsAPI.h"

#include "giBuffer.h"

namespace giEngineSDK {

  class Buffer;
  class ObjectLoader;
  struct SimpleVertex;

  

  /**
   * @class    Mesh.
   * @brief    This class have the funtionality for load models.
   * @bug      No known Bugs.
   */
  class GI_CORE_EXPORT Mesh {
   public:
    ///Default constructor
    Mesh() = default;

    ///Destructor
    ~Mesh();

    /**
     * @brief    Load a mesh data.
     * @bug      No known Bugs.
     */
    void 
    loadMesh();

    /**
     * @brief    Draw the mesh data.
     * @bug      No known Bugs.
     */
    void 
    drawMesh();


   protected:

    //The vertex buffer for the mesh
    Buffer* m_vertexBuffer = nullptr;

    //A vertex data Vector
    Vector<SimpleVertex> m_vertexVector;

    //The index buffer for the mesh
    Buffer* m_indexBuffer = nullptr;

    //The list of Faces
    Vector<Vector<unsigned short>> m_facesList;

    //The number of index in the mesh
    int m_indexNum = 0;

   public:
    //The model loader
    friend class ObjectLoader;
  };
}