/**
 * @file    giAMR.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    08/02/2023
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesAMR.h"
#include "giVector2i.h"
#include "giBaseAMR.h"
#include "giBaseConfig.h"

namespace giEngineSDK {
  /**
   * @class      AMR.
   * @brief      This class is for the utilities to use Appearance-Driven 
                  Automatic 3D Model Simplification, develop by NVIDIA, this is for
                  create an LOD (Level Of Detail) for the projects in giEngine.
   */
  class AMR : public BaseAMR 
  {
   public:
  	AMR() = default;
  	
    ~AMR() = default;

    /**
     * @brief    Assings the path for a mesh to take as a reference.
     * @param    inData        The path for the mesh.
     */
    void
    setRefMesh(Path inData) override;

    /**
     * @brief    Runs the process for the tool.
     */
    void
    run() override;

    /**
     * @brief    Reset the values for the tool.
     */
    void
    reset() override;


   private:
    /**
     * @brief    Creates the information needed for the usage of the tool.
     */
    void
    createJSON();

    /**
     * @brief    .
     */
    void
    createBatFiles();
  };

  /**
  * @brief      Create the giAMR tool with a dll.
  */
  extern "C" GI_PLUGIN_EXPORT AMR *
    createAMR() {
    auto amr = new AMR();
    return amr;
  }
};