/**
 * @file    giUnorderedAccessView.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/10/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"

namespace giEngineSDK {
  class BaseUnorderedAccessView
  {
   public:
    //Default Constructor
  	BaseUnorderedAccessView() = default;
  	
    //Destructor
    virtual 
    ~BaseUnorderedAccessView() = default;

   protected:
  	
   private:
  };
}