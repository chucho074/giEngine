///**
// * @file    giImGui.h
// * @author  Jesus Alberto Del Moral Cupil
// * @e       idv18c.jmoral@uartesdigitales.edu.mx
// * @date    23/10/2021
// * @brief   A basic description of the what do the doc.
// * @bug     No known Bugs.
// */
//
// /**
//  * @include
//  */
//#pragma once
//#include <imgui.h>
//#include <giVector2.h>
////#include <giPrerequisitesCore.h>
//
//using giEngineSDK::Vector2;
//
//
//namespace ImGui {
//
//  void
//  init(void* inWindow, Vector2 inWindowSize);
//
//  void
//  update(void* inWindow, float inDT);
//
//  void
//  render();
//
//  void
//  shutDown();
//
//  void
//  callBack();
//
//}


#pragma once
#include "imgui.h"      // IMGUI_IMPL_API

struct ID3D11Device;
struct ID3D11DeviceContext;

IMGUI_IMPL_API bool     ImGui_ImplDX11_Init(ID3D11Device* device, ID3D11DeviceContext* device_context);
IMGUI_IMPL_API void     ImGui_ImplDX11_Shutdown();
IMGUI_IMPL_API void     ImGui_ImplDX11_NewFrame();
IMGUI_IMPL_API void     ImGui_ImplDX11_RenderDrawData(ImDrawData* draw_data);

// Use if you want to reset your rendering device without losing Dear ImGui state.
IMGUI_IMPL_API void     ImGui_ImplDX11_InvalidateDeviceObjects();
IMGUI_IMPL_API bool     ImGui_ImplDX11_CreateDeviceObjects();
