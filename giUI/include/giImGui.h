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
#include "imgui.h"

#include "giPrerequisitesUI.h"

#include <giVector2.h>
#include <giTime.h>
#include <giInputManager.h>


// giEngine data
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