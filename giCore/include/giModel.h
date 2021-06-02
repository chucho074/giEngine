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
#include <giStdHeaders.h>
#include "giMesh.h"
#include "giObjectLoader.h"
#include "giBaseGraphicsAPI.h"

namespace giEngineSDK {
  /**
   * @class   Model. 
   * @brief   Basics models.
   */
  class GI_CORE_EXPORT Model {
   public:

    ///Default constructor
    Model();

    ///Destructor
    ~Model();

    /**
     * @brief    Load a model from file.
     * @param    inFileName   File to read a model.
     * @bug      No known Bugs.
     */
    void 
    loadModel(String inFileName);

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

   private:
    int32 m_indexNum;

    int32 m_vertexNum;

    //Obtener los nombres de las texturas a cargar por el modelo
    Vector<String> m_texturesNames;

    Map<String, Mesh*> m_meshes;
  };
}