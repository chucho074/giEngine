/**
 * @file    giGraphicsOGL.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    20/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
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
   * @bug      No known Bugs.
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
     * @bug      No known Bugs.
     */
    void 
    init(void * inWindow, 
         int32 inWidth, 
         int32 inHeight);
  
    /**
     * @brief    In Charge to create the device and the swap chain.
     * @return   Returns .
     * @bug      No known Bugs.
     */
    bool 
    createDeviceAndSwpaChain(void * inWindow, 
                             int32 inWidth, 
                             int32 inHeight);
  
    /**
     * @brief    Creates the texture in the Device.
     * @bug      No known Bugs.
     */
    Texture2D * 
    createTex2D(int32 inWidth,
                int32 inHeigh,
                int32 inMipLevels,
                GI_FORMAT::E inFormat,
                int32 inBindFlags);
    
    /**
     * @brief    Creates the View Port in the Device.
     * @bug      No known Bugs.
     */
    void 
    createVP(uint32 inNumVP,
             int32 inWidth,
             int32 inHeight,
             int32 inTopX,
             int32 inTopY);
  
    /**
     * @brief    Create the Vertex Shader.
     * @bug      No known Bugs.
     */
    BaseVertexShader * 
    createVS(String inFileName,
             String inEntryPoint,
             String inShaderModel);
  
    /**
     * @brief    Create the Pixel Shader
     * @bug      No known Bugs.
     */
    BasePixelShader * 
    createPS(String inFileName,
             String inEntryPoint,
             String inShaderModel);
  
    /**
     * @brief    Creates the Input Layout.
     * @bug      No known Bugs.
     */
    InputLayout * 
    createIL(Vector<InputLayoutDesc> & inDesc, BaseShader * inShader);
  
    /**
     * @brief    Creates a buffer.
     * @bug      No known Bugs.
     */
    Buffer *
    createBuffer(uint32 inByteWidth, 
                 uint32 inBindFlags, 
                 uint32 inOffset, 
                 void * inBufferData);
    
    /**
     * @brief    Creates a Sampler.
     * @bug      No known Bugs.
     */
    Sampler * 
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
    setVertexBuffer(Buffer * inBuffer, uint32 inStride);
  
    /**
     * @brief    Set IndexBuffer.
     * @bug      No known Bugs.
     */
    void 
    setIndexBuffer(Buffer * inBuffer, GI_FORMAT::E inFormat);
  
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
    updateSubresource(Buffer * inBuffer, 
                      void * inData, 
                      uint32 inPitch);
  
    /**
     * @brief    Update Texture.
     * @bug      No known Bugs.
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
     * @bug      No known Bugs.
     */
    void 
    clearRTV(Texture2D* inRTV, float inColor[4]);
  
    /**
     * @brief    Clear the Depth Stencil View.
     * @bug      No known Bugs.
     */
    void 
    clearDSV(Texture2D* inDSV);
  
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
    vsSetConstantBuffer(uint32 inSlot, Buffer * inBuffer = nullptr);
  
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
    psSetConstantBuffer(uint32 inSlot, Buffer * inBuffer);
  
    /**
     * @brief    Pixel Shadder Set Shader Resource.
     * @bug      No known Bugs.
     */
    void 
    psSetShaderResource(uint32 inSlot, Texture2D * inTexture = nullptr);
  
    /**
     * @brief    Pixel Shader Set Samplers.
     * @bug      No known Bugs.
     */
    void 
    psSetSampler(uint32 inSlot, 
                 uint32 inNumSamplers, 
                 Sampler * inSampler);
  
    /** 
     * @brief    IA Set Input Layout.
     * @bug      No known Bugs.
     */
    void 
    aiSetInputLayout(InputLayout * inInputLayout);
  
    /** 
     * @brief    OM Set Render Targets.
     * @bug      No known Bugs.
     */
    void 
    omSetRenderTarget(Texture2D * inRT = nullptr, 
                      Texture2D * inDS = nullptr);
  
    /** 
     * @brief    Draw Index.
     * @bug      No known Bugs.
     */
    void 
    drawIndexed(uint32 inNumIndexes, uint32 inStartLocation);
    
    /**
     * @brief    Gets the default Render Target.
     * @return   Returns the back Buffer texture.
     * @bug      No known Bugs.
     */
    Texture2D * 
    getDefaultRenderTarget() { 
      return nullptr/*m_backBuffer*/; 
    }
  
    /**
     * @brief    Gets the default Depth Stencil.
     * @return   Returns the Depth Stencil View texutre.
     * @bug      No known Bugs.
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