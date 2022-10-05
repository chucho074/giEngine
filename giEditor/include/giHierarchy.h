/**
 * @file    giHierarchy.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/06/2022
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#pragma once
#include <giStdHeaders.h>
#include <giSceneNode.h>
#include "giImGui.h"

using namespace giEngineSDK;
using namespace ImGui;

class Hierarchy
{
 public:
  //Default constructor.
  Hierarchy();

  //Default destructor.
  ~Hierarchy() = default;

  /**
   * @brief      Initialize the information.
   */
  void
  init();

  /**
   * @brief      Update the information.
   */
  void
  update(float inDeltaTime);

  /**
   * @brief      Render the information.
   */
  void
  render();

  /**
   * @brief      Destroy the information.
   */
  void
  destroy();

  /**
   * @brief      Renders the information of the node into the table of hierarchy.
   */
  void
  renderNode(SharedPtr<SceneNode> inNode);

 private:
 
  ImGuiWindowFlags m_windowFlags = 0;
  ImGuiTreeNodeFlags m_rootFlags = 0;
  ImGuiTreeNodeFlags m_treeSelectableFlags = 0;
  ImGuiTreeNodeFlags m_leafFlags = 0;

  


  friend class Details;
};