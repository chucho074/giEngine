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
//#include <giPrerequisitesCore.h>





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