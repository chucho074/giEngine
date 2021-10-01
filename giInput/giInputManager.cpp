/**
 * @file    giInputManager.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    23/09/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giInputManager.h"
#include <iostream>

using std::cout;

namespace giEngineSDK {
  void 
  Input::init() {
    mouseId = m_manager.CreateDevice<gainput::InputDeviceMouse>();
    keyboardId = m_manager.CreateDevice<gainput::InputDeviceKeyboard>();
    padId = m_manager.CreateDevice<gainput::InputDevicePad>();
    m_inputMap = new gainput::InputMap(m_manager);
    setButtons();
  }

  void
  Input::createInputDevice() {
    
  }
  
  void 
  Input::update() {
    m_manager.Update();
  }
  
  void 
  Input::updateSize(int inWidth, int inHeight) {
    m_manager.SetDisplaySize(inWidth, inHeight);
  }

  void 
  Input::sendEvent(MSG inMessage) {
    m_manager.HandleMessage(inMessage);
    //runEvents();
  }

  void 
  Input::setButtons() {
    m_inputMap->MapBool(FrontMovement, keyboardId, gainput::KeyW);
    m_inputMap->MapBool(BackMovement,  keyboardId, gainput::KeyS);
    m_inputMap->MapBool(LeftMovement,  keyboardId, gainput::KeyA);
    m_inputMap->MapBool(RightMovement, keyboardId, gainput::KeyD);
    
  }

  void 
  Input::runEvents() {
    // Check button states
    if (m_inputMap->GetBoolWasDown(FrontMovement)) {
      front = false;
    }
    if (m_inputMap->GetBoolWasDown(BackMovement)) {
      back = false;
    }
    if (m_inputMap->GetBoolWasDown(LeftMovement)) {
      left = false;
    }
    if (m_inputMap->GetBoolWasDown(RightMovement)) {
      right = false;
    }

    if (m_inputMap->GetBoolIsNew(FrontMovement)) {
      front = true;
    }
    if (m_inputMap->GetBoolIsNew(BackMovement)) {
      back = true;
    }
    if (m_inputMap->GetBoolIsNew(LeftMovement)) {
      left = true;
    }
    if (m_inputMap->GetBoolIsNew(RightMovement)) {
      right = true;
    }
  }

}