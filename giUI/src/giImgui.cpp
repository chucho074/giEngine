#include <giVector2.h>
#include <giVector4.h>
#include <giTime.h>
#include <giInputManager.h>

#include <giBaseGraphicsAPI.h>
#include <giBuffer.h>
#include <giTexture2D.h>
#include <giBlendState.h>


#include "giImGui.h"

using giEngineSDK::uint8;
using giEngineSDK::GraphicsAPI;
using giEngineSDK::g_graphicsAPI;
using giEngineSDK::SharedPtr;
using giEngineSDK::Buffer;
using giEngineSDK::BaseVertexShader;
using giEngineSDK::BasePixelShader;
using giEngineSDK::InputLayout;
using giEngineSDK::Sampler;
using giEngineSDK::SamplerDesc;
using giEngineSDK::Texture2D;
using giEngineSDK::uint32;
using giEngineSDK::BaseRasterizerState;
using giEngineSDK::BaseDepthStencilState;
using giEngineSDK::BaseBlendState;
using giEngineSDK::Vector2;
using giEngineSDK::Vector4;
using giEngineSDK::GI_FORMAT::E;
using giEngineSDK::GI_BIND_FLAG::E;
using giEngineSDK::GI_PRIMITIVE_TOPOLOGY::E;


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
static void 
ImGui_ImplGI_InitPlatformInterface();

static void 
ImGui_ImplGI_ShutdownPlatformInterface();

// Functions
static void 
ImGui_ImplGI_SetupRenderState(ImDrawData* draw_data) {

  auto& gapi = g_graphicsAPI();

  ImGui_ImplGI_Data* bd = ImGui_ImplGI_GetBackendData();

  // Setup viewport
  gapi.createViewport(1,
                draw_data->DisplaySize.x, 
                draw_data->DisplaySize.y,
                0, 
                0);

  // Setup shader and vertex buffers
  unsigned int stride = sizeof(ImDrawVert);
  unsigned int offset = 0;
  //Set Input Layout
  gapi.aiSetInputLayout(bd->spInputLayout);
  //Set Vertex Buffer
  gapi.setVertexBuffer(bd->spVB, stride);
  //Set Index Buffer
  gapi.setIndexBuffer(bd->spIB, sizeof(ImDrawIdx) == 2 
                      ? giEngineSDK::GI_FORMAT::E::kFORMAT_R16_UINT
                      : giEngineSDK::GI_FORMAT::E::kFORMAT_R32_UINT);
  //Set Topology
  gapi.setTopology(giEngineSDK::GI_PRIMITIVE_TOPOLOGY::E::kPRIMITIVE_TOPOLOGY_TRIANGLELIST);
  //Set Vertex Shader
  gapi.vsSetShader(bd->spVertexShader);
  //Set Set Constant Buffer
  gapi.vsSetConstantBuffer(0, bd->spVertexConstantBuffer);
  //Set Pixel Shader
  gapi.psSetShader(bd->spPixelShader);
  //Set Sampler
  gapi.psSetSampler(0, 1, bd->spFontSampler);

  // Setup blend state
  const float blend_factor[4] = { 0.f, 0.f, 0.f, 0.f };
  gapi.omSetBlendState(bd->spBlendState, blend_factor);
  gapi.omSetDepthStencilState(bd->spDepthStencilState, 0);
  gapi.rsSetState(bd->spRasterizerState);
}

// Render function
void 
ImGui_ImplDX11_RenderDrawData(ImDrawData* draw_data) {
  auto& gapi = g_graphicsAPI();
  // Avoid rendering when minimized
  if (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f) {
    return;
  }
  
  ImGui_ImplGI_Data* bd = ImGui_ImplGI_GetBackendData();
  
  
  // Create and grow vertex/index buffers if needed
  if (!bd->spVB || bd->VertexBufferSize < draw_data->TotalVtxCount) {
    if (bd->spVB) { 
      //bd->spVB->Release(); 
      bd->spVB = NULL; 
    }
    bd->VertexBufferSize = draw_data->TotalVtxCount + 5000;

    bd->spVB = gapi.createBuffer(bd->VertexBufferSize * sizeof(ImDrawVert),
                                 giEngineSDK::GI_BIND_FLAG::E::kBIND_VERTEX_BUFFER,
                                 0,
                                 nullptr); 
  }

  if (!bd->spIB || bd->IndexBufferSize < draw_data->TotalIdxCount) {
    if (bd->spIB) { 
      bd->spIB = NULL; 
    }
    bd->IndexBufferSize = draw_data->TotalIdxCount + 10000;
    bd->spIB = gapi.createBuffer(bd->IndexBufferSize * sizeof(ImDrawIdx),
                                 giEngineSDK::GI_BIND_FLAG::E::kBIND_INDEX_BUFFER, 
                                 0,
                                 nullptr);
  }
  
  // Upload vertex/index data into a single contiguous GPU buffer
  Buffer * vtx_resource;
  Buffer * idx_resource;
  
  ImDrawVert* vtx_dst = (ImDrawVert*)vtx_resource;
  ImDrawIdx* idx_dst  = (ImDrawIdx*)idx_resource;

  for (int n = 0; n < draw_data->CmdListsCount; n++) {
    const ImDrawList* cmd_list = draw_data->CmdLists[n];
    memcpy(vtx_dst, 
           cmd_list->VtxBuffer.Data, 
           cmd_list->VtxBuffer.Size * sizeof(ImDrawVert));

    memcpy(idx_dst, 
           cmd_list->IdxBuffer.Data, 
           cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));

    vtx_dst += cmd_list->VtxBuffer.Size;
    idx_dst += cmd_list->IdxBuffer.Size;

    gapi.updateSubresource(bd->spVB, vtx_resource, 0);
    gapi.updateSubresource(bd->spIB, idx_resource, 0);
  }
  
  // Setup orthographic projection matrix into our constant buffer
  // Our visible imgui space lies from draw_data->DisplayPos (top left) to 
  // draw_data->DisplayPos+data_data->DisplaySize (bottom right). DisplayPos 
  // is (0,0) for single viewport apps.
  {
   
    float L = draw_data->DisplayPos.x;
    float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
    float T = draw_data->DisplayPos.y;
    float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
    float mvp[4][4] = {
        { 2.0f/(R-L),   0.0f,           0.0f,       0.0f },
        { 0.0f,         2.0f/(T-B),     0.0f,       0.0f },
        { 0.0f,         0.0f,           0.5f,       0.0f },
        { (R+L)/(L-R),  (T+B)/(B-T),    0.5f,       1.0f },
    };

    gapi.updateSubresource(bd->spVertexConstantBuffer, mvp, 0);

  }
  
  // Backup DX state that will be modified to restore it afterwards 
  // (unfortunately this is very ugly looking and verbose. Close your eyes!)
  struct BACKUP_GI_STATE {
    uint32                               ScissorRectsCount, ViewportsCount;
    Vector4                              ScissorRects[GI_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
    Vector2                              Viewports[GI_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
    SharedPtr<BaseRasterizerState>       RS;
    SharedPtr<BaseBlendState>            BlenState;
    float                                BlendFactor[4];
    uint32                               SampleMask;
    uint32                               StencilRef;
    SharedPtr<BaseDepthStencilState>     DepthStencilState;
    SharedPtr<Texture2D>                 PSShaderResource;
    SharedPtr<Sampler>                   PSSampler;
    SharedPtr<BasePixelShader>           PS;
    SharedPtr<BaseVertexShader>          VS;
    //Aqui iria el geometry shader... si tan solo lo tuvieras
    uint32                               PSInstancesCount, VSInstancesCount, GSInstancesCount;
    //ID3D11ClassInstance *     PSInstances[256], *VSInstances[256], *GSInstances[256];   // 256 is max according to PSSetShader documentation
    giEngineSDK::GI_PRIMITIVE_TOPOLOGY::E  PrimitiveTopology;
    SharedPtr<Buffer>                    IndexBuffer;
    SharedPtr<Buffer>                    VertexBuffer;
    SharedPtr<Buffer>                    VSConstantBuffer;
    uint32                               IndexBufferOffset, VertexBufferStride, VertexBufferOffset;
    giEngineSDK::GI_FORMAT::E            IndexBufferFormat;
    SharedPtr<InputLayout>               InputL;
  };

  BACKUP_GI_STATE old = {};
  old.ScissorRectsCount = old.ViewportsCount = GI_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
  //old.ScissorRects = gapi.rsGetScissorRects(old.ScissorRectsCount);
  //gapi.rsGetViewports(old.ViewportsCount, old.Viewports);
  old.RS = gapi.rsGetState();
  old.BlenState = gapi.omGetBlendState(old.BlendFactor, old.SampleMask);
  old.DepthStencilState = gapi.omGetDepthStencilState(old.StencilRef);
  old.PSShaderResource = gapi.psGetShaderResources(0, 1);
  old.PSSampler = gapi.psGetSamplers(0, 1);
  old.PSInstancesCount = old.VSInstancesCount = old.GSInstancesCount = 256;
  old.PS = gapi.psGetShader(old.PSInstancesCount);
  old.VS = gapi.vsGetShader(old.VSInstancesCount);
  old.VSConstantBuffer = gapi.vsGetConstantBuffers(0, 1);
  //Aqui iria el geometry shader... si tan solo lo tuvieras
  
  old.PrimitiveTopology = gapi.iaGetPrimitiveTopology();
  old.IndexBuffer = gapi.iaGetIndexBuffer(old.IndexBufferFormat, old.IndexBufferOffset);
  old.VertexBuffer = gapi.iaGetVertexBuffer(1, old.VertexBufferStride, old.VertexBufferOffset);
  old.InputL = gapi.iaGetInputLayout();
  
  // Setup desired DX state
  ImGui_ImplGI_SetupRenderState(draw_data);
  
  // Render command lists
  // (Because we merged all buffers into a single one, we maintain our own offset into them)
  int global_idx_offset = 0;
  int global_vtx_offset = 0;
  ImVec2 clip_off = draw_data->DisplayPos;
  for (int n = 0; n < draw_data->CmdListsCount; n++) {
    const ImDrawList* cmd_list = draw_data->CmdLists[n];
    for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
      const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
      if (pcmd->UserCallback != NULL) {
        // User callback, registered via ImDrawList::AddCallback()
        // (ImDrawCallback_ResetRenderState is a special callback value used 
        // by the user to request the renderer to reset render state.)
        if (pcmd->UserCallback == ImDrawCallback_ResetRenderState) {
            ImGui_ImplGI_SetupRenderState(draw_data);
        }
        else {
          pcmd->UserCallback(cmd_list, pcmd);
        }
      }
      else {
        // Project scissor/clipping rectangles into framebuffer space
        ImVec2 clip_min(pcmd->ClipRect.x - clip_off.x, pcmd->ClipRect.y - clip_off.y);
        ImVec2 clip_max(pcmd->ClipRect.z - clip_off.x, pcmd->ClipRect.w - clip_off.y);
        if (clip_max.x < clip_min.x || clip_max.y < clip_min.y) {
          continue;
        }
        // Apply scissor/clipping rectangle
        Vector4 r = { (LONG)clip_min.x, 
                      (LONG)clip_min.y, 
                      (LONG)clip_max.x, 
                      (LONG)clip_max.y };
        gapi.rsSetScissorRects(1, &r);
  
        // Bind texture, Draw
        SharedPtr<Texture2D> texture_srv;
        texture_srv.reset(pcmd->GetTexID());
        gapi.psSetShaderResource(0, texture_srv);
        gapi.drawIndexed(pcmd->ElemCount, 
                         pcmd->VtxOffset + global_vtx_offset);
      }
    }
    global_idx_offset += cmd_list->IdxBuffer.Size;
    global_vtx_offset += cmd_list->VtxBuffer.Size;
  }
  
  // Restore modified DX state
  gapi.rsSetScissorRects(old.ScissorRectsCount, old.ScissorRects);

  //gapi.rsSetViewports(old.ViewportsCount, old.Viewports);
  
  gapi.rsSetState(old.RS); 
  
  gapi.omSetBlendState(old.BlenState, old.BlendFactor, old.SampleMask); 
  
  gapi.omSetDepthStencilState(old.DepthStencilState, old.StencilRef); 
  
  gapi.psSetShaderResource(0, old.PSShaderResource); 
  
  gapi.psSetSampler(0, 1, old.PSSampler); 
  
  gapi.psSetShader(old.PS); 
  
  gapi.vsSetShader(old.VS); 
  
  gapi.vsSetConstantBuffer(0, old.VSConstantBuffer); 
  
  
  gapi.setTopology(old.PrimitiveTopology);

  gapi.setIndexBuffer(old.IndexBuffer, old.IndexBufferFormat); 
  
  gapi.setVertexBuffer(old.VertexBuffer, old.VertexBufferStride); 
  
  gapi.aiSetInputLayout(old.InputL);
  
}

static void 
ImGui_ImplGI_CreateFontsTexture() {
  auto& gapi = g_graphicsAPI();
  // Build texture atlas
  ImGuiIO& io = ImGui::GetIO();
  ImGui_ImplGI_Data* bd = ImGui_ImplGI_GetBackendData();
  uint8* pixels;
  int width, height;
  io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

  // Upload texture to graphics system
  {
    SharedPtr<Texture2D> tmpTex;
    tmpTex = gapi.createTex2D(width, 
                              height, 
                              1, 
                              giEngineSDK::GI_FORMAT::kFORMAT_R8G8B8A8_UNORM, 
                              giEngineSDK::GI_BIND_FLAG::kBIND_SHADER_RESOURCE);
    
    gapi.TextureFromMem(pixels, width, height);

  }

  // Store our identifier
  io.Fonts->SetTexID((ImTextureID*)bd->spFontTextureView);

  // Create texture sampler
  {
    SamplerDesc desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.filter = giEngineSDK::GI_FILTER::kFILTER_MIN_MAG_MIP_LINEAR;
    desc.addressU = giEngineSDK::GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
    desc.addressV = giEngineSDK::GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
    desc.addressW = giEngineSDK::GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
    //desc.mipLODBias = 0.f;
    desc.comparisonFunc = giEngineSDK::GI_COMPARATION_FUNC::kCOMPARISON_ALWAYS;
    desc.minLOD = 0.f;
    desc.maxLOD = 0.f;

    bd->spFontSampler = gapi.createSampler(desc);
  }
}

bool    
ImGui_ImplDX11_CreateDeviceObjects() {
  auto& gapi = g_graphicsAPI();

  ImGui_ImplGI_Data* bd = ImGui_ImplGI_GetBackendData();
  
  if (bd->spFontSampler) {
    ImGui_ImplGI_InvalidateDeviceObjects();
  }

  // Create the vertex shader
  {
    const char* vertexShader =
      "cbuffer vertexBuffer : register(b0) \
            {\
              float4x4 ProjectionMatrix; \
            };\
            struct VS_INPUT\
            {\
              float2 pos : POSITION;\
              float4 col : COLOR0;\
              float2 uv  : TEXCOORD0;\
            };\
            \
            struct PS_INPUT\
            {\
              float4 pos : SV_POSITION;\
              float4 col : COLOR0;\
              float2 uv  : TEXCOORD0;\
            };\
            \
            PS_INPUT main(VS_INPUT input)\
            {\
              PS_INPUT output;\
              output.pos = mul( ProjectionMatrix, float4(input.pos.xy, 0.f, 1.f));\
              output.col = input.col;\
              output.uv  = input.uv;\
              return output;\
            }";

    gapi.createVShaderFromMem(vertexShader, "main");

    

    // Create the input layout
    D3D11_INPUT_ELEMENT_DESC local_layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,   0, (UINT)IM_OFFSETOF(ImDrawVert, pos), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,   0, (UINT)IM_OFFSETOF(ImDrawVert, uv),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, (UINT)IM_OFFSETOF(ImDrawVert, col), D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    if (bd->pd3dDevice->CreateInputLayout(local_layout, 
                                          3, 
                                          vertexShaderBlob->GetBufferPointer(), 
                                          vertexShaderBlob->GetBufferSize(), 
                                          &bd->pInputLayout) != S_OK) {
      return false;
    }

    // Create the constant buffer
    {
      D3D11_BUFFER_DESC desc;
      desc.ByteWidth = sizeof(VERTEX_CONSTANT_BUFFER);
      desc.Usage = D3D11_USAGE_DYNAMIC;
      desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
      desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
      desc.MiscFlags = 0;
      bd->pd3dDevice->CreateBuffer(&desc, NULL, &bd->pVertexConstantBuffer);
    }
  }

  // Create the pixel shader
  {
    static const char* pixelShader =
      "struct PS_INPUT\
            {\
            float4 pos : SV_POSITION;\
            float4 col : COLOR0;\
            float2 uv  : TEXCOORD0;\
            };\
            sampler sampler0;\
            Texture2D texture0;\
            \
            float4 main(PS_INPUT input) : SV_Target\
            {\
            float4 out_col = input.col * texture0.Sample(sampler0, input.uv); \
            return out_col; \
            }";

    gapi.createPShaderFromMem(pixelShader, "main");
    ID3DBlob* pixelShaderBlob;
    if (FAILED(D3DCompile(pixelShader, strlen(pixelShader), NULL, NULL, NULL, "main", "ps_4_0", 0, 0, &pixelShaderBlob, NULL)))
      return false; // NB: Pass ID3DBlob* pErrorBlob to D3DCompile() to get error showing in (const char*)pErrorBlob->GetBufferPointer(). Make sure to Release() the blob!
    if (bd->pd3dDevice->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), NULL, &bd->pPixelShader) != S_OK)
    {
      pixelShaderBlob->Release();
      return false;
    }
    pixelShaderBlob->Release();
  }

  // Create the blending setup
  {
    D3D11_BLEND_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.AlphaToCoverageEnable = false;
    desc.RenderTarget[0].BlendEnable = true;
    desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
    desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    bd->pd3dDevice->CreateBlendState(&desc, &bd->pBlendState);
  }

  // Create the rasterizer state
  {
    D3D11_RASTERIZER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.FillMode = D3D11_FILL_SOLID;
    desc.CullMode = D3D11_CULL_NONE;
    desc.ScissorEnable = true;
    desc.DepthClipEnable = true;
    bd->pd3dDevice->CreateRasterizerState(&desc, &bd->pRasterizerState);
  }

  // Create depth-stencil State
  {
    D3D11_DEPTH_STENCIL_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.DepthEnable = false;
    desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
    desc.StencilEnable = false;
    desc.FrontFace.StencilFailOp = desc.FrontFace.StencilDepthFailOp = desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    desc.BackFace = desc.FrontFace;
    bd->pd3dDevice->CreateDepthStencilState(&desc, &bd->pDepthStencilState);
  }

  ImGui_ImplDX11_CreateFontsTexture();

  return true;
}

void    
ImGui_ImplDX11_InvalidateDeviceObjects()
{
  ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
  if (!bd->pd3dDevice)
    return;

  if (bd->pFontSampler) { bd->pFontSampler->Release(); bd->pFontSampler = NULL; }
  if (bd->pFontTextureView) { bd->pFontTextureView->Release(); bd->pFontTextureView = NULL; ImGui::GetIO().Fonts->SetTexID(NULL); } // We copied data->pFontTextureView to io.Fonts->TexID so let's clear that as well.
  if (bd->pIB) { bd->pIB->Release(); bd->pIB = NULL; }
  if (bd->pVB) { bd->pVB->Release(); bd->pVB = NULL; }
  if (bd->pBlendState) { bd->pBlendState->Release(); bd->pBlendState = NULL; }
  if (bd->pDepthStencilState) { bd->pDepthStencilState->Release(); bd->pDepthStencilState = NULL; }
  if (bd->pRasterizerState) { bd->pRasterizerState->Release(); bd->pRasterizerState = NULL; }
  if (bd->pPixelShader) { bd->pPixelShader->Release(); bd->pPixelShader = NULL; }
  if (bd->pVertexConstantBuffer) { bd->pVertexConstantBuffer->Release(); bd->pVertexConstantBuffer = NULL; }
  if (bd->pInputLayout) { bd->pInputLayout->Release(); bd->pInputLayout = NULL; }
  if (bd->pVertexShader) { bd->pVertexShader->Release(); bd->pVertexShader = NULL; }
}

bool
ImGui_ImplDX11_Init() {
  ImGuiIO& io = ImGui::GetIO();
  IM_ASSERT(io.BackendRendererUserData == NULL && "Already initialized a renderer backend!");

  // Setup backend capabilities flags
  ImGui_ImplGI_Data* bd = IM_NEW(ImGui_ImplGI_Data)();
  io.BackendRendererUserData = (void*)bd;
  io.BackendRendererName = "imgui_impl_GI";
  io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;  // We can honor the ImDrawCmd::VtxOffset field, allowing for large meshes.
  io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;  // We can create multi-viewports on the Renderer side (optional)

  // Get factory from device
  IDXGIDevice* pDXGIDevice = NULL;
  IDXGIAdapter* pDXGIAdapter = NULL;
  IDXGIFactory* pFactory = NULL;

  if (device->QueryInterface(IID_PPV_ARGS(&pDXGIDevice)) == S_OK)
    if (pDXGIDevice->GetParent(IID_PPV_ARGS(&pDXGIAdapter)) == S_OK)
      if (pDXGIAdapter->GetParent(IID_PPV_ARGS(&pFactory)) == S_OK) {
        bd->pd3dDevice = device;
        bd->pd3dDeviceContext = device_context;
        bd->pFactory = pFactory;
      }
  if (pDXGIDevice) pDXGIDevice->Release();
  if (pDXGIAdapter) pDXGIAdapter->Release();
  bd->pd3dDevice->AddRef();
  bd->pd3dDeviceContext->AddRef();

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    ImGui_ImplDX11_InitPlatformInterface();

  return true;
}

void 
ImGui_ImplDX11_Shutdown()
{
  ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
  IM_ASSERT(bd != NULL && "No renderer backend to shutdown, or already shutdown?");
  ImGuiIO& io = ImGui::GetIO();

  ImGui_ImplDX11_ShutdownPlatformInterface();
  ImGui_ImplDX11_InvalidateDeviceObjects();
  if (bd->pFactory) { bd->pFactory->Release(); }
  if (bd->pd3dDevice) { bd->pd3dDevice->Release(); }
  if (bd->pd3dDeviceContext) { bd->pd3dDeviceContext->Release(); }
  io.BackendRendererName = NULL;
  io.BackendRendererUserData = NULL;
  IM_DELETE(bd);
}

void 
ImGui_ImplDX11_NewFrame()
{
  ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
  IM_ASSERT(bd != NULL && "Did you call ImGui_ImplDX11_Init()?");

  if (!bd->pFontSampler)
    ImGui_ImplDX11_CreateDeviceObjects();
}

static void 
ImGui_ImplDX11_CreateWindow(ImGuiViewport* viewport) {

  auto& gapi = g_graphicsAPI();

  ImGui_ImplGI_Data* bd = ImGui_ImplGI_GetBackendData();
  ImGui_ImplGI_ViewportData* vd = IM_NEW(ImGui_ImplGI_ViewportData)();
  viewport->RendererUserData = vd;

  // PlatformHandleRaw should always be a HWND, whereas PlatformHandle might be a higher-level handle (e.g. GLFWWindow*, SDL_Window*).
  // Some backend will leave PlatformHandleRaw NULL, in which case we assume PlatformHandle will contain the HWND.
  HWND hwnd = viewport->PlatformHandleRaw ? (HWND)viewport->PlatformHandleRaw : (HWND)viewport->PlatformHandle;
  IM_ASSERT(hwnd != 0);

  // Create swap chain
  gapi.

  DXGI_SWAP_CHAIN_DESC sd;
  ZeroMemory(&sd, sizeof(sd));
  sd.BufferDesc.Width = (UINT)viewport->Size.x;
  sd.BufferDesc.Height = (UINT)viewport->Size.y;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.BufferCount = 1;
  sd.OutputWindow = hwnd;
  sd.Windowed = TRUE;
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
  sd.Flags = 0;

  IM_ASSERT(vd->SwapChain == NULL && vd->RTView == NULL);
  bd->pFactory->CreateSwapChain(bd->pd3dDevice, &sd, &vd->SwapChain);

  // Create the render target
  if (vd->SwapChain)
  {
    Texture2D* pBackBuffer;
    vd->SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    bd->m_device->CreateRenderTargetView(pBackBuffer, NULL, &vd->RTView);
    pBackBuffer->Release();
  }
}

static void ImGui_ImplDX11_DestroyWindow(ImGuiViewport* viewport)
{
  // The main viewport (owned by the application) will always have RendererUserData == NULL since we didn't create the data for it.
  if (ImGui_ImplDX11_ViewportData* vd = (ImGui_ImplDX11_ViewportData*)viewport->RendererUserData)
  {
    if (vd->SwapChain)
      vd->SwapChain->Release();
    vd->SwapChain = NULL;
    if (vd->RTView)
      vd->RTView->Release();
    vd->RTView = NULL;
    IM_DELETE(vd);
  }
  viewport->RendererUserData = NULL;
}

static void ImGui_ImplDX11_SetWindowSize(ImGuiViewport* viewport, ImVec2 size)
{
  ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
  ImGui_ImplDX11_ViewportData* vd = (ImGui_ImplDX11_ViewportData*)viewport->RendererUserData;
  if (vd->RTView)
  {
    vd->RTView->Release();
    vd->RTView = NULL;
  }
  if (vd->SwapChain)
  {
    ID3D11Texture2D* pBackBuffer = NULL;
    vd->SwapChain->ResizeBuffers(0, (UINT)size.x, (UINT)size.y, DXGI_FORMAT_UNKNOWN, 0);
    vd->SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    if (pBackBuffer == NULL) { fprintf(stderr, "ImGui_ImplDX11_SetWindowSize() failed creating buffers.\n"); return; }
    bd->pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &vd->RTView);
    pBackBuffer->Release();
  }
}

static void ImGui_ImplDX11_RenderWindow(ImGuiViewport* viewport, void*)
{
  ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
  ImGui_ImplDX11_ViewportData* vd = (ImGui_ImplDX11_ViewportData*)viewport->RendererUserData;
  ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
  bd->pd3dDeviceContext->OMSetRenderTargets(1, &vd->RTView, NULL);
  if (!(viewport->Flags & ImGuiViewportFlags_NoRendererClear))
    bd->pd3dDeviceContext->ClearRenderTargetView(vd->RTView, (float*)&clear_color);
  ImGui_ImplDX11_RenderDrawData(viewport->DrawData);
}

static void ImGui_ImplDX11_SwapBuffers(ImGuiViewport* viewport, void*)
{
  ImGui_ImplDX11_ViewportData* vd = (ImGui_ImplDX11_ViewportData*)viewport->RendererUserData;
  vd->SwapChain->Present(0, 0); // Present without vsync
}

static void ImGui_ImplDX11_InitPlatformInterface()
{
  ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
  platform_io.Renderer_CreateWindow = ImGui_ImplDX11_CreateWindow;
  platform_io.Renderer_DestroyWindow = ImGui_ImplDX11_DestroyWindow;
  platform_io.Renderer_SetWindowSize = ImGui_ImplDX11_SetWindowSize;
  platform_io.Renderer_RenderWindow = ImGui_ImplDX11_RenderWindow;
  platform_io.Renderer_SwapBuffers = ImGui_ImplDX11_SwapBuffers;
}

static void ImGui_ImplDX11_ShutdownPlatformInterface()
{
  ImGui::DestroyPlatformWindows();
}
