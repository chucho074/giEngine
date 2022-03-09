/**
 * @file    giImGui.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    23/10/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include <imgui.h>
#include "giPrerequisitesUI.h"

#include <giVector2.h>
#include <giTime.h>
#include <giInputManager.h>


// giEngine data
struct ImGui_ImplGI_Data {
  
  SharedPtr<Buffer>                    spVB;
  SharedPtr<Buffer>                    spIB;
  SharedPtr<BaseVertexShader>          spVertexShader;
  SharedPtr<InputLayout>               spInputLayout;
  SharedPtr<Buffer>                    spVertexConstantBuffer;
  SharedPtr<BasePixelShader>           spPixelShader;
  SharedPtr<Sampler>                   spFontSampler;
  SharedPtr<Texture2D>                 spFontTextureView;
  SharedPtr<BaseRasterizerState>       spRasterizerState;
  SharedPtr<BaseBlendState>            spBlendState;
  SharedPtr<BaseDepthStencilState>     spDepthStencilState;
  uint32                               VertexBufferSize;
  uint32                               IndexBufferSize;

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


//--------------------------------------------------------------------------------------------------------
// MULTI-VIEWPORT / PLATFORM INTERFACE SUPPORT
// This is an _advanced_ and _optional_ feature, allowing the backend to create and handle multiple viewports simultaneously.
// If you are new to dear imgui or creating a new binding for dear imgui, it is recommended that you completely ignore this section first..
//--------------------------------------------------------------------------------------------------------

// Helper structure we store in the void* RenderUserData field of each ImGuiViewport to easily retrieve our backend data.
struct ImGui_ImplGI_ViewportData {
  IDXGISwapChain* SwapChain;
  ID3D11RenderTargetView* RTView;

  ImGui_ImplGI_ViewportData() {
    SwapChain = NULL;
    RTView = NULL;
  }
  ~ImGui_ImplGI_ViewportData() {
    IM_ASSERT(SwapChain == NULL && RTView == NULL);
  }
};


IMGUI_IMPL_API bool     
ImGui_ImplGI_Init();

IMGUI_IMPL_API void     
ImGui_ImplGI_Shutdown();

IMGUI_IMPL_API void     
ImGui_ImplGI_NewFrame();

IMGUI_IMPL_API void     
ImGui_ImplGI_RenderDrawData(ImDrawData* draw_data);


// Use if you want to reset your rendering device without losing Dear ImGui state.
IMGUI_IMPL_API void     
ImGui_ImplGI_InvalidateDeviceObjects();

IMGUI_IMPL_API bool     
ImGui_ImplGI_CreateDeviceObjects();

