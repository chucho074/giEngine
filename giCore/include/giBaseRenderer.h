/**
 * @file    giBaseRenderer
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    20/08/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include <giModule.h>
#include <giModel.h>

namespace giEngineSDK {
  class BaseRenderer : public Module<BaseRenderer>
  {
   public:
    //Default Constructor
  	BaseRenderer() = default;

    //Destructor
  	~BaseRenderer() = default;

    /**
     * @brief    .
     */
    virtual void
    create() {};
    
    /**
     * @brief    .
     */
    virtual void
    render() {};

    /**
     * @brief    .
     */
    virtual void
    update() {};

    /**
     * @brief    .
     */
    virtual void
    setModels(Vector<SharedPtr<Model>> inModelList) {};


    /**
     * @brief    Set the object of the Graphics API.
     * @param    inAPI   The api to set.
     */
    /*void
    setObject(BaseRenderer* inRenderer) {
      BaseRenderer::_instance() = inRenderer;
     }*/
  };

  GI_CORE_EXPORT BaseRenderer& 
  g_renderer();

  //For load the DLL
  using funCreateRenderer = BaseRenderer * (*)();

}