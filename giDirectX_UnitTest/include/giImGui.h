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
#include <giPrerequisitesCore.h>

#include <giVector2.h>
#include <giTime.h>
#include <giInputManager.h>


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

namespace ImGui {

  void
    init(void* inWindow);

  void
    update(void* inWindow, float inDT);

  void
    render();

  void
    shutDown();

  void
    callBack();


}