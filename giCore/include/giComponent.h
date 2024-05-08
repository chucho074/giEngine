/**
 * @file    giComponent.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    10/06/2021
 * @brief   .
 */
 
/**
 * @include
 */
#pragma once
#include "giObject.h"

namespace giEngineSDK {

  namespace COMPONENT_TYPE {
    enum E {
      kStaticMesh = 0,
      kCamera,
      /*
      Lights
      Sound
      */
    };
  }

  /**
   * @class    Component.
   * @brief    .   
   */
  class GI_CORE_EXPORT Component// : public Object
  {
   public:
    //Default Constructor.
    Component() = default;

    //Destructor.
    ~Component() = default;

    virtual void 
    update(float inDeltaTime) {
      GI_UNREFERENCED_PARAMETER(inDeltaTime);
    };


    virtual void 
    render() { };

    virtual void 
    destroy() { };
    
   protected:
    
   
   private:
   
  };

}