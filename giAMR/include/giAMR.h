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

    void
    setRefMesh(Path inData) override;

    void
    run() override;

    void
    reset() override;


   private:
    void
    createJSON();
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