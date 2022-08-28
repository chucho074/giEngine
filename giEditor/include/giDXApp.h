/**
 * @file    giDXApp.h
 * @author  Jesus Alberto Del Moral Cupil
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
#include "giEditor.h"

using giEngineSDK::Buffer;
using giEngineSDK::Vector4;
using giEngineSDK::Matrix4;
using giEngineSDK::FILE;

/**
 * @struct   CameraConstantBuffer.
 * @brief    The Camera constant buffer.
 * @bug      No known Bugs.
 */
struct CameraConstantBuffer {
  Matrix4 mView;
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
  onEvent(MSG inMsg) override;

 private:

  //The SamplerState
  SharedPtr<SamplerState> m_sampler = nullptr;

  //The Constant Buffer (Never Change)
  SharedPtr<Buffer> m_cBufferCamera = nullptr;

  //The Constant Buffer (Change on Resize)
  //Buffer * m_cBufferChangeOnResize = nullptr;

  //The Constant Buffer (Change Every Frame)
  SharedPtr<Buffer> m_cBufferChangeEveryFrame = nullptr;

  //The World Matrix
  Matrix4 m_world;

  SceneGraph sceneGraph;

  SharedPtr<Editor> m_editorUI;
};