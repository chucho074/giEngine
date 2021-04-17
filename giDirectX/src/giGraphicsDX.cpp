/**
 * @file    giGraphicsDX.cpp
 * @author  Jes�s Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    15/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giGraphicsDX.h"
//#include "CImageLoader.h"
#include <intrin.h>

#include "giTexture2DDX.h"
#include "giInputLayoutDX.h"
#include "giBufferDX.h"
#include "giDepthStencilViewDX.h"
#include "giViewPortDX.h"
#include "giSamplerDX.h"
#include "giRenderTargetViewDX.h"
#include "giVertexShaderDX.h"
#include "giPixelShaderDX.h"


namespace giEngineSDK {

  CGraphicsDX::CGraphicsDX() {
    m_Device = nullptr;
    m_DevContext = nullptr;
    m_SwapChain = nullptr;
  }


  CGraphicsDX::~CGraphicsDX() {
    delete m_backBuffer;
  }


  void 
  CGraphicsDX::init(void* inWindow,
  /****************/int inWidth,
  /****************/int inHeight) {
    createDeviceAndSwpaChain(inWindow, inWidth, inHeight);
  }


  bool 
  CGraphicsDX::createDeviceAndSwpaChain(void* inWindow,
  /************************************/int inWidth,
  /************************************/int inHeight) {
    HRESULT hr = S_OK;
    unsigned int createDeviceFlags = 0;

#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif 
    Vector<D3D_DRIVER_TYPE> driverTypes = {
      D3D_DRIVER_TYPE_HARDWARE,
      D3D_DRIVER_TYPE_WARP,
      D3D_DRIVER_TYPE_REFERENCE,
    };
    Vector<D3D_FEATURE_LEVEL> featureLvl = {
      D3D_FEATURE_LEVEL_11_0,
      D3D_FEATURE_LEVEL_10_1,
      D3D_FEATURE_LEVEL_10_0,
    };

    DXGI_SWAP_CHAIN_DESC sd;
    memset(&sd, 0, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = inWidth;
    sd.BufferDesc.Height = inHeight;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = reinterpret_cast<HWND>(inWindow);
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    D3D_FEATURE_LEVEL selectFeatureLvl;

    for (auto& driverType : driverTypes) {
      hr = D3D11CreateDeviceAndSwapChain(nullptr,
        driverType,
        nullptr,
        (UINT)createDeviceFlags,
        featureLvl.data(),
        (UINT)featureLvl.size(),
        (UINT)D3D11_SDK_VERSION,
        &sd,
        &m_SwapChain,
        &m_Device,
        &selectFeatureLvl,
        &m_DevContext);
      if (FAILED(hr)) {
        return hr;
      }
    }
    m_backBuffer = new CTexture2DDX();

    //Get a texture from Swap Chain
    m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_backBuffer->m_Texture);

    //Create RTV
    if (FAILED(m_Device->CreateRenderTargetView(m_backBuffer->m_Texture,
    /******************************************/nullptr,
    /******************************************/&m_backBuffer->m_RTV))) {

      __debugbreak();
    }



    //Create DSV
    m_defaultDSV = static_cast<CTexture2DDX*>(createTex2D(inWidth,
    /****************************************************/inHeight,
    /****************************************************/1,
    /****************************************************/GI_FORMAT::E::kFORMAT_D24_UNORM_S8_UINT,
    /****************************************************/D3D11_BIND_DEPTH_STENCIL));

    //Create and set a ViewPort
    m_defaultVP = static_cast<CViewPort*>(createVP(inWidth, inHeight));


    return hr;
  }


  void*
  CGraphicsDX::createTex2D(int inWidth,
  /***********************/int inHeigh,
  /***********************/int inMipLevels,
  /***********************/GI_FORMAT::E inFormat,
  /***********************/int inBindFlags) {

    CTexture2DDX* temp = new CTexture2DDX();
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

    if (FAILED(m_Device->CreateTexture2D(&tempDesc, nullptr, &temp->m_Texture))) {
      //Send error message
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
      if (FAILED(m_Device->CreateRenderTargetView(temp->m_Texture, nullptr, &temp->m_RTV))) {
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
      if (FAILED(m_Device->CreateDepthStencilView(temp->m_Texture, nullptr, &temp->m_DSV))) {
        __debugbreak();
        return nullptr;
      }
    }

    if (D3D11_BIND_SHADER_RESOURCE & inBindFlags) {
      D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
      memset(&srvDesc, 0, sizeof(srvDesc));
      srvDesc.Format = tempDesc.Format;
      srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
      srvDesc.Texture2D.MipLevels = 0;
      srvDesc.Texture2D.MostDetailedMip = 0;
      if (FAILED(m_Device->CreateShaderResourceView(temp->m_Texture, nullptr, &temp->m_SRV))) {
        __debugbreak();
        return nullptr;
      }
    }

    return temp;

  }


  void* 
  CGraphicsDX::createVP(int inWidth, int inHeight) {
    CViewPort* temp = new CViewPort();
    temp->m_VP.Width = (float)inWidth;
    temp->m_VP.Height = (float)inHeight;
    temp->m_VP.MinDepth = 0.0f;
    temp->m_VP.MaxDepth = 1.0f;
    temp->m_VP.TopLeftX = 0;
    temp->m_VP.TopLeftY = 0;
    m_DevContext->RSSetViewports(1, &temp->m_VP);
    return temp;

  }


  void 
  CGraphicsDX::setVP(CViewPort& inVP) {
    m_DevContext->RSSetViewports(1, &inVP.m_VP);
  }


  void* 
  CGraphicsDX::createVS(wchar* inFileName,
  /********************/lpcstr inEntryPoint,
  /********************/lpcstr inShaderModel) {

    VertexShaderDX* tempVS = new VertexShaderDX();
    tempVS->init(inFileName, inEntryPoint, inShaderModel);
    if (FAILED(m_Device->CreateVertexShader(tempVS->m_CompiledVShader->GetBufferPointer(),
      tempVS->m_CompiledVShader->GetBufferSize(),
      nullptr,
      &tempVS->m_VS))) {

      __debugbreak();
      return nullptr;
    }


    return tempVS;
  }


  void* 
  CGraphicsDX::createPS(wchar* inFileName,
  /********************/lpcstr inEntryPoint,
  /********************/lpcstr inShaderModel) {
    PixelShaderDX* tempPS = new PixelShaderDX();
    tempPS->init(inFileName, inEntryPoint, inShaderModel);
    if (FAILED(m_Device->CreatePixelShader(tempPS->m_CompiledPShader->GetBufferPointer(),
      tempPS->m_CompiledPShader->GetBufferSize(),
      nullptr,
      &tempPS->m_PS))) {

      __debugbreak();
      return nullptr;
    }

    return tempPS;
  }


  void* 
  CGraphicsDX::createIL(Vector<InputLayoutDesc>& inDesc,
  /********************/BaseShader* inShader) {

    CInputLayoutDX* tempIL = new CInputLayoutDX();
    tempIL->init(inDesc);
    auto tmpVS = static_cast<VertexShaderDX*>(inShader);
    if (FAILED(m_Device->CreateInputLayout(tempIL->m_Descriptors.data(),
    /*************************************/inDesc.size(),
    /*************************************/tmpVS->m_CompiledVShader->GetBufferPointer(),
    /*************************************/tmpVS->m_CompiledVShader->GetBufferSize(),
    /*************************************/&tempIL->m_InputLayout))) {
      __debugbreak();
      return nullptr;
    }
    return tempIL;
  }


  void* 
  CGraphicsDX::createBuffer(unsigned int inByteWidth,
  /************************/unsigned int inBindFlags,
  /************************/unsigned int inOffset,
  /************************/void* inBufferData) {

    CBufferDX* tmpBuffer = new CBufferDX();
    CD3D11_BUFFER_DESC tmpDesc(inByteWidth, inBindFlags);
    D3D11_SUBRESOURCE_DATA tmpData;
    tmpData.pSysMem = inBufferData;
    tmpData.SysMemPitch = inByteWidth;
    tmpData.SysMemSlicePitch = 0;

    if (FAILED(m_Device->CreateBuffer(&tmpDesc,
      /******************************/(inBufferData == nullptr ? nullptr : &tmpData),
      /******************************/&tmpBuffer->m_Buffer))) {

      __debugbreak();
      return nullptr;
    }

    return tmpBuffer;
  }


  void* 
  CGraphicsDX::createSampler(SamplerDesc inDesc) {
    CSampler* tmpSampler = new CSampler();
    tmpSampler->init(inDesc);
    if (FAILED(m_Device->CreateSamplerState(&tmpSampler->m_Desc, &tmpSampler->m_Sampler))) {
      __debugbreak();
      return nullptr;
    }
    return tmpSampler;
  }


  void 
  CGraphicsDX::show() {
    m_SwapChain->Present(0, 0);
  }


  void 
  CGraphicsDX::setVertexBuffer(CBuffer* inBuffer,
  /***************************/unsigned int inStride) {
    UINT offset = 0;
    m_DevContext->IASetVertexBuffers(0, 
    /*******************************/1, 
    /*******************************/&static_cast<CBufferDX*>(inBuffer)->m_Buffer, 
    /*******************************/&inStride, 
    /*******************************/&offset);
  }


  void 
  CGraphicsDX::setIndexBuffer(CBuffer* inBuffer,
  /**************************/GI_FORMAT::E inFormat) {
    m_DevContext->IASetIndexBuffer(static_cast<CBufferDX*>(inBuffer)->m_Buffer, 
    /*****************************/static_cast<DXGI_FORMAT>(inFormat), 
    /*****************************/0);
  }


  void 
  CGraphicsDX::setTopology(GI_PRIMITIVE_TOPOLOGY::E inTopotology) {
    auto tmpTopology = static_cast<D3D_PRIMITIVE_TOPOLOGY>(inTopotology);
    m_DevContext->IASetPrimitiveTopology(tmpTopology);
  }


  void 
  CGraphicsDX::updateSubresource(CBuffer* inBuffer,
  /*****************************/void* inData,
  /*****************************/unsigned int inPitch) {

    auto tmpBuffer = static_cast<CBufferDX*>(inBuffer);
    m_DevContext->UpdateSubresource(tmpBuffer->m_Buffer, 
    /******************************/0, 
    /******************************/NULL, 
    /******************************/inData, 
    /******************************/inPitch, 
    /******************************/0);
  }


  void 
  CGraphicsDX::updateTexture(CTexture2D* inTexture,
  /*************************/const void* inData,
  /*************************/unsigned int inPitch,
  /*************************/unsigned int inDepthPitch) {

    m_DevContext->UpdateSubresource(static_cast<CTexture2DDX*>(inTexture)->m_Texture,
      0,
      NULL,
      inData,
      inPitch,
      inDepthPitch);
  }


  void 
  CGraphicsDX::clearRTV(CTexture2D* inRTV, float inColor[4]) {
    m_DevContext->ClearRenderTargetView(static_cast<CTexture2DDX*>(inRTV)->m_RTV,
      inColor);
  }


  void 
  CGraphicsDX::clearDSV(CTexture2D* inDSV) {
    m_DevContext->ClearDepthStencilView(static_cast<CTexture2DDX*>(inDSV)->m_DSV,
      D3D11_CLEAR_DEPTH,
      1.0f,
      0);
  }


  void 
  CGraphicsDX::vsSetShader(BaseShader* inVShader) {
    
    auto tmpShader = static_cast<VertexShaderDX*>(inVShader);

    ID3D11VertexShader* tmpVShader = nullptr;
    if (nullptr != tmpShader) {
      tmpVShader = tmpShader->m_VS;
    }
    m_DevContext->VSSetShader(tmpVShader, NULL, 0);
  }


  void 
  CGraphicsDX::vsSetConstantBuffer(unsigned int inSlot,
  /*******************************/CBuffer* inBuffer) {

    auto tmpBuffer = static_cast<CBufferDX*>(inBuffer);

    ID3D11Buffer* Buffer = nullptr;
    if (nullptr != inBuffer) {
      Buffer = tmpBuffer->m_Buffer;
    }
    m_DevContext->VSSetConstantBuffers(inSlot, 1, &Buffer);
  }


  void 
  CGraphicsDX::psSetShader(BaseShader* inPShader) {

    auto tmpShader = static_cast<PixelShaderDX*>(inPShader);

    ID3D11PixelShader* tmpPShader = nullptr;
    if (nullptr != tmpShader) {
      tmpPShader = tmpShader->m_PS;
    }

    m_DevContext->PSSetShader(tmpPShader, NULL, 0);
  }


  void 
  CGraphicsDX::psSetConstantBuffer(unsigned int inSlot,
  /*******************************/CBuffer* inBuffer) {

    m_DevContext->PSSetConstantBuffers(inSlot, 
    /*********************************/1, 
    /*********************************/&static_cast<CBufferDX*>(inBuffer)->m_Buffer);
  }


  void 
  CGraphicsDX::psSetShaderResource(unsigned int inSlot,
  /*******************************/CTexture2D* inTexture) {

    ID3D11ShaderResourceView* tmpSRV = nullptr;
    if (nullptr != inTexture) {
      tmpSRV = static_cast<CTexture2DDX*>(inTexture)->getSRV();
    }

    m_DevContext->PSSetShaderResources(inSlot, 1, &tmpSRV);
  }


  void 
  CGraphicsDX::psSetSampler(unsigned int inSlot,
  /************************/unsigned int inNumSamplers,
  /************************/CSampler* inSampler) {

    m_DevContext->PSSetSamplers(inSlot, inNumSamplers, &inSampler->m_Sampler);
  }


  void 
  CGraphicsDX::aiSetInputLayout(CInputLayout* inInputLayout) {
    m_DevContext->IASetInputLayout(static_cast<CInputLayoutDX*>(inInputLayout)->m_InputLayout);
  }


  void 
  CGraphicsDX::omSetRenderTarget(CTexture2D* inRT,
  /*****************************/CTexture2D* inDS) {

    ID3D11RenderTargetView* tmpRTV[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
    for (int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) {
      tmpRTV[i] = nullptr;
    }


    ID3D11DepthStencilView* tmpDSV = nullptr;

    if (nullptr != inDS) {
      tmpDSV = static_cast<CTexture2DDX*>(inDS)->m_DSV;
    }

    if (nullptr != inRT) {
      tmpRTV[0] = static_cast<CTexture2DDX*>(inRT)->m_RTV;
    }
    else {
      m_DevContext->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT,
        tmpRTV,
        tmpDSV);
      return;
    }


    m_DevContext->OMSetRenderTargets(1, tmpRTV, tmpDSV);

  }


  void 
  CGraphicsDX::draw(unsigned int inNumIndexes,
  /****************/unsigned int inStartLocation) {
    m_DevContext->DrawIndexed(inNumIndexes, inStartLocation, 0);
  }
}