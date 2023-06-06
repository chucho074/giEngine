/**
 * @file    giEditor.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    01/06/2022
 * @brief   A basic implementation of the editor of the engine.
 */
 
/**
 * @include
 */
#pragma once
#include <giResourceManager.h>
#include <giFile.h>
#include "giImGui.h"
#include "giContentBrowser.h"
#include "giHierarchy.h"
#include "giDetails.h"

using namespace giEngineSDK;
using namespace ImGui;

/**
 * @brief     Basic implementation of the ui for the Editor for the engine.
 */
class Editor
{
 public:

  //Default constructor.
  Editor() = default;
  
  //Default destructor.
  ~Editor() = default;

  /**
   * @brief      Initialize the editor UI.
   */
  void
  init(void * inHandler, Vector2 inWindowSize);

  /**
   * @brief      Update the information of the editor.
   */
  void
  update(float inDeltaTime);

  /**
   * @brief      Render the information of the editor.
   */
  void 
  render();

  /**
   * @brief      Destroy the information of the editor.
   */
  void
  destroy();

  /**
   * @brief      Detect the inputs of the editor.
   */
  void
  callBack();

  /**
   * @brief      Renders a Window with the performance information.
   */
  void
  renderPerformanceWindow();

  /**
   * @brief      Renders a window with the information about the engine dev.
   */
  void
  renderAboutWindow();

  /**
   * @brief      Renders a window with the variable of the editor camera movement.
   */
  void
  renderCameraMovementWindow();

  /**
   * @brief      Renders a window for creation/selection of projects.
   */
  void
  renderProjectCreationSelection();

  /**
   * @brief      Renders a window for import into the project.
   */
  void
  renderImport();

  /**
   * @brief      Renders a window for giAMR tool.
   */
  void
  renderAMR();

  /**
   * @brief      Renders a window for giAMR tool.
   */
  void
  renderAMRprocess();

  /**
   * @brief      .
   * @return     Returns the reference of the .
   */
  ResourceRef 
  openFileDilog();

  /**
   * @brief      .
   */
  void 
  saveFileDilog();


 private:
   
   SharedPtr<UI> m_ui;

   SharedPtr<ContentBrowser> m_contentBrowser;

   SharedPtr<Hierarchy> m_hierarchy;

   SharedPtr<Details> m_details;

   void * m_windowHandle = nullptr;

   bool m_touchingImGui = false;

   void* m_windowsHandle = nullptr;

   bool m_startOmniverse = false;

   bool m_isRunningOmniverse = false;


   //Bools for rendering the diferent windows.

   bool m_renderPerformance = true;

   bool m_renderAbout = false;

   bool m_renderCamera = true;

   //The window for creation/selection of projects.
   bool m_renderProjectSelection = false;

   //To change
   Path m_savingPath;

};