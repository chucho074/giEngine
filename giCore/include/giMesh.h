/**
 * @file    Mesh.cpp
 * @author  Jesús Alberto Del Moral Cupil
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
#include <giVector2.h>
#include <giVector3.h>
#include <giTransform.h>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags


namespace giEngineSDK {

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
   * @brief 
   */
  struct Texture {
    uint32 id;
    String type;
    String path;
    Texture2D * texture;
    Sampler * samplerState;
  };

  /**
   * @class    Mesh.
   * @brief    This class have the funtionality for load models.
   * @bug      No known Bugs.
   */
  class GI_CORE_EXPORT Mesh {
   public:
    Mesh() = default;

    ///Default constructor
    Mesh(Vector<SimpleVertex> inVertex, 
         Vector<uint32> inIndex, 
         Vector<Texture> inTextures);

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
    Buffer * m_vertexBuffer = nullptr;

    //A vertex data Vector
    Vector<SimpleVertex> m_vertexVector;

    //The index buffer for the mesh
    Buffer * m_indexBuffer = nullptr;

    //The list of Faces
    Vector<uint32> m_facesList;

    //The number of index in the mesh
    int32 m_indexNum = 0;

    //Textures in the mesh
    Vector<Texture> m_textures;
  };
}