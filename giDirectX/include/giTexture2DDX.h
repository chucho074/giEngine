/**
 * @file    Texture2DDX.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    05/03/2021
 * @brief   Management of the Textures for DX.
 * @bug     No known Bugs.
 */

/**
 * @include
 */
#pragma once
#include <giPrerequisitesDX.h>
#include <giTexture2D.h>

struct TextureDesc;

/**
 * @class    Texture2DDX.
 * @brief    Manage the textures of DirectX.
 * @bug      No known Bugs.
 */
namespace giEngineSDK {
  class Texture2DDX : public Texture2D 
  {
   public:
    /**
     * @brief  : Constructor.
     * @bug    : No Bugs known.
     */
    Texture2DDX() = default;
  
    /**
     * @brief  : Destructor.
     * @bug    : No Bugs known.
     */
    ~Texture2DDX() = default;
  
    /**
     * @brief  : Object for direct management of the texture.
     * @bug    : No Bugs known.
     */
    ID3D11ShaderResourceView* 
    getSRV() { 
      return m_subResourceData; 
    }
   protected:
    friend class CGraphicsDX;
  
    ID3D11Texture2D* m_texture = nullptr;
    ID3D11ShaderResourceView* m_subResourceData = nullptr;
    ID3D11DepthStencilView* m_depthStencilView = nullptr;
    ID3D11RenderTargetView* m_renderTargetView = nullptr;
    ID3D11UnorderedAccessView * m_UAV = nullptr;
  };
}