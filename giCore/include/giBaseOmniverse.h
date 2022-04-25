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

    /**
     * @brief    Function in charge to decide if it needs to create a new USD for the 
     *           actual project or syncronize data from omniverse.
     */
    virtual void
    startConection() { }

    /**
     * @brief 
     */
    virtual void
    update() { }

    virtual void
    destroy() { }
    
    /**
     * @brief    .
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
     * @brief 
     * @return 
     */
    virtual SharedPtr<Model>
    modelFromUSD() { 
      return nullptr;
    }

    bool 
    m_liveEditActivation = true;
   
    /**
     * @brief    If reads a configuration project file and have's omniverse config
     *           and an existen USD stage, writes the stage here.
     */
    String
    m_existingStage;

    /**
     * @brief    .
     * @todo     Chage for a global variable in project settings, if is not another, 
     *           use this as a default.
     */
    String 
    m_destinationPath = "omniverse://localhost/Users/giProjects/";

  };

  GI_CORE_EXPORT BaseOmni& 
  g_omniverse();

  //For load the DLL
  using funCreateOmniverse = BaseOmni * (*)();
  

}