/**
 * @file    giInputLayoutDX.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    15/04/2021
 * @brief   A basic description of the what do the doc.
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
   * @class    InputLayoutDX.
   * @brief    Manage the Input Layout information.   
   */
  class InputLayoutDX : public InputLayout
  {
   public:
    ///Constructor
    InputLayoutDX();

    ///Destructor
    ~InputLayoutDX();

    /**
     * @brief    Initializer.
     * @param    inLayout   The layout information in a vector.     
     */
    void 
    init(const Vector<InputLayoutDesc>& inLayout);

   protected:

    ///GraphicsAPI Reference
    friend class CGraphicsDX;

    ///Reference to DirectX Input Layout
    ID3D11InputLayout* m_inputLayout;

    ///Reference to a DirectX Input element desc List
    Vector<D3D11_INPUT_ELEMENT_DESC> m_descriptors;

  };
}