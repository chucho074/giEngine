/**
 * @file    giTime.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    12/04/2021
 * @brief   A basic use of the time.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesUtilities.h"
#include "giModule.h"
#include <chrono>

namespace giEngineSDK {
  /**
   * @class    Time.
   * @brief    .
   * @bug      No known Bugs.
   */
  class Time : public Module<Time>
  {
   public:
    //Default Constructor.
    Time();
    //Destructor.
    ~Time();
    
   protected:
    
   
   private:
   
  };
  
  
  
}