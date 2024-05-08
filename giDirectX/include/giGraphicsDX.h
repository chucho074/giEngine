/**
 * @file    CGraphicsDX.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    05/03/2021
 * @brief   Management of the graphics APIs.
 */

/**
 * @include
 */
#pragma once
#include <giBaseGraphicsAPI.h>
#include "giPrerequisitesDX.h"
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
     * @param    inWindow      The window object.
     * @param    inWidth       The width of the screen.
     * @param    inHeight      The height of the screen.
     */
    void 
    init(void * inWindow) override;
    
    /**
     * @brief    In Charge to create the device and the swap chain.
     * @param    inWindow      The window object.
     * @param    inWidth       The width of the screen.
     * @param    inHeight      The height of the screen.
     */
    bool 
    createDeviceAndSwpaChain(void * inWindow) override;
         
    /**
     * @brief    Creates the texture in the Device.
     * @param    inWidth       The width of the texture.
     * @param    inHeigh       The heigh of the texture.
     * @param    inMipLevels   The mip levels.
     * @param    inFormat      The format of the texture.
     * @param    inBindFlags   The bind flags of the texture.
     */
    SharedPtr<Texture2D>
    createTex2D(int32 inWidth,
                int32 inHeigh,
                int32 inMipLevels,
                GI_FORMAT::E inFormat,
                int32 inBindFlags) override;

    /**
     * @brief    Creates the View Port in the Device.
     * @param    inWidth       The width of the viewport.
     * @param    inHeight      The height of the viewport.
     * @param    inTopX        The position to set the left corner of the window in x.
     * @param    inTopY        The position to set the left corner of the window in y.
     * @return   Returns .
     */
    void 
    createViewport(uint32 inNumVP,
                   int32 inWidth,
                   int32 inHeight,
                   int32 inTopX,
                   int32 inTopY) override;
    
    /**
     * @brief    Create the Vertex Shader.
     * @param    inFileName    The name of the file.
     * @param    inEntryPoint  The entry point in the shader.
     * @param    inShaderModel The model in the shader.
     */
    SharedPtr<BaseVertexShader>
    createVShaderFromFile(wString inFileName,
                          String inEntryPoint,
                          String inShaderModel) override;
    
    /**
     * @brief    Create the Pixel Shader.
     * @param    inFileName    The name of the file.
     * @param    inEntryPoint  The entry point in the shader.
     * @param    inShaderModel The model in the shader.
     */
    SharedPtr<BasePixelShader>
    createPShaderFromFile(wString inFileName,
                          String inEntryPoint,
                          String inShaderModel) override;
             
    /**
     * @brief    Create the Compute Shader.
     * @param    inFileName    The name of the file.
     * @param    inEntryPoint  The entry point in the shader.
     * @param    inShaderModel The model in the shader.
     */
    SharedPtr<BaseComputeShader>
    createCShaderFromFile(wString inFileName,
                          String inEntryPoint,
                          String inShaderModel) override;

    /**
     * @brief    The Shader to compile.
     * @param    inShaderRaw   The shader data in Raw.
     * @param    inEntryPoint  The entry point of the shader.
     */
    SharedPtr<BaseVertexShader>
    createVShaderFromMem(const char*inShaderRaw, 
                         String inEntryPoint) override;

    SharedPtr<BasePixelShader>
    createPShaderFromMem(const char* inShaderRaw,
                         String inEntryPoint);

    /**
     * @brief    Creates the Input Layout.
     * @param    inDesc        A vector with the inputLayout information.
     * @param    inShader      The vertex shader.
     * @return   Returns       The Input layout.
     */
    SharedPtr<InputLayout>
    createInputLayout(Vector<InputLayoutDesc> & inDesc, 
             SharedPtr<BaseShader> inShader) override;

    /**
     * @brief    Creates a buffer.
     * @param    inByteWidth   The byte Width for the buffer.
     * @param    inBindFlags   The bind flags for the buffer.
     * @param    inOffset      The offset of the buffer.
     * @param    inBufferData  The information to save into the buffer.
     * @return   Returns the buffer.     
     */
    SharedPtr<Buffer>
    createBuffer(size_T inByteWidth, 
                 int32 inBindFlags, 
                 void * inBufferData,
                 uint32 inStructureStride = 0,
                 uint32 inNumElements = 0,
                 GI_FORMAT::E = GI_FORMAT::kFORMAT_UNKNOWN) override;
    
    /**
     * @brief    Creates a SamplerState.
     * @param    inDesc        The descriptor of the sampler.
     */
    SharedPtr<SamplerState>
    createSampler(SamplerDesc inDesc) override;
    
    /**
     * @brief    Create a Rasterizer.
     */
    SharedPtr<BaseRasterizerState>
    createRasterizer(FILLMODE::E inFillMode,
                     CULLMODE::E inCullMode,
                     bool inClockwise,
                     bool inScissorEnable) override;

    /**
     * @brief    Create a Depth Stencil State.
     */
    SharedPtr<BaseDepthStencilState>
    createDepthState(bool inStencilEnable,
                     bool inDepthEnable, 
                     GI_COMPARATION_FUNC::E inCompar) override;

    /**
     * @brief    Create a new Blend State.
     * @param    inEnable      .
     * @param    inSource      .
     * @param    inDest        .
     * @param    inOp          .
     * @param    inAlphaSource .
     * @param    inAlphaDest   .
     * @param    inAlphaOp     .
     * @param    inBlendFactor .
     * @return   The blend state.
    */
    SharedPtr<BaseBlendState>
    createBlendState(bool inEnable, 
                     BLEND_TYPE::E inSource, 
                     BLEND_TYPE::E inDest,
                     BLEND_OP::E inOp,
                     BLEND_TYPE::E inAlplhaSource,
                     BLEND_TYPE::E inAlphaDest,
                     BLEND_OP::E inAlphaOp,
                     Vector4 inBlendFactor) override;

    /**
     * @brief    Present.     
     */
    void 
    show() override;
    
    /**
     * @brief    Set VertexBuffer.
     * @param    inBuffer      The buffer to set as vertex in the context.
     * @param    inStride      The stride for the buffer.     
     */
    void 
    setVertexBuffer(SharedPtr<Buffer> inBuffer,
                    uint32 inStride) override;
    
    /**
     * @brief    Set IndexBuffer.
     * @param    inBuffer      The buffer to set as index in the context.
     * @param    inFormat      The format of the data.     
     */
    void 
    setIndexBuffer(SharedPtr<Buffer> inBuffer,
                   GI_FORMAT::E inFormat) override;
    
    /**
     * @brief     Set PrimitiveTopology.
     * @param     inTopology   The type of topology to set.
     */
    void 
    setTopology(GI_PRIMITIVE_TOPOLOGY::E inTopotology) override;

    /**
     * @brief    Set the rasterizer State.
     * @param    inRaster      The rasterizer to set.     
     */
    void 
    setRasterizerState(SharedPtr<BaseRasterizerState> inRaster) override;

    /**
     * @brief    .
     * @param    .
     */
    void 
    setDepthState(SharedPtr<BaseDepthStencilState> inDepthState) override;
    
    /**
     * @brief   Set the Unordered Access Views.
     * @param   inUAV          The unordered Accesss View to set.
     */
    void
    setUAV(int32, Texture2D* inUAV) override;

    /**
     * @brief    Update Subresource.
     * @param    inBuffer      The buffer with the information.
     * @param    inData        The data to update.
     * @param    inPitch       Pitch of the data.     
     */
    void 
    updateSubresource(SharedPtr<Buffer> inBuffer,
                      void * inData, 
                      uint32 inPitch) override;
    
    /**
     * @brief    Update Texture.
     * @param    inTexture     The texture to update.
     * @param    inData        The data to udapte.
     * @param    inPitch       The pitch.
     * @param    inDepthPitch  The depth pitch.     
     */
    void 
    updateTexture(SharedPtr<Texture2D> inTexture,
                  const void * inData, 
                  uint32 inPitch, 
                  uint32 inDepthPitch) override;


    /**
     * @brief    Resizing the back buffer texture.
     * @param    inW           The width of the viewport.
     * @param    inH           The height of the viewport.
     */
    void
    resizeBackTexture(int32 inW, int32 inH) override;
    
    /**
     * @brief    Clear the Back Buffer.
     * @param    inColor       The color to set.     
     */
    void 
    clearBackTexture(float inColor[4]) override;
    
    /**
     * @brief    Clear Render Target View.
     * @param    inRTV         The render target view to clear.
     * @param    inColor       The color to set.     
     */
    void 
    clearRTV(SharedPtr<Texture2D> inRTV, float inColor[4]) override;
    
    /**
     * @brief    Clear Depth Stencil View.
     * @param    inDSV         The Depth stencil view to clear.     
     */
    void 
    clearDSV(SharedPtr<Texture2D> inDSV) override;

    /**
     * @brief    .
     * @param    inTopLeftX    .
     * @param    inTopLeftY    .
     * @param    inWidth       .
     * @param    inHeight      .
     * @param    inMinDepth    .
     * @param    inMaxDepth    .
     */
    void
    setViewport(int32 inTopLeftX,
                int32 inTopLeftY,
                int32 inWidth,
                int32 inHeight,
                float inMinDepth,
                float inMaxDepth) override;
    
    /**
     * @brief    Vertex Shader Set Shader.
     * @param    inVShader     The Vertex Shader to set.     
     */
    void 
    vsSetShader(SharedPtr<BaseVertexShader> inVShader = nullptr) override;
    
    /**
     * @brief    Vertex Shader Set Constant Buffer.
     * @param    inSlot        Index to begin setting constant buffers.
     * @param    inBuffer      The constant buffer to set.     
     */
    void 
    vsSetConstantBuffer(uint32 inSlot, 
                        SharedPtr<Buffer>inBuffer = nullptr) override;
    
    /**
     * @brief    Pixel Shader Set Shader.
     * @param    inPShader     The pixel Shader to set.     
     */
    void 
    psSetShader(SharedPtr<BasePixelShader> inPShader = nullptr) override;

    /**
     * @brief    Pixel Shader Set Shader.
     * @param    inPShader     The pixel Shader to set.     
     */
    void 
    csSetShader(SharedPtr<BaseShader> inCShader = nullptr) override;
    
    /**
     * @brief    Pixel Shader Set Constant Buffer.
     * @param    inSlot        The index to begin setting constant buffer.
     * @param    inBuffer      The constant buffer to set.     
     */
    void 
    psSetConstantBuffer(uint32 inSlot, 
                        SharedPtr<Buffer>) override;
    /**
     * @brief    Compute Shader Set Constant Buffer.
     * @param    inSlot        The index to begin setting constant buffer.
     * @param    inBuffer      The constant buffer to set.     
     */
    void 
    csSetConstantBuffer(uint32 inSlot, 
                        SharedPtr<Buffer> inBuffer) override;
    
    /**
     * @brief    Pixel Shadder Set Shader Resource.
     * @param    inSlot        The index to begin setting constant buffer.
     * @param    inTexture     The texture to set.     
     */
    void 
    psSetShaderResource(uint32 inSlot, 
                        SharedPtr<Texture2D> inTexture = nullptr) override;
    /**
     * @brief    Compute Shadder Set Shader Resource.
     * @param    inSlot        The index to begin setting constant buffer.
     * @param    inTexture     The texture to set.     
     */
    void 
    csSetShaderResource(uint32 inSlot, 
                        SharedPtr<Texture2D> inTexture = nullptr) override;
    
    /**
     * @brief    Pixel Shader Set Samplers.
     * @param    inSlot        The index to begin setting the sampler.
     * @param    inNumSamplers The number of samplers.
     * @param    inSampler     The sampler.     
     */
    void 
    psSetSamplerState(uint32 inSlot, 
                      uint32 inNumSamplers, 
                      SharedPtr<SamplerState> inSampler) override;
    
    /**
     * @brief    Compute Shader Set Samplers.
     * @param    inSlot        The index to begin setting the sampler.
     * @param    inNumSamplers The number of samplers.
     * @param    inSampler     The sampler.     
     */
    void 
    csSetSampler(uint32 inSlot, 
                 uint32 inNumSamplers, 
                 SharedPtr<SamplerState> inSampler) override;
    
    /** 
     * @brief    IA Set Input Layout.
     * @param    inInputLayout The input layout to set.     
     */
    void 
    aiSetInputLayout(SharedPtr<InputLayout> inInputLayout) override;
    
    /** 
     * @brief    OM Set Render Targets.
     * @param    inRT          The Render Target texture.
     * @param    inDS          The Depth Stencil texture.     
     */
    void 
    omSetRenderTarget(Vector<SharedPtr<Texture2D>> inRT,
                      SharedPtr<Texture2D> inDS = nullptr) override;

    void
    unbindRenderTarget() override;

    /** 
     * @brief    Set Blend State.
     * @param    inBlendState  Pointer to a blend-state interface. NULL for a default.
     * @param    inBlendFactor Array of blend factors, one for each RGBA component.
     * @param    inSampleMask  32-bit sample coverage. The default value is 0xffffffff.     
     */
    void 
    omSetBlendState(SharedPtr<BaseBlendState> inBlendState) override;
    
    /** 
     * @brief    Set Blend State.
     * @param    inDepthState  Pointer to a depth-state interface.
     * @param    inStencilRef  The reference to the stencil.     
     */
    void 
    omSetDepthStencilState(SharedPtr<BaseDepthStencilState> inDepthState) override;
     
    /**
     * @brief    Set the Rasterizer.
     * @param    inRaster      The rasterizer state to set.
     */
    void
    rsSetRasterizerState(SharedPtr<BaseRasterizerState> inRaster) override;

    /**
     * @brief    Get the scissor Rects.
     * @param    inNumRects    The num of regts.
     * @return   Returns the scissor Reacts as a Vector4.
     */
    Vector4 *
    rsGetScissorRects(uint32 inNumRects) override;

    /**
     * @brief    Get the Viewport.
     * @param    inNumVP       The number of Viewports.
     * @return   Returns the Viewport as a void *.
     */
    void *
    rsGetViewports(uint32 inNumVP) override;

    /**
     * @brief    Get the RasterState.
     * @return   Returns the RasterState as a Shared Ptr.
     */
    SharedPtr<BaseRasterizerState>
    rsGetState() override;

    /**
     * @brief    Get the blend state.
     * @return   Returns the  blendState as a Shared Ptr.
     */
    SharedPtr<BaseBlendState>
    omGetBlendState() override;

    /**
     * @brief    Get the depth stencil state.
     * @return   Returns the depth stencil state as a Shared Ptr.
     */
    SharedPtr<BaseDepthStencilState>
    omGetDepthStencilState() override;

    /**
     * @brief    Get the shader Resource.
     * @param    inStartSlot   The start slot of the memory.
     * @param    inNumViews    The number of views of the resource.
     * @return   Returns the Shader Resource as a Shared Ptr.
     */
    SharedPtr<Texture2D>
    psGetShaderResources(uint32 inStartSlot, 
                         uint32 inNumViews) override;

    /**
     * @brief    Get the sampler.
     * @param    inStartSlot   The start slot of the memory.
     * @param    inNumSamplers The number of samplers.
     * @return   Returns the Sampler as a Shared Ptr.
     */
    SharedPtr<SamplerState>
    psGetSamplers(uint32 inStartSlot, 
                  uint32 inNumSamplers) override;

    /**
     * @brief    Get the Pixel Shader.
     * @return   Returns the Pixel Shader as a Shared Ptr.
     */
    SharedPtr<BasePixelShader>
    psGetShader() override;

    /**
     * @brief    Get the Vertex Shader 
     * @return   Returns the Vertex Shader as a Shared Ptr.
     */
    SharedPtr<BaseVertexShader>
    vsGetShader() override;

    /**
     * @brief    Get the constant buffer .
     * @param    inStartSlot   The start slot of the memory.
     * @param    inNumBuffers  The number of buffers.
     * @return   Returns the constant buffer as a Shared Ptr.
     */
    SharedPtr<Buffer>
    vsGetConstantBuffers(int32 inStartSlot, 
                         int32 inNumBuffers) override;

    /**
     * @brief   Get the topology setted.
     * @return   Returns the topology.
     */
    GI_PRIMITIVE_TOPOLOGY::E
    iaGetPrimitiveTopology() override;

    /**
     * @brief    Get index Buffer.
     * @return   Returns the Index Buffer as a Shared Ptr.
     */
    SharedPtr<Buffer>
    iaGetIndexBuffer() override;

    /**
     * @brief    Get the Vertex Buffer.
     * @param    inStartSlot   The start Slot for the memory. 
     * @param    inStride      The stride for the Buffer.
     * @param    inOffset      The offset for the memory.
     * @return   Returns the Vertex Buffer as a Shared Ptr.
     */
    SharedPtr<Buffer>
    iaGetVertexBuffer(uint32 inStartSlot, 
                      uint32 inStride, 
                      uint32 inOffset) override;
    
    /**
     * @brief    Get the Input Layout.
     * @return   Returns the input layout as a Shared Ptr.
     */
    SharedPtr<InputLayout>
    iaGetInputLayout() override;

    /**
     * @brief    Set the scissor Rects.
     * @param    inNumRects    The number of rects.
     * @param    inRects       The rects to set.
     */
    void 
    rsSetScissorRects(uint32 inNumRects, Vector4* inRects) override;
    
    /** 
     * @brief    Draw Index.
     * @param    inNumIndexes       The number of idexes to draw.
     * @param    inStartLoc    the start location to draw.     
     */
    void 
    drawIndexed(size_T inNumIndexes, 
                uint32 inStartLoc) override;

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
     */
    SharedPtr<Texture2D>
    getDefaultRenderTarget() { 
      return m_backBuffer; 
    }
  
    /**
     * @brief    Gets the default Depth Stencil.
     * @return   Returns the Depth Stencil View texutre.     
     */
    SharedPtr<Texture2D>
    getDefaultDephtStencil() { 
      return m_defaultDSV;
    }
    
    void * 
    getDevice() override {
      return m_device;
    }
    
    void * 
    getDeviceContext() override {
      return m_devContext;
    } 
  
    SharedPtr<Texture2D>
    getViewportTex() override {
      return m_viewportTexture;
    }


   private:
    //Texture for render in the UI.
    SharedPtr<Texture2DDX> m_viewportTexture = nullptr;
  
    ///Reference to the device
    ID3D11Device * m_device;
  
    ///Reference to the device Context
    ID3D11DeviceContext * m_devContext;
  
    ///Reference to the Swap Chain
    IDXGISwapChain * m_swapChain;
  
    ///Reference to the default Render Target
    SharedPtr<Texture2DDX> m_backBuffer = nullptr;

    ///Reference to the default Depth Stencil
    SharedPtr<Texture2DDX> m_defaultDSV = nullptr;
   

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