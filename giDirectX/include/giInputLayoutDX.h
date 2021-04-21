/**
 * @file    giInputLayoutDX.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    15/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesDX.h"
#include <giInputLayout.h>

namespace giEngineSDK {
  struct InputLayoutDesc;


  /**
   * @class    CInputLayoutDX.
   * @brief    Manage the Input Layout information.
   * @bug      No known Bugs.
   */
  class CInputLayoutDX : public InputLayout
  {
   public:
    ///Constructor
    CInputLayoutDX();

    ///Destructor
    ~CInputLayoutDX();

    /**
     * @brief    Initializer.
     * @param    inLayout   The layout information in a vector.
     * @bug      No known Bugs.
     */
    void 
    init(const Vector<InputLayoutDesc>& inLayout);

   protected:

    ///GraphicsAPI Reference
    friend class CGraphicsDX;

    ///Reference to DirectX Input Layout
    ID3D11InputLayout* m_InputLayout;

    ///Reference to a DirectX Input element desc List
    Vector<D3D11_INPUT_ELEMENT_DESC> m_Descriptors;

  };
}