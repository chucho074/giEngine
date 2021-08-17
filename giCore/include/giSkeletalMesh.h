/**
 * @file    giSkeletalMesh.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    14/08/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giResource.h"
#include "giTexture2D.h"
#include "giSampler.h"
#include <giVector4.h>
#include <giVector3.h>
#include <giVector2.h>
#include <giMatrix4.h>
#include <giTransform.h>

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
   * @brief
   */
  struct Texture {
    uint32 id;
    String type;
    String path;
    Texture2D* texture;
    Sampler* samplerState;
  };

  /**
   * @struct
   * @brief
   */
  struct BoneInfo {
    Matrix4 offset;
    Matrix4 transformation;
  };

  struct SkeletalVertex {
    Vector3 Pos;
    Vector2 Tex;
    Vector3 Nor;
    AnimationBone bones[4];
  };

  class GI_CORE_EXPORT SkeletalMesh final : public Resource
  {
   public:
    //Default Constructor
    SkeletalMesh() = default;

    SkeletalMesh(Vector<SkeletalVertex> inVertex,
                 Vector<uint32> inIndex, 
                 Vector<Texture> inTextures,
                 //const aiScene* inScene,
                 uint32 inNumBones,
                 //Vector<BoneInfo> inBoneInfo,
                 Map<String, uint32> inBoneMapping) {};

    //Destructor
    ~SkeletalMesh() = default;

    bool
    loadFromFile(const String& inPath);

    bool
    loadFromMemory(const char* inData, size_T inSizeOfData);

    void
    unload();

    void
    saveToFile(const String& inFile);

    /**
     * @brief
     * @param    inDeltaTime
     * @param    inTransforms
     */
    void 
    update(float inDeltaTime, Vector<Matrix4>& inTransforms);

    ///**
    // * @brief 
    // * @param node 
    // * @param scene 
    // */
    //void 
    //processNode(aiNode* node, const aiScene* scene);
    //
    ///**
    // * @brief 
    // * @param mesh 
    // * @param scene 
    // * @return 
    // */
    //Mesh 
    //processMesh(aiMesh* mesh, const aiScene* scene);
    
    /**
     * @brief 
     * @param mat 
     * @param type 
     * @param typeName 
     * @return 
     */
    /*Vector<Texture> 
    loadMaterialTextures(Model inModel, aiMaterial* mat, aiTextureType type, String typeName);*/

    Map<String, uint32> m_boneMapping;

    uint32 m_numBones;

    Vector<BoneInfo> m_boneInfo;

    Vector<uint32> m_ids;

    Vector<uint32> m_weights;

    Matrix4 m_globalInverseTransform;

    protected:
    //Mesh antes
    //Vector<BoneInfo> m_boneInfo;
    
    //uint32 m_numBones;

    //Map<String, uint32> m_boneMapping;

    private:
    //Mesh antes
    /*void
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
    findPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);*/

  };
}