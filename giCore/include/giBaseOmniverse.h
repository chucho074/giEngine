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
     * @brief    .
     */
    virtual void
    createUSD() { }

    virtual SharedPtr<Model>
    modelFromUSD() { 
      return nullptr;
    }

    bool 
    m_liveEditActivation = true;
   
  };

  GI_CORE_EXPORT BaseOmni& 
  g_omniverse();

  //For load the DLL
  using funCreateOmniverse = BaseOmni * (*)();
  

}