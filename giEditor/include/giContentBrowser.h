/**
 * @file    giContentBrowser.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    01/06/2022
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#pragma once
#include <giStdHeaders.h>
#include "giImGui.h"

using namespace giEngineSDK;
using namespace ImGui;

class ContentBrowser
{
 public:
  //Default constructor.
  ContentBrowser(Path inWorkingDir);
  
  //Default destructor.
  ~ContentBrowser() = default;
  
  /**
   * @brief      Initialize the content Browser.
   */
  void
  init();

  /**
   * @brief      Update the information of the content browser.
   */
  void
  update(float inDeltaTime);

  /**
   * @brief      Render the information of the content browser.
   */
  void 
  render();

  /**
   * @brief      Destroy the information of the content browser.
   */
  void
  destroy();

  /**
   * @brief      .
   * @param      inWorkingDir 
   */
  void
  changeWorkingDir(Path inWorkingDir);

 protected:
  void
  drawFolders(Path& inIter,
              int32& inTreeCount, 
              int32& inSelectedNode);

 private:

  ImGuiTreeNodeFlags m_treeFolders = ImGuiTreeNodeFlags_OpenOnArrow
                                     | ImGuiTreeNodeFlags_OpenOnDoubleClick
                                     | ImGuiTreeNodeFlags_SpanAvailWidth;
  
  ImGuiTreeNodeFlags m_treeEmpty = ImGuiTreeNodeFlags_SpanAvailWidth
                                    | ImGuiTreeNodeFlags_Leaf
                                    | ImGuiTreeNodeFlags_NoTreePushOnOpen;


  Path m_workingDirectory;

  Path m_currentDirectory;
  
  ImGuiWindowFlags m_windowFlags = 0;
};