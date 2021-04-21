/**
 * @file    giGraphicsOGL.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    20/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giGraphicsOGL.h"

namespace giEngineSDK {
  GraphicsOGL::GraphicsOGL() {
  }

  GraphicsOGL::~GraphicsOGL() {

  }

  void 
  GraphicsOGL::init(void* inWindow, int inWidth, int inHeight) {

  }
  
  bool 
  GraphicsOGL::createDeviceAndSwpaChain(void* inWindow, int inWidth, int inHeight) {
    return false;
  }

  CTexture2D* 
  GraphicsOGL::createTex2D(int inWidth, 
  /***********************/int inHeigh, 
  /***********************/int inMipLevels, 
  /***********************/GI_FORMAT::E inFormat, 
  /***********************/int inBindFlags) {
    return nullptr;
  }
  
  void
  GraphicsOGL::createVP(uint32 inNumVP, 
  /********************/int inWidth, 
  /********************/int inHeight, 
  /********************/int inTopX, 
  /********************/int inTopY) {

    //glViewport(inTopX, inTopY, inWidth, inHeight);

  }

  
  BaseVertexShader* 
  GraphicsOGL::createVS(lpcstr inFileName, lpcstr inEntryPoint, lpcstr inShaderModel) {
    return nullptr;
  }
  
  BasePixelShader* 
  GraphicsOGL::createPS(lpcstr inFileName, lpcstr inEntryPoint, lpcstr inShaderModel) {
    return nullptr;
  }
  
  CInputLayout*
  GraphicsOGL::createIL(Vector<InputLayoutDesc>& inDesc, BaseShader* inShader) {
    return nullptr;
  }
  
  CBuffer* 
  GraphicsOGL::createBuffer(uint32 inByteWidth, 
  /************************/uint32 inBindFlags, 
  /************************/uint32 inOffset, 
  /************************/void* inBufferData) {
    return nullptr;
  }
  
  CSampler* 
  GraphicsOGL::createSampler(SamplerDesc inDesc) {
    return nullptr;
  }
  
  void 
  GraphicsOGL::show() {

  }
  
  void 
  GraphicsOGL::setVertexBuffer(CBuffer* inBuffer, uint32 inStride) {

  }
  
  void 
  GraphicsOGL::setIndexBuffer(CBuffer* inBuffer, GI_FORMAT::E inFormat) {
  
  }
  
  void 
  GraphicsOGL::setTopology(GI_PRIMITIVE_TOPOLOGY::E inTopotology) {

  }
  
  void 
  GraphicsOGL::updateSubresource(CBuffer* inBuffer, void* inData, uint32 inPitch) {

  }
  
  void 
  GraphicsOGL::updateTexture(CTexture2D* inTexture, 
  /*************************/const void* inData, 
  /*************************/uint32 inPitch, 
  /*************************/uint32 inDepthPitch) {

  }
  
  void 
  GraphicsOGL::clearRTV(CTexture2D* inRTV, float inColor[4]) {
  
  }
  
  void 
  GraphicsOGL::clearDSV(CTexture2D* inDSV) {
  
  }
  
  void 
  GraphicsOGL::vsSetShader(BaseShader* inVShader) {
  
  }
  
  void 
  GraphicsOGL::vsSetConstantBuffer(uint32 inSlot, CBuffer* inBuffer) {
  
  }
  
  void 
  GraphicsOGL::psSetShader(BaseShader* inPShader) {

  }
  
  void 
  GraphicsOGL::psSetConstantBuffer(uint32 inSlot, CBuffer* inBuffer) {
  
  }
  
  void 
  GraphicsOGL::psSetShaderResource(uint32 inSlot, CTexture2D* inTexture) {
  
  }
  
  void 
  GraphicsOGL::psSetSampler(uint32 inSlot, uint32 inNumSamplers, CSampler* inSampler) {
  
  }
  
  void 
  GraphicsOGL::aiSetInputLayout(CInputLayout* inInputLayout) {
  
  }
  
  void 
  GraphicsOGL::omSetRenderTarget(CTexture2D* inRT, CTexture2D* inDS) {
  
  }
  
  void 
  GraphicsOGL::draw(uint32 inNumIndexes, uint32 inStartLocation) {
  
  }
}