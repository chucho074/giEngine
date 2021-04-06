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
#include <vector>
#include <string>

#include <windows.h>



///Forward declarations
class CTexture2D;
class CViewPort;
class CVertexShader;
class CPixelShader;
class CBuffer;
class CInputLayout;
class CSampler;
class CImageLoader;

struct TextureDesc;
struct DepthStencilViewDesc;
struct InputLayoutDesc;
struct SamplerDesc;


/**
 * @class    CBaseGraphicsAPI.
 * @brief    Manage the graphics APIs.
 * @bug      No known Bugs.
 */
namespace giEngineSDK {
  class CBaseGraphicsAPI : public Module<CBaseGraphicsAPI> {
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
      * @bug      No known Bugs.
      */
     virtual void 
     init(void * inWindow, 
     /***/int inWidth, 
     /***/int inHeight) = 0;
     
     /**
      * @brief    In Charge to create the device and the swap chain.
      * @bug      No known Bugs.
      */
     virtual bool 
     createDeviceAndSwpaChain(void * inWindow, 
     /***********************/int inWidth, 
     /***********************/int inHeight) = 0;
     
     /**
      * @brief    Creates the texture in the Device.
      * @bug      No known Bugs.
      */
     virtual void * 
     createTex2D(int inWidth,
     /**********/int inHeigh,
     /**********/int inMipLevels,
     /**********/DXGI_FORMAT inFormat,
     /**********/int inBindFlags) = 0;
     
     /**
      * @brief    Creates the View Port in the Device.
      * @bug      No known Bugs.
      */
     virtual void * 
     createVP(int inWidth, 
     /*******/int inHeight) = 0;
     
     /**
      * @brief    Sets the View Port in the DeviceContext.
      * @bug      No known Bugs.
      */
     virtual void 
     setVP(CViewPort &inVP) = 0;
     
     /**
      * @brief    Create the Vertex Shader.
      * @bug      No known Bugs.
      */
     virtual void * 
     createVS(WCHAR* inFileName,
     /*******/LPCSTR inEntryPoint,
     /*******/LPCSTR inShaderModel) = 0;
     
     /**
      * @brief    Create the Pixel Shader
      * @bug      No known Bugs.
      */
     virtual void * 
     createPS(WCHAR* inFileName,
     /*******/LPCSTR inEntryPoint,
     /*******/LPCSTR inShaderModel) = 0;
     
     /**
      * @brief    Creates the Input Layout.
      * @bug      No known Bugs.
      */
     virtual void * 
     createIL(std::vector<InputLayoutDesc> & inDesc, 
     /*******/CVertexShader * inShader) = 0;
     
     /**
      * @brief    Creates a buffer.
      * @bug      No known Bugs.
      */
     virtual void * 
     createBuffer(unsigned int inByteWidth, 
     /***********/unsigned int inBindFlags, 
     /***********/unsigned int inOffset, 
     /***********/void * inBufferData) = 0;
     
     /**
      * @brief    Creates a Sampler.
      * @bug      No known Bugs.
      */
     virtual void * 
     createSampler(SamplerDesc inDesc) = 0;
     
     /**
      * @brief    Present.
      * @bug      No known Bugs.
      */
     virtual void 
     show() = 0;
     
     /**
      * @brief    Set VertexBuffer.
      * @bug      No known Bugs.
      */
     virtual void 
     setVertexBuffer(CBuffer * inBuffer, 
     /**************/unsigned int inStride) = 0;
     
     /**
      * @brief    Set IndexBuffer.
      * @bug      No known Bugs.
      */
     virtual void 
     setIndexBuffer(CBuffer * inBuffer, 
     /*************/DXGI_FORMAT inFormat) = 0;
     
     /**
      * @brieft    Set PrimitiveTopology.
      * @bug      No known Bugs.
      */
     virtual void 
     setTopology(D3D_PRIMITIVE_TOPOLOGY inTopotology) = 0;
     
     /**
      * @brief    Update Subresource.
      * @bug      No known Bugs.
      */
     virtual void 
     updateSubresource(CBuffer * inBuffer, 
     /****************/void * inData, 
     /****************/unsigned int inPitch) = 0;
     
     /**
      * @brief    Update Texture.
      * @bug      No known Bugs.
      */
     virtual void 
     updateTexture(CTexture2D * inTexture, 
     /************/const void * inData, 
     /************/unsigned int inPitch, 
     /************/unsigned int inDepthPitch) = 0;
     
     /**
      * @brief    Clear Render Target View.
      * @bug      No known Bugs.
      */
     virtual void 
     clearRTV(CTexture2D* inRTV, float inColor[4]) = 0;
     
     /**
      * @brief    Clear Depth Stencil View.
      * @bug      No known Bugs.
      */
     virtual void 
     clearDSV(CTexture2D* inDSV) = 0;
     
     /**
      * @brief    Vertex Shader Set Shader.
      * @bug      No known Bugs.
      */
     virtual void 
     vsSetShader(CVertexShader * inVShader = nullptr) = 0;
     
     /**
      * @brief    Vertex Shader Set Constant Buffer.
      * @bug      No known Bugs.
      */
     virtual void 
     vsSetConstantBuffer(unsigned int inSlot, 
     /******************/CBuffer * inBuffer = nullptr) = 0;
     
     /**
      * @brief    Pixel Shader Set Shader.
      * @bug      No known Bugs.
      */
     virtual void 
     psSetShader(CPixelShader * inPShader = nullptr) = 0;
     
     /**
      * @brief    Pixel Shader Set Constant Buffer.
      * @bug      No known Bugs.
      */
     virtual void 
     psSetConstantBuffer(unsigned int inSlot, 
     /******************/CBuffer * inBuffer) = 0;
     
     /**
      * @brief    Pixel Shadder Set Shader Resource.
      * @bug      No known Bugs.
      */
     virtual void 
     psSetShaderResource(unsigned int inSlot, 
     /******************/CTexture2D * inTexture = nullptr) = 0;
     
     /**
      * @brief    Pixel Shader Set Samplers.
      * @bug      No known Bugs.
      */
     virtual void 
     psSetSampler(unsigned int inSlot, 
     /***********/unsigned int inNumSamplers, 
     /***********/CSampler * inSampler) = 0;
     
     /** 
      * @brief    IA Set Input Layout.
      * @bug      No known Bugs.
      */
     virtual void 
     aiSetInputLayout(CInputLayout * inInputLayout) = 0;
     
     /** 
      * @brief    OM Set Render Targets.
      * @bug      No known Bugs.
      */
     virtual void 
     omSetRenderTarget(CTexture2D * inRT = nullptr, 
     /****************/CTexture2D * inDS = nullptr) = 0;
     
     /** 
      * @brief    Draw Index.
      * @bug      No known Bugs.
      */
     virtual void 
     draw(unsigned int inNumIndexes, 
     /***/unsigned int inStartLocation) = 0;
     
     /**
      * @brief    Gets the default Render Target.
      * @return   Returns the back Buffer texture.
      */
     virtual void * 
     getDefaultRenderTarget() = 0;
     
     /**
      * @brief    Gets the default Depth Stencil.
      * @return   Returns the Depth Stencil View texutre;
      */
     virtual void * 
     getDefaultDephtStencil() = 0;
  
  };
  
  static CBaseGraphicsAPI& 
  g_GraphicsAPI();
}