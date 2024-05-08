/**
 * @file    giGraphicsOGL.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    20/04/2021
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesOGL.h"
#include <giBaseGraphicsAPI.h>
#include <SFML/Window/WindowBase.hpp>


using sf::WindowBase;


namespace giEngineSDK {
  /**
   * @class    GraphicsOGL.
   * @brief    .   
   */
  class GraphicsOGL : public GraphicsAPI
  {
  public:
    //Default Constructor.
    GraphicsOGL();
    //Destructor.
    ~GraphicsOGL();

    /**
     * @brief    In charge of the creation of the device & SwapChain     
     */
    void 
    init(void * inWindow, 
         int32 inWidth, 
         int32 inHeight);
  
    /**
     * @brief    In Charge to create the device and the swap chain.
     * @return   Returns .     
     */
    bool 
    createDeviceAndSwpaChain(void * inWindow, 
                             int32 inWidth, 
                             int32 inHeight);
  
    /**
     * @brief    Creates the texture in the Device.     
     */
    Texture2D * 
    createTex2D(int32 inWidth,
                int32 inHeigh,
                int32 inMipLevels,
                GI_FORMAT::E inFormat,
                int32 inBindFlags);
    
    /**
     * @brief    Creates the View Port in the Device.     
     */
    void 
    createViewport(uint32 inNumVP,
             int32 inWidth,
             int32 inHeight,
             int32 inTopX,
             int32 inTopY);
  
    /**
     * @brief    Create the Vertex Shader.     
     */
    BaseVertexShader * 
    createVShaderFromFile(String inFileName,
             String inEntryPoint,
             String inShaderModel);
  
    /**
     * @brief    Create the Pixel Shader     
     */
    BasePixelShader * 
    createPShaderFromFile(String inFileName,
             String inEntryPoint,
             String inShaderModel);
  
    /**
     * @brief    Creates the Input Layout.     
     */
    InputLayout * 
    createInputLayout(Vector<InputLayoutDesc> & inDesc, BaseShader * inShader);
  
    /**
     * @brief    Creates a buffer.     
     */
    Buffer *
    createBuffer(uint32 inByteWidth, 
                 uint32 inBindFlags, 
                 uint32 inOffset, 
                 void * inBufferData);
    
    /**
     * @brief    Creates a SamplerState.     
     */
    SamplerState * 
    createSampler(SamplerDesc inDesc);
  
    /**
     * @brief    Present.
     */
    void 
    show();
  
    /**
     * @brief    Set VertexBuffer.
     */
    void 
    setVertexBuffer(Buffer * inBuffer, uint32 inStride);
  
    /**
     * @brief    Set IndexBuffer.  
     */
    void 
    setIndexBuffer(Buffer * inBuffer, GI_FORMAT::E inFormat);
  
    /**
     * @brief    Set PrimitiveTopology.   
     */
    void 
    setTopology(GI_PRIMITIVE_TOPOLOGY::E inTopotology);
  
    /**
     * @brief    Update Subresource.    
     */
    void 
    updateSubresource(Buffer * inBuffer, 
                      void * inData, 
                      uint32 inPitch);
  
    /**
     * @brief    Update Texture.     
     */
    void 
    updateTexture(Texture2D * inTexture, 
                  const void * inData, 
                  uint32 inPitch, 
                  uint32 inDepthPitch);
  
    /**
     * @brief 
     * @param inColor 
     */
    void
    clearBackTexture(float inColor[4]) override;

    /**
     * @brief    Clear the Render Target View.     
     */
    void 
    clearRTV(Texture2D* inRTV, float inColor[4]);
  
    /**
     * @brief    Clear the Depth Stencil View.     
     */
    void 
    clearDSV(Texture2D* inDSV);
  
    /**
     * @brief    Vertex Shader Set Shader.     
     */
    void 
    vsSetShader(BaseShader * inVShader = nullptr);
  
    /**
     * @brief    Vertex Shader Set Constant Buffer.     
     */
    void 
    vsSetConstantBuffer(uint32 inSlot, Buffer * inBuffer = nullptr);
  
    /**
     * @brief    Pixel Shader Set Shader.     
     */
    void 
    psSetShader(BaseShader * inPShader = nullptr);
  
    /**
     * @brief    Pixel Shader Set Constant Buffer.     
     */
    void 
    psSetConstantBuffer(uint32 inSlot, Buffer * inBuffer);
  
    /**
     * @brief    Pixel Shadder Set Shader Resource.     
     */
    void 
    psSetShaderResource(uint32 inSlot, Texture2D * inTexture = nullptr);
  
    /**
     * @brief    Pixel Shader Set Samplers.     
     */
    void 
    psSetSamplerState(uint32 inSlot, 
                 uint32 inNumSamplers, 
                 SamplerState * inSampler);
  
    /** 
     * @brief    IA Set Input Layout.     
     */
    void 
    aiSetInputLayout(InputLayout * inInputLayout);
  
    /** 
     * @brief    OM Set Render Targets.     
     */
    void 
    omSetRenderTarget(Texture2D * inRT = nullptr, 
                      Texture2D * inDS = nullptr);
  
    /** 
     * @brief    Draw Index.     
     */
    void 
    drawIndexed(uint32 inNumIndexes, uint32 inStartLocation);
    
    /**
     * @brief    Gets the default Render Target.
     * @return   Returns the back Buffer texture.     
     */
    Texture2D * 
    getDefaultRenderTarget() { 
      return nullptr/*m_backBuffer*/; 
    }
  
    /**
     * @brief    Gets the default Depth Stencil.
     * @return   Returns the Depth Stencil View texutre.     
     */
    Texture2D * 
    getDefaultDephtStencil() { 
      return nullptr/*m_defaultDSV*/; 
    }
  
    /**
     * @brief     For the format of OGL.
     * @param     inFormat 
     * @return    Returns the format.
     */
    int32
    getFormat(GI_FORMAT::E inFormat);
    
    /**
     * @brief     For the format of OGL.
     * @param     inFormat 
     * @return    Returns the format.
     */
    int32
    getImgFormat(GI_FORMAT::E inFormat); //izquierda
   protected:

     HDC m_handle = 0;

     HGLRC oglRenderContext = 0;

     uint32 m_topology;

     /*///Reference to the device
     ID3D11Device* m_device;

     ///Reference to the device Context
     ID3D11DeviceContext* m_devContext;

     ///Reference to the Swap Chain
     IDXGISwapChain* m_swapChain;

     ///Reference to the defautl Render Target
     Texture2DDX* m_backBuffer = nullptr;

     ///Reference to the default Depth Stencil
     Texture2DDX* m_defaultDSV = nullptr;

     ///Reference to the default View Port
     CViewPort* m_defaultVP = nullptr;*/

  };
}