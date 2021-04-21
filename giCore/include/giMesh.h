/**
* @file		CMesh.cpp
* @author	Jesús Alberto Del Moral Cupil
* @e	    idv18c.jmoral@uartesdigitales.edu.mx
* @date		28/11/2020
* @brief	This class have the funtionality for load models.
* @bug		No known Bugs.
**/

#pragma once
#include "giPrerequisitesCore.h"
#include "giBaseGraphicsAPI.h"
#include "giBuffer.h"

namespace giEngineSDK {

  class CBuffer;
  class CObjectLoader;
  struct SimpleVertex;


/**
* @class    CMesh.
* @brief    This class have the funtionality for load models.
* @bug      No known Bugs.
**/
  class GI_CORE_EXPORT CMesh {
   public:
    ///Default constructor
    CMesh() = default;

    ///Destructor
    ~CMesh();

    /**
    * @brief    Load a mesh data.
    * @bug      No known Bugs.
    **/
    void 
    loadMesh();

    /**
    * @brief    Draw the mesh data.
    * @bug      No known Bugs.
    **/
    void 
    drawMesh();


   protected:

    //The vertex buffer for the mesh
    CBuffer* m_VertexBuffer = nullptr;

    //A vertex data Vector
    Vector<SimpleVertex*> m_VertexVector;

    //The index buffer for the mesh
    CBuffer* m_IndexBuffer = nullptr;

    //The list of Faces
    Vector<Vector<unsigned short>> m_FacesList;

    //The number of index in the mesh
    int m_IndexNum = 0;

   public:
    //The model loader
    friend class CObjectLoader;
  };
}