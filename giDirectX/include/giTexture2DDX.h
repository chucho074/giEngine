/**
* @file		CTexture2DDX.h
* @author	Jesús Alberto Del Moral Cupil
* @e	    idv18c.jmoral@uartesdigitales.edu.mx
* @date		05/03/2021
* @brief	Management of the Textures for DX.
* @bug		No known Bugs.
**/

/**
* @include
**/
#pragma once
#include <giPrerequisitesCore.h>
#include <giTexture2D.h>

struct TextureDesc;

/**
* @class    CTexture2DDX.
* @brief    Manage the textures of DirectX.
* @bug      No known Bugs.
**/
namespace giEngineSDK {
  class CTexture2DDX : public CTexture2D 
  {
   public:
    /**
    * @brief	: Constructor.
    * @bug		: No Bugs known.
    **/
    CTexture2DDX();
  
    /**
    * @brief	: Destructor.
    * @bug		: No Bugs known.
    **/
    ~CTexture2DDX();
  
    /**
    * @brief	: Object for direct management of the texture.
    * @bug		: No Bugs known.
    **/
    ID3D11ShaderResourceView* 
    getSRV() { return m_SRV; }
   protected:
    friend class CGraphicsDX;
  
    ID3D11Texture2D* m_Texture = nullptr;
    ID3D11ShaderResourceView* m_SRV = nullptr;
    ID3D11DepthStencilView* m_DSV = nullptr;
    ID3D11RenderTargetView* m_RTV = nullptr;
  };
}