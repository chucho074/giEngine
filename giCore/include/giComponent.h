/**
 * @file    giComponent.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    10/06/2021
 * @brief   .
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giObject.h"

namespace giEngineSDK {

  namespace COMPONENT_TYPE {
    enum E {
      kModel = 0,
      k
    };
  }

  /**
   * @class    Component.
   * @brief    .
   * @bug      No known Bugs.
   */
  class GI_CORE_EXPORT Component// : public Object
  {
   public:
    //Default Constructor.
    Component() = default;

    //Destructor.
    ~Component() = default;

    virtual void 
    update(float inDeltaTime) = 0;


    virtual void 
    render() = 0;
    
   protected:
    
   
   private:
   
  };

}