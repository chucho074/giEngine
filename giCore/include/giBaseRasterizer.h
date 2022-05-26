/**
 * @file    giBaseRasterizer
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/08/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"

namespace giEngineSDK {

  namespace FILLMODE {
    enum E {
      kSolid = 0,
      kWireFrame
    };
  }

  namespace CULLMODE {
    enum E {
      kNone = 0,
      kFront,
      kBack
    };
  }

  class BaseRasterizerState
  {
   public:
  	//Default constructor
    BaseRasterizerState() = default;

    //Destructor
    virtual
  	~BaseRasterizerState() = default;
  };
}