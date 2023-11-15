/**
 * @file    Mesh.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    28/11/2020
 * @brief   This class have the funtionality for load models.
 */

/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giBaseGraphicsAPI.h"
#include "giBuffer.h"
#include "giMaterial.h"
#include <giVector2.h>
#include <giVector3.h>
#include <giTransform.h>

namespace giEngineSDK {

  /**
   * @struct    SimpleVertex.
   * @brief     Basic struc for my vertex.
   */
  struct SimpleVertex {
    Vector3 Pos = Vector3::ZERO;
    Vector2 Tex = Vector2::ZERO;  //UV
    Vector3 Nor = Vector3::ZERO;
    Vector3 Tang = Vector3::ZERO;
    Vector3 BiNor = Vector3::ZERO;
  };

  /**
   * @class    Mesh.
   * @brief    This class have the funtionality for load models.
   */
  class GI_CORE_EXPORT Mesh {
   public:
    //Mesh() = default;

    /**
     * @brief    .
     * @param    inVertex      .
     * @param    inIndex       .
     * @param    inTextures    .
     */
    Mesh(Vector<SimpleVertex> inVertex, 
         Vector<uint32> inIndex, 
         Vector<ResourceRef> inTextures);

    ///Destructor
    ~Mesh();

    /**
     * @brief 
     */
    void
    destroy();

    /**
     * @brief    Load a mesh data.
     */
    void 
    loadMesh();
           
    /**
     * @brief    Draw the mesh data.
     */
    void 
    drawMesh();


    //The vertex buffer for the mesh
    SharedPtr<Buffer> m_vertexBuffer = nullptr;

    //A vertex data Vector
    Vector<SimpleVertex> m_vertexVector;

    //The index buffer for the mesh
    SharedPtr<Buffer> m_indexBuffer = nullptr;

    //The list of Faces / Index data
    Vector<uint32> m_facesList;

    //The number of index in the mesh
    //int32 m_indexNum = 0;

    //Textures in the mesh
    Vector<ResourceRef> m_textures;

    String m_name;

    //The reference for the path in Omniverse.
    String m_omniRefPath = "";
  };
}