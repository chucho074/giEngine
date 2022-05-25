/**
 * @file    giImgui.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    03/05/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */

/**
  * @include
  */

#include <giVector4.h>
#include <giTime.h>
#include <giBaseInput.h>
#include <giInputLayout.h>
#include <giMatrix4.h>
#include <giTexture2D.h>
#include <giBaseGraphicsAPI.h>
#include <giBuffer.h>
#include <giTexture2D.h>
#include <giBlendState.h>


#include "giImGui.h"
#include <iostream>

using giEngineSDK::uint8;
using giEngineSDK::int32;
using giEngineSDK::GraphicsAPI;
//using giEngineSDK::g_graphicsAPI;
using giEngineSDK::SharedPtr;
using giEngineSDK::Buffer;
using giEngineSDK::BaseVertexShader;
using giEngineSDK::BasePixelShader;
using giEngineSDK::InputLayout;
using giEngineSDK::InputLayoutDesc;
using giEngineSDK::SamplerState;
using giEngineSDK::SamplerDesc;
using giEngineSDK::Texture2D;
using giEngineSDK::uint32;
using giEngineSDK::BaseRasterizerState;
using giEngineSDK::BaseDepthStencilState;
using giEngineSDK::BaseBlendState;
using giEngineSDK::Vector;
using giEngineSDK::Vector4;
using giEngineSDK::Matrix4;


// giEngine data
struct ImGui_ImplGI_Data {

  SharedPtr<Buffer>                    spVB;
  SharedPtr<Buffer>                    spIB;
  SharedPtr<BaseVertexShader>          spVertexShader;
  SharedPtr<BasePixelShader>           spPixelShader;
  SharedPtr<InputLayout>               spInputLayout;
  SharedPtr<Buffer>                    spVertexConstantBuffer;
  SharedPtr<SamplerState>              spFontSampler;
  SharedPtr<BaseRasterizerState>       spRasterizerState;
  SharedPtr<BaseDepthStencilState>     spDepthStencilState;
  SharedPtr<BaseBlendState>            spBlendState;
  SharedPtr<Texture2D>                 spFontTextureView;
  uint32                               VertexBufferSize;
  uint32                               IndexBufferSize;

  ImGui_ImplGI_Data() {
    memset(this, 0, sizeof(*this));
    VertexBufferSize = 5000;
    IndexBufferSize = 10000;
  }
};

//Backup state that will be modified to restore it later
struct BACKUP_STATE {
  SharedPtr<BaseRasterizerState>        spRasterState;
  SharedPtr<BaseBlendState>             spBlendState;
  SharedPtr<BaseDepthStencilState>      spDepthState;
  SharedPtr<SamplerState>               spSamplerState;
  SharedPtr<BaseVertexShader>           spVertexShader;
  SharedPtr<BasePixelShader>            spPixelShader;
  SharedPtr<Buffer>                     spIndexBuffer;
  SharedPtr<Buffer>                     spVertexBuffer;
  SharedPtr<Buffer>                     spVertexCB;
  SharedPtr<InputLayout>                spInputLayout;
  SharedPtr<Texture2D>                  spShaderResource;
  uint32 vertexStride = 0;
  uint32 vertexOffset = 0;
};

struct
VERTEX_CONSTANT_BUFFER {
  float mvp[4][4];
};


struct ImGui_MouseData {
  bool MouseTracked;
  ImGuiMouseCursor LastMouseCursor;
};


static
ImGui_ImplGI_Data* ImGui_ImplGI_GetBackendData() {
  return ImGui::GetCurrentContext() ?
    (ImGui_ImplGI_Data*)ImGui::GetIO().BackendRendererUserData : NULL;
}

// Forward Declarations
//static void 
//ImGui_ImplGI_InitPlatformInterface();
//
//static void 
//ImGui_ImplGI_ShutdownPlatformInterface();

 //Functions
static void
ImGui_ImplGI_SetupRenderState(ImDrawData* draw_data) {

  auto& gapi = giEngineSDK::g_graphicsAPI();

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
  gapi.setIndexBuffer(bd->spIB, giEngineSDK::GI_FORMAT::E::kFORMAT_R16_UINT);
  //Set Topology
  gapi.setTopology(giEngineSDK::GI_PRIMITIVE_TOPOLOGY::E::kPRIMITIVE_TOPOLOGY_TRIANGLELIST);
  //Set Vertex Shader
  gapi.vsSetShader(bd->spVertexShader);
  //Set Set Constant Buffer
  gapi.vsSetConstantBuffer(0, bd->spVertexConstantBuffer);
  //Set Pixel Shader
  gapi.psSetShader(bd->spPixelShader);
  //Set SamplerState
  gapi.psSetSamplerState(0, 1, bd->spFontSampler);

  // Setup blend state
  gapi.omSetBlendState(bd->spBlendState);
  gapi.omSetDepthStencilState(bd->spDepthStencilState);
  gapi.rsSetRasterizerState(bd->spRasterizerState);
}

namespace ImGui {

  static ImGui_MouseData*
  ImGui_MouseData_GetBackendData() {
    return ImGui::GetCurrentContext() ?
      static_cast<ImGui_MouseData*>(ImGui::GetIO().BackendPlatformUserData) :
      nullptr;
  }

  static ImGui_ImplGI_Data*
  ImGui_ImplGI_GetBackendData() {
    return ImGui::GetCurrentContext() ?
      static_cast<ImGui_ImplGI_Data*>(ImGui::GetIO().BackendRendererUserData) :
      nullptr;
  }

  void
  init(void* inWindow, Vector2 inWindowSize) {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_MouseData* data = IM_NEW(ImGui_MouseData);
    io.BackendPlatformUserData = (void*)data;
    io.BackendPlatformName = "imgui_impl_win32";
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    ImGuiViewport* mainViewport = ImGui::GetMainViewport();
    mainViewport->PlatformHandle = mainViewport->PlatformHandleRaw = inWindow;

    //Inputs of the keyboard

    io.DisplaySize = ImVec2(inWindowSize.x, inWindowSize.y);

    ImGui::StyleColorsDark();

    ImGui_ImplGI_Data* tmpData = IM_NEW(ImGui_ImplGI_Data);
    io.BackendRendererName = "ImGui_giImplementation";
    io.BackendRendererUserData = static_cast<void*>(tmpData);
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

    auto& gapi = giEngineSDK::g_graphicsAPI();

    const char* vertexShader = {
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
              output.pos = mul(ProjectionMatrix, float4(input.pos.xy, 0.f, 1.f));\
              output.col = input.col;\
              output.uv  = input.uv;\
              return output;\
            }" };

    tmpData->spVertexShader = gapi.createVShaderFromMem(vertexShader, "main");

    static const char* pixelShader = {
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
            }" };

    tmpData->spPixelShader = gapi.createPShaderFromMem(pixelShader, "main");

    //Create Input Layout
    Vector<InputLayoutDesc> layoutDesc;

    //Set the size for the inputLayout
    layoutDesc.resize(3);

    //Sets the input Layout values

    //Positions
    layoutDesc[0].semanticName = "POSITION";
    layoutDesc[0].semanticIndex = 0;
    layoutDesc[0].format = giEngineSDK::GI_FORMAT::kFORMAT_R32G32_FLOAT;
    layoutDesc[0].inputSlot = 0;
    layoutDesc[0].alignedByteOffset = IM_OFFSETOF(ImDrawVert, pos);
    layoutDesc[0].inputSlotClass = giEngineSDK::GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
    layoutDesc[0].instanceDataStepRate = 0;

    //texcoords
    layoutDesc[1].semanticName = "TEXCOORD";
    layoutDesc[1].semanticIndex = 0;
    layoutDesc[1].format = giEngineSDK::GI_FORMAT::kFORMAT_R32G32_FLOAT;
    layoutDesc[1].inputSlot = 0;
    layoutDesc[1].alignedByteOffset = IM_OFFSETOF(ImDrawVert, uv);;
    layoutDesc[1].inputSlotClass = giEngineSDK::GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
    layoutDesc[1].instanceDataStepRate = 0;

    //color
    layoutDesc[2].semanticName = "COLOR";
    layoutDesc[2].semanticIndex = 0;
    layoutDesc[2].format = giEngineSDK::GI_FORMAT::kFORMAT_R8G8B8A8_UNORM;
    layoutDesc[2].inputSlot = 0;
    layoutDesc[2].alignedByteOffset = IM_OFFSETOF(ImDrawVert, col);;
    layoutDesc[2].inputSlotClass = giEngineSDK::GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
    layoutDesc[2].instanceDataStepRate = 0;

    //Create the Input Layout
    tmpData->spInputLayout = gapi.createInputLayout(layoutDesc, tmpData->spVertexShader);

    //
    tmpData->spVertexConstantBuffer = gapi.createBuffer(sizeof(Matrix4),
                                                        giEngineSDK::GI_BIND_FLAG::kBIND_CONSTANT_BUFFER,
                                                        nullptr);
    //Create Blend State
    Vector4 tmpkk = { 0.f, 0.f, 0.f, 0.f };
    tmpData->spBlendState = gapi.createBlendState(true,
                                                  giEngineSDK::BLEND_TYPE::src_alpha,
                                                  giEngineSDK::BLEND_TYPE::inv_src_alpha,
                                                  giEngineSDK::BLEND_OP::add,
                                                  giEngineSDK::BLEND_TYPE::one,
                                                  giEngineSDK::BLEND_TYPE::inv_src_alpha,
                                                  giEngineSDK::BLEND_OP::add,
                                                  //Vector4(0.f, 0.f, 0.f, 0.f));
                                                  tmpkk);

    //Create raster state
    tmpData->spRasterizerState = gapi.createRasterizer(giEngineSDK::FILLMODE::kSolid,
                                                       giEngineSDK::CULLMODE::kNone,
                                                       false,
                                                       true);

    //Create Depth stencil state
    tmpData->spDepthStencilState = gapi.createDepthState(false,
                                                         false,
                                                         giEngineSDK::GI_COMPARATION_FUNC::kCOMPARISON_ALWAYS);

    //Build Texture Atlas
    uint8* tmpPixels;
    int32 tmpWidth, tmpHeight;
    io.Fonts->GetTexDataAsRGBA32(&tmpPixels, &tmpWidth, &tmpHeight);

    // Upload texture to graphics system
    
    tmpData->spFontTextureView = gapi.TextureFromMem(tmpPixels,
                                 tmpWidth,
                                 tmpHeight,
                                 giEngineSDK::GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
                                 giEngineSDK::GI_BIND_FLAG::kBIND_SHADER_RESOURCE);
    

    // Store our identifier
    io.Fonts->SetTexID(static_cast<ImTextureID>(&tmpData->spFontTextureView));

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

      tmpData->spFontSampler = gapi.createSampler(desc);
    }
  }

  void
  update(void* inWindow, float inDT) {
    ImGuiIO& io = ImGui::GetIO();

    ImGui_MouseData* tmpData = ImGui_MouseData_GetBackendData();

    IM_ASSERT(tmpData != nullptr && "Failed backend platform initialization.\n");
    const ImVec2 mousePosPrev = io.MousePos;
    io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
    io.MouseHoveredViewport = 0;

    if (io.WantSetMousePos) {
      Vector2 pos(mousePosPrev.x, mousePosPrev.y);
      ::SetCursorPos(pos.x, pos.y);
    }

    //Set dear ImGui mouse Position from OS position
    POINT mouseScreenPos;
    if (!::GetCursorPos(&mouseScreenPos)) {
      return;
    }
    ::ScreenToClient((HWND)inWindow, &mouseScreenPos);
    io.MousePos = ImVec2((float)mouseScreenPos.x, (float)mouseScreenPos.y);
    //Update OS mouse cursor with the cursor requested by imgui.
    ImGuiMouseCursor mouseCursor = io.MouseDrawCursor ? ImGuiMouseCursor_None :
                                   ImGui::GetMouseCursor();
    if (tmpData->LastMouseCursor != mouseCursor) {
      tmpData->LastMouseCursor = mouseCursor;
      if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) {
        return;
      }
      ImGuiMouseCursor imguiCursor = ImGui::GetMouseCursor();
      if (imguiCursor != ImGuiMouseCursor_None || io.MouseDrawCursor) {
        //Hide OS mouse cursor if imgui is drawing it or if it wants no cursor.
        ::SetCursor(0);
      }
      else {
        //Show OS mouse cursor.
        LPTSTR win32Cursor = IDC_ARROW;
        switch (imguiCursor) {
        case ImGuiMouseCursor_Arrow: {
          win32Cursor = IDC_ARROW;
          break;
        }
        case ImGuiMouseCursor_TextInput: {
          win32Cursor = IDC_IBEAM;
          break;
        }
        case ImGuiMouseCursor_ResizeAll: {
          win32Cursor = IDC_SIZEALL;
          break;
        }
        case ImGuiMouseCursor_ResizeEW: {
          win32Cursor = IDC_SIZEWE;
          break;
        }
        case ImGuiMouseCursor_ResizeNS: {
          win32Cursor = IDC_SIZENS;
          break;
        }
        case ImGuiMouseCursor_ResizeNESW: {
          win32Cursor = IDC_SIZENESW;
          break;
        }
        case ImGuiMouseCursor_ResizeNWSE: {
          win32Cursor = IDC_SIZENWSE;
          break;
        }
        case ImGuiMouseCursor_Hand: {
          win32Cursor = IDC_HAND;
          break;
        }
        case ImGuiMouseCursor_NotAllowed: {
          win32Cursor = IDC_NO;
          break;
        }
        }
        ::SetCursor(::LoadCursor(0, win32Cursor));
      }
      UNREFERENCED_PARAMETER(inDT);
      callBack();
    }

  }

  void
  render() {
    ImGui::Render();
    ImDrawData* data = ImGui::GetDrawData();
    if (0 == data->CmdListsCount) {
      return;
    }
    ImGuiIO& io = ImGui::GetIO();
    assert(io.Fonts->TexID != NULL);

    int32 width = static_cast<int32>(io.DisplaySize.x * io.DisplayFramebufferScale.x);
    int32 height = static_cast<int32>(io.DisplaySize.y * io.DisplayFramebufferScale.y);
    if (0 == width || 0 == height) {
      return;
    }
    data->ScaleClipRects(io.DisplayFramebufferScale);
    ImGui_ImplGI_Data* tmpData = ImGui_ImplGI_GetBackendData();

    auto& gapi = giEngineSDK::g_graphicsAPI();

    //Create and grow vertex/index buffer if needed
    if (!tmpData->spVB || tmpData->VertexBufferSize < data->TotalVtxCount) {
      if (tmpData->spVB) {
        tmpData->spVB.reset();
      }
      tmpData->VertexBufferSize = data->TotalVtxCount;
      tmpData->spVB = gapi.createBuffer(tmpData->VertexBufferSize * sizeof(ImDrawVert),
                                        giEngineSDK::GI_BIND_FLAG::kBIND_VERTEX_BUFFER,
                                        nullptr);
    }
    if (!tmpData->spIB || tmpData->IndexBufferSize < data->TotalIdxCount) {
      if (tmpData->spIB) {
        tmpData->spIB.reset();
      }
      tmpData->IndexBufferSize = data->TotalIdxCount;
      tmpData->spIB = gapi.createBuffer(tmpData->IndexBufferSize * sizeof(ImDrawIdx),
                                        giEngineSDK::GI_BIND_FLAG::kBIND_INDEX_BUFFER,
                                        nullptr);
    }
    //Upload vertex/index data
    Vector<ImDrawVert> vertices;
    Vector<ImDrawIdx> indices;
    for (int32 n = 0; n < data->CmdListsCount; ++n) {
      const ImDrawList* cmd_list = data->CmdLists[n];
      for (int32 x = 0; x < cmd_list->VtxBuffer.Size; ++x) {
        vertices.push_back(cmd_list->VtxBuffer[x]);
      }
      for (int32 y = 0; y < cmd_list->IdxBuffer.Size; ++y) {
        indices.push_back(cmd_list->IdxBuffer[y]);
      }
    }
    gapi.updateSubresource(tmpData->spVB, vertices.data(), 0);
    gapi.updateSubresource(tmpData->spIB, indices.data(), 0);
    float L = data->DisplayPos.x;
    float R = data->DisplayPos.x + data->DisplaySize.x;
    float T = data->DisplayPos.y;
    float B = data->DisplayPos.y + data->DisplaySize.y;
    float mvp[4][4] =
    {
        { 2.0f / (R - L),      0.0f,               0.0f,       0.0f },
        { 0.0f,                2.0f / (T - B),     0.0f,       0.0f },
        { 0.0f,                0.0f,               0.5f,       0.0f },
        { (R + L) / (L - R),  (T + B) / (B - T),   0.5f,       1.0f },
    };
    gapi.updateSubresource(tmpData->spVertexConstantBuffer, &mvp, 0);

    //Backup the old information.
    BACKUP_STATE old = {};
    //old.ScissorRects = gapi.rsGetScissorRects(old.ScissorRectsCount);
    //gapi.rsGetViewports(old.ViewportsCount, old.Viewports);
    old.spRasterState = gapi.rsGetState();
    old.spBlendState = gapi.omGetBlendState();
    old.spDepthState = gapi.omGetDepthStencilState();
    old.spShaderResource = gapi.psGetShaderResources(0, 1);
    old.spSamplerState = gapi.psGetSamplers(0, 1);
    old.spPixelShader = gapi.psGetShader();
    old.spVertexShader = gapi.vsGetShader();
    old.spVertexCB = gapi.vsGetConstantBuffers(0, 1);
    //Aqui iria el geometry shader... si tan solo lo tuvieras

    old.spIndexBuffer = gapi.iaGetIndexBuffer();
    old.spVertexBuffer = gapi.iaGetVertexBuffer(1, old.vertexStride, old.vertexOffset);
    old.spInputLayout = gapi.iaGetInputLayout();

    // Setup desired DX state
    ImGui_ImplGI_SetupRenderState(data);

    // Render command lists
    // (Because we merged all buffers into a single one, we maintain our own offset into them)
    int global_idx_offset = 0;
    int global_vtx_offset = 0;
    ImVec2 clip_off = data->DisplayPos;
    for (int n = 0; n < data->CmdListsCount; n++) {
      const ImDrawList* cmd_list = data->CmdLists[n];
      for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
        const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
        if (pcmd->UserCallback != NULL) {
          // User callback, registered via ImDrawList::AddCallback()
          // (ImDrawCallback_ResetRenderState is a special callback value used 
          // by the user to request the renderer to reset render state.)
          if (pcmd->UserCallback == ImDrawCallback_ResetRenderState) {
            ImGui_ImplGI_SetupRenderState(data);
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
          Vector4 r = { clip_min.x,
                        clip_min.y,
                        clip_max.x,
                        clip_max.y };
          gapi.rsSetScissorRects(1, &r);

          // Bind texture, Draw
          SharedPtr<Texture2D>* texture_srv = static_cast<SharedPtr<Texture2D>*>(pcmd->GetTexID());
          //texture_srv.reset(pcmd->GetTexID());
          gapi.psSetShaderResource(0, *texture_srv);
          gapi.drawIndexed(pcmd->ElemCount,
                           pcmd->VtxOffset + global_vtx_offset);
        }
      }
      global_idx_offset += cmd_list->IdxBuffer.Size;
      global_vtx_offset += cmd_list->VtxBuffer.Size;
    }

    //gapi.rsSetViewports(old.ViewportsCount, old.Viewports);

    gapi.rsSetRasterizerState(old.spRasterState);

    gapi.omSetBlendState(old.spBlendState);

    gapi.omSetDepthStencilState(old.spDepthState);

    gapi.psSetShaderResource(0, old.spShaderResource);

    gapi.psSetSamplerState(0, 1, old.spSamplerState);

    gapi.psSetShader(old.spPixelShader);

    gapi.vsSetShader(old.spVertexShader);

    gapi.vsSetConstantBuffer(0, old.spVertexCB);

    //gapi.setTopology(old.spPrimitiveTopology);

    gapi.setIndexBuffer(old.spIndexBuffer,
                        giEngineSDK::GI_FORMAT::kFORMAT_R16_UINT);

    gapi.setVertexBuffer(old.spVertexBuffer, old.vertexStride);

    gapi.aiSetInputLayout(old.spInputLayout);
  }

  void
  shutDown() {
    ImGui_MouseData* be = ImGui_MouseData_GetBackendData();
    IM_ASSERT(be != nullptr && "No platform backend to shutdown, or already shutdown?");
    ImGui_ImplGI_Data* bd = ImGui_ImplGI_GetBackendData();
    IM_ASSERT(bd != nullptr && "No renderer backend to shitdon, or already shutdown?");
    ImGuiIO& io = ImGui::GetIO();

    ImGui::DestroyPlatformWindows();
    io.BackendRendererName = nullptr;
    io.BackendRendererUserData = nullptr;
    io.BackendPlatformName = nullptr;
    io.BackendPlatformUserData = nullptr;
    IM_DELETE(bd);
    IM_DELETE(be);
    ImGui::DestroyContext();
  }

  void
  callBack() {
    ImGuiIO& io = ImGui::GetIO();
    //Mouse Pressed case
    {
      int32 button = -1;
      button = giEngineSDK::g_inputManager().isMouseButtonPressed(giEngineSDK::MOUSE_BUTTONS::kLEFTCLIC) ?
        0 : button;
      button = giEngineSDK::g_inputManager().isMouseButtonPressed(giEngineSDK::MOUSE_BUTTONS::kRIGHTCLIC) ?
        1 : button;
      button = giEngineSDK::g_inputManager().isMouseButtonPressed(giEngineSDK::MOUSE_BUTTONS::kMIDCLIC) ?
        2 : button;
      button = giEngineSDK::g_inputManager().isMouseButtonPressed(giEngineSDK::MOUSE_BUTTONS::kBUTTON3) ?
        3 : button;
      button = giEngineSDK::g_inputManager().isMouseButtonPressed(giEngineSDK::MOUSE_BUTTONS::kBUTTON4) ?
        4 : button;
      if (button > -1) {
        io.MouseDown[button] = true;
      }
    }
    //Mouse released case
    {
      int32 button = -1;
      button = giEngineSDK::g_inputManager().isMouseButtonReleassed(giEngineSDK::MOUSE_BUTTONS::kLEFTCLIC) ?
        0 : button;
      button = giEngineSDK::g_inputManager().isMouseButtonReleassed(giEngineSDK::MOUSE_BUTTONS::kRIGHTCLIC) ?
        1 : button;
      button = giEngineSDK::g_inputManager().isMouseButtonReleassed(giEngineSDK::MOUSE_BUTTONS::kMIDCLIC) ?
        2 : button;
      button = giEngineSDK::g_inputManager().isMouseButtonReleassed(giEngineSDK::MOUSE_BUTTONS::kBUTTON3) ?
        3 : button;
      button = giEngineSDK::g_inputManager().isMouseButtonReleassed(giEngineSDK::MOUSE_BUTTONS::kBUTTON4) ?
        4 : button;
      if (button > -1) {
        io.MouseDown[button] = false;
      }
    }
  }

}