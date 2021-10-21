/**
 * @file    giUnorderedAccessViewDX.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    20/10/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesDX.h"
#include <giBaseUnorderedAccessView.h>

/**
 * @class    UnorderedAccessViewDX.
 * @brief    A unordered access view interface for owns for DX.
 * @bug      No known Bugs.
 */
namespace giEngineSDK {
  class UnorderedAccessViewDX final : public BaseUnorderedAccessView
  {
   public:
    //Default Constructor
  	UnorderedAccessViewDX() = default;

    //Destructor
  	~UnorderedAccessViewDX() {
      SAFE_RELEASE(m_uav);
    }

    //Access to the DirectX Unordered Access View
    ID3D11UnorderedAccessView * m_uav = nullptr;
   protected:
  	
   private:

  };
}