/**
 * @file     giInputLayout.h
 * @author   Jesus Alberto Del Moral Cupil
 * @e        idv18c.jmoral@uartesdigitales.edu.mx
 * @date     10/03/2021
 * @brief    Manage the Input Layout information. 
 */

/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"

namespace giEngineSDK {
  /**
   * @struct  InputLayoutDesc.
   * @brief   Data to the Input Layout. 
   */
  struct InputLayoutDesc {
    String semanticName;
    uint32 semanticIndex = 0;
    uint32 format = 0;
    uint32 inputSlot = 0;
    uint32 alignedByteOffset = 0;
    uint32 inputSlotClass = 0;
    uint32 instanceDataStepRate = 0;
  };
  
  /**
   * @class    InputLayout.
   * @brief    Manage the Input Layout information.   
   */
  class InputLayout {
   public:
  
     ///Constructor
     InputLayout() {}
  
     ///Destructor
     ~InputLayout() = default;
  
     /**
      * @brief    Initializer.
      * @param    inLayout   The layout information in a vector.      
      */
     virtual void 
     init(const Vector<InputLayoutDesc>& inLayout) = 0;
  };
}