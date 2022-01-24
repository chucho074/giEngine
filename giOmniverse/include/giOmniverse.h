/**
 * @file    giOmniverse.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/01/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesOmniverse.h"

namespace giEngineSDK {
  /**
   * @class    Omni.
   * @brief    .
   * @bug      No known Bugs.
   */
  class Omni
  {
   public:
    //Default Constructor.
    Omni() = default;
    //Destructor.
    ~Omni() = default;
    
    /**
     * @brief    .
     */
    void
    createUSD();
   
  };

  /**
   * @brief   Create the gAPI with a dll.
   */
  extern "C" GI_PLUGIN_EXPORT Omni *
    createOmniverse() {
    auto ov = new Omni();
    return ov;
  }
  
}