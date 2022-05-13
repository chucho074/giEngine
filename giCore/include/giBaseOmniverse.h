/**
 * @file    giBaseOmniverse.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    24/01/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include <giModule.h>


namespace giEngineSDK {
  class Model;
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
    init(String inStage, String inDestination) { 
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
    createEmptyUSD(String inProjectName) { }

    /**
     * @brief    .
     * @return   Returns .
     */
    virtual SharedPtr<Model>
    modelFromUSD() { 
      return nullptr;
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