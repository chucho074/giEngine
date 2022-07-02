/**
 * @file    giBaseOmniverse.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    24/01/2022
 * @brief   A basic implementation for NVIDIA Omniverse conection.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include <giModule.h>
#include <giVector3.h>


namespace giEngineSDK {
  
  class Model;

  namespace GI_OMNI_OP {
    enum E {
      kTRANSLATE,
      kROTATE,
      kSCALE
    };
  }

  namespace GI_OMNI_PRECISION {
    enum E {
      kDOUBLE,
      kFLOAT
    };
  }

  /**
   * @class    BaseOmni.
   * @brief    .
   * @bug      No known Bugs.
   */
  class BaseOmni : public Module<BaseOmni>
  {
   public:
    //Default Constructor.
    BaseOmni() = default;

    //Destructor.
    ~BaseOmni() = default;

    void
    init(StringView inStage, StringView inDestination) { 
      m_existingStage = inStage;
      m_destinationPath = inDestination;
    }

    /**
     * @brief    Function in charge to decide if it needs to create a new USD for the 
     *           actual project or syncronize data from omniverse.
     */
    virtual void
    startConection() { }

    /**
     * @brief    Update the data of the class.
     */
    virtual void
    update() { }

    /**
     * @brief    Destroy the data of the class.
     */
    virtual void
    destroy() { }
    
    /**
     * @brief    Create a USD with the information of the SceneGraph.
     */
    virtual void
    createUSDFromSG() { }


    /**
     * @brief    Create an empty USD in Omniverse Nucleus/Users/giProjects.
     * @param    inProjectName The name of the current project.
     */
    virtual void
    createEmptyUSD(StringView inProjectName) {
      GI_UNREFERENCED_PARAMETER(inProjectName);
    }

    /**
     * @brief    Set the transformation to omni.
     * @param    inData        Vector data to save.
     * @param    inOp          The operation to realize.
     * @param    inPrecision   The precision of the operation.
     * @param    omniPath      The ref path of the model to change.
     */
    virtual void
    setTransformOp(Vector3 inData,
                   GI_OMNI_OP::E inOp,
                   GI_OMNI_PRECISION::E inPrecision,
                   StringView omniPath) {
      GI_UNREFERENCED_PARAMETER(inData);
      GI_UNREFERENCED_PARAMETER(inOp);
      GI_UNREFERENCED_PARAMETER(inPrecision);
      GI_UNREFERENCED_PARAMETER(omniPath);
    }


    bool 
    m_liveEditActivation = true;

    String 
    m_destinationPath;

    String
    m_existingStage;

  };

  GI_CORE_EXPORT BaseOmni& 
  g_omniverse();

  //For load the DLL
  using funCreateOmniverse = BaseOmni * (*)();
  

}