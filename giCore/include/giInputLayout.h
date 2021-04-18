/**
 * @file     giInputLayout.h
 * @author   Jesús Alberto Del Moral Cupil
 * @e        idv18c.jmoral@uartesdigitales.edu.mx
 * @date     10/03/2021
 * @brief    Manage the Input Layout information.
 * @bug      No known Bugs.
 */

/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include <string>
#include <vector>

namespace giEngineSDK {
  /**
   * @struct  InputLayoutDesc.
   * @brief   Data to the Input Layout.
   * @bug     No known Bugs.
   */
  struct InputLayoutDesc {
    String semanticName;
    unsigned int semanticIndex;
    unsigned int format;
    unsigned int inputSlot;
    unsigned int alignedByteOffset;
    unsigned int inputSlotClass;
    unsigned int instanceDataStepRate;
  };
  
  /**
   * @class    CInputLayout.
   * @brief    Manage the Input Layout information.
   * @bug      No known Bugs.
   */
  class CInputLayout {
   public:
  
     ///Constructor
     CInputLayout() {}
  
     ///Destructor
     ~CInputLayout() {}
  
     /**
      * @brief    Initializer.
      * @param    inLayout   The layout information in a vector.
      * @bug      No known Bugs.
      */
     virtual void 
     init(const std::vector<InputLayoutDesc>& inLayout) = 0;
  };
}