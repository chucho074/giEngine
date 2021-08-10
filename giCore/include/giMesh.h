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

  struct AnimationBone {
    uint32 id;
    float weight;
  };


  struct AnimationNode {
    Transform transformation;
    Vector<SharedPtr<AnimationNode>> childBones;
  };


  /**
   * @struct
   * @brief
   */
  struct BoneInfo {
    Matrix4 offset;
    Matrix4 transformation;
  };


  /**
   * @struct    SimpleVertex.
   * @brief     Basic struc for my vertex.
   */
  struct SimpleVertex {
    Vector3 Pos;
    Vector2 Tex;
    Vector3 Nor;
    AnimationBone bones[4];
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
    ///Default constructor
    Mesh(Vector<SimpleVertex> inVertex, 
         Vector<uint32> inIndex, 
         Vector<Texture> inTextures,
         aiScene* inScene,
         uint32 inNumBones,
         Vector<BoneInfo> inBoneInfo,
         Map<String, uint32> inBoneMapping);

    ///Destructor
    ~Mesh();

    /**
     * @brief    Load a mesh data.
     * @bug      No known Bugs.
     */
    void 
    loadMesh();

    /**
     * @brief 
     * @param    inDeltaTime 
     * @param    inTransforms
     */
    void
    update(float inDeltaTime, 
           Vector<Matrix4>& inTransforms, 
           const Matrix4& inGlobalTransform);

    /**
     * @brief    Draw the mesh data.
     * @bug      No known Bugs.
     */
    void 
    drawMesh();

   private:
    void
    readNodeHeirarchy(float inAnimationTime, 
                      const aiNode* inNode, 
                      const Matrix4& inParentTransform,
                      const Matrix4& inGlobalTransform);

    const aiNodeAnim * 
    findNodeAnim(const aiAnimation * inAnim, const String inNodeName);

    void
    calcInterpolatedRotation(aiQuaternion& Out, 
                             float AnimationTime, 
                             const aiNodeAnim* pNodeAnim);

    uint32
    findRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);

    void
    calcInterpolatedScaling(aiVector3D& Out, 
                            float inAnimationTime, 
                            const aiNodeAnim* inNodeAnim);

    uint32
    findScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);

    void
    calcInterpolatedPosition(aiVector3D& Out, 
                             float AnimationTime, 
                             const aiNodeAnim* pNodeAnim);

    uint32
    findPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);


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


    //aiScene* m_scene = nullptr;

    Vector<BoneInfo> m_boneInfo;
    
    uint32 m_numBones;

    Map<String, uint32> m_boneMapping;

    
  };
}