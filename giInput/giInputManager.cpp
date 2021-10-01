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
  Input::sendEvent() {
    m_manager.HandleMessage();
  }

  void 
  Input::setButtons() {
    m_inputMap->MapBool(ButtonMenu, keyboardId, gainput::KeyEscape);
    m_inputMap->MapBool(ButtonConfirm, mouseId, gainput::MouseButtonLeft);
    m_inputMap->MapBool(ButtonConfirm, padId, gainput::PadButtonA);
    m_inputMap->MapFloat(MouseX, mouseId, gainput::MouseAxisX);
    m_inputMap->MapFloat(MouseY, mouseId, gainput::MouseAxisY);
  }

}