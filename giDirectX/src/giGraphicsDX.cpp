/**
 * @file    giGraphicsDX.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    15/04/2021
 * @brief   The Graphics API in charge to use DX11.
 */
 
/**
 * @include
 */
#include <intrin.h>
#include "giGraphicsDX.h"
#include <giVector4.h>

#include "giTexture2DDX.h"
#include "giInputLayoutDX.h"
#include "giBufferDX.h"
#include "giDepthStencilViewDX.h"
#include "giSamplerDX.h"
#include "giRenderTargetViewDX.h"
#include "giVertexShaderDX.h"
#include "giComputeShaderDX.h"
#include "giPixelShaderDX.h"
#include "giRasterizerDX.h"
#include "giDepthStateDX.h"
#include "giBlendStateDX.h"
#include "stb_image.h"


namespace giEngineSDK {

  CGraphicsDX::CGraphicsDX() {
    m_device = nullptr;
    m_devContext = nullptr;
    m_swapChain = nullptr;
  }


  CGraphicsDX::~CGraphicsDX() {
    
  }


  void 
  CGraphicsDX::init(void* inWindow) {
    createDeviceAndSwpaChain(inWindow);
  }


  bool 
  CGraphicsDX::createDeviceAndSwpaChain(void* inWindow) {
    HRESULT hr = S_OK;
    uint32 createDeviceFlags = 0;

    auto hWindow = reinterpret_cast<HWND>(inWindow);

    RECT tmpWindowSize;
    GetClientRect(hWindow, &tmpWindowSize);
    uint32 inWidth = (tmpWindowSize.right - tmpWindowSize.left);
    uint32 inHeight = (tmpWindowSize.bottom - tmpWindowSize.top);
#ifdef _DEBUG
    createDeviceFlags |= GI_DEVICE_FLAG::E::kCREATE_DEVICE_DEBUG;
#endif 
    Vector<GI_DRIVER_TYPE::E> driverTypes = {
      GI_DRIVER_TYPE::kDRIVER_TYPE_HARDWARE,
      GI_DRIVER_TYPE::kDRIVER_TYPE_WARP,
      GI_DRIVER_TYPE::kDRIVER_TYPE_REFERENCE
    };
    Vector<GI_FEATURE_LEVEL::E> featureLvl = {
      GI_FEATURE_LEVEL::kFEATURE_LEVEL_11_0,
      GI_FEATURE_LEVEL::kFEATURE_LEVEL_10_1,
      GI_FEATURE_LEVEL::kFEATURE_LEVEL_10_0
    };

    DXGI_SWAP_CHAIN_DESC sd;
    memset(&sd, 0, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = inWidth;
    sd.BufferDesc.Height = inHeight;
    sd.BufferDesc.Format = static_cast<DXGI_FORMAT>(GI_FORMAT::kFORMAT_R8G8B8A8_UNORM);
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWindow;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    GI_FEATURE_LEVEL::E selectFeatureLvl;

    for (auto& driverType : driverTypes) {
      hr = D3D11CreateDeviceAndSwapChain(nullptr,
                                         static_cast<D3D_DRIVER_TYPE>(driverType),
                                         nullptr,
                                         (UINT)createDeviceFlags,
                                         reinterpret_cast<const D3D_FEATURE_LEVEL*>(featureLvl.data()),
                                         (UINT)featureLvl.size(),
                                         (UINT)D3D11_SDK_VERSION,
                                         &sd,
                                         &m_swapChain,
                                         &m_device,
                                         reinterpret_cast<D3D_FEATURE_LEVEL*>(&selectFeatureLvl),
                                         &m_devContext);
      
      if (S_OK == hr) {
        break;;
      }
      else {
        return false;
      }
      
    }
    m_backBuffer.reset(new Texture2DDX);

    //Get a texture from Swap Chain
    m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_backBuffer->m_texture);

    //Create RTV
    if (FAILED(m_device->CreateRenderTargetView(m_backBuffer->m_texture,
                                                nullptr,
                                                &m_backBuffer->m_renderTargetView))) {

      __debugbreak();
    }

    //Texture for the viewport.
    m_viewportTexture.reset(new Texture2DDX);

    m_viewportTexture = static_pointer_cast<Texture2DDX>(createTex2D(inWidth,
                                                                     inHeight,
                                                                     1,
                                                                     GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                                                                     GI_BIND_FLAG::kBIND_RENDER_TARGET
                                                                     | GI_BIND_FLAG::kBIND_SHADER_RESOURCE));
    
    //Create DSV
    m_defaultDSV = static_pointer_cast<Texture2DDX>(createTex2D(inWidth,
                                                                inHeight,
                                                                1,
                                                                GI_FORMAT::kFORMAT_D24_UNORM_S8_UINT,
                                                                GI_BIND_FLAG::kBIND_DEPTH_STENCIL));

    //Create and set a ViewPort
    createViewport(1, inWidth, inHeight, 0, 0);

    if (S_OK == hr) {
      return true;
    }
    else {
      return false;
    }
  }


  SharedPtr<Texture2D>
  CGraphicsDX::createTex2D(int32 inWidth,
                           int32 inHeigh,
                           int32 inMipLevels,
                           GI_FORMAT::E inFormat,
                           int32 inBindFlags) {

    SharedPtr<Texture2DDX> temp;
    temp.reset(new Texture2DDX);
    CD3D11_TEXTURE2D_DESC tempDesc;
    memset(&tempDesc, 0, sizeof(tempDesc));
    tempDesc.Width = inWidth;
    tempDesc.Height = inHeigh;
    tempDesc.MipLevels = inMipLevels;
    tempDesc.ArraySize = 1;
    tempDesc.Format = (DXGI_FORMAT)inFormat;
    tempDesc.SampleDesc.Count = 1;
    tempDesc.SampleDesc.Quality = 0;
    tempDesc.Usage = D3D11_USAGE_DEFAULT;
    tempDesc.BindFlags = (D3D11_BIND_FLAG)inBindFlags;
    tempDesc.CPUAccessFlags = 0;
    tempDesc.MiscFlags = 0;

    if (FAILED(m_device->CreateTexture2D(&tempDesc, nullptr, &temp->m_texture))) {
      //Send error message
      g_logger().SetError(ERROR_TYPE::kTextureCreation, "Texture can't be created");
      //Pone un breakpoint cuando llegue aqui
      __debugbreak();
      return nullptr;
    }

    if (D3D11_BIND_RENDER_TARGET & inBindFlags) {
      D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
      memset(&rtvDesc, 0, sizeof(rtvDesc));
      rtvDesc.Format = tempDesc.Format;
      rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
      rtvDesc.Texture2D.MipSlice = 0;
      if (FAILED(m_device->CreateRenderTargetView(temp->m_texture, 
                                                  &rtvDesc, 
                                                  &temp->m_renderTargetView))) {
        //Send error message
        g_logger().SetError(ERROR_TYPE::kTextureCreation, 
                            "Texture can't be created as Render Target View");
        __debugbreak();
        return nullptr;
      }

    }

    if (D3D11_BIND_DEPTH_STENCIL & inBindFlags) {
      D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
      memset(&dsvDesc, 0, sizeof(dsvDesc));
      dsvDesc.Format = tempDesc.Format;
      dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
      dsvDesc.Texture2D.MipSlice = 0;
      if (FAILED(m_device->CreateDepthStencilView(temp->m_texture, 
                                                  &dsvDesc, 
                                                  &temp->m_depthStencilView))) {
        //Send error message
        g_logger().SetError(ERROR_TYPE::kTextureCreation, 
                            "Texture can't be created as a Depth Stencil View");
        __debugbreak();
        return nullptr;
      }
    }

    if (D3D11_BIND_SHADER_RESOURCE & inBindFlags) {
      D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
      memset(&srvDesc, 0, sizeof(srvDesc));
      srvDesc.Format = tempDesc.Format;
      srvDesc.ViewDimension = static_cast<D3D11_SRV_DIMENSION>(GI_SRV_DIMENSION::kSRV_DIMENSION_TEXTURE2D);
      srvDesc.Texture2D.MipLevels = 1;
      srvDesc.Texture2D.MostDetailedMip = 0;

      if (FAILED(m_device->CreateShaderResourceView(temp->m_texture, 
                                                    &srvDesc, 
                                                    &temp->m_subResourceData))) {

        //Send error message
        g_logger().SetError(ERROR_TYPE::kTextureCreation, 
                            "Texture can't be created as a Shader Resource View");
        __debugbreak();
        return nullptr;
      }
    }

    if(D3D11_BIND_UNORDERED_ACCESS & inBindFlags) {
      D3D11_UNORDERED_ACCESS_VIEW_DESC tmpDesc;
      memset(&tmpDesc, 0, sizeof(tmpDesc));
      tmpDesc.Format = (DXGI_FORMAT)inFormat;
      tmpDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
      tmpDesc.Buffer.Flags = 0;
      tmpDesc.Buffer.FirstElement = 0;
      tmpDesc.Buffer.NumElements = 1;
      
      
      if(FAILED(m_device->CreateUnorderedAccessView(temp->m_texture,
                                                    &tmpDesc,
                                                    &temp->m_UAV))) {
      
        g_logger().SetError(ERROR_TYPE::kUAVCreation,
                            "A Unordered Access View can't be created");
        __debugbreak();
        return nullptr;
      }
    }

    return temp;

  }


  void
  CGraphicsDX::createViewport(uint32 inNumVP, 
                              int32 inWidth, 
                              int32 inHeight, 
                              int32 inTopX, 
                              int32 inTopY) {

    CD3D11_VIEWPORT VP(static_cast<float>(inTopX), 
                       static_cast<float>(inTopY), 
                       static_cast<float>(inWidth), 
                       static_cast<float>(inHeight));

    m_devContext->RSSetViewports(inNumVP, &VP);

  }


  SharedPtr<BaseVertexShader>
  CGraphicsDX::createVShaderFromFile(wString inFileName,
                                     String inEntryPoint,
                                     String inShaderModel) {

    SharedPtr<VertexShaderDX> tempVS;
    tempVS.reset(new VertexShaderDX);
    tempVS->init(inFileName, inEntryPoint, inShaderModel);
    if (FAILED(m_device->CreateVertexShader(tempVS->m_compiledVShader->GetBufferPointer(),
                                            tempVS->m_compiledVShader->GetBufferSize(),
                                            nullptr,
                                            &tempVS->m_vertexShader))) {

      __debugbreak();
      return nullptr;
    }


    return tempVS;
  }


  SharedPtr<BasePixelShader>
  CGraphicsDX::createPShaderFromFile(wString inFileName,
                                     String inEntryPoint,
                                     String inShaderModel) {
    SharedPtr<PixelShaderDX> tempPS;
    tempPS.reset(new PixelShaderDX);
    tempPS->init(inFileName, inEntryPoint, inShaderModel);
    if (FAILED(m_device->CreatePixelShader(tempPS->m_compiledPShader->GetBufferPointer(),
                                           tempPS->m_compiledPShader->GetBufferSize(),
                                           nullptr,
                                           &tempPS->m_pixelShader))) {

      __debugbreak();
      return nullptr;
    }

    return tempPS;
  }

  SharedPtr<BaseComputeShader>
  CGraphicsDX::createCShaderFromFile(wString inFileName,
                                     String inEntryPoint, 
                                     String inShaderModel) {

    SharedPtr<ComputeShaderDX> tempCS;
    tempCS->init(inFileName, inEntryPoint, inShaderModel);
    if (FAILED(m_device->CreateComputeShader(tempCS->m_compiledCShader->GetBufferPointer(),
                                             tempCS->m_compiledCShader->GetBufferSize(),
                                             nullptr,
                                             &tempCS->m_computeShader))) {
                                             
      __debugbreak();
      return nullptr;
    }

    return tempCS;
  }

  SharedPtr<BaseVertexShader> 
  CGraphicsDX::createVShaderFromMem(const char* inShaderRaw, 
                                    String inEntryPoint) {
    SharedPtr<VertexShaderDX> tmpVShader;
    tmpVShader.reset(new VertexShaderDX);
    //Compile the shader.
    if (FAILED(D3DCompile(inShaderRaw, 
                          strlen(inShaderRaw), 
                          NULL, 
                          NULL, 
                          NULL, 
                          inEntryPoint.c_str(), 
                          "vs_4_0", 
                          0, 
                          0, 
                          &tmpVShader->m_compiledVShader,
                          NULL))) {
      return nullptr;
    }
    //Create the vertex shader with the compiled data.
    if (m_device->CreateVertexShader(tmpVShader->m_compiledVShader->GetBufferPointer(), 
                                     tmpVShader->m_compiledVShader->GetBufferSize(),
                                     NULL, 
                                     &tmpVShader->m_vertexShader) != S_OK) {
      
      return nullptr;
    }
    //If the shader can be created.
    return tmpVShader;
  }

  SharedPtr<BasePixelShader>
  CGraphicsDX::createPShaderFromMem(const char* inShaderRaw,
                                    String inEntryPoint) {
    SharedPtr<PixelShaderDX> tmpPShader;
    tmpPShader.reset(new PixelShaderDX);
    //Compile the data.
    if (FAILED(D3DCompile(inShaderRaw, 
                          strlen(inShaderRaw), 
                          NULL, 
                          NULL, 
                          NULL, 
                          inEntryPoint.c_str(), 
                          "ps_4_0", 
                          0, 
                          0, 
                          &tmpPShader->m_compiledPShader,
                          NULL))) {
      return nullptr; 
    }
    //Create the pixel shader with the compiled data.
    if (m_device->CreatePixelShader(tmpPShader->m_compiledPShader->GetBufferPointer(), 
                                    tmpPShader->m_compiledPShader->GetBufferSize(), 
                                    NULL, 
                                    &tmpPShader->m_pixelShader) != S_OK) {
      return nullptr;
    }
    //If the shader can't be created.
    return tmpPShader;
  }
  


  SharedPtr<InputLayout>
  CGraphicsDX::createInputLayout(Vector<InputLayoutDesc>& inDesc,
                                 SharedPtr<BaseShader> inShader) {

    SharedPtr<InputLayoutDX> tempIL;
    tempIL.reset(new InputLayoutDX);
    tempIL->init(inDesc);
    SharedPtr<VertexShaderDX> tmpVS = static_pointer_cast<VertexShaderDX>(inShader);
    if (FAILED(m_device->CreateInputLayout(tempIL->m_descriptors.data(),
                                           static_cast<int32>(inDesc.size()),
                                           tmpVS.get()->m_compiledVShader->GetBufferPointer(),
                                           static_cast<uint32>(tmpVS.get()->m_compiledVShader->GetBufferSize()),
                                           &tempIL->m_inputLayout))) {
      //Add error
      __debugbreak();
      return nullptr;
    }
    return tempIL;
  }


  SharedPtr<Buffer>
  CGraphicsDX::createBuffer(size_T inByteWidth,
                            int32 inBindFlags,
                            void*  inBufferData,
                            uint32 inStructureStride,
                            uint32 inNumElements,
                            GI_FORMAT::E inFormat) {

    SharedPtr<BufferDX> tmpBuffer;
    tmpBuffer.reset(new BufferDX);

    CD3D11_BUFFER_DESC tmpDesc((uint32)inByteWidth, inBindFlags);
    D3D11_SUBRESOURCE_DATA tmpData;
    tmpData.pSysMem = inBufferData;
    tmpData.SysMemPitch = (uint32)inByteWidth;
    tmpData.SysMemSlicePitch = 0;
    tmpDesc.StructureByteStride = 0;

    //If is a unordered Access View or shader Resource
    if (inBindFlags & GI_BIND_FLAG::kBIND_SHADER_RESOURCE 
        && inBindFlags & GI_BIND_FLAG::kBIND_UNORDERED_ACCESS) {
      tmpDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
      tmpDesc.StructureByteStride = inStructureStride;
    }
    //Create The buffer
    if (FAILED(m_device->CreateBuffer(&tmpDesc,
                                      (inBufferData == nullptr ? nullptr : &tmpData),
                                      &tmpBuffer->m_buffer))) {
      g_logger().SetError(ERROR_TYPE::kBufferCreation, 
                          "A buffer can't be created");
      __debugbreak();
      return nullptr;
    }
    //Create the UAV
    if (inBindFlags & GI_BIND_FLAG::kBIND_UNORDERED_ACCESS) {
      D3D11_BUFFER_UAV tmpBufferUAV;
      tmpBufferUAV.Flags = 0;
      tmpBufferUAV.FirstElement = 0;
      tmpBufferUAV.NumElements = inNumElements;
      
      D3D11_UNORDERED_ACCESS_VIEW_DESC tmpDescUAV;
      tmpDescUAV.Format = (DXGI_FORMAT)inFormat;
      tmpDescUAV.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
      tmpDescUAV.Buffer = tmpBufferUAV;
      
      if (FAILED(m_device->CreateUnorderedAccessView(tmpBuffer->m_buffer,
                                                     &tmpDescUAV,
                                                     &tmpBuffer->m_UAV))) {
      
        g_logger().SetError(ERROR_TYPE::kUAVCreation,
                            "A Unordered Access View can't be created");
        __debugbreak();
        return nullptr;
      }
    }
    return tmpBuffer;
  }


  SharedPtr<SamplerState>
  CGraphicsDX::createSampler(SamplerDesc inDesc) {
    SharedPtr<SamplerDX> tmpSampler;
    tmpSampler.reset(new SamplerDX);
    tmpSampler->init(inDesc);
    if (FAILED(m_device->CreateSamplerState(&tmpSampler->m_desc, 
                                            &tmpSampler->m_sampler))) {
      g_logger().SetError(ERROR_TYPE::kSamplerCreation, 
                          "A sampler can't be created");
      __debugbreak();
      return nullptr;
    }
    return tmpSampler;
  }


  SharedPtr<BaseRasterizerState>
  CGraphicsDX::createRasterizer(FILLMODE::E inFillMode,
                                CULLMODE::E inCullMode,
                                bool inClockwise,
                                bool inScissorEnable) {
    SharedPtr<RasterizerDX> tmpRaster;
    tmpRaster.reset(new RasterizerDX);
    D3D11_RASTERIZER_DESC tmpDesc;
    memset(&tmpDesc, 0, sizeof(tmpDesc));
    switch (inFillMode) {
    case FILLMODE::kSolid:
      tmpDesc.FillMode = D3D11_FILL_SOLID;
      break;
    case FILLMODE::kWireFrame:
      tmpDesc.FillMode = D3D11_FILL_WIREFRAME;
      break;
    default:
      tmpDesc.FillMode = D3D11_FILL_SOLID;
      break;
    }  

    switch (inCullMode) {
    case CULLMODE::kNone:
      tmpDesc.CullMode = D3D11_CULL_NONE;
      break;
    case CULLMODE::kFront:
      tmpDesc.CullMode = D3D11_CULL_FRONT;
      break;
    case CULLMODE::kBack:
      tmpDesc.CullMode = D3D11_CULL_BACK;
      break;
    default:
      tmpDesc.CullMode = D3D11_CULL_BACK;
      break;
    }

    tmpDesc.FrontCounterClockwise = inClockwise;
    tmpDesc.DepthClipEnable = true;
    tmpDesc.ScissorEnable = inScissorEnable;


    m_device->CreateRasterizerState(&tmpDesc, &tmpRaster->m_rasterizerState);

    return tmpRaster;
  }


  SharedPtr<BaseDepthStencilState>
  CGraphicsDX::createDepthState(bool inStencilEnable,
                                bool inDepthEnable,
                                GI_COMPARATION_FUNC::E inCompar) {
    SharedPtr<DepthStateDX> tmpState;
    tmpState.reset(new DepthStateDX);
    D3D11_DEPTH_STENCIL_DESC tmpDesc;

    tmpDesc.StencilEnable = inStencilEnable;
    tmpDesc.DepthEnable = inDepthEnable;

    tmpDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    tmpDesc.DepthFunc = static_cast<D3D11_COMPARISON_FUNC>(inCompar);
    
    tmpDesc.StencilReadMask = 0xFF;
    tmpDesc.StencilWriteMask = 0xFF;

    tmpDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    tmpDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    tmpDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    tmpDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    if(FAILED(m_device->CreateDepthStencilState(&tmpDesc, &tmpState->m_State))) {
      g_logger().SetError(ERROR_TYPE::kDepthStencilStateCreation,
                          "A Depth Stencil State can't be created");
      return nullptr;
    }

    return tmpState;
  }

  SharedPtr<BaseBlendState> 
    CGraphicsDX::createBlendState(bool inEnable,
                                  BLEND_TYPE::E inSource,
                                  BLEND_TYPE::E inDest,
                                  BLEND_OP::E inOp,
                                  BLEND_TYPE::E inAlphaSource,
                                  BLEND_TYPE::E inAlphaDest,
                                  BLEND_OP::E inAlphaOp,
                                  Vector4 inBlendFactor) {

    D3D11_BLEND_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.AlphaToCoverageEnable = false;
    desc.RenderTarget[0].BlendEnable = inEnable;
    desc.RenderTarget[0].SrcBlend = static_cast<D3D11_BLEND>(inSource);
    desc.RenderTarget[0].DestBlend = static_cast<D3D11_BLEND>(inDest);
    desc.RenderTarget[0].BlendOp = static_cast<D3D11_BLEND_OP>(inOp);
    desc.RenderTarget[0].SrcBlendAlpha = static_cast<D3D11_BLEND>(inAlphaSource);
    desc.RenderTarget[0].DestBlendAlpha = static_cast<D3D11_BLEND>(inAlphaDest);
    desc.RenderTarget[0].BlendOpAlpha = static_cast<D3D11_BLEND_OP>(inAlphaOp);
    desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    SharedPtr<BlendStateDX> tmpBS(new BlendStateDX);
    tmpBS->m_blendFactor = inBlendFactor;
    if(FAILED(m_device->CreateBlendState(&desc, &tmpBS->m_blendState))) {
      g_logger().SetError(ERROR_TYPE::kBufferCreation,
                          "A Blend State can't be created");
      return nullptr;
    }
    return tmpBS;
  }


  void 
  CGraphicsDX::show() {
    m_swapChain->Present(0, 0);
  }


  void 
  CGraphicsDX::setVertexBuffer(SharedPtr<Buffer> inBuffer,
                               uint32 inStride) {
    UINT offset = 0;
    m_devContext->IASetVertexBuffers(0, 
                                     1, 
                                     &(static_pointer_cast<BufferDX>(inBuffer)->m_buffer),
                                     &inStride, 
                                     &offset);
  }




  void 
  CGraphicsDX::setIndexBuffer(SharedPtr<Buffer> inBuffer,
                              GI_FORMAT::E inFormat) {
    m_devContext->IASetIndexBuffer(static_pointer_cast<BufferDX>(inBuffer)->m_buffer,
                                   static_cast<DXGI_FORMAT>(inFormat), 
                                   0);
  }


  void 
  CGraphicsDX::setTopology(GI_PRIMITIVE_TOPOLOGY::E inTopotology) {
    auto tmpTopology = static_cast<D3D_PRIMITIVE_TOPOLOGY>(inTopotology);
    m_devContext->IASetPrimitiveTopology(tmpTopology);
  }

  void 
  CGraphicsDX::setRasterizerState(SharedPtr<BaseRasterizerState> inRaster) {
    SharedPtr<RasterizerDX> tmpRaster = static_pointer_cast<RasterizerDX>(inRaster);
    m_devContext->RSSetState(tmpRaster->m_rasterizerState);
  }

  void
  CGraphicsDX::setDepthState(SharedPtr<BaseDepthStencilState> inDepthState) {
    SharedPtr<DepthStateDX> tmpState = static_pointer_cast<DepthStateDX>(inDepthState);
    m_devContext->OMSetDepthStencilState(tmpState->m_State, 0);
  }

  void
  CGraphicsDX::setUAV(int32 inStartSlot, Texture2D * inUAV) {
    ID3D11UnorderedAccessView * tmpUAV = nullptr;

    if (nullptr != inUAV) {
      tmpUAV = static_cast<Texture2DDX*>(inUAV)->m_UAV;
      
    }
    m_devContext->CSSetUnorderedAccessViews(inStartSlot, 
                                            1, 
                                            &tmpUAV,
                                            nullptr);
  }

  void 
  CGraphicsDX::updateSubresource(SharedPtr<Buffer> inBuffer,
                                 void* inData,
                                 uint32 inPitch) {

    SharedPtr<BufferDX> tmpBuffer = static_pointer_cast<BufferDX>(inBuffer);
    m_devContext->UpdateSubresource(tmpBuffer->m_buffer, 
                                    0, 
                                    NULL, 
                                    inData, 
                                    inPitch, 
                                    0);
  }


  void 
  CGraphicsDX::updateTexture(SharedPtr<Texture2D> inTexture,
                             const void* inData,
                             uint32 inPitch,
                             uint32 inDepthPitch) {

    m_devContext->UpdateSubresource(static_pointer_cast<Texture2DDX>(inTexture)->m_texture,
                                    0,
                                    NULL,
                                    inData,
                                    inPitch,
                                    inDepthPitch);
  }

  void 
  CGraphicsDX::resizeBackTexture(int32 inW, int32 inH) {
    m_devContext->OMSetRenderTargets(0, 0, 0);
    m_backBuffer.reset();
    m_defaultDSV.reset();

    if(FAILED(m_swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0))) {
      Logger::instance().SetError(ERROR_TYPE::kResizeTextures, 
                                  "Error resizing the viewport Texture");
      return;
    }

    SharedPtr<Texture2DDX> backBuffer(new Texture2DDX);
    if(FAILED(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), 
              (void**)&backBuffer->m_texture))) {
      Logger::instance().SetError(ERROR_TYPE::kResizeTextures, 
                                  "Error obtaining back buffer from swapchain");
      return;
    }

    if(FAILED(m_device->CreateRenderTargetView(backBuffer->m_texture,
                                               nullptr,
                                               &backBuffer->m_renderTargetView))) {
      Logger::instance().SetError(ERROR_TYPE::kResizeTextures, 
                                  "Error creating the render target view for the back buffer");
      return;
    }

    m_devContext->OMSetRenderTargets(1, &backBuffer->m_renderTargetView, NULL);

    //Texture for the viewport.
    m_viewportTexture.reset(new Texture2DDX);

    m_viewportTexture = static_pointer_cast<Texture2DDX>(createTex2D(inW,
                                                                     inH,
                                                                     1,
                                                                     GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                                                                     GI_BIND_FLAG::kBIND_RENDER_TARGET
                                                                     | GI_BIND_FLAG::kBIND_SHADER_RESOURCE));

    SharedPtr<Texture2D> depthTex = createTex2D(inW, 
                                                inH, 
                                                1, 
                                                GI_FORMAT::kFORMAT_D24_UNORM_S8_UINT, 
                                                GI_BIND_FLAG::kBIND_DEPTH_STENCIL);

    m_backBuffer.reset();
    m_defaultDSV.reset();
    m_backBuffer = backBuffer;
    m_defaultDSV = static_pointer_cast<Texture2DDX>(depthTex);

    setViewport(0, 0, inW, inH, 0.f, 1.f);
  }

  void
  CGraphicsDX::clearBackTexture(float inColor[4]) {
    clearRTV(static_pointer_cast<Texture2D>(getViewportTex()),
             inColor);

    clearDSV(static_pointer_cast<Texture2D>(getDefaultDephtStencil()));
  }


  void 
  CGraphicsDX::clearRTV(SharedPtr<Texture2D> inRTV, float inColor[4]) {
    m_devContext->ClearRenderTargetView(static_pointer_cast<Texture2DDX>(inRTV)->m_renderTargetView,
                                        inColor);
  }


  void 
  CGraphicsDX::clearDSV(SharedPtr<Texture2D> inDSV) {
    m_devContext->ClearDepthStencilView(static_pointer_cast<Texture2DDX>(inDSV)->m_depthStencilView,
                                        static_cast<D3D11_CLEAR_FLAG>(GI_CLEAR_FLAG::kCLEAR_DEPTH),
                                        1.0f,
                                        0);
  }


  void 
  CGraphicsDX::setViewport(int32 inTopLeftX, 
                           int32 inTopLeftY, 
                           int32 inWidth, 
                           int32 inHeight, 
                           float inMinDepth, 
                           float inMaxDepth) {
    D3D11_VIEWPORT vp;
    vp.Width = static_cast<FLOAT>(inWidth);
    vp.Height = static_cast<FLOAT>(inHeight);
    vp.MinDepth = inMinDepth;
    vp.MaxDepth = inMaxDepth;
    vp.TopLeftX = static_cast<FLOAT>(inTopLeftX);
    vp.TopLeftY = static_cast<FLOAT>(inTopLeftY);
    m_devContext->RSSetViewports(1, &vp);
  }

  void
  CGraphicsDX::vsSetShader(SharedPtr<BaseVertexShader> inVShader) {
    
    auto tmpShader = static_pointer_cast<VertexShaderDX>(inVShader);

    ID3D11VertexShader* tmpVShader = nullptr;
    if (nullptr != tmpShader) {
      tmpVShader = tmpShader->m_vertexShader;
    }
    m_devContext->VSSetShader(tmpVShader, NULL, 0);
  }


  void 
  CGraphicsDX::vsSetConstantBuffer(uint32 inSlot,
                                   SharedPtr<Buffer> inBuffer) {

    auto tmpBuffer = static_pointer_cast<BufferDX>(inBuffer);

    ID3D11Buffer* Buffer = nullptr;
    if (nullptr != inBuffer) {
      Buffer = tmpBuffer->m_buffer;
    }
    m_devContext->VSSetConstantBuffers(inSlot, 1, &Buffer);
  }


  void 
  CGraphicsDX::psSetShader(SharedPtr<BasePixelShader> inPShader) {

    auto tmpShader = static_pointer_cast<PixelShaderDX>(inPShader);

    ID3D11PixelShader* tmpPShader = nullptr;
    if (nullptr != tmpShader) {
      tmpPShader = tmpShader->m_pixelShader;
    }

    m_devContext->PSSetShader(tmpPShader, NULL, 0);
  }

  void 
  CGraphicsDX::csSetShader(SharedPtr<BaseShader> inCShader) {
    SharedPtr<ComputeShaderDX> tmpShader = static_pointer_cast<ComputeShaderDX>(inCShader);

    ID3D11ComputeShader* tmpCShader = nullptr;
    if (nullptr != tmpShader) {
      tmpCShader = tmpShader->m_computeShader;
    }

    m_devContext->CSSetShader(tmpCShader, NULL, 0);
  }


  void 
  CGraphicsDX::psSetConstantBuffer(uint32 inSlot,
                                   SharedPtr<Buffer> inBuffer) {

    m_devContext->PSSetConstantBuffers(inSlot, 
                                       1, 
                                       &static_pointer_cast<BufferDX>(inBuffer)->m_buffer);
  }

  void 
  CGraphicsDX::csSetConstantBuffer(uint32 inSlot, SharedPtr<Buffer> inBuffer) {
    SharedPtr<BufferDX> tmpBuffer = static_pointer_cast<BufferDX>(inBuffer);
    m_devContext->CSSetConstantBuffers(inSlot, 
                                       1, 
                                       &tmpBuffer->m_buffer);
  }


  void 
  CGraphicsDX::psSetShaderResource(uint32 inSlot,
                                   SharedPtr<Texture2D> inTexture) {
    
    SharedPtr<Texture2DDX> tmpTexture = static_pointer_cast<Texture2DDX>(inTexture);
    ID3D11ShaderResourceView* tmpSRV = nullptr;
    if (nullptr != tmpTexture) {
      tmpSRV = tmpTexture->getSRV();
    }

    m_devContext->PSSetShaderResources(inSlot, 1, &tmpSRV);
  }

  void 
  CGraphicsDX::csSetShaderResource(uint32 inSlot, SharedPtr<Texture2D> inTexture) {
    ID3D11ShaderResourceView* tmpSRV = nullptr;
    SharedPtr<Texture2DDX> tmpTexture= static_pointer_cast<Texture2DDX>(inTexture);
    if (nullptr != inTexture) {
      tmpSRV = tmpTexture->getSRV();
    }

    m_devContext->CSSetShaderResources(inSlot, 1, &tmpSRV);
  }


  void 
  CGraphicsDX::psSetSamplerState(uint32 inSlot,
                            uint32 inNumSamplers,
                            SharedPtr<SamplerState> inSampler) {

    SharedPtr<SamplerDX> tmpSampler = static_pointer_cast<SamplerDX>(inSampler);

    m_devContext->PSSetSamplers(inSlot, inNumSamplers, &tmpSampler->m_sampler);
  }

  void 
  CGraphicsDX::csSetSampler(uint32 inSlot,
                            uint32 inNumSamplers,
                            SharedPtr<SamplerState> inSampler) {

    SharedPtr<SamplerDX> tmpSampler = static_pointer_cast<SamplerDX>(inSampler);

    m_devContext->CSSetSamplers(inSlot, inNumSamplers, &tmpSampler->m_sampler);
  }


  void 
  CGraphicsDX::aiSetInputLayout(SharedPtr<InputLayout> inInputLayout) {
    SharedPtr<InputLayoutDX> tmpIL = static_pointer_cast<InputLayoutDX>(inInputLayout);
    m_devContext->IASetInputLayout(tmpIL->m_inputLayout);
  }


  void 
  CGraphicsDX::omSetRenderTarget(Vector<SharedPtr<Texture2D>> inRTs,
                                 SharedPtr<Texture2D> inDS) {

    static ID3D11RenderTargetView* tmpRTV[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
    for (int32 i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) {
      tmpRTV[i] = nullptr;
    }

    ID3D11DepthStencilView* tmpDSV = nullptr;

    if (nullptr != inDS) {
      tmpDSV = static_pointer_cast<Texture2DDX>(inDS)->m_depthStencilView;
    }

    size_T tmpSize = inRTs.size();

    for (int32 i = 0; i < tmpSize; ++i) {
      if (nullptr != inRTs[i]) {
        tmpRTV[i] = static_pointer_cast<Texture2DDX>(inRTs[i])->m_renderTargetView;
      }
      else {
        break;
      }
    }

    m_devContext->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, tmpRTV, tmpDSV);

  }

  void
  CGraphicsDX::unbindRenderTarget() {

    ID3D11RenderTargetView* tmpRTV[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
  
    for (int32 i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) {
      tmpRTV[i] = nullptr;
    }
    
    ID3D11DepthStencilView* tmpDSV = nullptr;
    
    m_devContext->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, tmpRTV, tmpDSV);
  }

  void 
  CGraphicsDX::omSetBlendState(SharedPtr<BaseBlendState> inBlendState) {
    
    SharedPtr<BlendStateDX> tmpState = static_pointer_cast<BlendStateDX>(inBlendState);
    float tmpFactor[4] { tmpState->m_blendFactor.x, 
                         tmpState->m_blendFactor.y, 
                         tmpState->m_blendFactor.z, 
                         tmpState->m_blendFactor.w };
    m_devContext->OMSetBlendState(tmpState->m_blendState, tmpFactor, tmpState->m_mask);
  }

  void 
  CGraphicsDX::omSetDepthStencilState(SharedPtr<BaseDepthStencilState> inDepthState) {

    SharedPtr<DepthStateDX> tmpState = static_pointer_cast<DepthStateDX>(inDepthState);
    m_devContext->OMSetDepthStencilState(tmpState->m_State, 0);
  }

  void 
  CGraphicsDX::rsSetRasterizerState(SharedPtr<BaseRasterizerState> inRaster) {

    SharedPtr<RasterizerDX> tmpState = static_pointer_cast<RasterizerDX>(inRaster);
    m_devContext->RSSetState(tmpState->m_rasterizerState);
  }

  Vector4 * 
  CGraphicsDX::rsGetScissorRects(uint32 inNumRects) {
    Vector4 * tmpScissor;
    for (uint32 i = 0; i < inNumRects; ++i) {
       D3D11_RECT r = { (LONG)tmpScissor[i].x,
                        (LONG)tmpScissor[i].y,
                        (LONG)tmpScissor[i].z,
                        (LONG)tmpScissor[i].w };

      m_devContext->RSGetScissorRects(&inNumRects, &r);
    }
    return tmpScissor;
  }
  
  void *
  CGraphicsDX::rsGetViewports(uint32 inNumViewports) {
    void* tmpViewport;
    m_devContext->RSGetViewports(&inNumViewports, (D3D11_VIEWPORT*)tmpViewport);
    return tmpViewport;
  }

  SharedPtr<BaseRasterizerState>
  CGraphicsDX::rsGetState() {
    SharedPtr<RasterizerDX> tmpState(new RasterizerDX);
    m_devContext->RSGetState(&tmpState->m_rasterizerState);
    return tmpState;
  }

  SharedPtr<BaseBlendState>
  CGraphicsDX::omGetBlendState() {
    SharedPtr<BlendStateDX> tmpBlend;
    tmpBlend.reset(new BlendStateDX);
    float tmpFactor[4];
    uint32 tmpMask;

    m_devContext->OMGetBlendState(&tmpBlend->m_blendState, tmpFactor, &tmpMask);

    tmpBlend->m_blendFactor.x = tmpFactor[0];
    tmpBlend->m_blendFactor.y = tmpFactor[1];
    tmpBlend->m_blendFactor.z = tmpFactor[2];
    tmpBlend->m_blendFactor.w = tmpFactor[3];


    return tmpBlend;
  }

  SharedPtr<BaseDepthStencilState>
  CGraphicsDX::omGetDepthStencilState() {
    SharedPtr<DepthStateDX> tmpState;
    tmpState.reset(new DepthStateDX);
    m_devContext->OMGetDepthStencilState(&tmpState->m_State, nullptr);
    return tmpState;
  }

  SharedPtr<Texture2D>
  CGraphicsDX::psGetShaderResources(uint32 inStartSlot, 
                                    uint32 inNumViews) {
    SharedPtr<Texture2DDX> tmpShaderResource;
    tmpShaderResource.reset(new Texture2DDX);
    m_devContext->PSGetShaderResources(inStartSlot, 
                                       inNumViews, 
                                       &tmpShaderResource->m_subResourceData);
    return tmpShaderResource;
  }

  SharedPtr<SamplerState>
  CGraphicsDX::psGetSamplers(uint32 inStartSlot, 
                             uint32 inNumSamplers) {
    SharedPtr<SamplerDX> tmpSampler(new SamplerDX);
    m_devContext->PSGetSamplers(inStartSlot, 
                                inNumSamplers, 
                                &tmpSampler->m_sampler);
    return tmpSampler;
  }

  SharedPtr<BasePixelShader>
  CGraphicsDX::psGetShader() {
    SharedPtr<PixelShaderDX> tmpShader(new PixelShaderDX);
    m_devContext->PSGetShader(&tmpShader->m_pixelShader, nullptr, nullptr);
    return tmpShader;
  }

  SharedPtr<BaseVertexShader>
  CGraphicsDX::vsGetShader() {
    SharedPtr<VertexShaderDX> tmpShader(new VertexShaderDX);
    m_devContext->VSGetShader(&tmpShader->m_vertexShader, nullptr, nullptr);
    return tmpShader;
  }

  SharedPtr<Buffer>
  CGraphicsDX::vsGetConstantBuffers(int32 inStartSlot, 
                                    int32 inNumBuffers) {
    SharedPtr<BufferDX> tmpBuffer(new BufferDX);
    m_devContext->VSGetConstantBuffers(inStartSlot, 
                                       inNumBuffers, 
                                       &tmpBuffer->m_buffer);
    return tmpBuffer;
  }

  GI_PRIMITIVE_TOPOLOGY::E
  CGraphicsDX::iaGetPrimitiveTopology() {
    D3D11_PRIMITIVE_TOPOLOGY tmpTopology;
    m_devContext->IAGetPrimitiveTopology(&tmpTopology);
    return (GI_PRIMITIVE_TOPOLOGY::E)tmpTopology;
  }

  SharedPtr<Buffer>
  CGraphicsDX::iaGetIndexBuffer() {
    SharedPtr<BufferDX> tmpBuffer(new BufferDX);
    m_devContext->IAGetIndexBuffer(&tmpBuffer->m_buffer, nullptr, nullptr);
    return tmpBuffer;
  }

  SharedPtr<Buffer>
  CGraphicsDX::iaGetVertexBuffer(uint32 inStartSlot, 
                                 uint32 inStride, 
                                 uint32 inOffset) {
    SharedPtr<BufferDX> tmpBuffer(new BufferDX);
    m_devContext->IAGetVertexBuffers(inStartSlot, 
                                     1, 
                                     &tmpBuffer->m_buffer, 
                                     &inStride, 
                                     &inOffset);
    return tmpBuffer;
  }

  SharedPtr<InputLayout>
  CGraphicsDX::iaGetInputLayout() {
    SharedPtr<InputLayoutDX> tmpIL(new InputLayoutDX);
    m_devContext->IAGetInputLayout(&tmpIL->m_inputLayout);
    return tmpIL;
  }

  void 
  CGraphicsDX::rsSetScissorRects(uint32 inNumRects, Vector4* inRects) {
    D3D11_RECT tmpRect;
    m_devContext->RSSetScissorRects(inNumRects, &tmpRect);
    inRects->x = (float)tmpRect.top;
    inRects->y = (float)tmpRect.left;
    inRects->z = (float)tmpRect.right;
    inRects->w = (float)tmpRect.bottom;
  }
  

  void
  CGraphicsDX::drawIndexed(size_T inNumIndexes,
                           uint32 inStartLocation) {
    m_devContext->DrawIndexed((uint32)inNumIndexes, inStartLocation, 0);
  }

  void 
  CGraphicsDX::dispatch(uint32 inThreadGroupX, 
                        uint32 inThreadGroupY, 
                        uint32 inThreadGroupZ) {
    m_devContext->Dispatch(inThreadGroupX, inThreadGroupY, inThreadGroupZ);
  }


}