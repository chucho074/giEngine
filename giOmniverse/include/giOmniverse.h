/**
 * @file    giOmniverse.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/01/2022
 * @brief   A basic conection to NVIDIA Omniverse Service.
 */
 
/**
 * @include
 */
#pragma once
#include <giBaseOmniverse.h>
#include "giPrerequisitesOmniverse.h"
#include "giMesh.h"
namespace giEngineSDK {

  class Model;

  /**
   * @class    Omni.
   * @brief    A conection to Nvidia Omniverse.   
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
    createEmptyUSD(StringView inProjectName) override;

    /**
     * @brief    Creates / Sets data in the Scene Graph from an existent 
     *           USD file.
     * @param    inMesh        USD data obtained.
     */
    void
    createSGFromUSD();

    /**
     * @brief    Creates a mesh with the information of a GeoMesh.
     * @param    inMesh        USD data obtained.
     * @param    inPath        The reference path for the mesh.
     */
    SharedPtr<Mesh>
    createMeshFromGeoMesh(UsdGeomMesh inMesh, StringView inPath);

    /**
     * @brief    Function to send the information to Omni.
     * @param    inData        The data to set to model/mesh in omni.
     * @param    inOp          The operation to set.
     * @param    inPrecision   The precision of the operation.
     * @param    omniPath      The reference path to the model/mesh of Omni.
     */
    void
    setTransformOp(Vector3 inData,
                   GI_OMNI_OP::E inOp,
                   GI_OMNI_PRECISION::E inPrecision,
                   StringView omniPath) override;

    /**
     * @brief    Get the information from the SG.
     */
    void
    getFromSG();

   private:
    
    /**
     * @brief    Make a syncronization between the engine and NVIDIA Omniverse tool.
     * @param    inMesh        The mesh to syncronize.
     */
    void 
    liveEdit(Vector<UsdPrim>);


    UsdGeomMesh tmpMesh;


    Vector<UsdGeomXformOp> m_transformXForm;
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