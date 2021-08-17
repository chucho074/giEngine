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
  class GI_CORE_EXPORT Model final : public Resource
  {
   public:

    ///Default constructor
    Model() = default;

    ///Destructor
    ~Model();

    /**
     * @brief    Load a model from file.
     * @param    inFileName   File to read a model.
     * @bug      No known Bugs.
     */
    bool 
    loadFromFile(const String& inFileName) override;

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
    Vector<Texture> 
    loadMaterialTextures(Model inModel, 
                         aiMaterial* mat, 
                         aiTextureType type, 
                         String typeName);

    //Get the name of the textures linked to the model
    Vector<String> m_texturesNames;

    //Meshes
    Vector<Mesh> m_meshes;

    String m_directory;

    Vector<Texture> m_texturesLoaded;

    Transform m_transform;

  };
}