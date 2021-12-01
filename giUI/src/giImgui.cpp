#include <giVector2.h>
#include <giVector4.h>
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
  gapi.omSetDepthStencilState(bd->spDepthStencilState.get(), 0);
  gapi.rsSetState(bd->spRasterizerState.get());
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

    if (gapi.createBuffer(bd->VertexBufferSize * sizeof(ImDrawVert), 
                          giEngineSDK::GI_BIND_FLAG::E::kBIND_VERTEX_BUFFER,
                          0,
                          &bd->spVB) < 0) {
      return;
    }
  }

  if (!bd->spIB || bd->IndexBufferSize < draw_data->TotalIdxCount) {
    if (bd->spIB) { 
      bd->spIB = NULL; 
    }
    bd->IndexBufferSize = draw_data->TotalIdxCount + 10000;
    if (gapi.createBuffer(bd->IndexBufferSize * sizeof(ImDrawIdx),
                          giEngineSDK::GI_BIND_FLAG::E::kBIND_INDEX_BUFFER, 
                          0,
                          &bd->spIB) < 0) {
      return;
    }
  }
  
  // Upload vertex/index data into a single contiguous GPU buffer
  Texture2D * vtx_resource;
  
  Texture2D * idx_resource;
  
  ImDrawVert* vtx_dst = (ImDrawVert*)vtx_resource->pData;
  ImDrawIdx* idx_dst  = (ImDrawIdx*)idx_resource->pData;

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

    gapi.updateSubresource(bd->spVB.get(), vtx_resource, 0);
    gapi.updateSubresource(bd->spIB.get(), idx_resource, 0);
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

    gapi.updateSubresource(bd->spVertexConstantBuffer.get(), mvp, 0);

  }
  
  // Backup DX state that will be modified to restore it afterwards 
  // (unfortunately this is very ugly looking and verbose. Close your eyes!)
  struct BACKUP_GI_STATE {
    uint32                    ScissorRectsCount, ViewportsCount;
    Vector4                   ScissorRects[GI_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
    Vector2                   Viewports[GI_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
    Rasterizer*               RS;
    BlendState*               BlenState;
    float                     BlendFactor[4];
    uint32                    SampleMask;
    uint32                    StencilRef;
    DepthState*               DepthStencilState;
    Texture2D*                PSShaderResource;
    Sampler*                  PSSampler;
    BasePixelShader*          PS;
    BaseVertexShader*         VS;
    //ID3D11GeometryShader*     GS;
    uint32                    PSInstancesCount, VSInstancesCount, GSInstancesCount;
    //ID3D11ClassInstance *     PSInstances[256], *VSInstances[256], *GSInstances[256];   // 256 is max according to PSSetShader documentation
    giEngineSDK::GI_PRIMITIVE_TOPOLOGY::E  PrimitiveTopology;
    Buffer*                   IndexBuffer;
    Buffer*                   VertexBuffer;
    Buffer*                   VSConstantBuffer;
    uint32                    IndexBufferOffset, VertexBufferStride, VertexBufferOffset;
    giEngineSDK::GI_FORMAT::E IndexBufferFormat;
    InputLayout*              InputL;
  };

  BACKUP_GI_STATE old = {};
  old.ScissorRectsCount = old.ViewportsCount = GI_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
  gapi.rsGetScissorRects(&old.ScissorRectsCount, old.ScissorRects);
  gapi.rsGetViewports(&old.ViewportsCount, old.Viewports);
  gapi.rsGetState(&old.RS);
  gapi.omGetBlendState(&old.BlendState, old.BlendFactor, &old.SampleMask);
  gapi.omGetDepthStencilState(&old.DepthStencilState, &old.StencilRef);
  gapi.psGetShaderResources(0, 1, &old.PSShaderResource);
  gapi.psGetSamplers(0, 1, &old.PSSampler);
  old.PSInstancesCount = old.VSInstancesCount = old.GSInstancesCount = 256;
  gapi.psGetShader(&old.PS, old.PSInstances, &old.PSInstancesCount);
  gapi.vsGetShader(&old.VS, old.VSInstances, &old.VSInstancesCount);
  gapi.vsGetConstantBuffers(0, 1, &old.VSConstantBuffer);
  //gapi.gsGetShader(&old.GS, old.GSInstances, &old.GSInstancesCount);
  
  gapi.iaGetPrimitiveTopology(&old.PrimitiveTopology);
  gapi.iaGetIndexBuffer(&old.IndexBuffer, &old.IndexBufferFormat, &old.IndexBufferOffset);
  gapi.iaGetVertexBuffers(0, 1, &old.VertexBuffer, &old.VertexBufferStride, &old.VertexBufferOffset);
  gapi.iaGetInputLayout(&old.InputL);
  
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
        const D3D11_RECT r = { (LONG)clip_min.x, 
                               (LONG)clip_min.y, 
                               (LONG)clip_max.x, 
                               (LONG)clip_max.y };
        gapi.rsSetScissorRects(1, &r);
  
        // Bind texture, Draw
        SharedPtr<Texture2D> texture_srv = (ID3D11ShaderResourceView*)pcmd->GetTexID();
        gapi.psSetShaderResources(0, 1, &texture_srv);
        gapi.drawIndexed(pcmd->ElemCount, 
                         pcmd->IdxOffset + global_idx_offset, 
                         pcmd->VtxOffset + global_vtx_offset);
      }
    }
    global_idx_offset += cmd_list->IdxBuffer.Size;
    global_vtx_offset += cmd_list->VtxBuffer.Size;
  }
  
  // Restore modified DX state
  gapi.RSSetScissorRects(old.ScissorRectsCount, old.ScissorRects);
  gapi.RSSetViewports(old.ViewportsCount, old.Viewports);
  gapi.RSSetState(old.RS); 
  if (old.RS) {
    old.RS->Release();
  }
  gapi.OMSetBlendState(old.BlenState, old.BlendFactor, old.SampleMask); 
  if (old.BlenState) {
    old.BlenState->Release();
  }
  gapi.omSetDepthStencilState(old.DepthStencilState, old.StencilRef); 
  if (old.DepthStencilState) {
    old.DepthStencilState->Release();
  }
  gapi.psSetShaderResource(0, 1, &old.PSShaderResource); 
  if (old.PSShaderResource) {
    old.PSShaderResource->Release();
  }
  gapi.psSetSampler(0, 1, &old.PSSampler); 
  if (old.PSSampler) {
    old.PSSampler->Release();
  }
  gapi.psSetShader(old.PS, old.PSInstances, old.PSInstancesCount); 
  if (old.PS) {
    old.PS->Release();
  }
  for (uint32 i = 0; i < old.PSInstancesCount; i++) { 
    if (old.PSInstances[i]) {
      old.PSInstances[i]->Release(); 
    }
  }
  gapi.vsSetShader(old.VS, old.VSInstances, old.VSInstancesCount); 
  if (old.VS) {
    old.VS->Release();
  }
  gapi.vsSetConstantBuffer(0, 1, &old.VSConstantBuffer); 
  if (old.VSConstantBuffer) {
    old.VSConstantBuffer->Release();
  }
  gapi.gsSetShader(old.GS, old.GSInstances, old.GSInstancesCount); 
  if (old.GS) { 
    old.GS->Release();
  }
  for (uint32 i = 0; i < old.VSInstancesCount; i++) { 
    if (old.VSInstances[i]) {
      old.VSInstances[i]->Release();
    }
  }
  gapi.iaSetPrimitiveTopology(old.PrimitiveTopology);
  gapi.iaSetIndexBuffer(old.IndexBuffer, old.IndexBufferFormat, old.IndexBufferOffset); 
  if (old.IndexBuffer) {
    old.IndexBuffer->Release();
  }
  gapi.iaSetVertexBuffers(0, 1, &old.VertexBuffer, &old.VertexBufferStride, &old.VertexBufferOffset); 
  if (old.VertexBuffer) {
    old.VertexBuffer->Release();
  }
  gapi.iaSetInputLayout(old.InputLayout); 
  if (old.InputLayout) {
    old.InputLayout->Release();
  }
}