/**
 * @file    CGraphicsDX.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    05/03/2021
 * @brief   Management of the graphics APIs.
 * @bug     No known Bugs.
 */

/**
 * @include
 */
#pragma once
#include "giPrerequisitesDX.h"
#include <giBaseGraphicsAPI.h>


namespace giEngineSDK {
  class CTexture2DDX;
  class CViewPortDX;
  class BaseShader;
  class CBufferDX;
  class CInputLayoutDX;
  class CSamplerDX;

  class CImageLoader;

}

namespace giEngineSDK {
  /**
   * @class    CGraphicsDX.
   * @brief    Manage the graphics of DirectX.
   * @bug      No known Bugs.
   */
  class CGraphicsDX final : public CBaseGraphicsAPI
  {
   public:
    //Default Constructor.
    CGraphicsDX();
    
    ///Destructor.
    ~CGraphicsDX();
      
    /**
     * @brief    In charge of the creation of the device & SwapChain
     * @bug      No known Bugs.
     */
    void 
    init(void * inWindow, 
    /***/int inWidth, 
    /***/int inHeight);
  
    /**
     * @brief    In Charge to create the device and the swap chain.
     * @return   Returns .
     * @bug      No known Bugs.
     */
    bool 
    createDeviceAndSwpaChain(void * inWindow, 
    /***********************/int inWidth, 
    /***********************/int inHeight);
  
    /**
     * @brief    Creates the texture in the Device.
     * @bug      No known Bugs.
     */
    CTexture2D * 
    createTex2D(int inWidth,
    /**********/int inHeigh,
    /**********/int inMipLevels,
    /**********/GI_FORMAT::E inFormat,
    /**********/int inBindFlags);
    
    /**
     * @brief    Creates the View Port in the Device.
     * @bug      No known Bugs.
     */
    CViewPort * 
    createVP(int inWidth, 
    /*******/int inHeight);
  
    /**
     * @brief    Sets the View Port in the DeviceContext.
     * @bug      No known Bugs.
     */
    void 
    setVP(CViewPort &inVP);
  
    /**
     * @brief    Create the Vertex Shader.
     * @bug      No known Bugs.
     */
    CBaseShader * 
    createVS(wchar* inFileName,
    /*******/lpcstr inEntryPoint,
    /*******/lpcstr inShaderModel);
  
    /**
     * @brief    Create the Pixel Shader
     * @bug      No known Bugs.
     */
    CBaseShader * 
    createPS(wchar* inFileName,
    /*******/lpcstr inEntryPoint,
    /*******/lpcstr inShaderModel);
  
    /**
     * @brief    Creates the Input Layout.
     * @bug      No known Bugs.
     */
    CInputLayout * 
    createIL(Vector<InputLayoutDesc> & inDesc, BaseShader * inShader);
  
    /**
     * @brief    Creates a buffer.
     * @bug      No known Bugs.
     */
    CBuffer *
    createBuffer(unsigned int inByteWidth, 
    /***********/unsigned int inBindFlags, 
    /***********/unsigned int inOffset, 
    /***********/void * inBufferData);
    
    /**
     * @brief    Creates a Sampler.
     * @bug      No known Bugs.
     */
    CSampler * 
    createSampler(SamplerDesc inDesc);
  
    /**
     * @brief    Present.
     * @bug      No known Bugs.
     */
    void 
    show();
  
    /**
     * @brief    Set VertexBuffer.
     * @bug      No known Bugs.
     */
    void 
    setVertexBuffer(CBuffer * inBuffer, unsigned int inStride);
  
    /**
     * @brief    Set IndexBuffer.
     * @bug      No known Bugs.
     */
    void 
    setIndexBuffer(CBuffer * inBuffer, GI_FORMAT::E inFormat);
  
    /**
     * @brieft    Set PrimitiveTopology.
     * @bug      No known Bugs.
     */
    void 
    setTopology(GI_PRIMITIVE_TOPOLOGY::E inTopotology);
  
    /**
     * @brief    Update Subresource.
     * @bug      No known Bugs.
     */
    void 
    updateSubresource(CBuffer * inBuffer, 
    /****************/void * inData, 
    /****************/unsigned int inPitch);
  
    /**
     * @brief    Update Texture.
     * @bug      No known Bugs.
     */
    void 
    updateTexture(CTexture2D * inTexture, 
    /************/const void * inData, 
    /************/unsigned int inPitch, 
    /************/unsigned int inDepthPitch);
  
    /**
     * @brief    Clear the Render Target View.
     * @bug      No known Bugs.
     */
    void 
    clearRTV(CTexture2D* inRTV, float inColor[4]);
  
    /**
     * @brief    Clear the Depth Stencil View.
     * @bug      No known Bugs.
     */
    void 
    clearDSV(CTexture2D* inDSV);
  
    /**
     * @brief    Vertex Shader Set Shader.
     * @bug      No known Bugs.
     */
    void 
    vsSetShader(BaseShader * inVShader = nullptr);
  
    /**
     * @brief    Vertex Shader Set Constant Buffer.
     * @bug      No known Bugs.
     */
    void 
    vsSetConstantBuffer(unsigned int inSlot, CBuffer * inBuffer = nullptr);
  
    /**
     * @brief    Pixel Shader Set Shader.
     * @bug      No known Bugs.
     */
    void 
    psSetShader(BaseShader * inPShader = nullptr);
  
    /**
     * @brief    Pixel Shader Set Constant Buffer.
     * @bug      No known Bugs.
     */
    void 
    psSetConstantBuffer(unsigned int inSlot, CBuffer * inBuffer);
  
    /**
     * @brief    Pixel Shadder Set Shader Resource.
     * @bug      No known Bugs.
     */
    void 
    psSetShaderResource(unsigned int inSlot, CTexture2D * inTexture = nullptr);
  
    /**
     * @brief    Pixel Shader Set Samplers.
     * @bug      No known Bugs.
     */
    void 
    psSetSampler(unsigned int inSlot, 
    /***********/unsigned int inNumSamplers, 
    /***********/CSampler * inSampler);
  
    /** 
     * @brief    IA Set Input Layout.
     * @bug      No known Bugs.
     */
    void 
    aiSetInputLayout(CInputLayout * inInputLayout);
  
    /** 
     * @brief    OM Set Render Targets.
     * @bug      No known Bugs.
     */
    void 
    omSetRenderTarget(CTexture2D * inRT = nullptr, 
    /****************/CTexture2D * inDS = nullptr);
  
    /** 
     * @brief    Draw Index.
     * @bug      No known Bugs.
     */
    void 
    draw(unsigned int inNumIndexes, unsigned int inStartLocation);
    
    /**
     * @brief    Gets the default Render Target.
     * @return   Returns the back Buffer texture.
     * @bug      No known Bugs.
     */
    CTexture2D * 
    getDefaultRenderTarget() { return m_backBuffer; }
  
    /**
     * @brief    Gets the default Depth Stencil.
     * @return   Returns the Depth Stencil View texutre.
     * @bug      No known Bugs.
     */
    CTexture2D * 
    getDefaultDephtStencil() { return m_defaultDSV; }
  
  
   private:
  
    ///Reference to the device
    ID3D11Device* m_Device;
  
    ///Reference to the device Context
    ID3D11DeviceContext* m_DevContext;
  
    ///Reference to the Swap Chain
    IDXGISwapChain* m_SwapChain;
  
    ///Reference to the defautl Render Target
    CTexture2DDX  * m_backBuffer = nullptr;
  
    ///Reference to the default Depth Stencil
    CTexture2DDX  * m_defaultDSV = nullptr;
  
    ///Reference to the default View Port
    CViewPort * m_defaultVP = nullptr;
  
  };
}