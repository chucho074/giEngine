/**
 * @file    giBaseViewport.h
 * @author  Jes�s Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    27/11/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"

namespace giEngineSDK {
  /**
   * @class    BaseViewport.
   * @brief    .
   * @bug      No known Bugs.
   */
  class BaseViewport
  {
   public:
    //Default Constructor.
    BaseViewport() = default;

    //Destructor.
    ~BaseViewport() {};
    
   private:
    float m_width;
    float m_height;
  };
  
}