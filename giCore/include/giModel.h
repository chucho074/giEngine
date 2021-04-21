/**
 * @file    giModel.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/04/2021
 * @brief   A basic description of the what do the doc.
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
  class GI_CORE_EXPORT CModel {
   public:

    ///Default constructor
    CModel();

    ///Destructor
    ~CModel();

    /**
    * @brief    Specific constructor.
    * @param    _param1 parameter one.
    * @bug      No known Bugs.
    **/
    void 
    loadModel(String inFileName);

    void 
    drawModel();


    int 
    getNumTextures() { return m_TexturesNames.size(); }

    Vector<String> getTextures() { return m_TexturesNames; }
   private:
    int m_IndexNum;

    CBuffer* m_IndexBuffer;

    int m_VertexNum;

    CBuffer* m_VertexBuffer;

    //Obtener los nombres de las texturas a cargar por el modelo
    Vector<String> m_TexturesNames;

    Map<String, CMesh*> m_Meshes;
  };
}