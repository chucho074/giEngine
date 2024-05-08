/**
 * @file    giObject.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    10/06/2021
 * @brief   .
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
   */
  class GI_CORE_EXPORT Object
  {
   public:
    //Default Constructor.
    Object() = default;

    //Destructor.
    virtual 
    ~Object() = default;
    
   protected:
    
   
   private:
   
  };
  
}