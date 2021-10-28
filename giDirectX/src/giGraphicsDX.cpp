/**
 * @file    giGraphicsDX.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    15/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giGraphicsDX.h"
#include <intrin.h>

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
#include "giUnorderedAccessViewDX.h"
#include "stb_image.h"


namespace giEngineSDK {

  CGraphicsDX::CGraphicsDX() {
    m_device = nullptr;
    m_devContext = nullptr;
    m_swapChain = nullptr;
  }


  CGraphicsDX::~CGraphicsDX() {
    delete m_backBuffer;
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
    m_backBuffer = new Texture2DDX();

    //Get a texture from Swap Chain
    m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_backBuffer->m_texture);

    //Create RTV
    if (FAILED(m_device->CreateRenderTargetView(m_backBuffer->m_texture,
                                                nullptr,
                                                &m_backBuffer->m_renderTargetView))) {

      __debugbreak();
    }



    //Create DSV
    m_defaultDSV = static_cast<Texture2DDX*>(createTex2D(inWidth,
                                             inHeight,
                                             1,
                                             GI_FORMAT::kFORMAT_D24_UNORM_S8_UINT,
                                             GI_BIND_FLAG::kBIND_DEPTH_STENCIL));

    //Create and set a ViewPort
    createVP(1, inWidth, inHeight, 0, 0);

    if (S_OK == hr) {
      return true;
    }
    else {
      return false;
    }
  }


  Texture2D*
  CGraphicsDX::createTex2D(int32 inWidth,
                           int32 inHeigh,
                           int32 inMipLevels,
                           GI_FORMAT::E inFormat,
                           int32 inBindFlags) {

    Texture2DDX* temp = new Texture2DDX();
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

    return temp;

  }


  void
  CGraphicsDX::createVP(uint32 inNumVP, 
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


  BaseVertexShader* 
  CGraphicsDX::createVS(String inFileName,
                        String inEntryPoint,
                        String inShaderModel) {

    VertexShaderDX* tempVS = new VertexShaderDX();
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


  BasePixelShader* 
  CGraphicsDX::createPS(String inFileName,
                        String inEntryPoint,
                        String inShaderModel) {
    PixelShaderDX* tempPS = new PixelShaderDX();
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

  BaseComputeShader* 
  CGraphicsDX::createCS(String inFileName, 
                        String inEntryPoint, 
                        String inShaderModel) {

    ComputeShaderDX* tempCS = new ComputeShaderDX();
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


  InputLayout* 
  CGraphicsDX::createIL(Vector<InputLayoutDesc>& inDesc,
                        BaseShader* inShader) {

    CInputLayoutDX* tempIL = new CInputLayoutDX();
    tempIL->init(inDesc);
    auto tmpVS = static_cast<VertexShaderDX*>(inShader);
    if (FAILED(m_device->CreateInputLayout(tempIL->m_descriptors.data(),
                                           static_cast<int32>(inDesc.size()),
                                           tmpVS->m_compiledVShader->GetBufferPointer(),
                                           static_cast<uint32>(tmpVS->m_compiledVShader->GetBufferSize()),
                                           &tempIL->m_inputLayout))) {
      __debugbreak();
      return nullptr;
    }
    return tempIL;
  }


  Buffer* 
  CGraphicsDX::createBuffer(size_T inByteWidth,
                            uint32 inBindFlags,
                            uint32 inOffset,
                            void* inBufferData,
                            uint32 inStructureStride) {

    GI_UNREFERENCED_PARAMETER(inOffset);
    CBufferDX* tmpBuffer = new CBufferDX();
    CD3D11_BUFFER_DESC tmpDesc(inByteWidth, inBindFlags);
    D3D11_SUBRESOURCE_DATA tmpData;
    tmpData.pSysMem = inBufferData;
    tmpData.SysMemPitch = inByteWidth;
    tmpData.SysMemSlicePitch = 0;



    if (inBindFlags & GI_BIND_FLAG::kBIND_SHADER_RESOURCE 
        && inBindFlags & GI_BIND_FLAG::kBIND_UNORDERED_ACCESS) {
      tmpDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
      tmpDesc.StructureByteStride = inStructureStride;
    }
    
    
    if (FAILED(m_device->CreateBuffer(&tmpDesc,
                                      (inBufferData == nullptr ? nullptr : &tmpData),
                                      &tmpBuffer->m_buffer))) {
      g_logger().SetError(ERROR_TYPE::kBufferCreation, 
                          "A buffer can't be created");
      __debugbreak();
      return nullptr;
    }



    return tmpBuffer;
  }


  Sampler* 
  CGraphicsDX::createSampler(SamplerDesc inDesc) {
    CSamplerDX* tmpSampler = new CSamplerDX();
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


  Rasterizer *
  CGraphicsDX::createRasterizer(FILLMODE::E inFillMode,
                                CULLMODE::E inCullMode,
                                bool inClockwise) {
    RasterizerDX* tmpRaster = new RasterizerDX();
    D3D11_RASTERIZER_DESC tmpDesc;
    memset(&tmpDesc, 0, sizeof(tmpDesc));
    switch (inFillMode) {
    case FILLMODE::kSolid:
      tmpDesc.FillMode == D3D11_FILL_SOLID;
      break;
    case FILLMODE::kWireFrame:
      tmpDesc.FillMode == D3D11_FILL_WIREFRAME;
      break;
    default:
      tmpDesc.FillMode == D3D11_FILL_SOLID;
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

    m_device->CreateRasterizerState(&tmpDesc, &tmpRaster->m_rasterizerState);

    return tmpRaster;
  }


  DepthState *
  CGraphicsDX::createDepthState(bool inStencilEnable,
                                bool inDepthEnable) {
    DepthStateDX * tmpState = new DepthStateDX();

    D3D11_DEPTH_STENCIL_DESC tmpDesc;

    tmpDesc.StencilEnable = inStencilEnable;
    tmpDesc.DepthEnable = inDepthEnable;

    m_device->CreateDepthStencilState(&tmpDesc, &tmpState->m_State);

    return tmpState;
  }

  BaseUnorderedAccessView* 
  CGraphicsDX::createUAVBuffer(Buffer * inData,
                               GI_FORMAT::E inFormat,
                               int32 inNumElements) {

    CBufferDX* tmpBufferData = static_cast<CBufferDX*>(inData);
    UnorderedAccessViewDX * tmpUAV = new UnorderedAccessViewDX();

    D3D11_BUFFER_UAV tmpBufferUAV;
    tmpBufferUAV.Flags = 0;
    tmpBufferUAV.FirstElement = 0;
    tmpBufferUAV.NumElements = inNumElements;

    D3D11_UNORDERED_ACCESS_VIEW_DESC tmpDesc;
    tmpDesc.Format = (DXGI_FORMAT)inFormat;
    tmpDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    tmpDesc.Buffer = tmpBufferUAV;
    if (tmpBufferData == nullptr) {
      return nullptr;
    }
    if(FAILED(m_device->CreateUnorderedAccessView(tmpBufferData->m_buffer,
                                                  &tmpDesc,
                                                  &tmpUAV->m_uav))) {

      g_logger().SetError(ERROR_TYPE::kUAVCreation,
                          "A Unordered Access View can't be created");
      __debugbreak();
      return nullptr;
    }

    return tmpUAV;
  }

  BaseUnorderedAccessView* 
  CGraphicsDX::createUAVTexture(Texture2D * inData,
                                GI_FORMAT::E inFormat,
                                int32 inNumElements) {

    CBufferDX* tmpBufferData = (CBufferDX*)inData;
    UnorderedAccessViewDX * tmpUAV = new UnorderedAccessViewDX();

    
    D3D11_UNORDERED_ACCESS_VIEW_DESC tmpDesc;
    tmpDesc.Format = (DXGI_FORMAT)inFormat;
    tmpDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
    tmpDesc.Buffer.Flags = 0;
    tmpDesc.Buffer.FirstElement = 0;
    tmpDesc.Buffer.NumElements = 1;


    if(FAILED(m_device->CreateUnorderedAccessView((tmpBufferData == nullptr 
                                                   ? nullptr 
                                                    : tmpBufferData->m_buffer),
                                                  &tmpDesc,
                                                  &tmpUAV->m_uav))) {

      g_logger().SetError(ERROR_TYPE::kUAVCreation,
                          "A Unordered Access View can't be created");
      __debugbreak();
      return nullptr;
    }

    return tmpUAV;
  }

  void 
  CGraphicsDX::show() {
    m_swapChain->Present(0, 0);
  }


  void 
  CGraphicsDX::setVertexBuffer(Buffer* inBuffer,
                               uint32 inStride) {
    UINT offset = 0;
    m_devContext->IASetVertexBuffers(0, 
                                     1, 
                                     &(static_cast<CBufferDX*>(inBuffer)->m_buffer),
                                     &inStride, 
                                     &offset);
  }


  void 
  CGraphicsDX::setIndexBuffer(Buffer* inBuffer,
                              GI_FORMAT::E inFormat) {
    m_devContext->IASetIndexBuffer(static_cast<CBufferDX*>(inBuffer)->m_buffer, 
                                   static_cast<DXGI_FORMAT>(inFormat), 
                                   0);
  }


  void 
  CGraphicsDX::setTopology(GI_PRIMITIVE_TOPOLOGY::E inTopotology) {
    auto tmpTopology = static_cast<D3D_PRIMITIVE_TOPOLOGY>(inTopotology);
    m_devContext->IASetPrimitiveTopology(tmpTopology);
  }

  void 
  CGraphicsDX::setRasterizerState(RasterizerDX * inRaster) {
    m_devContext->RSSetState(inRaster->m_rasterizerState);
  }

  void
  CGraphicsDX::setDepthState(DepthStateDX * inDepthState) {
    m_devContext->OMSetDepthStencilState(inDepthState->m_State, 0);
  }


  void 
  CGraphicsDX::updateSubresource(Buffer* inBuffer,
                                 void* inData,
                                 uint32 inPitch) {

    auto tmpBuffer = static_cast<CBufferDX*>(inBuffer);
    m_devContext->UpdateSubresource(tmpBuffer->m_buffer, 
                                    0, 
                                    NULL, 
                                    inData, 
                                    inPitch, 
                                    0);
  }


  void 
  CGraphicsDX::updateTexture(Texture2D* inTexture,
                             const void* inData,
                             uint32 inPitch,
                             uint32 inDepthPitch) {

    m_devContext->UpdateSubresource(static_cast<Texture2DDX*>(inTexture)->m_texture,
                                    0,
                                    NULL,
                                    inData,
                                    inPitch,
                                    inDepthPitch);
  }

  void 
  CGraphicsDX::clearBackTexture(float inColor[4]) {
    clearRTV(static_cast<Texture2D*>(getDefaultRenderTarget()),
             inColor);

    clearDSV(static_cast<Texture2D*>(getDefaultDephtStencil()));
  }


  void 
  CGraphicsDX::clearRTV(Texture2D* inRTV, float inColor[4]) {
    m_devContext->ClearRenderTargetView(static_cast<Texture2DDX*>(inRTV)->m_renderTargetView,
                                        inColor);
  }


  void 
  CGraphicsDX::clearDSV(Texture2D* inDSV) {
    m_devContext->ClearDepthStencilView(static_cast<Texture2DDX*>(inDSV)->m_depthStencilView,
                                        static_cast<D3D11_CLEAR_FLAG>(GI_CLEAR_FLAG::kCLEAR_DEPTH),
                                        1.0f,
                                        0);
  }


  void 
  CGraphicsDX::vsSetShader(BaseShader* inVShader) {
    
    auto tmpShader = static_cast<VertexShaderDX*>(inVShader);

    ID3D11VertexShader* tmpVShader = nullptr;
    if (nullptr != tmpShader) {
      tmpVShader = tmpShader->m_vertexShader;
    }
    m_devContext->VSSetShader(tmpVShader, NULL, 0);
  }


  void 
  CGraphicsDX::vsSetConstantBuffer(uint32 inSlot,
                                   Buffer* inBuffer) {

    auto tmpBuffer = static_cast<CBufferDX*>(inBuffer);

    ID3D11Buffer* Buffer = nullptr;
    if (nullptr != inBuffer) {
      Buffer = tmpBuffer->m_buffer;
    }
    m_devContext->VSSetConstantBuffers(inSlot, 1, &Buffer);
  }


  void 
  CGraphicsDX::psSetShader(BaseShader* inPShader) {

    auto tmpShader = static_cast<PixelShaderDX*>(inPShader);

    ID3D11PixelShader* tmpPShader = nullptr;
    if (nullptr != tmpShader) {
      tmpPShader = tmpShader->m_pixelShader;
    }

    m_devContext->PSSetShader(tmpPShader, NULL, 0);
  }


  void 
  CGraphicsDX::psSetConstantBuffer(uint32 inSlot,
                                   Buffer* inBuffer) {

    m_devContext->PSSetConstantBuffers(inSlot, 
                                       1, 
                                       &static_cast<CBufferDX*>(inBuffer)->m_buffer);
  }


  void 
  CGraphicsDX::psSetShaderResource(uint32 inSlot,
                                   Texture2D* inTexture) {

    ID3D11ShaderResourceView* tmpSRV = nullptr;
    if (nullptr != inTexture) {
      tmpSRV = static_cast<Texture2DDX*>(inTexture)->getSRV();
    }

    m_devContext->PSSetShaderResources(inSlot, 1, &tmpSRV);
  }


  void 
  CGraphicsDX::psSetSampler(uint32 inSlot,
                            uint32 inNumSamplers,
                            Sampler* inSampler) {

    auto tmpSampler = static_cast<CSamplerDX*>(inSampler);

    m_devContext->PSSetSamplers(inSlot, inNumSamplers, &tmpSampler->m_sampler);
  }


  void 
  CGraphicsDX::aiSetInputLayout(InputLayout* inInputLayout) {
    m_devContext->IASetInputLayout(static_cast<CInputLayoutDX*>(inInputLayout)->m_inputLayout);
  }


  void 
  CGraphicsDX::omSetRenderTarget(Vector<Texture2D*> inRTs,
                                 Texture2D* inDS) {

    static ID3D11RenderTargetView* tmpRTV[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
    for (int32 i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) {
      tmpRTV[i] = nullptr;
    }

    ID3D11DepthStencilView* tmpDSV = nullptr;

    if (nullptr != inDS) {
      tmpDSV = static_cast<Texture2DDX*>(inDS)->m_depthStencilView;
    }

    size_T tmpSize = inRTs.size();

    for (int32 i = 0; i < tmpSize; ++i) {
      if (nullptr != inRTs[i]) {
        tmpRTV[i] = static_cast<Texture2DDX*>(inRTs[i])->m_renderTargetView;
      }
      else {
        break;
      }
    }

    m_devContext->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, tmpRTV, tmpDSV);

  }


  void 
  CGraphicsDX::drawIndexed(size_T inNumIndexes,
                           uint32 inStartLocation) {
    m_devContext->DrawIndexed(inNumIndexes, inStartLocation, 0);
  }

  void 
  CGraphicsDX::dispatch(uint32 inThreadGroupX, 
                        uint32 inThreadGroupY, 
                        uint32 inThreadGroupZ) {
    m_devContext->Dispatch(inThreadGroupX, inThreadGroupY, inThreadGroupZ);
  }

  Texture2D* 
  CGraphicsDX::TextureFromFile(String inString, String inDirectory) {
    int32 width, height, nrChannels;
    inString = inString.substr(inString.find_last_of('/') + 1, inString.length());
    uint8* data = stbi_load((inDirectory + inString).c_str(), 
                            &width, 
                            &height, 
                            &nrChannels, 4);
    if (data) {
      Texture2DDX* temp = new Texture2DDX();
      CD3D11_TEXTURE2D_DESC tempDesc;
      memset(&tempDesc, 0, sizeof(tempDesc));
      tempDesc.Width = width;
      tempDesc.Height = height;
      tempDesc.MipLevels = 1;
      tempDesc.ArraySize = 1;
      tempDesc.Format = (DXGI_FORMAT)GI_FORMAT::kFORMAT_R8G8B8A8_UNORM;
      tempDesc.SampleDesc.Count = 1;
      tempDesc.SampleDesc.Quality = 0;
      tempDesc.Usage = D3D11_USAGE_DEFAULT;
      tempDesc.BindFlags = (D3D11_BIND_FLAG)GI_BIND_FLAG::kBIND_SHADER_RESOURCE;
      tempDesc.CPUAccessFlags = 0;
      tempDesc.MiscFlags = 0;

      D3D11_SUBRESOURCE_DATA srdata;
      memset(&srdata, 0, sizeof(srdata));
      srdata.pSysMem = data;
      srdata.SysMemPitch = width * 4;
      srdata.SysMemSlicePitch = 0;

      if (FAILED(m_device->CreateTexture2D(&tempDesc, &srdata, &temp->m_texture))) {
        //Send error message
        //Pone un breakpoint cuando llegue aqui
        __debugbreak();
        return nullptr;
      }

      D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
      memset(&srvDesc, 0, sizeof(srvDesc));
      srvDesc.Format = tempDesc.Format;
      srvDesc.ViewDimension = static_cast<D3D11_SRV_DIMENSION>(GI_SRV_DIMENSION::kSRV_DIMENSION_TEXTURE2D);
      srvDesc.Texture2D.MipLevels = 0;
      srvDesc.Texture2D.MostDetailedMip = 0;

      if (FAILED(m_device->CreateShaderResourceView(temp->m_texture, nullptr, &temp->m_subResourceData))) {
        __debugbreak();
        return nullptr;
      }


      stbi_image_free(data);
      return temp;
    }
    return nullptr;
  }
}