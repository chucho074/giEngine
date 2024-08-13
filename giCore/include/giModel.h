/**
 * @file    giModel.h
 * @author  Jesus Alberto Del Moral Cupil
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
#include "giMesh.h"
#include "giResource.h"
#include <giTransform.h>

namespace giEngineSDK {

  struct ModelInfo {
    uint32 totalTriangles = 0;
    uint32 totalVertices = 0;
    uint32 totalMeshes = 0;
    uint32 totalMaterials = 0;
    uint32 totalAnimations = 0;
    uint32 totalFaces = 0;
    uint32 totalIndex = 0;
  };

  /**
   * @class   Model. 
   * @brief   Basics models.
   */
  class GI_CORE_EXPORT Model final : public Resource
  {
   public:

    ///Default constructor
    Model() = default;

    Model(Vector<SharedPtr<Mesh>> inMeshes, Vector<SharedPtr<Texture>> inMaterials);

    ///Destructor
    ~Model();

    /**
     * @brief    Load a model from file.
     * @param    inFileName    File to read a model.
     * @bug      No known Bugs.
     */
    bool 
    loadFromFile(const Path& inFile) override;

    /**
     * @brief    Load a model from memory.
     * @param    inData        The data of the model.
     * @param    inSizeOfData  The size of the data.
     * @bug      No known Bugs.
     */
    bool
    loadFromMemory(const char* inData, size_T inSizeOfData) override;

    /**
    * @brief    Unload the model.
    * @bug      No known Bugs.
    */
    void
    unload();

    /**
    * @brief    Save the model to a file.
    * @bug      No known Bugs.
    */
    void 
    saveToFile(const String& inFile);

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
     * @brief 
     * @param mat 
     * @param type 
     * @param typeName 
     * @return 
     */
    /*Vector<Texture> 
    loadMaterialTextures(Model inModel, 
                         aiMaterial* mat, 
                         aiTextureType type, 
                         String typeName);*/




    static SharedPtr<Model>    
    createSphere(int32 inNumTriangles);


    static void
    createQuadSphere(int32 inNumSubdivisions);

    //Get the name of the textures linked to the model
    Vector<String> m_texturesNames;

    //Meshes
    Vector<SharedPtr<Mesh>> m_meshes;

    String m_directory;

    Vector<SharedPtr<Texture>> m_texturesLoaded;

    //Transform m_transform;

  };
}