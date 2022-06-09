/**
 * @file    giDetails.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/06/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once

#include <giStdHeaders.h>
#include "giImGui.h"

using namespace giEngineSDK;
using namespace ImGui;

class Details
{
 public:
  //Default constructor.
  Details();

  //Default destructor.
  ~Details() = default;

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

 private:
 
  ImGuiWindowFlags m_windowFlags = 0;
  
};