/**
 * @file     giBaseGraphicsAPI.h
 * @author   Jes�s Alberto Del Moral Cupil
 * @e        idv18c.jmoral@uartesdigitales.edu.mx
 * @date     10/03/2021
 * @brief    Management of the graphics APIs.
 * @bug      No known Bugs.
 */

/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include <giModule.h>
#include "giSampler.h"

///Forward declarations
namespace giEngineSDK {
  class Texture2D;
  class BaseShader;
  class BaseVertexShader;
  class BasePixelShader;
  class BaseComputeShader;
  class BaseShader;
  class Buffer;
  class InputLayout;
  class Sampler;
  class Rasterizer;
  class DepthState;
  class BlendState;

  struct TextureDesc;
  struct DepthStencilViewDesc;
  struct InputLayoutDesc;
  struct SamplerDesc;

  namespace FILLMODE {
    enum E;
  }

  namespace CULLMODE {
    enum E;
  }
}

/**
 * @class    GraphicsAPI.
 * @brief    Manage the graphics APIs.
 * @bug      No known Bugs.
 */
namespace giEngineSDK {
  class GraphicsAPI : public Module<GraphicsAPI>
  {
   public:
    
    ///Default Constructor.
    GraphicsAPI() = default;
    
    ///Destructor.
    ~GraphicsAPI() = default;
    
    /**
     * @brief    Prepare the Module.
     * @bug      No known Bugs.
     */
    void 
    onStartUp() override {};
    
    /**
     * @brief    Clear the Module.
     * @bug      No known Bugs.
     */
    void 
    onShutDown() override {};
    
    /**
     * @brief    In charge of the creation of the device & SwapChain
     * @param    inWindow   The window object.
     * @param    inWidth    The width of the screen.
     * @param    inHeight   The height of the screen.
     * @bug      No known Bugs.
     */
    virtual void 
    init(void *) {};
    
    /**
     * @brief    In Charge to create the device and the swap chain.
     * @param    inWindow   The window object.
     * @param    inWidth    The width of the screen.
     * @param    inHeight   The height of the screen.
     * @bug      No known Bugs.
     */
    virtual bool 
    createDeviceAndSwpaChain(void *) { 
      return false;  
    };
         
    /**
     * @brief    Creates the texture in the Device.
     * @param    inWidth        The width of the texture.
     * @param    inHeigh        The heigh of the texture.
     * @param    inMipLevels    The mip levels.
     * @param    inFormat       The format of the texture.
     * @param    inBindFlags    The bind flags of the texture.
     * @bug      No known Bugs.
     */
    virtual Texture2D * 
    createTex2D(int32,
                int32,
                int32,
                GI_FORMAT::E,
                int32) { 
      return nullptr; 
    };

    /**
     * @brief    Creates the View Port in the Device.
     * @param    inWidth     The width of the viewport.
     * @param    inHeight    The height of the viewport.
     * @param    inTopX      The position to set the left corner of the window in x.
     * @param    inTopY      The position to set the left corner of the window in y.
     * @return   Returns .
     * @bug      No known Bugs.
     */
    virtual void 
    createVP(uint32,
             int32,
             int32,
             int32,
             int32) {};
    
    /**
     * @brief    Create the Vertex Shader.
     * @param    inFileName    The name of the file.
     * @param    inEntryPoint  The entry point in the shader.
     * @param    inShaderModel The model in the shader.
     * @bug      No known Bugs.
     */
    virtual BaseVertexShader * 
    createVS(wString,
             String,
             String) { 

      return nullptr;
    };
    
    /**
     * @brief    Create the Pixel Shader.
     * @param    inFileName    The name of the file.
     * @param    inEntryPoint  The entry point in the shader.
     * @param    inShaderModel The model in the shader.
     * @bug      No known Bugs.
     */
    virtual BasePixelShader * 
    createPS(wString,
             String,
             String){ 
      return nullptr; 
    };

    /**
     * @brief    Create the Pixel Shader.
     * @param    inFileName    The name of the file.
     * @param    inEntryPoint  The entry point in the shader.
     * @param    inShaderModel The model in the shader.
     * @bug      No known Bugs.
     */
    virtual BaseComputeShader * 
    createCS(wString,
             String,
             String){ 
      return nullptr; 
    };

    /**
     * @brief    Creates the Input Layout.
     * @param    inDesc    A vector with the inputLayout information.
     * @param    inShader  The vertex shader.
     * @return   Returns   The Input layout.
     * @bug      No known Bugs.
     */
    virtual InputLayout * 
    createIL(Vector<InputLayoutDesc> &, 
             BaseShader *) { 
      return nullptr; 
    };

    /**
     * @brief    Creates a buffer.
     * @param    inByteWidth   The byte Width for the buffer.
     * @param    inBindFlags   The bind flags for the buffer.
     * @param    inOffset      The offset of the buffer.
     * @param    inBufferData  The information to save into the buffer.
     * @return   Returns the buffer.
     * @bug      No known Bugs.
     */
    virtual Buffer * 
    createBuffer(size_T, 
                 int32, 
                 void *,
                 uint32 = 0,
                 uint32 = 0,
                 GI_FORMAT::E = GI_FORMAT::kFORMAT_UNKNOWN) { 
       return nullptr; 
     };
    
    /**
     * @brief    Creates a Sampler.
     * @param    inDesc   The descriptor of the sampler.
     * @bug      No known Bugs.
     */
    virtual Sampler * 
    createSampler(SamplerDesc) { 
      return nullptr; 
    };

    /**
     * @brief    Creates a Rasterizer.
     * @param    inFillMode  The fill mode for the raster.
     * @param    inCullMode  The cull mode for the raster.
     * @param    inClockwise If the raster is in clockwise.
     */
    virtual Rasterizer *
    createRasterizer(FILLMODE::E inFillMode,
                     CULLMODE::E inCullMode,
                     bool inClockwise) {
      return nullptr;
    }
    
    /**
     * @brief    Creates a DepthState.
     * @param    inStencilEnable  The Stencil for the DepthState.
     * @param    inDepthEnable    The Depth  for the DepthState.
     */
    virtual DepthState *
    createDepthState(bool inStencilEnable,
                     bool inDepthEnable) {
      return nullptr;
    }
        
    /**
     * @brief    Present.
     * @bug      No known Bugs.
     */
    virtual void 
    show() {};
    
    /**
     * @brief    Set VertexBuffer.
     * @param    inBuffer   The buffer to set as vertex in the context.
     * @param    inStride   The stride for the buffer.
     * @bug      No known Bugs.
     */
    virtual void 
    setVertexBuffer(Buffer *, 
                    uint32 ) {};
    
    /**
     * @brief    Set IndexBuffer.
     * @param    inBuffer   The buffer to set as index in the context.
     * @param    inFormat   The format of the data.
     * @bug      No known Bugs.
     */
    virtual void 
    setIndexBuffer(Buffer *, 
                   GI_FORMAT::E) {};
    
    /**
     * @brief     Set PrimitiveTopology.
     * @param     inTopology   The type of topology to set.
     * @bug       No known Bugs.
     */
    virtual void 
    setTopology(GI_PRIMITIVE_TOPOLOGY::E) {};

    /**
     * @brief     Set Unordered Access View.
     * @param     inUAV     The Unordered Access View to set.
     * @bug       No known Bugs.
     */
     virtual void
     setUAV(int32, Texture2D*) {};
    
    /**
     * @brief    Update Subresource.
     * @param    inBuffer   The buffer with the information.
     * @param    inData     The data to update.
     * @param    inPitch    Pitch of the data.
     * @bug      No known Bugs.
     */
    virtual void 
    updateSubresource(Buffer *, 
                      void *, 
                      uint32) {};
    
    /**
     * @brief    Update Texture.
     * @param    inTexture      The texture to update.
     * @param    inData         The data to udapte.
     * @param    inPitch        The pitch.
     * @param    inDepthPitch   The depth pitch.
     * @bug      No known Bugs.
     */
    virtual void 
    updateTexture(Texture2D *, 
                  const void *, 
                  uint32, 
                  uint32) {};
    
    /**
     * @brief    Clear the Back Buffer.
     * @param    inColor    The color to set.
     * @bug      No known Bugs.
     */
    virtual void 
    clearBackTexture(float[4]) {};
    
    /**
     * @brief    Clear Render Target View.
     * @param    inRTV      The render target view to clear.
     * @param    inColor    The color to set.
     * @bug      No known Bugs.
     */
    virtual void 
    clearRTV(Texture2D*, float [4]) {};
    
    /**
     * @brief    Clear Depth Stencil View.
     * @param    inDSV   The Depth stencil view to clear.
     * @bug      No known Bugs.
     */
    virtual void 
    clearDSV(Texture2D*) {};
    
    /**
     * @brief    Vertex Shader Set Shader.
     * @param    inVShader   The Vertex Shader to set.
     * @bug      No known Bugs.
     */
    virtual void 
    vsSetShader(BaseVertexShader * = nullptr) {};
    
    /**
     * @brief    Vertex Shader Set Constant Buffer.
     * @param    inSlot     Index to begin setting constant buffers.
     * @param    inBuffer   The constant buffer to set.
     * @bug      No known Bugs.
     */
    virtual void 
    vsSetConstantBuffer(uint32, 
                        Buffer * = nullptr) {};
    
    /**
     * @brief    Pixel Shader Set Shader.
     * @param    inPShader    The pixel Shader to set.
     * @bug      No known Bugs.
     */
    virtual void 
    psSetShader(BaseShader * = nullptr) {};

    /**
     * @brief    Pixel Shader Set Shader.
     * @param    inPShader    The pixel Shader to set.
     * @bug      No known Bugs.
     */
    virtual void 
    csSetShader(BaseShader * = nullptr) {};
    
    /**
     * @brief    Pixel Shader Set Constant Buffer.
     * @param    inSlot      The index to begin setting constant buffer.
     * @param    inBuffer    The constant buffer to set.
     * @bug      No known Bugs.
     */
    virtual void 
    psSetConstantBuffer(uint32, 
                        Buffer *) {};
    
    /**
     * @brief    Compute Shader Set Constant Buffer.
     * @param    inSlot      The index to begin setting constant buffer.
     * @param    inBuffer    The constant buffer to set.
     * @bug      No known Bugs.
     */
    virtual void 
    csSetConstantBuffer(uint32, 
                        Buffer *) {};
    
    /**
     * @brief    Pixel Shadder Set Shader Resource.
     * @param    inSlot      The index to begin setting constant buffer.
     * @param    inTexture   The texture to set.
     * @bug      No known Bugs.
     */
    virtual void 
    psSetShaderResource(uint32, 
                        Texture2D * = nullptr) {};
    /**
     * @brief    Compute Shadder Set Shader Resource.
     * @param    inSlot      The index to begin setting constant buffer.
     * @param    inTexture   The texture to set.
     * @bug      No known Bugs.
     */
    virtual void 
    csSetShaderResource(uint32, 
                        Texture2D * = nullptr) {};
    
    /**
     * @brief    Pixel Shader Set Samplers.
     * @param    inSlot          The index to begin setting the sampler.
     * @param    inNumSamplers   The number of samplers.
     * @param    inSampler       The sampler.
     * @bug      No known Bugs.
     */
    virtual void 
    psSetSampler(uint32, 
                 uint32, 
                 Sampler *) {};

    /**
     * @brief    Compute Shader Set Samplers.
     * @param    inSlot          The index to begin setting the sampler.
     * @param    inNumSamplers   The number of samplers.
     * @param    inSampler       The sampler.
     * @bug      No known Bugs.
     */
    virtual void 
    csSetSampler(uint32, 
                 uint32, 
                 Sampler *) {};
    
    /** 
     * @brief    IA Set Input Layout.
     * @param    inInputLayout   The input layout to set.
     * @bug      No known Bugs.
     */
    virtual void 
    aiSetInputLayout(InputLayout *) {};
    
    /** 
     * @brief    Set Render Targets.
     * @param    inRT    The Render Target texture.
     * @param    inDS    The Depth Stencil texture.
     * @bug      No known Bugs.
     */
    virtual void 
    omSetRenderTarget(Vector<Texture2D *>, 
                      Texture2D * = nullptr) {};
    /**
     * @brief
     */
    virtual void
    unbindRenderTarget() {};


    /** 
     * @brief    Set Blend State.
     * @param    inBlendState   Pointer to a blend-state interface. NULL for a default.
     * @param    inBlendFactor  Array of blend factors, one for each RGBA component.
     * @param    inSampleMask   32-bit sample coverage. The default value is 0xffffffff.
     * @bug      No known Bugs.
     */
    virtual void 
    omSetBlendState(BlendState *, 
                    const float[4], 
                    uint32 = 0xffffffff) {};
    
    /** 
     * @brief    Draw Index.
     * @param    inNumIndexes       The number of idexes to draw.
     * @param    inStartLocation    the start location to draw.
     * @bug      No known Bugs.
     */
    virtual void 
    drawIndexed(size_T, 
                uint32) {};

    /**
     * @brief    Dispatch for Compute Shaders.
     * @param    inThreadGroupX  The number of groups dispatched in the x direction.
     * @param    inThreadGroupY  The number of groups dispatched in the y direction.
     * @param    inThreadGroupZ  The number of groups dispatched in the z direction.
     */
     virtual void
     dispatch(uint32, uint32, uint32) {}
         
    /**
     * @brief    Gets the default Render Target.
     * @return   Returns the back Buffer texture.
     */
    virtual Texture2D * 
    getDefaultRenderTarget() { 
      return nullptr; 
    };
    
    /**
     * @brief    Gets the default Depth Stencil.
     * @return   Returns the Depth Stencil View texutre.
     */
    virtual Texture2D*
    getDefaultDephtStencil() { 
      return nullptr; 
    };

    /**
     * @brief    Reads a texture form a file.
     * @param    inString     .
     * @param    inDirectory  The directory of the texture to read.
     * @return   Returns the texture readed from a file.
     */
    virtual Texture2D *
    TextureFromFile(String inString, String inDirectory) { 
      return nullptr;
    };
  
    /**
     * @brief    Set the object of the Graphics API.
     * @param    inAPI   The api to set.
     */
   /* void
    setObject(GraphicsAPI * inAPI) {
       GraphicsAPI::_instance() = inAPI;
    }*/
  };
  
  GI_CORE_EXPORT GraphicsAPI& 
  g_graphicsAPI();

  //For load the DLL
  using funCreateGraphicsAPI = GraphicsAPI * (*)();
}