/**
 * @file    giModel.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/04/2021
 * @brief   For load models.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giBaseGraphicsAPI.h"
#include "giMesh.h"
#include "giResource.h"
#include <giTransform.h>
#include <giStdHeaders.h>
#include <giVector2.h>
#include <giVector3.h>

namespace giEngineSDK {

  /**
   * @class   Model. 
   * @brief   Basics models.
   */
  class GI_CORE_EXPORT Model final : public Resource {
   public:

    ///Default constructor
    Model() = default;

    Model(String inFileName);

    ///Destructor
    ~Model();

    /**
     * @brief    Draw the model.
     */
    void 
    drawModel();

    /**
     * @brief     Get the num of textures.
     * @return    Return the num of textures in a int.
     */
    int 
    getNumTextures() { 
      return static_cast<int32>(m_texturesNames.size());
    }

    /**
     * @brief     Get the list of textures.
     * @return    Return the list of the textures.
     */
    Vector<String> getTextures() { 
      return m_texturesNames; 
    }

    /**
     * @brief    Load a model from file.
     * @param    inFileName   File to read a model.
     * @bug      No known Bugs.
     */
    bool 
    loadFromFile(const String& inFileName) override;

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
    //
    ///**
    // * @brief 
    // * @param mat 
    // * @param type 
    // * @param typeName 
    // * @return 
    // */
    //Vector<Texture> 
    //loadMaterialTextures(aiMaterial* mat, aiTextureType type, String typeName);


    //Obtener los nombres de las texturas a cargar por el modelo
    Vector<String> m_texturesNames;

    //Meshes
    Vector<Mesh> m_meshes;

    String m_directory;

    Vector<Texture> m_texturesLoaded;

    //aiScene* m_scene = nullptr;

    Transform m_transform;

    //For bones

    Map<String, uint32> m_boneMapping;

    uint32 m_numBones;

    Vector<BoneInfo> m_boneInfo;

    Vector<uint32> m_ids;

    Vector<uint32> m_weights;

    Matrix4 m_globalInverseTransform;
  };
}