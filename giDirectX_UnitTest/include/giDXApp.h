/**
 * @file    giDXApp.h
 * @author  Jes�s Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once

#include <giBaseApp.h>
#include <giCamera.h>
#include <giMatrix4.h>
#include <giVector4.h>
#include <giVector3.h>
#include <giVector2.h>
#include <giTexture2D.h>
#include <giDepthStencilView.h>
#include <giRenderTargetView.h>
#include <giVertexShaderDX.h>
#include <giPixelShaderDX.h>
#include <giBuffer.h>
#include <giInputLayout.h>
#include <giSampler.h>
#include <giMesh.h>
#include <giModel.h>
#include <giStaticMesh.h>
#include <giSceneGraph.h>
#include <SFML/Window.hpp>
#include <SFML/Window/WindowBase.hpp>

using giEngineSDK::Buffer;
using giEngineSDK::Vector4;
using giEngineSDK::Matrix4;


/**
 * @struct   CBNeverChanges.
 * @brief    The Never changes constant buffer.
 * @bug      No known Bugs.
 */ 
struct CBNeverChanges {
  Matrix4 mView;
};

/**
 * @struct   CBChangeOnResize.
 * @brief    The change on Resize Constant buffer.
 * @bug      No known Bugs.
 */
struct CBChangeOnResize {
  Matrix4 mProjection;
};

/**
 * @struct   CBChangesEveryFrame.
 * @brief    The Changes Every Frames Constant Buffer.
 * @bug      No known Bugs.
 */
struct CBChangesEveryFrame {
  Matrix4 mWorld;
  Vector4 vMeshColor;
};

/**
 * @class    DirectXApp.
 * @brief    App for DirectX API
 * @bug      No known Bugs.
 */
class DirectXApp : public BaseApp {
 public:
  ///Default constructor
  DirectXApp();

  ///Destructor
  ~DirectXApp() = default;

  /**
   * @brief  Create the information for DirectX App.
   * @bug    No known Bugs.
   */
  void 
  onCreate() override;

  /**
   * @brief  Destroy the information useless.
   * @bug    No known Bugs.
   */
  void 
  onDestroy() override;

  /**
   * @brief  Update the Directx API information.
   * @param  inDeltaTime     The delta time.
   */
  void 
  onUpdate(float inDeltaTime = 0) override;

  /**
   * @brief  Render the 3D information for DirectX API.
   * @bug    No known Bugs.
   */
  void 
  onRender() override;

  /**
   * @brief  Update the events
   * @param  inMsg    The message
   * @param  inwParam  The W parameter
   * @bug    No known Bugs.
   */
  void 
  onEvent(Event inEvent) override;

 private:

  //The main camera 
  Camera m_mainCamera;

  //The input Layout
  InputLayout * m_inputLayout = nullptr;

  //The Sampler
  Sampler * m_sampler = nullptr;

  //The Vertex Buffer
  //Buffer * m_vertexBuffer = nullptr;

  //The Index Buffer 
  //Buffer * m_indexBuffer = nullptr;

  //The Constant Buffer (Never Change)
  Buffer * m_cBufferNeverChange = nullptr;

  //The Constant Buffer (Change on Resize)
  Buffer * m_cBufferChangeOnResize = nullptr;

  //The Constant Buffer (Change Every Frame)
  Buffer * m_cBufferChangeEveryFrame = nullptr;

  //The Vertex shader
  BaseVertexShader * m_vertexShader = nullptr;

  //The Pixel Shader
  BasePixelShader * m_pixelShader = nullptr;

  //The World Matrix
  Matrix4 m_world;

  //The color For the mesh
  Vector4 m_meshColor { 0.f, 0.f, 0.f, 0.f };

  
          //MODELS

  //Yoshi Model
  Model m_yoshi;

  //Yoshi Textures
  Texture2D * m_colorTexture = nullptr;

  SceneGraph sceneGraph;

  //Peach Model
  //Model m_peach;

  //Peach Textures
  //Texture2D * m_peachTexture = nullptr;
};