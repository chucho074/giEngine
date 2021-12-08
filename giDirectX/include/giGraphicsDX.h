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
#include "giTexture2DDX.h"

#define STB_IMAGE_IMPLEMENTATION

namespace giEngineSDK {
  class BaseShader;
  class BufferDX;
  class InputLayoutDX;
  class SamplerDX;
  class RasterizerDX;
  class DepthStateDX;
}

namespace giEngineSDK {
  /**
   * @class    CGraphicsDX.
   * @brief    Manage the graphics of DirectX.
   * @bug      No known Bugs.
   */
  class CGraphicsDX : public GraphicsAPI
  {
   public:
    //Default Constructor.
    CGraphicsDX();
    
    ///Destructor.
    ~CGraphicsDX();
      
    /**
     * @brief    In charge of the creation of the device & SwapChain
     * @param    inWindow   The window object.
     * @param    inWidth    The width of the screen.
     * @param    inHeight   The height of the screen.
     * @bug      No known Bugs.
     */
    void 
    init(void * inWindow) override;
    
    /**
     * @brief    In Charge to create the device and the swap chain.
     * @param    inWindow   The window object.
     * @param    inWidth    The width of the screen.
     * @param    inHeight   The height of the screen.
     * @bug      No known Bugs.
     */
    bool 
    createDeviceAndSwpaChain(void * inWindow) override;
         
    /**
     * @brief    Creates the texture in the Device.
     * @param    inWidth        The width of the texture.
     * @param    inHeigh        The heigh of the texture.
     * @param    inMipLevels    The mip levels.
     * @param    inFormat       The format of the texture.
     * @param    inBindFlags    The bind flags of the texture.
     * @bug      No known Bugs.
     */
    Texture2D * 
    createTex2D(int32 inWidth,
                int32 inHeigh,
                int32 inMipLevels,
                GI_FORMAT::E inFormat,
                int32 inBindFlags) override;

    /**
     * @brief    Creates the View Port in the Device.
     * @param    inWidth     The width of the viewport.
     * @param    inHeight    The height of the viewport.
     * @param    inTopX      The position to set the left corner of the window in x.
     * @param    inTopY      The position to set the left corner of the window in y.
     * @return   Returns .
     * @bug      No known Bugs.
     */
    void 
    createVP(uint32 inNumVP,
             int32 inWidth,
             int32 inHeight,
             int32 inTopX,
             int32 inTopY) override;
    
    /**
     * @brief    Create the Vertex Shader.
     * @param    inFileName    The name of the file.
     * @param    inEntryPoint  The entry point in the shader.
     * @param    inShaderModel The model in the shader.
     * @bug      No known Bugs.
     */
    BaseVertexShader * 
    createVS(String inFileName,
             String inEntryPoint,
             String inShaderModel) override;
    
    /**
     * @brief    Create the Pixel Shader.
     * @param    inFileName    The name of the file.
     * @param    inEntryPoint  The entry point in the shader.
     * @param    inShaderModel The model in the shader.
     * @bug      No known Bugs.
     */
    BasePixelShader * 
    createPS(String inFileName,
             String inEntryPoint,
             String inShaderModel) override;
             
    /**
     * @brief    Create the Compute Shader.
     * @param    inFileName    The name of the file.
     * @param    inEntryPoint  The entry point in the shader.
     * @param    inShaderModel The model in the shader.
     * @bug      No known Bugs.
     */
    BaseComputeShader * 
    createCS(String inFileName,
             String inEntryPoint,
             String inShaderModel) override;

    /**
     * @brief    Creates the Input Layout.
     * @param    inDesc    A vector with the inputLayout information.
     * @param    inShader  The vertex shader.
     * @return   Returns   The Input layout.
     * @bug      No known Bugs.
     */
    InputLayout * 
    createIL(Vector<InputLayoutDesc> & inDesc, 
             BaseShader * inShader) override;

    /**
     * @brief    Creates a buffer.
     * @param    inByteWidth   The byte Width for the buffer.
     * @param    inBindFlags   The bind flags for the buffer.
     * @param    inOffset      The offset of the buffer.
     * @param    inBufferData  The information to save into the buffer.
     * @return   Returns the buffer.
     * @bug      No known Bugs.
     */
    Buffer * 
    createBuffer(size_T inByteWidth, 
                 uint32 inBindFlags, 
                 uint32 inOffset, 
                 void * inBufferData) override;
    
    /**
     * @brief    Creates a Sampler.
     * @param    inDesc   The descriptor of the sampler.
     * @bug      No known Bugs.
     */
    Sampler * 
    createSampler(SamplerDesc inDesc) override;
    
    /**
     * @brief    Create a Rasterizer.
     */
    BaseRasterizerState *
    createRasterizer(FILLMODE::E inFillMode,
                     CULLMODE::E inCullMode,
                     bool inClockwise) override;

    /**
     * @brief    Create a Depth Stencil State.
     */
    BaseDepthStencilState *
    createDepthState(bool inStencilEnable,
                     bool inDepthEnable) override;

    /**
     * @brief    Present.
     * @bug      No known Bugs.
     */
    void 
    show() override;
    
    /**
     * @brief    Set VertexBuffer.
     * @param    inBuffer   The buffer to set as vertex in the context.
     * @param    inStride   The stride for the buffer.
     * @bug      No known Bugs.
     */
    void 
    setVertexBuffer(Buffer * inBuffer, 
                    uint32 inStride) override;
    
    /**
     * @brief    Set IndexBuffer.
     * @param    inBuffer   The buffer to set as index in the context.
     * @param    inFormat   The format of the data.
     * @bug      No known Bugs.
     */
    void 
    setIndexBuffer(Buffer * inBuffer, 
                   GI_FORMAT::E inFormat) override;
    
    /**
     * @brief     Set PrimitiveTopology.
     * @param     inTopology   The type of topology to set.
     * @bug       No known Bugs.
     */
    void 
    setTopology(GI_PRIMITIVE_TOPOLOGY::E inTopotology) override;

    /**
     * @brief    Set the rasterizer State.
     * @param    inRaster      The rasterizer to set.
     * @bug      No known Bugs.
     */
    void 
    setRasterizerState(RasterizerDX* inRaster);

    void 
    setDepthState(DepthStateDX* inDepthState);
    
    /**
     * @brief    Update Subresource.
     * @param    inBuffer   The buffer with the information.
     * @param    inData     The data to update.
     * @param    inPitch    Pitch of the data.
     * @bug      No known Bugs.
     */
    void 
    updateSubresource(Buffer * inBuffer, 
                      void * inData, 
                      uint32 inPitch) override;
    
    /**
     * @brief    Update Texture.
     * @param    inTexture      The texture to update.
     * @param    inData         The data to udapte.
     * @param    inPitch        The pitch.
     * @param    inDepthPitch   The depth pitch.
     * @bug      No known Bugs.
     */
    void 
    updateTexture(Texture2D * inTexture, 
                  const void * inData, 
                  uint32 inPitch, 
                  uint32 inDepthPitch) override;
    
    /**
     * @brief    Clear the Back Buffer.
     * @param    inColor    The color to set.
     * @bug      No known Bugs.
     */
    void 
    clearBackTexture(float inColor[4]) override;
    
    /**
     * @brief    Clear Render Target View.
     * @param    inRTV      The render target view to clear.
     * @param    inColor    The color to set.
     * @bug      No known Bugs.
     */
    void 
    clearRTV(Texture2D* inRTV, float inColor[4]) override;
    
    /**
     * @brief    Clear Depth Stencil View.
     * @param    inDSV   The Depth stencil view to clear.
     * @bug      No known Bugs.
     */
    void 
    clearDSV(Texture2D* inDSV) override;
    
    /**
     * @brief    Vertex Shader Set Shader.
     * @param    inVShader   The Vertex Shader to set.
     * @bug      No known Bugs.
     */
    void 
    vsSetShader(BaseVertexShader * inVShader = nullptr) override;
    
    /**
     * @brief    Vertex Shader Set Constant Buffer.
     * @param    inSlot     Index to begin setting constant buffers.
     * @param    inBuffer   The constant buffer to set.
     * @bug      No known Bugs.
     */
    void 
    vsSetConstantBuffer(uint32 inSlot, 
                        Buffer * inBuffer = nullptr) override;
    
    /**
     * @brief    Pixel Shader Set Shader.
     * @param    inPShader    The pixel Shader to set.
     * @bug      No known Bugs.
     */
    void 
    psSetShader(BasePixelShader * inPShader = nullptr) override;
    
    /**
     * @brief    Pixel Shader Set Constant Buffer.
     * @param    inSlot      The index to begin setting constant buffer.
     * @param    inBuffer    The constant buffer to set.
     * @bug      No known Bugs.
     */
    void 
    psSetConstantBuffer(uint32 inSlot, 
                        Buffer * inBuffer) override;
    
    /**
     * @brief    Pixel Shadder Set Shader Resource.
     * @param    inSlot      The index to begin setting constant buffer.
     * @param    inTexture   The texture to set.
     * @bug      No known Bugs.
     */
    void 
    psSetShaderResource(uint32 inSlot, 
                        Texture2D * inTexture = nullptr) override;
    
    /**
     * @brief    Pixel Shader Set Samplers.
     * @param    inSlot          The index to begin setting the sampler.
     * @param    inNumSamplers   The number of samplers.
     * @param    inSampler       The sampler.
     * @bug      No known Bugs.
     */
    void 
    psSetSampler(uint32 inSlot, 
                 uint32 inNumSamplers, 
                 Sampler * inSampler) override;
    
    /** 
     * @brief    IA Set Input Layout.
     * @param    inInputLayout   The input layout to set.
     * @bug      No known Bugs.
     */
    void 
    aiSetInputLayout(InputLayout * inInputLayout) override;
    
    /** 
     * @brief    OM Set Render Targets.
     * @param    inRT    The Render Target texture.
     * @param    inDS    The Depth Stencil texture.
     * @bug      No known Bugs.
     */
    void 
    omSetRenderTarget(Vector<Texture2D *> inRT, 
                      Texture2D * inDS = nullptr) override;

    /** 
     * @brief    Set Blend State.
     * @param    inBlendState   Pointer to a blend-state interface. NULL for a default.
     * @param    inBlendFactor  Array of blend factors, one for each RGBA component.
     * @param    inSampleMask   32-bit sample coverage. The default value is 0xffffffff.
     * @bug      No known Bugs.
     */
    void 
    omSetBlendState(BaseBlendState * inBlendState,
                    const float inBlendFactor[4],
                    uint32 inSampleMask = 0xffffffff) override;
    
    /** 
     * @brief    Set Blend State.
     * @param    inDepthState   Pointer to a depth-state interface.
     * @param    inStencilRef   The reference to the stencil.
     * @bug      No known Bugs.
     */
    void 
    omSetDepthStencilState(BaseDepthStencilState * inDepthState,
                           uint32 inStencilRef) override;
     
    /**
     * @brief    Set the Rasterizer.
     * @param    inRaster       The rasterizer state to set.
     */
    void
    rsSetState(BaseRasterizerState * inRaster) override;

    
    /** 
     * @brief    Set Blend State.
     * @param    inBlendState   Pointer to a blend-state interface. NULL for a default.
     * @param    inBlendFactor  Array of blend factors, one for each RGBA component.
     * @param    inSampleMask   32-bit sample coverage. The default value is 0xffffffff.
     * @bug      No known Bugs.
     */
    void 
    omSetBlendState(BaseBlendState *, 
                    const float[4], 
                    uint32 = 0xffffffff) override;
                    
    /** 
     * @brief    Set Blend State.
     * @param    inDepthState   Pointer to a depth-state interface.
     * @param    inStencilRef   The reference to the stencil.
     * @bug      No known Bugs.
     */
    void 
    omSetDepthStencilState(BaseDepthStencilState * inDepthState,
                           uint32 inStencilRef) override;
    /**
     * @brief    Set the Rasterizer.
     * @param    inRaster       The rasterizer state to set.
     */
    void
    rsSetState(BaseRasterizerState * inRaster) override;

    /**
     * @brief 
     * @param    inNumRects 
     * @param    inRects 
     */
    void
    rsGetScissorRects(uint32 inNumRects, Vector4 inRects[]) override;

    /**
     * @brief 
     * @param    inNumViewports 
     * @param    inViewport 
     */
    void
    rsGetViewports(uint32 inNumViewports, void* inViewport) override;

    /**
     * @brief 
     * @param    inRasterState 
     */
    void
    rsGetState(BaseRasterizerState * inRasterState) override;

    /**
     * @brief 
     * @param    inBlendState 
     * @param    inBlendFactor 
     * @param    inSampleMask 
     */
    void 
    omGetBlendState(BaseBlendState * inBlendState, 
                    float inBlendFactor[4], 
                    uint32 inSampleMask) override;

    /**
     * @brief 
     * @param    inDepthStencilState 
     * @param    inStencilRef 
     */
    void 
    omGetDepthStencilState(BaseDepthStencilState * inDepthStencilState, 
                           uint32 inStencilRef) override;

    /**
     * @brief 
     * @param    inStartSlot 
     * @param    inNumViews 
     * @param    inShaderResource 
     */
    void
    psGetShaderResources(uint32 inStartSlot, 
                         uint32 inNumViews, 
                         Texture2D * inShaderResource) override;

    /**
     * @brief 
     * @param    inStartSlot 
     * @param    inNumSamplers 
     * @param    inSampler 
     */
    void
    psGetSamplers(uint32 inStartSlot, 
                  uint32 inNumSamplers, 
                  Sampler * inSampler) override;

    /**
     * @brief 
     * @param    inPixelShader 
     * @param    inNumClassInstances 
     */
    void
    psGetShader(BasePixelShader * inPixelShader, 
                int32 inNumClassInstances) override;

    /**
     * @brief 
     * @param    inVertexShader 
     * @param    inNumClassInstances 
     */
    void
    vsGetShader(BaseVertexShader * inVertexShader, 
                int32 inNumClassInstances) override;

    /**
     * @brief 
     * @param    inStartSlot 
     * @param    inNumBuffers 
     * @param    inConstantBuffer 
     */
    void
    vsGetConstantBuffers(int32 inStartSlot, 
                         int32 inNumBuffers, 
                         Buffer * inConstantBuffer) override;

    /**
     * @brief 
     * @param    inTopology 
     */
    void
    iaGetPrimitiveTopology(GI_PRIMITIVE_TOPOLOGY::E inTopology) override;

    /**
     * @brief 
     * @param    inIndexBuffer 
     * @param    inFormat 
     * @param    inOffset 
     */
    void
    iaGetIndexBuffer(Buffer * inIndexBuffer, 
                     GI_FORMAT::E inFormat, 
                     uint32 inOffset) override;

    /**
     * @brief 
     * @param    inStartSlot 
     * @param    inVertexBuffer 
     * @param    inStride 
     * @param    inOffset 
     */
    void
    iaGetVertexBuffer(uint32 inStartSlot, 
                      Buffer * inVertexBuffer, 
                      uint32 inStride, 
                      uint32 inOffset) override;
    
    /**
     * @brief 
     * @param    inInputLayout 
     */
    void
    iaGetInputLayout(InputLayout * inInputLayout) override;

    /**
     * @brief 
     * @param    inNumRects 
     * @param    inRects 
     */
    void 
    rsSetScissorRects(uint32 inNumRects, Vector4* inRects) override;
    
    /** 
     * @brief    Draw Index.
     * @param    inNumIndexes       The number of idexes to draw.
     * @param    inStartLocation    the start location to draw.
     * @bug      No known Bugs.
     */
    void 
    drawIndexed(size_T inNumIndexes, 
                uint32 inStartLocation) override;

    /**
     * @brief    Dispatch for Compute Shaders.
     * @param    inThreadGroupX  The number of groups dispatched in the x direction.
     * @param    inThreadGroupY  The number of groups dispatched in the y direction.
     * @param    inThreadGroupZ  The number of groups dispatched in the z direction.
     */
    void
    dispatch(uint32 inThreadGroupX, 
             uint32 inThreadGroupY, 
             uint32 inThreadGroupZ) override;
    
    /**
     * @brief    Gets the default Render Target.
     * @return   Returns the back Buffer texture.
     * @bug      No known Bugs.
     */
    Texture2D * 
    getDefaultRenderTarget() { 
      return m_backBuffer; 
    }
  
    /**
     * @brief    Gets the default Depth Stencil.
     * @return   Returns the Depth Stencil View texutre.
     * @bug      No known Bugs.
     */
    Texture2D * 
    getDefaultDephtStencil() { 
      return m_defaultDSV;
    }
    
    /**
     * @brief 
     * @param    inString 
     * @param    inDirectory 
     * @return 
     */
     Texture2D *
     TextureFromFile(String inString, 
                     String inDirectory);

  
   private:
  
    ///Reference to the device
    ID3D11Device * m_device;
  
    ///Reference to the device Context
    ID3D11DeviceContext * m_devContext;
  
    ///Reference to the Swap Chain
    IDXGISwapChain * m_swapChain;
  
    ///Reference to the defautl Render Target
    Texture2DDX * m_backBuffer = nullptr;
  
    ///Reference to the default Depth Stencil
    Texture2DDX * m_defaultDSV = nullptr;
   

  };
  
  /**
   * @brief      Create the gAPI with a dll.
   */
  extern "C" GI_PLUGIN_EXPORT CGraphicsDX *
  createGraphicsAPI() {
    auto DX = new CGraphicsDX();
    return DX;
  }
}