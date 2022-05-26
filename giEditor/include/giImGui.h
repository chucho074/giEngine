/**
 * @file    giImGui.h
 * @author  Jesus Alberto Del Moral Cupil
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
#include <giVector2.h>
//#include <giPrerequisitesCore.h>

using giEngineSDK::Vector2;


namespace ImGui {

  void
  init(void* inWindow, Vector2 inWindowSize);

  void
  update(void* inWindow, float inDT);

  void
  render();

  void
  shutDown();

  void
  callBack();

}