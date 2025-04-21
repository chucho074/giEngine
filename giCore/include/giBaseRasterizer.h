/**
 * @file    giBaseRasterizer
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/08/2021
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"

namespace giEngineSDK {

  namespace FILLMODE {
    enum E {
      kWireFrame = 2,
      kSolid = 3
    };
  }

  namespace CULLMODE {
    enum E {
      kNone = 1,
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

    FILLMODE::E m_fillMode = FILLMODE::kSolid;

    CULLMODE::E m_cullMode = CULLMODE::kNone;
  };
}