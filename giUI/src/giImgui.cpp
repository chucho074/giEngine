#include <giVector2.h>
#include <giTime.h>
#include <giInputManager.h>

#include <giBaseGraphicsAPI.h>
#include <giBuffer.h>
#include <giTexture2D.h>
#include <giBlendState.h>

#include "giImGui.h"

using giEngineSDK::GraphicsAPI;
using giEngineSDK::g_graphicsAPI;
using giEngineSDK::SharedPtr;
using giEngineSDK::Buffer;
using giEngineSDK::BaseVertexShader;
using giEngineSDK::BasePixelShader;
using giEngineSDK::InputLayout;
using giEngineSDK::Sampler;
using giEngineSDK::Texture2D;
using giEngineSDK::uint32;
using giEngineSDK::Rasterizer;
using giEngineSDK::DepthState;
using giEngineSDK::BlendState;
using giEngineSDK::GI_FORMAT::E;
using giEngineSDK::GI_PRIMITIVE_TOPOLOGY::E;

// DirectX11 data
struct ImGui_ImplGI_Data {
  
  SharedPtr<Buffer>           spVB;
  SharedPtr<Buffer>           spIB;
  SharedPtr<BaseVertexShader> spVertexShader;
  SharedPtr<InputLayout>      spInputLayout;
  SharedPtr<Buffer>           spVertexConstantBuffer;
  SharedPtr<BasePixelShader>  spPixelShader;
  SharedPtr<Sampler>          spFontSampler;
  SharedPtr<Texture2D>        spFontTextureView;
  SharedPtr<Rasterizer>       spRasterizerState;
  SharedPtr<BlendState>       spBlendState;
  SharedPtr<DepthState>       spDepthStencilState;
  uint32                      VertexBufferSize;
  uint32                      IndexBufferSize;

  ImGui_ImplGI_Data() { 
    memset(this, 0, sizeof(*this)); 
    VertexBufferSize = 5000; 
    IndexBufferSize = 10000; 
  }
};

struct 
VERTEX_CONSTANT_BUFFER {
  float mvp[4][4];
};

// Backend data stored in io.BackendRendererUserData 
// to allow support for multiple Dear ImGui contexts
// It is STRONGLY preferred that you use docking branch 
// with multi-viewports (== single Dear ImGui context + multiple windows) 
// instead of multiple Dear ImGui contexts.
static 
ImGui_ImplGI_Data* ImGui_ImplGI_GetBackendData() {
  return ImGui::GetCurrentContext() ? 
          (ImGui_ImplGI_Data*)ImGui::GetIO().BackendRendererUserData : NULL;
}

// Forward Declarations
static void ImGui_ImplGI_InitPlatformInterface();
static void ImGui_ImplGI_ShutdownPlatformInterface();

// Functions
static void 
ImGui_ImplGI_SetupRenderState(ImDrawData* draw_data) {

  auto& gapi = g_graphicsAPI();

  ImGui_ImplGI_Data* bd = ImGui_ImplGI_GetBackendData();

  // Setup viewport
  gapi.createVP(1,
                draw_data->DisplaySize.x, 
                draw_data->DisplaySize.y,
                0, 
                0);

  // Setup shader and vertex buffers
  unsigned int stride = sizeof(ImDrawVert);
  unsigned int offset = 0;
  //Set Input Layout
  gapi.aiSetInputLayout(bd->spInputLayout.get());
  //Set Vertex Buffer
  gapi.setVertexBuffer(bd->spVB.get(), stride);
  //Set Index Buffer
  gapi.setIndexBuffer(bd->spIB.get(), sizeof(ImDrawIdx) == 2 
                      ? giEngineSDK::GI_FORMAT::E::kFORMAT_R16_UINT
                      : giEngineSDK::GI_FORMAT::E::kFORMAT_R32_UINT);
  //Set Topology
  gapi.setTopology(giEngineSDK::GI_PRIMITIVE_TOPOLOGY::E::kPRIMITIVE_TOPOLOGY_TRIANGLELIST);
  //Set Vertex Shader
  gapi.vsSetShader(bd->spVertexShader.get());
  //Set Set Constant Buffer
  gapi.vsSetConstantBuffer(0, bd->spVertexConstantBuffer.get());
  //Set Pixel Shader
  gapi.psSetShader(bd->spPixelShader.get());
  //Set Sampler
  gapi.psSetSampler(0, 1, bd->spFontSampler.get());

  // Setup blend state
  const float blend_factor[4] = { 0.f, 0.f, 0.f, 0.f };
  gapi.omSetBlendState(bd->spBlendState.get(), blend_factor);
  gapi.omSetDepthStencilState(bd->spDepthStencilState, 0);
  gapi.RSSetState(bd->spRasterizerState);
}