/**
 * @file    giGraphicsOGL.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    20/04/2021
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giGraphicsOGL.h"
#include "giBufferOGL.h"
#include "giTexture2DOGL.h"
#include "giInputLayoutOGL.h"


namespace giEngineSDK {
  GraphicsOGL::GraphicsOGL() {

  }

  GraphicsOGL::~GraphicsOGL() {
    wglDeleteContext(oglRenderContext);
  }

  void 
  GraphicsOGL::init(void* inWindow, int inWidth, int inHeight) {
    PIXELFORMATDESCRIPTOR desc = {
      sizeof(PIXELFORMATDESCRIPTOR),
      1,
      PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
      PFD_TYPE_RGBA,
      32,
      0, 0, 0, 0, 0, 0,
      0,
      0,
      0,
      0, 0, 0, 0,
      24,
      8,
      0,
      PFD_MAIN_PLANE,
      0,
      0, 0, 0
    };

    auto window = static_cast<WindowBase*>(inWindow);
    m_handle = GetDC(window->getSystemHandle());

    int32 pxlFormat = ChoosePixelFormat(m_handle, &desc);

    SetPixelFormat(m_handle, pxlFormat, &desc);

    oglRenderContext = wglCreateContext(m_handle);


    if (!gladLoadGL()) {
      //Error boi
    }
  }
  
  bool 
  GraphicsOGL::createDeviceAndSwpaChain(void* inWindow, 
                                        int32 inWidth, 
                                        int32 inHeight) {
    return false;
  }

  Texture2D* 
  GraphicsOGL::createTex2D(int32 inWidth, 
                           int32 inHeigh, 
                           int32 inMipLevels, 
                           GI_FORMAT::E inFormat, 
                           int32 inBindFlags) {

    Texture2DOGL* tmpTexture = new Texture2DOGL();
    
    
    if (GI_BIND_FLAG::kBIND_DEPTH_STENCIL & inBindFlags) {
      //Generate the render buffer object
      glGenRenderbuffers(1, &tmpTexture->m_texture);
      //Bind the render buffer
      glBindRenderbuffer(GL_RENDERBUFFER, tmpTexture->m_texture);
      //Storage the render buffer
      glRenderbufferStorage(GL_RENDERBUFFER, getFormat(inFormat), inWidth, inHeigh);
    } 
    else {
      //Generate the texture
      glGenTextures(1, &tmpTexture->m_texture);
      //Bind the texture
      glBindTexture(GL_TEXTURE_2D, tmpTexture->m_texture);
      //Create the image
      glTexImage2D(GL_TEXTURE_2D,
                   0,
                   getFormat(inFormat),
                   inWidth,
                   inHeigh,
                   0,
                   getImgFormat(inFormat),
                   GL_UNSIGNED_BYTE,
                   NULL);
    }
    if (GI_BIND_FLAG::kBIND_RENDER_TARGET & inBindFlags) {
      //Generate the Frame buffer
      glGenFramebuffers(1, &tmpTexture->m_bufferFrame);
      //Bind the texture
      glBindFramebuffer(GL_FRAMEBUFFER, tmpTexture->m_bufferFrame);
      //Fill the decription of the texture
      //Filters
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      //Wraps
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }


    return tmpTexture;
  }
  
  void
  GraphicsOGL::createViewport(uint32 inNumVP, 
                        int32 inWidth, 
                        int32 inHeight, 
                        int32 inTopX, 
                        int32 inTopY) {

    glViewport(inTopX, inTopY, inWidth, inHeight);

  }

  
  BaseVertexShader* 
  GraphicsOGL::createVShaderFromFile(String inFileName, 
                        String inEntryPoint, 
                        String inShaderModel) {
    return nullptr;
  }
  
  BasePixelShader* 
  GraphicsOGL::createPShaderFromFile(String inFileName, 
                        String inEntryPoint, 
                        String inShaderModel) {
    return nullptr;
  }
  
  InputLayout*
  GraphicsOGL::createInputLayout(Vector<InputLayoutDesc>& inDesc, BaseShader* inShader) {
    InputLayoutOGL* tmpLayout = new InputLayoutOGL();
    glGenVertexArrays(1, &tmpLayout->m_vao);
    glBindVertexArray(tmpLayout->m_vao);
    
    return tmpLayout;
  }
  
  Buffer* 
  GraphicsOGL::createBuffer(uint32 inByteWidth, 
                            uint32 inBindFlags, 
                            uint32 inOffset, 
                            void* inBufferData) {
    //Create the buffer
    BufferOGL* tmpBuffer = new BufferOGL();
    //Create in OGL
    glGenBuffers(1, &tmpBuffer->m_buffer);
    
    if (0 != inByteWidth) {
      //Set the size
      tmpBuffer->m_size = inByteWidth;
      if (GI_BIND_FLAG::kBIND_VERTEX_BUFFER ==  inBindFlags) {
        tmpBuffer->m_buffer = GL_ARRAY_BUFFER;
      }
      if (GI_BIND_FLAG::kBIND_INDEX_BUFFER ==  inBindFlags) {
        tmpBuffer->m_buffer = GL_ELEMENT_ARRAY_BUFFER;
      }
      if (GI_BIND_FLAG::kBIND_CONSTANT_BUFFER ==  inBindFlags) {
        tmpBuffer->m_buffer = GL_UNIFORM_BUFFER;
      }

      //Set the bind to the buffer
      glBindBuffer(tmpBuffer->m_type, tmpBuffer->m_buffer);

      //Set the data in the buffer
      glBufferData(tmpBuffer->m_type, tmpBuffer->m_size, inBufferData, GL_STATIC_DRAW);
      
      //UnBind the buffer for not errors
      glBindBuffer(tmpBuffer->m_type, 0);
      //Return the info
      return tmpBuffer;
    }
    //Error in size
    return nullptr;

  }
  
  SamplerState* 
  GraphicsOGL::createSampler(SamplerDesc inDesc) {
    return nullptr;
  }
  
  void 
  GraphicsOGL::show() {
    SwapBuffers(m_handle);
  }
  
  void 
  GraphicsOGL::setVertexBuffer(Buffer* inBuffer, uint32 inStride) {

  }
  
  void 
  GraphicsOGL::setIndexBuffer(Buffer* inBuffer, GI_FORMAT::E inFormat) {
  
  }
  
  void 
  GraphicsOGL::setTopology(GI_PRIMITIVE_TOPOLOGY::E inTopotology) {
    switch (inTopotology) {
    case giEngineSDK::GI_PRIMITIVE_TOPOLOGY::kPRIMITIVE_TOPOLOGY_POINTLIST: {
      m_topology = GL_POINTS;
      break;
    }
    case giEngineSDK::GI_PRIMITIVE_TOPOLOGY::kPRIMITIVE_TOPOLOGY_LINELIST: {
      m_topology = GL_LINES;
      break;
    }
    case giEngineSDK::GI_PRIMITIVE_TOPOLOGY::kPRIMITIVE_TOPOLOGY_LINESTRIP: {
      m_topology = GL_LINE_STRIP;
      break;
    }
    case giEngineSDK::GI_PRIMITIVE_TOPOLOGY::kPRIMITIVE_TOPOLOGY_TRIANGLELIST: {
      m_topology = GL_TRIANGLES;
      break;
    }
    case giEngineSDK::GI_PRIMITIVE_TOPOLOGY::kPRIMITIVE_TOPOLOGY_TRIANGLESTRIP: {
      m_topology = GL_TRIANGLE_STRIP;
      break;
    }
    case giEngineSDK::GI_PRIMITIVE_TOPOLOGY::kPRIMITIVE_TOPOLOGY_LINELIST_ADJ: {
      m_topology = GL_LINES_ADJACENCY;
      break;
    }
    case giEngineSDK::GI_PRIMITIVE_TOPOLOGY::kPRIMITIVE_TOPOLOGY_LINESTRIP_ADJ: {
      m_topology = GL_LINE_STRIP_ADJACENCY;
      break;
    }
    case giEngineSDK::GI_PRIMITIVE_TOPOLOGY::kPRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ: {
      m_topology = GL_TRIANGLES_ADJACENCY;
      break;
    }
    case giEngineSDK::GI_PRIMITIVE_TOPOLOGY::kPRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ: {
      m_topology = GL_TRIANGLE_STRIP_ADJACENCY;
      break;
    }
    default:
      m_topology = GL_INVALID_ENUM;
      break;
    }
  }
  
  void 
  GraphicsOGL::updateSubresource(Buffer* inBuffer, void* inData, uint32 inPitch) {

    auto tmpBuffer = static_cast<BufferOGL*>(inBuffer);

    //Set the bind to the buffer
    glBindBuffer(tmpBuffer->m_type, tmpBuffer->m_buffer);

    //Set the data in the buffer
    glBufferSubData(tmpBuffer->m_type, 0, tmpBuffer->m_size, inData);

    //UnBind the buffer for not errors
    glBindBuffer(tmpBuffer->m_type, 0);
  }
  
  void 
  GraphicsOGL::updateTexture(Texture2D* inTexture, 
                             const void* inData, 
                             uint32 inPitch, 
                             uint32 inDepthPitch) {

  }

  void 
  GraphicsOGL::clearBackTexture(float inColor[4]) {
    glClearColor(inColor[0],inColor[1],inColor[2],inColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
  
  void 
  GraphicsOGL::clearRTV(Texture2D* inRTV, float inColor[4]) {
  
  }
  
  void 
  GraphicsOGL::clearDSV(Texture2D* inDSV) {
  }
  
  void 
  GraphicsOGL::vsSetShader(BaseShader* inVShader) {
  
  }
  
  void 
  GraphicsOGL::vsSetConstantBuffer(uint32 inSlot, Buffer* inBuffer) {
  
  }
  
  void 
  GraphicsOGL::psSetShader(BaseShader* inPShader) {

  }
  
  void 
  GraphicsOGL::psSetConstantBuffer(uint32 inSlot, Buffer* inBuffer) {
  
  }
  
  void 
  GraphicsOGL::psSetShaderResource(uint32 inSlot, Texture2D* inTexture) {
  
  }
  
  void 
  GraphicsOGL::psSetSamplerState(uint32 inSlot, 
                            uint32 inNumSamplers, 
                            SamplerState* inSampler) {
  
  }
  
  void 
  GraphicsOGL::aiSetInputLayout(InputLayout* inInputLayout) {
    glBindVertexArray(static_cast<InputLayoutOGL*>(inInputLayout)->m_vao);
  }
  
  void 
  GraphicsOGL::omSetRenderTarget(Texture2D* inRT, Texture2D* inDS) {
  
  }
  
  void 
  GraphicsOGL::drawIndexed(uint32 inNumIndexes, uint32 inStartLocation) {
    glDrawElements(m_topology, inNumIndexes, GL_UNSIGNED_INT, 0);
  }
  
  int32 
  GraphicsOGL::getFormat(GI_FORMAT::E inFormat) {
    

    //derecha es este formato
    if(GI_FORMAT::kFORMAT_R8_SNORM   == inFormat ) {
      return GL_RED;
    }
    if(GI_FORMAT::kFORMAT_R16_SNORM  == inFormat ) {
      return GL_RED;
    }
    if(GI_FORMAT::kFORMAT_R16_FLOAT  == inFormat ) {
      return GL_RED;
    }
    if(GI_FORMAT::kFORMAT_R32_FLOAT  == inFormat ) {
      return GL_RED;
    }
    if(GI_FORMAT::kFORMAT_R8_UINT    == inFormat ) {
      return GL_RED_INTEGER;
    }
    if(GI_FORMAT::kFORMAT_R16_UINT   == inFormat ) {
      return GL_RED_INTEGER;
    }
    if(GI_FORMAT::kFORMAT_R32_UINT   == inFormat ) {
      return GL_RED_INTEGER;
    }
    if(GI_FORMAT::kFORMAT_R8_UNORM   == inFormat ) {
      return GL_RED;
    }
    if(GI_FORMAT::kFORMAT_R16_UNORM  == inFormat ) {
      return GL_RED;
    }

  }

  int32 
  GraphicsOGL::getImgFormat(GI_FORMAT::E inFormat) {
    
    if(GI_FORMAT::kFORMAT_R8_SNORM   == inFormat) { 
      return GL_R8_SNORM;  
    }
    if(GI_FORMAT::kFORMAT_R16_SNORM  == inFormat) { 
      return GL_R16_SNORM; 
    }
    if(GI_FORMAT::kFORMAT_R16_FLOAT  == inFormat) { 
      return GL_R16F;      
    }
    if(GI_FORMAT::kFORMAT_R32_FLOAT  == inFormat) { 
      return GL_R32F;      
    }
    if(GI_FORMAT::kFORMAT_R8_UINT    == inFormat) { 
      return GL_R8UI;      
    }
    if(GI_FORMAT::kFORMAT_R16_UINT   == inFormat) { 
      return GL_R16UI;     
    }
    if(GI_FORMAT::kFORMAT_R32_UINT   == inFormat) { 
      return GL_R32UI;     
    }
    if(GI_FORMAT::kFORMAT_R8_UNORM   == inFormat) { 
      return GL_R8;        
    }
    if(GI_FORMAT::kFORMAT_R16_UNORM  == inFormat) { 
      return GL_R16;       
    }
  }
}