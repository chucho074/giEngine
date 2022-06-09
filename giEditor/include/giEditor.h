/**
 * @file    giEditor.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    01/06/2022
 * @brief   A basic implementation of the editor of the engine.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giImGui.h"
#include "giContentBrowser.h"
#include "giHierarchy.h"
#include "giDetails.h"

using namespace giEngineSDK;
using namespace ImGui;

/**
 * @brief      .
 */
class Editor
{
 public:

  //Default constructor.
	Editor() = default;
	
  //Default destructor.
  ~Editor() = default;

  /**
   * @brief      .
   */
  void
  init(void * inHandler, Vector2 inWindowSize);

  /**
   * @brief      .
   */
  void
  update(float inDeltaTime);

  /**
   * @brief      .
   */
  void 
  render();

  /**
   * @brief      .
   */
  void
  destroy();

  /**
   * 
   */
  void
  callBack();



 protected:


	
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

};