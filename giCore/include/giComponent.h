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
  /**
   * @class    Component.
   * @brief    .
   * @bug      No known Bugs.
   */
  class Component : public Object
  {
   public:
    //Default Constructor.
    Component() = default;
    //Destructor.
    virtual 
    ~Component() = default;
    
   protected:
    
   
   private:
   
  };

}