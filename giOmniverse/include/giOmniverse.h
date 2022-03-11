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
  
}