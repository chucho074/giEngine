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
#include <giStdHeaders.h>
//#include <giPrerequisitesCore.h>



namespace giEngineSDK {
  class UI
  {
   public:
  	UI() = default;
  	~UI() = default;
  
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
  
  
    Vector2 m_windowSize;
  
    bool m_touchingUI = false;
  
    float m_size;
  
    String m_text;
  
    void* m_windowHandle = nullptr;
  
  };
}