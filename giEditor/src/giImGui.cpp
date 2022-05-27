///**
// * @file    giImgui.cpp
// * @author  Jesus Alberto Del Moral Cupil
// * @e       idv18c.jmoral@uartesdigitales.edu.mx
// * @date    03/05/2022
// * @brief   A basic description of the what do the doc.
// * @bug     No known Bugs.
// */
//
///**
//  * @include
//  */
//
//#include <giVector4.h>
//#include <giTime.h>
//#include <giBaseInput.h>
//#include <giInputLayout.h>
//#include <giMatrix4.h>
//#include <giTexture2D.h>
//#include <giBaseGraphicsAPI.h>
//#include <giBuffer.h>
//#include <giTexture2D.h>
//#include <giBlendState.h>
//
//
//#include "giImGui.h"
//#include <iostream>
//
//using giEngineSDK::uint8;
//using giEngineSDK::int32;
//using giEngineSDK::GraphicsAPI;
////using giEngineSDK::g_graphicsAPI;
//using giEngineSDK::SharedPtr;
//using giEngineSDK::Buffer;
//using giEngineSDK::BaseVertexShader;
//using giEngineSDK::BasePixelShader;
//using giEngineSDK::InputLayout;
//using giEngineSDK::InputLayoutDesc;
//using giEngineSDK::SamplerState;
//using giEngineSDK::SamplerDesc;
//using giEngineSDK::Texture2D;
//using giEngineSDK::uint32;
//using giEngineSDK::BaseRasterizerState;
//using giEngineSDK::BaseDepthStencilState;
//using giEngineSDK::BaseBlendState;
//using giEngineSDK::Vector;
//using giEngineSDK::Vector4;
//using giEngineSDK::Matrix4;
//
//
//// giEngine data
//struct ImGui_ImplGI_Data {
//
//  SharedPtr<Buffer>                    spVB;
//  SharedPtr<Buffer>                    spIB;
//  SharedPtr<BaseVertexShader>          spVertexShader;
//  SharedPtr<BasePixelShader>           spPixelShader;
//  SharedPtr<InputLayout>               spInputLayout;
//  SharedPtr<Buffer>                    spVertexConstantBuffer;
//  SharedPtr<SamplerState>              spFontSampler;
//  SharedPtr<BaseRasterizerState>       spRasterizerState;
//  SharedPtr<BaseDepthStencilState>     spDepthStencilState;
//  SharedPtr<BaseBlendState>            spBlendState;
//  SharedPtr<Texture2D>                 spFontTextureView;
//  uint32                               VertexBufferSize;
//  uint32                               IndexBufferSize;
//
//  ImGui_ImplGI_Data() {
//    memset(this, 0, sizeof(*this));
//    VertexBufferSize = 5000;
//    IndexBufferSize = 10000;
//  }
//};
//
////Backup state that will be modified to restore it later
//struct BACKUP_STATE {
//  SharedPtr<BaseRasterizerState>        spRasterState;
//  SharedPtr<BaseBlendState>             spBlendState;
//  SharedPtr<BaseDepthStencilState>      spDepthState;
//  SharedPtr<SamplerState>               spSamplerState;
//  SharedPtr<BaseVertexShader>           spVertexShader;
//  SharedPtr<BasePixelShader>            spPixelShader;
//  SharedPtr<Buffer>                     spIndexBuffer;
//  SharedPtr<Buffer>                     spVertexBuffer;
//  SharedPtr<Buffer>                     spVertexCB;
//  SharedPtr<InputLayout>                spInputLayout;
//  SharedPtr<Texture2D>                  spShaderResource;
//  uint32 vertexStride = 0;
//  uint32 vertexOffset = 0;
//};
//
//struct
//VERTEX_CONSTANT_BUFFER {
//  float mvp[4][4];
//};
//
//
//struct ImGui_MouseData {
//  bool MouseTracked;
//  ImGuiMouseCursor LastMouseCursor;
//};
//
//
//static
//ImGui_ImplGI_Data* ImGui_ImplGI_GetBackendData() {
//  return ImGui::GetCurrentContext() ?
//    (ImGui_ImplGI_Data*)ImGui::GetIO().BackendRendererUserData : NULL;
//}
//
//// Forward Declarations
////static void 
////ImGui_ImplGI_InitPlatformInterface();
////
////static void 
////ImGui_ImplGI_ShutdownPlatformInterface();
//
// //Functions
//static void
//ImGui_ImplGI_SetupRenderState(ImDrawData* draw_data) {
//
//  auto& gapi = giEngineSDK::g_graphicsAPI();
//
//  ImGui_ImplGI_Data* bd = ImGui_ImplGI_GetBackendData();
//
//  // Setup viewport
//  gapi.createViewport(1,
//                      draw_data->DisplaySize.x,
//                      draw_data->DisplaySize.y,
//                      0,
//                      0);
//
//  // Setup shader and vertex buffers
//  unsigned int stride = sizeof(ImDrawVert);
//  unsigned int offset = 0;
//  //Set Input Layout
//  gapi.aiSetInputLayout(bd->spInputLayout);
//  //Set Vertex Buffer
//  gapi.setVertexBuffer(bd->spVB, stride);
//  //Set Index Buffer
//  gapi.setIndexBuffer(bd->spIB, giEngineSDK::GI_FORMAT::E::kFORMAT_R16_UINT);
//  //Set Topology
//  gapi.setTopology(giEngineSDK::GI_PRIMITIVE_TOPOLOGY::E::kPRIMITIVE_TOPOLOGY_TRIANGLELIST);
//  //Set Vertex Shader
//  gapi.vsSetShader(bd->spVertexShader);
//  //Set Set Constant Buffer
//  gapi.vsSetConstantBuffer(0, bd->spVertexConstantBuffer);
//  //Set Pixel Shader
//  gapi.psSetShader(bd->spPixelShader);
//  //Set SamplerState
//  gapi.psSetSamplerState(0, 1, bd->spFontSampler);
//
//  // Setup blend state
//  gapi.omSetBlendState(bd->spBlendState);
//  gapi.omSetDepthStencilState(bd->spDepthStencilState);
//  gapi.rsSetRasterizerState(bd->spRasterizerState);
//}
//
//namespace ImGui {
//
//  static ImGui_MouseData*
//  ImGui_MouseData_GetBackendData() {
//    return ImGui::GetCurrentContext() ?
//      static_cast<ImGui_MouseData*>(ImGui::GetIO().BackendPlatformUserData) :
//      nullptr;
//  }
//
//  static ImGui_ImplGI_Data*
//  ImGui_ImplGI_GetBackendData() {
//    return ImGui::GetCurrentContext() ?
//      static_cast<ImGui_ImplGI_Data*>(ImGui::GetIO().BackendRendererUserData) :
//      nullptr;
//  }
//
//  void
//  init(void* inWindow, Vector2 inWindowSize) {
//
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO();
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
//    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
//
//    ImGui_MouseData* data = IM_NEW(ImGui_MouseData);
//    io.BackendPlatformUserData = (void*)data;
//    io.BackendPlatformName = "imgui_impl_win32";
//    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
//    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
//
//    ImGuiViewport* mainViewport = ImGui::GetMainViewport();
//    mainViewport->PlatformHandle = mainViewport->PlatformHandleRaw = inWindow;
//
//    //Inputs of the keyboard
//
//    io.DisplaySize = ImVec2(inWindowSize.x, inWindowSize.y);
//
//    ImGui::StyleColorsDark();
//
//    ImGui_ImplGI_Data* tmpData = IM_NEW(ImGui_ImplGI_Data);
//    io.BackendRendererName = "ImGui_giImplementation";
//    io.BackendRendererUserData = static_cast<void*>(tmpData);
//    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;
//
//    auto& gapi = giEngineSDK::g_graphicsAPI();
//
//    const char* vertexShader = {
//      "cbuffer vertexBuffer : register(b0) \
//            {\
//              float4x4 ProjectionMatrix; \
//            };\
//            struct VS_INPUT\
//            {\
//              float2 pos : POSITION;\
//              float4 col : COLOR0;\
//              float2 uv  : TEXCOORD0;\
//            };\
//            \
//            struct PS_INPUT\
//            {\
//              float4 pos : SV_POSITION;\
//              float4 col : COLOR0;\
//              float2 uv  : TEXCOORD0;\
//            };\
//            \
//            PS_INPUT main(VS_INPUT input)\
//            {\
//              PS_INPUT output;\
//              output.pos = mul(ProjectionMatrix, float4(input.pos.xy, 0.f, 1.f));\
//              output.col = input.col;\
//              output.uv  = input.uv;\
//              return output;\
//            }" };
//
//    tmpData->spVertexShader = gapi.createVShaderFromMem(vertexShader, "main");
//
//    static const char* pixelShader = {
//      "struct PS_INPUT\
//            {\
//            float4 pos : SV_POSITION;\
//            float4 col : COLOR0;\
//            float2 uv  : TEXCOORD0;\
//            };\
//            sampler sampler0;\
//            Texture2D texture0;\
//            \
//            float4 main(PS_INPUT input) : SV_Target\
//            {\
//            float4 out_col = input.col * texture0.Sample(sampler0, input.uv); \
//            return out_col; \
//            }" };
//
//    tmpData->spPixelShader = gapi.createPShaderFromMem(pixelShader, "main");
//
//    //Create Input Layout
//    Vector<InputLayoutDesc> layoutDesc;
//
//    //Set the size for the inputLayout
//    layoutDesc.resize(3);
//
//    //Sets the input Layout values
//
//    //Positions
//    layoutDesc[0].semanticName = "POSITION";
//    layoutDesc[0].semanticIndex = 0;
//    layoutDesc[0].format = giEngineSDK::GI_FORMAT::kFORMAT_R32G32_FLOAT;
//    layoutDesc[0].inputSlot = 0;
//    layoutDesc[0].alignedByteOffset = IM_OFFSETOF(ImDrawVert, pos);
//    layoutDesc[0].inputSlotClass = giEngineSDK::GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
//    layoutDesc[0].instanceDataStepRate = 0;
//
//    //texcoords
//    layoutDesc[1].semanticName = "TEXCOORD";
//    layoutDesc[1].semanticIndex = 0;
//    layoutDesc[1].format = giEngineSDK::GI_FORMAT::kFORMAT_R32G32_FLOAT;
//    layoutDesc[1].inputSlot = 0;
//    layoutDesc[1].alignedByteOffset = IM_OFFSETOF(ImDrawVert, uv);;
//    layoutDesc[1].inputSlotClass = giEngineSDK::GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
//    layoutDesc[1].instanceDataStepRate = 0;
//
//    //color
//    layoutDesc[2].semanticName = "COLOR";
//    layoutDesc[2].semanticIndex = 0;
//    layoutDesc[2].format = giEngineSDK::GI_FORMAT::kFORMAT_R8G8B8A8_UNORM;
//    layoutDesc[2].inputSlot = 0;
//    layoutDesc[2].alignedByteOffset = IM_OFFSETOF(ImDrawVert, col);;
//    layoutDesc[2].inputSlotClass = giEngineSDK::GI_INPUT_CLASSIFICATION::kINPUT_PER_VERTEX_DATA;
//    layoutDesc[2].instanceDataStepRate = 0;
//
//    //Create the Input Layout
//    tmpData->spInputLayout = gapi.createInputLayout(layoutDesc, tmpData->spVertexShader);
//
//    //
//    tmpData->spVertexConstantBuffer = gapi.createBuffer(sizeof(Matrix4),
//                                                        giEngineSDK::GI_BIND_FLAG::kBIND_CONSTANT_BUFFER,
//                                                        nullptr);
//    //Create Blend State
//    Vector4 tmpkk = { 0.f, 0.f, 0.f, 0.f };
//    tmpData->spBlendState = gapi.createBlendState(true,
//                                                  giEngineSDK::BLEND_TYPE::src_alpha,
//                                                  giEngineSDK::BLEND_TYPE::inv_src_alpha,
//                                                  giEngineSDK::BLEND_OP::add,
//                                                  giEngineSDK::BLEND_TYPE::one,
//                                                  giEngineSDK::BLEND_TYPE::inv_src_alpha,
//                                                  giEngineSDK::BLEND_OP::add,
//                                                  //Vector4(0.f, 0.f, 0.f, 0.f));
//                                                  tmpkk);
//
//    //Create raster state
//    tmpData->spRasterizerState = gapi.createRasterizer(giEngineSDK::FILLMODE::kSolid,
//                                                       giEngineSDK::CULLMODE::kNone,
//                                                       false,
//                                                       true);
//
//    //Create Depth stencil state
//    tmpData->spDepthStencilState = gapi.createDepthState(false,
//                                                         false,
//                                                         giEngineSDK::GI_COMPARATION_FUNC::kCOMPARISON_ALWAYS);
//
//    //Build Texture Atlas
//    uint8* tmpPixels;
//    int32 tmpWidth, tmpHeight;
//    io.Fonts->GetTexDataAsRGBA32(&tmpPixels, &tmpWidth, &tmpHeight);
//
//    // Upload texture to graphics system
//    
//    tmpData->spFontTextureView = gapi.TextureFromMem(tmpPixels,
//                                 tmpWidth,
//                                 tmpHeight,
//                                 giEngineSDK::GI_FORMAT::kFORMAT_R8G8B8A8_UNORM,
//                                 giEngineSDK::GI_BIND_FLAG::kBIND_SHADER_RESOURCE);
//    
//
//    // Store our identifier
//    io.Fonts->SetTexID(static_cast<ImTextureID>(&tmpData->spFontTextureView));
//
//    // Create texture sampler
//    {
//      SamplerDesc desc;
//      ZeroMemory(&desc, sizeof(desc));
//      desc.filter = giEngineSDK::GI_FILTER::kFILTER_MIN_MAG_MIP_LINEAR;
//      desc.addressU = giEngineSDK::GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
//      desc.addressV = giEngineSDK::GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
//      desc.addressW = giEngineSDK::GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
//      //desc.mipLODBias = 0.f;
//      desc.comparisonFunc = giEngineSDK::GI_COMPARATION_FUNC::kCOMPARISON_ALWAYS;
//      desc.minLOD = 0.f;
//      desc.maxLOD = 0.f;
//
//      tmpData->spFontSampler = gapi.createSampler(desc);
//    }
//  }
//
//  void
//  update(void* inWindow, float inDT) {
//    ImGuiIO& io = ImGui::GetIO();
//
//    ImGui_MouseData* tmpData = ImGui_MouseData_GetBackendData();
//
//    IM_ASSERT(tmpData != nullptr && "Failed backend platform initialization.\n");
//    const ImVec2 mousePosPrev = io.MousePos;
//    io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
//    io.MouseHoveredViewport = 0;
//
//    if (io.WantSetMousePos) {
//      Vector2 pos(mousePosPrev.x, mousePosPrev.y);
//      ::SetCursorPos(pos.x, pos.y);
//    }
//
//    //Set dear ImGui mouse Position from OS position
//    POINT mouseScreenPos;
//    if (!::GetCursorPos(&mouseScreenPos)) {
//      return;
//    }
//    ::ScreenToClient((HWND)inWindow, &mouseScreenPos);
//    io.MousePos = ImVec2((float)mouseScreenPos.x, (float)mouseScreenPos.y);
//    //Update OS mouse cursor with the cursor requested by imgui.
//    ImGuiMouseCursor mouseCursor = io.MouseDrawCursor ? ImGuiMouseCursor_None :
//                                   ImGui::GetMouseCursor();
//    if (tmpData->LastMouseCursor != mouseCursor) {
//      tmpData->LastMouseCursor = mouseCursor;
//      if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) {
//        return;
//      }
//      ImGuiMouseCursor imguiCursor = ImGui::GetMouseCursor();
//      if (imguiCursor != ImGuiMouseCursor_None || io.MouseDrawCursor) {
//        //Hide OS mouse cursor if imgui is drawing it or if it wants no cursor.
//        ::SetCursor(0);
//      }
//      else {
//        //Show OS mouse cursor.
//        LPTSTR win32Cursor = IDC_ARROW;
//        switch (imguiCursor) {
//        case ImGuiMouseCursor_Arrow: {
//          win32Cursor = IDC_ARROW;
//          break;
//        }
//        case ImGuiMouseCursor_TextInput: {
//          win32Cursor = IDC_IBEAM;
//          break;
//        }
//        case ImGuiMouseCursor_ResizeAll: {
//          win32Cursor = IDC_SIZEALL;
//          break;
//        }
//        case ImGuiMouseCursor_ResizeEW: {
//          win32Cursor = IDC_SIZEWE;
//          break;
//        }
//        case ImGuiMouseCursor_ResizeNS: {
//          win32Cursor = IDC_SIZENS;
//          break;
//        }
//        case ImGuiMouseCursor_ResizeNESW: {
//          win32Cursor = IDC_SIZENESW;
//          break;
//        }
//        case ImGuiMouseCursor_ResizeNWSE: {
//          win32Cursor = IDC_SIZENWSE;
//          break;
//        }
//        case ImGuiMouseCursor_Hand: {
//          win32Cursor = IDC_HAND;
//          break;
//        }
//        case ImGuiMouseCursor_NotAllowed: {
//          win32Cursor = IDC_NO;
//          break;
//        }
//        }
//        ::SetCursor(::LoadCursor(0, win32Cursor));
//      }
//      UNREFERENCED_PARAMETER(inDT);
//      callBack();
//    }
//
//  }
//
//  void
//  render() {
//    ImGui::Render();
//    ImDrawData* data = ImGui::GetDrawData();
//    if (0 == data->CmdListsCount) {
//      return;
//    }
//    ImGuiIO& io = ImGui::GetIO();
//    assert(io.Fonts->TexID != NULL);
//
//    int32 width = static_cast<int32>(io.DisplaySize.x * io.DisplayFramebufferScale.x);
//    int32 height = static_cast<int32>(io.DisplaySize.y * io.DisplayFramebufferScale.y);
//    if (0 == width || 0 == height) {
//      return;
//    }
//    data->ScaleClipRects(io.DisplayFramebufferScale);
//    ImGui_ImplGI_Data* tmpData = ImGui_ImplGI_GetBackendData();
//
//    auto& gapi = giEngineSDK::g_graphicsAPI();
//
//    //Create and grow vertex/index buffer if needed
//    if (!tmpData->spVB || tmpData->VertexBufferSize < data->TotalVtxCount) {
//      if (tmpData->spVB) {
//        tmpData->spVB.reset();
//      }
//      tmpData->VertexBufferSize = data->TotalVtxCount;
//      tmpData->spVB = gapi.createBuffer(tmpData->VertexBufferSize * sizeof(ImDrawVert),
//                                        giEngineSDK::GI_BIND_FLAG::kBIND_VERTEX_BUFFER,
//                                        nullptr);
//    }
//    if (!tmpData->spIB || tmpData->IndexBufferSize < data->TotalIdxCount) {
//      if (tmpData->spIB) {
//        tmpData->spIB.reset();
//      }
//      tmpData->IndexBufferSize = data->TotalIdxCount;
//      tmpData->spIB = gapi.createBuffer(tmpData->IndexBufferSize * sizeof(ImDrawIdx),
//                                        giEngineSDK::GI_BIND_FLAG::kBIND_INDEX_BUFFER,
//                                        nullptr);
//    }
//    //Upload vertex/index data
//    Vector<ImDrawVert> vertices;
//    Vector<ImDrawIdx> indices;
//    for (int32 n = 0; n < data->CmdListsCount; ++n) {
//      const ImDrawList* cmd_list = data->CmdLists[n];
//      for (int32 x = 0; x < cmd_list->VtxBuffer.Size; ++x) {
//        vertices.push_back(cmd_list->VtxBuffer[x]);
//      }
//      for (int32 y = 0; y < cmd_list->IdxBuffer.Size; ++y) {
//        indices.push_back(cmd_list->IdxBuffer[y]);
//      }
//    }
//    gapi.updateSubresource(tmpData->spVB, vertices.data(), 0);
//    gapi.updateSubresource(tmpData->spIB, indices.data(), 0);
//    float L = data->DisplayPos.x;
//    float R = data->DisplayPos.x + data->DisplaySize.x;
//    float T = data->DisplayPos.y;
//    float B = data->DisplayPos.y + data->DisplaySize.y;
//    float mvp[4][4] =
//    {
//        { 2.0f / (R - L),      0.0f,               0.0f,       0.0f },
//        { 0.0f,                2.0f / (T - B),     0.0f,       0.0f },
//        { 0.0f,                0.0f,               0.5f,       0.0f },
//        { (R + L) / (L - R),  (T + B) / (B - T),   0.5f,       1.0f },
//    };
//    gapi.updateSubresource(tmpData->spVertexConstantBuffer, &mvp, 0);
//
//    //Backup the old information.
//    BACKUP_STATE old = {};
//    //old.ScissorRects = gapi.rsGetScissorRects(old.ScissorRectsCount);
//    //gapi.rsGetViewports(old.ViewportsCount, old.Viewports);
//    old.spRasterState = gapi.rsGetState();
//    old.spBlendState = gapi.omGetBlendState();
//    old.spDepthState = gapi.omGetDepthStencilState();
//    old.spShaderResource = gapi.psGetShaderResources(0, 1);
//    old.spSamplerState = gapi.psGetSamplers(0, 1);
//    old.spPixelShader = gapi.psGetShader();
//    old.spVertexShader = gapi.vsGetShader();
//    old.spVertexCB = gapi.vsGetConstantBuffers(0, 1);
//    //Aqui iria el geometry shader... si tan solo lo tuvieras
//
//    old.spIndexBuffer = gapi.iaGetIndexBuffer();
//    old.spVertexBuffer = gapi.iaGetVertexBuffer(1, old.vertexStride, old.vertexOffset);
//    old.spInputLayout = gapi.iaGetInputLayout();
//
//    // Setup desired DX state
//    ImGui_ImplGI_SetupRenderState(data);
//
//    // Render command lists
//    // (Because we merged all buffers into a single one, we maintain our own offset into them)
//    int global_idx_offset = 0;
//    int global_vtx_offset = 0;
//    ImVec2 clip_off = data->DisplayPos;
//    for (int n = 0; n < data->CmdListsCount; n++) {
//      const ImDrawList* cmd_list = data->CmdLists[n];
//      for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
//        const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
//        if (pcmd->UserCallback != NULL) {
//          // User callback, registered via ImDrawList::AddCallback()
//          // (ImDrawCallback_ResetRenderState is a special callback value used 
//          // by the user to request the renderer to reset render state.)
//          if (pcmd->UserCallback == ImDrawCallback_ResetRenderState) {
//            ImGui_ImplGI_SetupRenderState(data);
//          }
//          else {
//            pcmd->UserCallback(cmd_list, pcmd);
//          }
//        }
//        else {
//          // Project scissor/clipping rectangles into framebuffer space
//          ImVec2 clip_min(pcmd->ClipRect.x - clip_off.x, pcmd->ClipRect.y - clip_off.y);
//          ImVec2 clip_max(pcmd->ClipRect.z - clip_off.x, pcmd->ClipRect.w - clip_off.y);
//          if (clip_max.x < clip_min.x || clip_max.y < clip_min.y) {
//            continue;
//          }
//          // Apply scissor/clipping rectangle
//          Vector4 r = { clip_min.x,
//                        clip_min.y,
//                        clip_max.x,
//                        clip_max.y };
//          gapi.rsSetScissorRects(1, &r);
//
//          // Bind texture, Draw
//          SharedPtr<Texture2D>* texture_srv = static_cast<SharedPtr<Texture2D>*>(pcmd->GetTexID());
//          //texture_srv.reset(pcmd->GetTexID());
//          gapi.psSetShaderResource(0, *texture_srv);
//          gapi.drawIndexed(pcmd->ElemCount,
//                           pcmd->VtxOffset + global_vtx_offset);
//        }
//      }
//      global_idx_offset += cmd_list->IdxBuffer.Size;
//      global_vtx_offset += cmd_list->VtxBuffer.Size;
//    }
//
//    //gapi.rsSetViewports(old.ViewportsCount, old.Viewports);
//
//    gapi.rsSetRasterizerState(old.spRasterState);
//
//    gapi.omSetBlendState(old.spBlendState);
//
//    gapi.omSetDepthStencilState(old.spDepthState);
//
//    gapi.psSetShaderResource(0, old.spShaderResource);
//
//    gapi.psSetSamplerState(0, 1, old.spSamplerState);
//
//    gapi.psSetShader(old.spPixelShader);
//
//    gapi.vsSetShader(old.spVertexShader);
//
//    gapi.vsSetConstantBuffer(0, old.spVertexCB);
//
//    //gapi.setTopology(old.spPrimitiveTopology);
//
//    gapi.setIndexBuffer(old.spIndexBuffer,
//                        giEngineSDK::GI_FORMAT::kFORMAT_R16_UINT);
//
//    gapi.setVertexBuffer(old.spVertexBuffer, old.vertexStride);
//
//    gapi.aiSetInputLayout(old.spInputLayout);
//  }
//
//  void
//  shutDown() {
//    ImGui_MouseData* be = ImGui_MouseData_GetBackendData();
//    IM_ASSERT(be != nullptr && "No platform backend to shutdown, or already shutdown?");
//    ImGui_ImplGI_Data* bd = ImGui_ImplGI_GetBackendData();
//    IM_ASSERT(bd != nullptr && "No renderer backend to shitdon, or already shutdown?");
//    ImGuiIO& io = ImGui::GetIO();
//
//    ImGui::DestroyPlatformWindows();
//    io.BackendRendererName = nullptr;
//    io.BackendRendererUserData = nullptr;
//    io.BackendPlatformName = nullptr;
//    io.BackendPlatformUserData = nullptr;
//    IM_DELETE(bd);
//    IM_DELETE(be);
//    ImGui::DestroyContext();
//  }
//
//  void
//  callBack() {
//    ImGuiIO& io = ImGui::GetIO();
//    //Mouse Pressed case
//    {
//      int32 button = -1;
//      button = giEngineSDK::g_inputManager().isMouseButtonPressed(giEngineSDK::MOUSE_BUTTONS::kLEFTCLIC) ?
//        0 : button;
//      button = giEngineSDK::g_inputManager().isMouseButtonPressed(giEngineSDK::MOUSE_BUTTONS::kRIGHTCLIC) ?
//        1 : button;
//      button = giEngineSDK::g_inputManager().isMouseButtonPressed(giEngineSDK::MOUSE_BUTTONS::kMIDCLIC) ?
//        2 : button;
//      button = giEngineSDK::g_inputManager().isMouseButtonPressed(giEngineSDK::MOUSE_BUTTONS::kBUTTON3) ?
//        3 : button;
//      button = giEngineSDK::g_inputManager().isMouseButtonPressed(giEngineSDK::MOUSE_BUTTONS::kBUTTON4) ?
//        4 : button;
//      if (button > -1) {
//        io.MouseDown[button] = true;
//      }
//    }
//    //Mouse released case
//    {
//      int32 button = -1;
//      button = giEngineSDK::g_inputManager().isMouseButtonReleassed(giEngineSDK::MOUSE_BUTTONS::kLEFTCLIC) ?
//        0 : button;
//      button = giEngineSDK::g_inputManager().isMouseButtonReleassed(giEngineSDK::MOUSE_BUTTONS::kRIGHTCLIC) ?
//        1 : button;
//      button = giEngineSDK::g_inputManager().isMouseButtonReleassed(giEngineSDK::MOUSE_BUTTONS::kMIDCLIC) ?
//        2 : button;
//      button = giEngineSDK::g_inputManager().isMouseButtonReleassed(giEngineSDK::MOUSE_BUTTONS::kBUTTON3) ?
//        3 : button;
//      button = giEngineSDK::g_inputManager().isMouseButtonReleassed(giEngineSDK::MOUSE_BUTTONS::kBUTTON4) ?
//        4 : button;
//      if (button > -1) {
//        io.MouseDown[button] = false;
//      }
//    }
//  }
//
//}










#include "imgui.h"
#include "giImGui.h"

// DirectX
#include <stdio.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#ifdef _MSC_VER
#pragma comment(lib, "d3dcompiler") // Automatically link with d3dcompiler.lib as we are using D3DCompile() below.
#endif

// DirectX11 data
struct ImGui_ImplDX11_Data
{
  ID3D11Device* pd3dDevice;
  ID3D11DeviceContext* pd3dDeviceContext;
  IDXGIFactory* pFactory;
  ID3D11Buffer* pVB;
  ID3D11Buffer* pIB;
  ID3D11VertexShader* pVertexShader;
  ID3D11InputLayout* pInputLayout;
  ID3D11Buffer* pVertexConstantBuffer;
  ID3D11PixelShader* pPixelShader;
  ID3D11SamplerState* pFontSampler;
  ID3D11ShaderResourceView* pFontTextureView;
  ID3D11RasterizerState* pRasterizerState;
  ID3D11BlendState* pBlendState;
  ID3D11DepthStencilState* pDepthStencilState;
  int                         VertexBufferSize;
  int                         IndexBufferSize;

  ImGui_ImplDX11_Data() { memset((void*)this, 0, sizeof(*this)); VertexBufferSize = 5000; IndexBufferSize = 10000; }
};

struct VERTEX_CONSTANT_BUFFER
{
  float   mvp[4][4];
};

// Backend data stored in io.BackendRendererUserData to allow support for multiple Dear ImGui contexts
// It is STRONGLY preferred that you use docking branch with multi-viewports (== single Dear ImGui context + multiple windows) instead of multiple Dear ImGui contexts.
static ImGui_ImplDX11_Data* ImGui_ImplDX11_GetBackendData()
{
  return ImGui::GetCurrentContext() ? (ImGui_ImplDX11_Data*)ImGui::GetIO().BackendRendererUserData : NULL;
}

// Forward Declarations
static void ImGui_ImplDX11_InitPlatformInterface();
static void ImGui_ImplDX11_ShutdownPlatformInterface();

// Functions
static void ImGui_ImplDX11_SetupRenderState(ImDrawData* draw_data, ID3D11DeviceContext* ctx)
{
  ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();

  // Setup viewport
  D3D11_VIEWPORT vp;
  memset(&vp, 0, sizeof(D3D11_VIEWPORT));
  vp.Width = draw_data->DisplaySize.x;
  vp.Height = draw_data->DisplaySize.y;
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = vp.TopLeftY = 0;
  ctx->RSSetViewports(1, &vp);

  // Setup shader and vertex buffers
  unsigned int stride = sizeof(ImDrawVert);
  unsigned int offset = 0;
  ctx->IASetInputLayout(bd->pInputLayout);
  ctx->IASetVertexBuffers(0, 1, &bd->pVB, &stride, &offset);
  ctx->IASetIndexBuffer(bd->pIB, sizeof(ImDrawIdx) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT, 0);
  ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  ctx->VSSetShader(bd->pVertexShader, NULL, 0);
  ctx->VSSetConstantBuffers(0, 1, &bd->pVertexConstantBuffer);
  ctx->PSSetShader(bd->pPixelShader, NULL, 0);
  ctx->PSSetSamplers(0, 1, &bd->pFontSampler);
  ctx->GSSetShader(NULL, NULL, 0);
  ctx->HSSetShader(NULL, NULL, 0); // In theory we should backup and restore this as well.. very infrequently used..
  ctx->DSSetShader(NULL, NULL, 0); // In theory we should backup and restore this as well.. very infrequently used..
  ctx->CSSetShader(NULL, NULL, 0); // In theory we should backup and restore this as well.. very infrequently used..

  // Setup blend state
  const float blend_factor[4] = { 0.f, 0.f, 0.f, 0.f };
  ctx->OMSetBlendState(bd->pBlendState, blend_factor, 0xffffffff);
  ctx->OMSetDepthStencilState(bd->pDepthStencilState, 0);
  ctx->RSSetState(bd->pRasterizerState);
}

// Render function
void ImGui_ImplDX11_RenderDrawData(ImDrawData* draw_data)
{
  // Avoid rendering when minimized
  if (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f)
    return;

  ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
  ID3D11DeviceContext* ctx = bd->pd3dDeviceContext;

  // Create and grow vertex/index buffers if needed
  if (!bd->pVB || bd->VertexBufferSize < draw_data->TotalVtxCount)
  {
    if (bd->pVB) { bd->pVB->Release(); bd->pVB = NULL; }
    bd->VertexBufferSize = draw_data->TotalVtxCount + 5000;
    D3D11_BUFFER_DESC desc;
    memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.ByteWidth = bd->VertexBufferSize * sizeof(ImDrawVert);
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;
    if (bd->pd3dDevice->CreateBuffer(&desc, NULL, &bd->pVB) < 0)
      return;
  }
  if (!bd->pIB || bd->IndexBufferSize < draw_data->TotalIdxCount)
  {
    if (bd->pIB) { bd->pIB->Release(); bd->pIB = NULL; }
    bd->IndexBufferSize = draw_data->TotalIdxCount + 10000;
    D3D11_BUFFER_DESC desc;
    memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.ByteWidth = bd->IndexBufferSize * sizeof(ImDrawIdx);
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    if (bd->pd3dDevice->CreateBuffer(&desc, NULL, &bd->pIB) < 0)
      return;
  }

  // Upload vertex/index data into a single contiguous GPU buffer
  D3D11_MAPPED_SUBRESOURCE vtx_resource, idx_resource;
  if (ctx->Map(bd->pVB, 0, D3D11_MAP_WRITE_DISCARD, 0, &vtx_resource) != S_OK)
    return;
  if (ctx->Map(bd->pIB, 0, D3D11_MAP_WRITE_DISCARD, 0, &idx_resource) != S_OK)
    return;
  ImDrawVert* vtx_dst = (ImDrawVert*)vtx_resource.pData;
  ImDrawIdx* idx_dst = (ImDrawIdx*)idx_resource.pData;
  for (int n = 0; n < draw_data->CmdListsCount; n++)
  {
    const ImDrawList* cmd_list = draw_data->CmdLists[n];
    memcpy(vtx_dst, cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.Size * sizeof(ImDrawVert));
    memcpy(idx_dst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
    vtx_dst += cmd_list->VtxBuffer.Size;
    idx_dst += cmd_list->IdxBuffer.Size;
  }
  ctx->Unmap(bd->pVB, 0);
  ctx->Unmap(bd->pIB, 0);

  // Setup orthographic projection matrix into our constant buffer
  // Our visible imgui space lies from draw_data->DisplayPos (top left) to draw_data->DisplayPos+data_data->DisplaySize (bottom right). DisplayPos is (0,0) for single viewport apps.
  {
    D3D11_MAPPED_SUBRESOURCE mapped_resource;
    if (ctx->Map(bd->pVertexConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource) != S_OK)
      return;
    VERTEX_CONSTANT_BUFFER* constant_buffer = (VERTEX_CONSTANT_BUFFER*)mapped_resource.pData;
    float L = draw_data->DisplayPos.x;
    float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
    float T = draw_data->DisplayPos.y;
    float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
    float mvp[4][4] =
    {
        { 2.0f / (R - L),   0.0f,           0.0f,       0.0f },
        { 0.0f,         2.0f / (T - B),     0.0f,       0.0f },
        { 0.0f,         0.0f,           0.5f,       0.0f },
        { (R + L) / (L - R),  (T + B) / (B - T),    0.5f,       1.0f },
    };
    memcpy(&constant_buffer->mvp, mvp, sizeof(mvp));
    ctx->Unmap(bd->pVertexConstantBuffer, 0);
  }

  // Backup DX state that will be modified to restore it afterwards (unfortunately this is very ugly looking and verbose. Close your eyes!)
  struct BACKUP_DX11_STATE
  {
    UINT                        ScissorRectsCount, ViewportsCount;
    D3D11_RECT                  ScissorRects[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
    D3D11_VIEWPORT              Viewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
    ID3D11RasterizerState* RS;
    ID3D11BlendState* BlendState;
    FLOAT                       BlendFactor[4];
    UINT                        SampleMask;
    UINT                        StencilRef;
    ID3D11DepthStencilState* DepthStencilState;
    ID3D11ShaderResourceView* PSShaderResource;
    ID3D11SamplerState* PSSampler;
    ID3D11PixelShader* PS;
    ID3D11VertexShader* VS;
    ID3D11GeometryShader* GS;
    UINT                        PSInstancesCount, VSInstancesCount, GSInstancesCount;
    ID3D11ClassInstance* PSInstances[256], * VSInstances[256], * GSInstances[256];   // 256 is max according to PSSetShader documentation
    D3D11_PRIMITIVE_TOPOLOGY    PrimitiveTopology;
    ID3D11Buffer* IndexBuffer, * VertexBuffer, * VSConstantBuffer;
    UINT                        IndexBufferOffset, VertexBufferStride, VertexBufferOffset;
    DXGI_FORMAT                 IndexBufferFormat;
    ID3D11InputLayout* InputLayout;
  };
  BACKUP_DX11_STATE old = {};
  old.ScissorRectsCount = old.ViewportsCount = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
  ctx->RSGetScissorRects(&old.ScissorRectsCount, old.ScissorRects);
  ctx->RSGetViewports(&old.ViewportsCount, old.Viewports);
  ctx->RSGetState(&old.RS);
  ctx->OMGetBlendState(&old.BlendState, old.BlendFactor, &old.SampleMask);
  ctx->OMGetDepthStencilState(&old.DepthStencilState, &old.StencilRef);
  ctx->PSGetShaderResources(0, 1, &old.PSShaderResource);
  ctx->PSGetSamplers(0, 1, &old.PSSampler);
  old.PSInstancesCount = old.VSInstancesCount = old.GSInstancesCount = 256;
  ctx->PSGetShader(&old.PS, old.PSInstances, &old.PSInstancesCount);
  ctx->VSGetShader(&old.VS, old.VSInstances, &old.VSInstancesCount);
  ctx->VSGetConstantBuffers(0, 1, &old.VSConstantBuffer);
  ctx->GSGetShader(&old.GS, old.GSInstances, &old.GSInstancesCount);

  ctx->IAGetPrimitiveTopology(&old.PrimitiveTopology);
  ctx->IAGetIndexBuffer(&old.IndexBuffer, &old.IndexBufferFormat, &old.IndexBufferOffset);
  ctx->IAGetVertexBuffers(0, 1, &old.VertexBuffer, &old.VertexBufferStride, &old.VertexBufferOffset);
  ctx->IAGetInputLayout(&old.InputLayout);

  // Setup desired DX state
  ImGui_ImplDX11_SetupRenderState(draw_data, ctx);

  // Render command lists
  // (Because we merged all buffers into a single one, we maintain our own offset into them)
  int global_idx_offset = 0;
  int global_vtx_offset = 0;
  ImVec2 clip_off = draw_data->DisplayPos;
  for (int n = 0; n < draw_data->CmdListsCount; n++)
  {
    const ImDrawList* cmd_list = draw_data->CmdLists[n];
    for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
    {
      const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
      if (pcmd->UserCallback != NULL)
      {
        // User callback, registered via ImDrawList::AddCallback()
        // (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the renderer to reset render state.)
        if (pcmd->UserCallback == ImDrawCallback_ResetRenderState)
          ImGui_ImplDX11_SetupRenderState(draw_data, ctx);
        else
          pcmd->UserCallback(cmd_list, pcmd);
      }
      else
      {
        // Project scissor/clipping rectangles into framebuffer space
        ImVec2 clip_min(pcmd->ClipRect.x - clip_off.x, pcmd->ClipRect.y - clip_off.y);
        ImVec2 clip_max(pcmd->ClipRect.z - clip_off.x, pcmd->ClipRect.w - clip_off.y);
        if (clip_max.x <= clip_min.x || clip_max.y <= clip_min.y)
          continue;

        // Apply scissor/clipping rectangle
        const D3D11_RECT r = { (LONG)clip_min.x, (LONG)clip_min.y, (LONG)clip_max.x, (LONG)clip_max.y };
        ctx->RSSetScissorRects(1, &r);

        // Bind texture, Draw
        ID3D11ShaderResourceView* texture_srv = (ID3D11ShaderResourceView*)pcmd->GetTexID();
        ctx->PSSetShaderResources(0, 1, &texture_srv);
        ctx->DrawIndexed(pcmd->ElemCount, pcmd->IdxOffset + global_idx_offset, pcmd->VtxOffset + global_vtx_offset);
      }
    }
    global_idx_offset += cmd_list->IdxBuffer.Size;
    global_vtx_offset += cmd_list->VtxBuffer.Size;
  }

  // Restore modified DX state
  ctx->RSSetScissorRects(old.ScissorRectsCount, old.ScissorRects);
  ctx->RSSetViewports(old.ViewportsCount, old.Viewports);
  ctx->RSSetState(old.RS); if (old.RS) old.RS->Release();
  ctx->OMSetBlendState(old.BlendState, old.BlendFactor, old.SampleMask); if (old.BlendState) old.BlendState->Release();
  ctx->OMSetDepthStencilState(old.DepthStencilState, old.StencilRef); if (old.DepthStencilState) old.DepthStencilState->Release();
  ctx->PSSetShaderResources(0, 1, &old.PSShaderResource); if (old.PSShaderResource) old.PSShaderResource->Release();
  ctx->PSSetSamplers(0, 1, &old.PSSampler); if (old.PSSampler) old.PSSampler->Release();
  ctx->PSSetShader(old.PS, old.PSInstances, old.PSInstancesCount); if (old.PS) old.PS->Release();
  for (UINT i = 0; i < old.PSInstancesCount; i++) if (old.PSInstances[i]) old.PSInstances[i]->Release();
  ctx->VSSetShader(old.VS, old.VSInstances, old.VSInstancesCount); if (old.VS) old.VS->Release();
  ctx->VSSetConstantBuffers(0, 1, &old.VSConstantBuffer); if (old.VSConstantBuffer) old.VSConstantBuffer->Release();
  ctx->GSSetShader(old.GS, old.GSInstances, old.GSInstancesCount); if (old.GS) old.GS->Release();
  for (UINT i = 0; i < old.VSInstancesCount; i++) if (old.VSInstances[i]) old.VSInstances[i]->Release();
  ctx->IASetPrimitiveTopology(old.PrimitiveTopology);
  ctx->IASetIndexBuffer(old.IndexBuffer, old.IndexBufferFormat, old.IndexBufferOffset); if (old.IndexBuffer) old.IndexBuffer->Release();
  ctx->IASetVertexBuffers(0, 1, &old.VertexBuffer, &old.VertexBufferStride, &old.VertexBufferOffset); if (old.VertexBuffer) old.VertexBuffer->Release();
  ctx->IASetInputLayout(old.InputLayout); if (old.InputLayout) old.InputLayout->Release();
}

static void ImGui_ImplDX11_CreateFontsTexture()
{
  // Build texture atlas
  ImGuiIO& io = ImGui::GetIO();
  ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
  unsigned char* pixels;
  int width, height;
  io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

  // Upload texture to graphics system
  {
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = pixels;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    bd->pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);
    IM_ASSERT(pTexture != NULL);

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    bd->pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, &bd->pFontTextureView);
    pTexture->Release();
  }

  // Store our identifier
  io.Fonts->SetTexID((ImTextureID)bd->pFontTextureView);

  // Create texture sampler
  // (Bilinear sampling is required by default. Set 'io.Fonts->Flags |= ImFontAtlasFlags_NoBakedLines' or 'style.AntiAliasedLinesUseTex = false' to allow point/nearest sampling)
  {
    D3D11_SAMPLER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.MipLODBias = 0.f;
    desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    desc.MinLOD = 0.f;
    desc.MaxLOD = 0.f;
    bd->pd3dDevice->CreateSamplerState(&desc, &bd->pFontSampler);
  }
}

bool    ImGui_ImplDX11_CreateDeviceObjects()
{
  ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
  if (!bd->pd3dDevice)
    return false;
  if (bd->pFontSampler)
    ImGui_ImplDX11_InvalidateDeviceObjects();

  // By using D3DCompile() from <d3dcompiler.h> / d3dcompiler.lib, we introduce a dependency to a given version of d3dcompiler_XX.dll (see D3DCOMPILER_DLL_A)
  // If you would like to use this DX11 sample code but remove this dependency you can:
  //  1) compile once, save the compiled shader blobs into a file or source code and pass them to CreateVertexShader()/CreatePixelShader() [preferred solution]
  //  2) use code to detect any version of the DLL and grab a pointer to D3DCompile from the DLL.
  // See https://github.com/ocornut/imgui/pull/638 for sources and details.

  // Create the vertex shader
  {
    static const char* vertexShader =
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

    ID3DBlob* vertexShaderBlob;
    if (FAILED(D3DCompile(vertexShader, strlen(vertexShader), NULL, NULL, NULL, "main", "vs_4_0", 0, 0, &vertexShaderBlob, NULL)))
      return false; // NB: Pass ID3DBlob* pErrorBlob to D3DCompile() to get error showing in (const char*)pErrorBlob->GetBufferPointer(). Make sure to Release() the blob!
    if (bd->pd3dDevice->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), NULL, &bd->pVertexShader) != S_OK)
    {
      vertexShaderBlob->Release();
      return false;
    }

    // Create the input layout
    D3D11_INPUT_ELEMENT_DESC local_layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,   0, (UINT)IM_OFFSETOF(ImDrawVert, pos), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,   0, (UINT)IM_OFFSETOF(ImDrawVert, uv),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, (UINT)IM_OFFSETOF(ImDrawVert, col), D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    if (bd->pd3dDevice->CreateInputLayout(local_layout, 3, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &bd->pInputLayout) != S_OK)
    {
      vertexShaderBlob->Release();
      return false;
    }
    vertexShaderBlob->Release();

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

void    ImGui_ImplDX11_InvalidateDeviceObjects()
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

bool    ImGui_ImplDX11_Init(ID3D11Device* device, ID3D11DeviceContext* device_context)
{
  ImGuiIO& io = ImGui::GetIO();
  IM_ASSERT(io.BackendRendererUserData == NULL && "Already initialized a renderer backend!");

  // Setup backend capabilities flags
  ImGui_ImplDX11_Data* bd = IM_NEW(ImGui_ImplDX11_Data)();
  io.BackendRendererUserData = (void*)bd;
  io.BackendRendererName = "imgui_impl_dx11";
  io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;  // We can honor the ImDrawCmd::VtxOffset field, allowing for large meshes.
  io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;  // We can create multi-viewports on the Renderer side (optional)

  // Get factory from device
  IDXGIDevice* pDXGIDevice = NULL;
  IDXGIAdapter* pDXGIAdapter = NULL;
  IDXGIFactory* pFactory = NULL;

  if (device->QueryInterface(IID_PPV_ARGS(&pDXGIDevice)) == S_OK)
    if (pDXGIDevice->GetParent(IID_PPV_ARGS(&pDXGIAdapter)) == S_OK)
      if (pDXGIAdapter->GetParent(IID_PPV_ARGS(&pFactory)) == S_OK)
      {
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

void ImGui_ImplDX11_Shutdown()
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

void ImGui_ImplDX11_NewFrame()
{
  ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
  IM_ASSERT(bd != NULL && "Did you call ImGui_ImplDX11_Init()?");

  if (!bd->pFontSampler)
    ImGui_ImplDX11_CreateDeviceObjects();
}

//--------------------------------------------------------------------------------------------------------
// MULTI-VIEWPORT / PLATFORM INTERFACE SUPPORT
// This is an _advanced_ and _optional_ feature, allowing the backend to create and handle multiple viewports simultaneously.
// If you are new to dear imgui or creating a new binding for dear imgui, it is recommended that you completely ignore this section first..
//--------------------------------------------------------------------------------------------------------

// Helper structure we store in the void* RenderUserData field of each ImGuiViewport to easily retrieve our backend data.
struct ImGui_ImplDX11_ViewportData
{
  IDXGISwapChain* SwapChain;
  ID3D11RenderTargetView* RTView;

  ImGui_ImplDX11_ViewportData() { SwapChain = NULL; RTView = NULL; }
  ~ImGui_ImplDX11_ViewportData() { IM_ASSERT(SwapChain == NULL && RTView == NULL); }
};

static void ImGui_ImplDX11_CreateWindow(ImGuiViewport* viewport)
{
  ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
  ImGui_ImplDX11_ViewportData* vd = IM_NEW(ImGui_ImplDX11_ViewportData)();
  viewport->RendererUserData = vd;

  // PlatformHandleRaw should always be a HWND, whereas PlatformHandle might be a higher-level handle (e.g. GLFWWindow*, SDL_Window*).
  // Some backend will leave PlatformHandleRaw NULL, in which case we assume PlatformHandle will contain the HWND.
  HWND hwnd = viewport->PlatformHandleRaw ? (HWND)viewport->PlatformHandleRaw : (HWND)viewport->PlatformHandle;
  IM_ASSERT(hwnd != 0);

  // Create swap chain
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
    ID3D11Texture2D* pBackBuffer;
    vd->SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    bd->pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &vd->RTView);
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
