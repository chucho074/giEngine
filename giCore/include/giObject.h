/**
 * @file    giObject.h
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
#include "giPrerequisitesCore.h"

namespace giEngineSDK {
  /**
   * @class    Object.
   * @brief    .
   * @bug      No known Bugs.
   */
  class GI_CORE_EXPORT Object
  {
   public:
    //Default Constructor.
    Object() = default;

    //Destructor.
    virtual 
    ~Object() = 0;
    
   protected:
    
   
   private:
   
  };
  
}