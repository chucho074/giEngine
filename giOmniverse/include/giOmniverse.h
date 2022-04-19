/**
 * @file    giOmniverse.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/01/2022
 * @brief   A basic conection to Nvidia Omniverse Service.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include <giBaseOmniverse.h>
#include <giSceneGraph.h>
#include "giPrerequisitesOmniverse.h"
#include <iostream>

using std::cout;
using std::endl;

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
     * @brief    Creates the USD file.
     */
    void
    createUSD() override;

    /**
     * @brief    Get the data from the Scene Graph.
     */
    UsdGeomMesh
    getData();
   
    /**
     * @brief    .
     */
    SharedPtr<Model>
    modelFromUSD() override;

  };

  /**
   * @brief   Create the omniverse with a dll.
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
        std::unique_lock<std::mutex> lk(gLogMutex);
        cout << " Adding " << UsdGeomXformOp::GetOpTypeToken(opType) << endl;
      }

      if (op.GetPrecision() == UsdGeomXformOp::Precision::PrecisionFloat) {
        op.Set(GfVec3f(value));
      }
      else { 
        op.Set(value);
      }
      std::unique_lock<std::mutex> lk(gLogMutex);
      cout << " Setting " << UsdGeomXformOp::GetOpTypeToken(opType) << endl;
    }
  };

}