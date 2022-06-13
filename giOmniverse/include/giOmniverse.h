/**
 * @file    giOmniverse.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/01/2022
 * @brief   A basic conection to NVIDIA Omniverse Service.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include <giBaseOmniverse.h>
#include <giSceneGraph.h>
#include "giPrerequisitesOmniverse.h"`

namespace giEngineSDK {

  class Model;

  /**
   * @class    Omni.
   * @brief    A conection to Nvidia Omniverse.
   * @bug      No known Bugs.
   */
  class Omni : public BaseOmni
  {
   public:
    //Default Constructor.
    Omni() = default;

    //Destructor.
    ~Omni() = default;

    /**
     * @brief    Function in charge to decide if it needs to create a new USD for the
     *           actual project or syncronize data from omniverse.
     */
    void 
    startConection();

    /**
     * @brief    Update the data.
     */
    void
    update() override;

    /**
     * @brief    Delete/destroy the information.
     */
    void 
    destroy() override;

    /**
     * @brief    Creates the USD file from the Scene Graph.
     */
    void
    createUSDFromSG() override;

    /**
     * @brief    Create an empty USD in Omniverse Nucleus/Users/giProjects.
     * @param    inProjectName The name of the current project.
     */
    void
    createEmptyUSD(String inProjectName) override;

    /**
     * @brief    Creates / Sets data in the Scene Graph from an existent 
     *           USD file.
     * @param    inMesh        USD data obtained.
     */
    void
    createSGFromUSD();

    void
    setTransformOp(Vector3 inData,
                   GI_OMNI_OP::E inOp,
                   GI_OMNI_PRECISION::E inPrecision,
                   String omniPath) override;

   private:
    
    /**
     * @brief    Make a syncronization between the engine and NVIDIA Omniverse tool.
     * @param    inMesh        The mesh to syncronize.
     */
    void 
    liveEdit(Vector<UsdPrim>);

    UsdGeomMesh tmpMesh;

  };

  /**
   * @brief      Create the omniverse with a dll.
   */
  extern "C" GI_PLUGIN_EXPORT Omni *
    createOmniverse() {
    auto ov = new Omni();
    return ov;
  }
  

  // A utility class to set the position, rotation, or scale values
  class SetOp
  {
   public:
    /**
     * @brief    Constructor with parameters.
     * @param    xForm         .
     * @param    op            .
     * @param    opType        .
     * @param    value         .
     * @param    precision     .
    */
    SetOp(UsdGeomXformable& xForm, 
          UsdGeomXformOp& op, 
          UsdGeomXformOp::Type opType, 
          const GfVec3d& value, 
          const UsdGeomXformOp::Precision precision) {
      if (!op) {
        op = xForm.AddXformOp(opType, precision);
      }

      if (op.GetPrecision() == UsdGeomXformOp::Precision::PrecisionFloat) {
        op.Set(GfVec3f(value));
      }
      else { 
        op.Set(value);
      }
    }
  };

}