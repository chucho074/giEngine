/**
 * @file     giBaseGraphicsAPI.h
 * @author   Jesús Alberto Del Moral Cupil
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
  class CTexture2D;
  class CBaseShader;
  class CViewPort;
  class BaseShader;
  class CBuffer;
  class CInputLayout;
  class CSampler;
  class CImageLoader;

  struct TextureDesc;
  struct DepthStencilViewDesc;
  struct InputLayoutDesc;
  struct SamplerDesc;
}

/**
 * @class    CBaseGraphicsAPI.
 * @brief    Manage the graphics APIs.
 * @bug      No known Bugs.
 */
namespace giEngineSDK {
  class CBaseGraphicsAPI : public Module<CBaseGraphicsAPI> 
  {
   public:
  
     ///Default Constructor.
     CBaseGraphicsAPI() = default;
     
     ///Destructor.
     ~CBaseGraphicsAPI() = default;
     
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
     init(void * inWindow, 
     /***/int inWidth, 
     /***/int inHeight) {};
     
     /**
      * @brief    In Charge to create the device and the swap chain.
      * @param    inWindow   The window object.
      * @param    inWidth    The width of the screen.
      * @param    inHeight   The height of the screen.
      * @bug      No known Bugs.
      */
     virtual bool 
     createDeviceAndSwpaChain(void * inWindow, 
     /***********************/int inWidth, 
     /***********************/int inHeight) { return false; };
          
     /**
      * @brief    Creates the texture in the Device.
      * @param    inWidth        The width of the texture.
      * @param    inHeigh        The heigh of the texture.
      * @param    inMipLevels    The mip levels.
      * @param    inFormat       The format of the texture.
      * @param    inBindFlags    The bind flags of the texture.
      * @bug      No known Bugs.
      */
     virtual CTexture2D * 
     createTex2D(int inWidth,
     /**********/int inHeigh,
     /**********/int inMipLevels,
     /**********/GI_FORMAT::E inFormat,
     /**********/int inBindFlags) { return nullptr; };

     /**
      * @brief    Creates the View Port in the Device.
      * @param    inWidth     The width of the viewport.
      * @param    inHeight    The height of the viewport.
      * @return   Returns .
      * @bug      No known Bugs.
      */
     virtual CViewPort * 
     createVP(int inWidth, 
     /*******/int inHeight){ return nullptr; };
     
     /**
      * @brief    Sets the View Port in the DeviceContext.
      * @param    inVP   A reference of the viewport.
      * @bug      No known Bugs.
      */
     virtual void 
     setVP(CViewPort &inVP){};
     
     /**
      * @brief    Create the Vertex Shader.
      * @bug      No known Bugs.
      */
     virtual CBaseShader * 
     createVS(wString inFileName,
     /*******/lpcstr inEntryPoint,
     /*******/lpcstr inShaderModel) { return nullptr;};
     
     /**
      * @brief    Create the Pixel Shader
      * @bug      No known Bugs.
      */
     virtual CBaseShader * 
     createPS(wString inFileName,
     /*******/lpcstr inEntryPoint,
     /*******/lpcstr inShaderModel){ return nullptr; };

     /**
      * @brief    Creates the Input Layout.
      * @param    inDesc    A vector with the inputLayout information.
      * @param    inShader  The vertex shader.
      * @return   Returns the Input layout.
      * @bug      No known Bugs.
      */
     virtual CInputLayout * 
     createIL(Vector<InputLayoutDesc> & inDesc, 
     /*******/BaseShader * inShader) { return nullptr; };

     /**
      * @brief    Creates a buffer.
      * @param    inByteWidth   The byte Width for the buffer.
      * @param    inBindFlags   The bind flags for the buffer.
      * @param    inOffset      The offset of the buffer.
      * @param    inBufferData  The information to save into the buffer.
      * @return   Returns the buffer.
      * @bug      No known Bugs.
      */
     virtual CBuffer * 
     createBuffer(unsigned int inByteWidth, 
     /***********/unsigned int inBindFlags, 
     /***********/unsigned int inOffset, 
     /***********/void * inBufferData) { return nullptr; };
     
     /**
      * @brief    Creates a Sampler.
      * @param    inDesc   The descriptor of the sampler.
      * @bug      No known Bugs.
      */
     virtual CSampler * 
     createSampler(SamplerDesc inDesc) { return nullptr; };
     
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
     setVertexBuffer(CBuffer * inBuffer, 
     /**************/unsigned int inStride) {};
     
     /**
      * @brief    Set IndexBuffer.
      * @param    inBuffer   The buffer to set as index in the context.
      * @param    inFormat   The format of the data.
      * @bug      No known Bugs.
      */
     virtual void 
     setIndexBuffer(CBuffer * inBuffer, 
     /*************/GI_FORMAT::E inFormat) {};
     
     /**
      * @brief     Set PrimitiveTopology.
      * @param     inTopology   The type of topology to set.
      * @bug       No known Bugs.
      */
     virtual void 
     setTopology(GI_PRIMITIVE_TOPOLOGY::E inTopotology) {};
     
     /**
      * @brief    Update Subresource.
      * @param    inBuffer   The buffer with the information.
      * @param    inData     The data to update.
      * @param    inPitch    Pitch of the data.
      * @bug      No known Bugs.
      */
     virtual void 
     updateSubresource(CBuffer * inBuffer, 
     /****************/void * inData, 
     /****************/unsigned int inPitch) {};
     
     /**
      * @brief    Update Texture.
      * @param    inTexture      The texture to update.
      * @param    inData         The data to udapte.
      * @param    inPitch        The pitch.
      * @param    inDepthPitch   The depth pitch.
      * @bug      No known Bugs.
      */
     virtual void 
     updateTexture(CTexture2D * inTexture, 
     /************/const void * inData, 
     /************/unsigned int inPitch, 
     /************/unsigned int inDepthPitch) {};
     
     /**
      * @brief    Clear Render Target View.
      * @param    inRTV      The render target view to clear.
      * @param    inColor    The color to set.
      * @bug      No known Bugs.
      */
     virtual void 
     clearRTV(CTexture2D* inRTV, float inColor[4]) {};
     
     /**
      * @brief    Clear Depth Stencil View.
      * @param    inDSV   The Depth stencil view to clear.
      * @bug      No known Bugs.
      */
     virtual void 
     clearDSV(CTexture2D* inDSV) {};
     
     /**
      * @brief    Vertex Shader Set Shader.
      * @param    inVShader   The Vertex Shader to set.
      * @bug      No known Bugs.
      */
     virtual void 
     vsSetShader(BaseShader * inVShader = nullptr) {};
     
     /**
      * @brief    Vertex Shader Set Constant Buffer.
      * @param    inSlot     Index to begin setting constant buffers.
      * @param    inBuffer   The constant buffer to set.
      * @bug      No known Bugs.
      */
     virtual void 
     vsSetConstantBuffer(unsigned int inSlot, 
     /******************/CBuffer * inBuffer = nullptr) {};
     
     /**
      * @brief    Pixel Shader Set Shader.
      * @param    inPShader    The pixel Shader to set.
      * @bug      No known Bugs.
      */
     virtual void 
     psSetShader(BaseShader * inPShader = nullptr) {};
     
     /**
      * @brief    Pixel Shader Set Constant Buffer.
      * @param    inSlot      The index to begin setting constant buffer.
      * @param    inBuffer    The constant buffer to set.
      * @bug      No known Bugs.
      */
     virtual void 
     psSetConstantBuffer(unsigned int inSlot, 
     /******************/CBuffer * inBuffer) {};
     
     /**
      * @brief    Pixel Shadder Set Shader Resource.
      * @param    inSlot      The index to begin setting constant buffer.
      * @param    inTexture   The texture to set.
      * @bug      No known Bugs.
      */
     virtual void 
     psSetShaderResource(unsigned int inSlot, 
     /******************/CTexture2D * inTexture = nullptr) {};
     
     /**
      * @brief    Pixel Shader Set Samplers.
      * @param    inSlot          The index to begin setting the sampler.
      * @param    inNumSamplers   The number of samplers.
      * @param    inSampler       The sampler.
      * @bug      No known Bugs.
      */
     virtual void 
     psSetSampler(unsigned int inSlot, 
     /***********/unsigned int inNumSamplers, 
     /***********/CSampler * inSampler) {};
     
     /** 
      * @brief    IA Set Input Layout.
      * @param    inInputLayout   The input layout to set.
      * @bug      No known Bugs.
      */
     virtual void 
     aiSetInputLayout(CInputLayout * inInputLayout) {};
     
     /** 
      * @brief    OM Set Render Targets.
      * @param    inRT    The Render Target texture.
      * @param    inDS    The Depth Stencil texture.
      * @bug      No known Bugs.
      */
     virtual void 
     omSetRenderTarget(CTexture2D * inRT = nullptr, 
     /****************/CTexture2D * inDS = nullptr) {};
     
     /** 
      * @brief    Draw Index.
      * @param    inNumIndexes       The number of idexes to draw.
      * @param    inStartLocation    the start location to draw.
      * @bug      No known Bugs.
      */
     virtual void 
     draw(unsigned int inNumIndexes, 
     /***/unsigned int inStartLocation) {};
     
     /**
      * @brief    Gets the default Render Target.
      * @return   Returns the back Buffer texture.
      */
     virtual CTexture2D * 
     getDefaultRenderTarget() { return nullptr; };
     
     /**
      * @brief    Gets the default Depth Stencil.
      * @return   Returns the Depth Stencil View texutre;
      */
     virtual CTexture2D * 
     getDefaultDephtStencil() { return nullptr; };
  
     /**
      * @brief 
      * @param inAPI 
      */
     void
     setObject(CBaseGraphicsAPI * inAPI) {
       CBaseGraphicsAPI::_instance() = inAPI;
     }
  };
  
  GI_CORE_EXPORT CBaseGraphicsAPI& 
  g_GraphicsAPI();

  //For load the DLL
  using funCreateGraphicsAPI = CBaseGraphicsAPI * (*)();
}