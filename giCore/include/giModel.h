/**
 * @file    giModel.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/04/2021
 * @brief   For load models.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giResourceManager.h"
#include "giResource.h"
#include "giBaseGraphicsAPI.h"
#include "giMesh.h"
#include <giTransform.h>
#include <giStdHeaders.h>
#include <giVector2.h>
#include <giVector3.h>

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

    ///Destructor
    ~Model();
    
    /**
     * @brief    Unload the model.     
     */
    void
    unload() override;

    /**
     * @brief    Draw the model.
     */
    void 
    drawModel();

    /**
     * @brief    Get the num of textures.
     * @return   Return the num of textures in a int.
     */
    int32
    getNumTextures() { 
      return static_cast<int32>(m_materialsLoaded.size());
    }

    //The references of the Materials.
    Vector<ResourceRef> m_materialsLoaded;

    //Meshes.
    Vector<SharedPtr<Mesh>> m_meshes;

    //The directory of the model.
    Path m_directory;

  };
}