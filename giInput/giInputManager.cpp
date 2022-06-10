/**
 * @file    giInputManager.cpp
 * @author  Jesus Alberto Del Moral Cupil
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
    mouseId    = m_manager.CreateDevice<gainput::InputDeviceMouse>();
    keyboardId = m_manager.CreateDevice<gainput::InputDeviceKeyboard>();
    padId      = m_manager.CreateDevice<gainput::InputDevicePad>();

    m_keyboardMap = new gainput::InputMap(m_manager);
    m_mouseAxisMap = new gainput::InputMap(m_manager);
    m_mouseButtonsMap = new gainput::InputMap(m_manager);
    m_gamepadAxisMap = new gainput::InputMap(m_manager);
    m_gamepadButtonsMap = new gainput::InputMap(m_manager);
    
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
    MSG msg = tagMSG(inMessage);
    m_manager.HandleMessage(msg);
  }

  bool 
  Input::isKeyPressed(KEYBOARD_KEYS::E inKey) {
    return m_keyboardMap->GetBoolIsNew(inKey);
  }

  bool
  Input::isKeyReleassed(KEYBOARD_KEYS::E inKey) {
    return m_keyboardMap->GetBoolWasDown(inKey);
  }

  bool 
  Input::isMouseButtonPressed(MOUSE_BUTTONS::E inButton) {
    return m_mouseButtonsMap->GetBoolIsNew(inButton);
  }

  bool
  Input::isMouseButtonReleassed(MOUSE_BUTTONS::E inButton) {
    return m_mouseButtonsMap->GetBoolWasDown(inButton);
  }

  bool 
  Input::isButtonPressed(CONTROL_BUTTONS::E inButton) {
    return m_gamepadButtonsMap->GetBoolIsNew(inButton);
  }

  bool 
  Input::isButtonReleassed(CONTROL_BUTTONS::E inButton) {
    return m_gamepadButtonsMap->GetBoolWasDown(inButton);
  }

  Vector2 
  Input::isMouseMoved() {
    uint32 x = m_mouseAxisMap->GetFloat(MOUSE_MOVEMENTS::kXAxis) * m_manager.GetDisplayWidth();
    uint32 y = m_mouseAxisMap->GetFloat(MOUSE_MOVEMENTS::kYAxis) * m_manager.GetDisplayHeight();
    return Vector2(x, y);
  }

  void
  Input::setButtons() {
    //Keyboard
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kESQ,         keyboardId, gainput::KeyEscape);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kF1,          keyboardId, gainput::KeyF1);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kF2,          keyboardId, gainput::KeyF2);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kF3,          keyboardId, gainput::KeyF3);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kF4,          keyboardId, gainput::KeyF4);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kF5,          keyboardId, gainput::KeyF5);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kF6,          keyboardId, gainput::KeyF6);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kF7,          keyboardId, gainput::KeyF7);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kF8,          keyboardId, gainput::KeyF8);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kF9,          keyboardId, gainput::KeyF9);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kF10,         keyboardId, gainput::KeyF10);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kF11,         keyboardId, gainput::KeyF11);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kF12,         keyboardId, gainput::KeyF12);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kPRTSC,       keyboardId, gainput::KeyPrint);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kSCRLK,       keyboardId, gainput::KeyScrollLock);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kPAUSE,       keyboardId, gainput::KeyBreak);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kGRAVEACCENT, keyboardId, gainput::KeyGrave);      //
    m_keyboardMap->MapBool(KEYBOARD_KEYS::k1,           keyboardId, gainput::Key1);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::k2,           keyboardId, gainput::Key2);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::k3,           keyboardId, gainput::Key3);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::k4,           keyboardId, gainput::Key4);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::k5,           keyboardId, gainput::Key5);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::k6,           keyboardId, gainput::Key6);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::k7,           keyboardId, gainput::Key7);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::k8,           keyboardId, gainput::Key8);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::k9,           keyboardId, gainput::Key9);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::k0,           keyboardId, gainput::Key0);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kMINUS,       keyboardId, gainput::KeyMinus);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kEQUAL,       keyboardId, gainput::KeyEqual);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kBACKSPACE,   keyboardId, gainput::KeyBackSpace);
    //m_keyboardMap->MapBool(KEYBOARD_KEYS::kINSERT,      keyboardId, gainput::KeyInsert);
    //m_keyboardMap->MapBool(KEYBOARD_KEYS::kHOME,        keyboardId, gainput::KeyHome);
    //m_keyboardMap->MapBool(KEYBOARD_KEYS::kPGUP,        keyboardId, gainput::KeyPageUp);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kTAB,         keyboardId, gainput::KeyTab);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kQ,           keyboardId, gainput::KeyQ);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kW,           keyboardId, gainput::KeyW);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kE,           keyboardId, gainput::KeyE);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kR,           keyboardId, gainput::KeyR);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kT,           keyboardId, gainput::KeyT);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kY,           keyboardId, gainput::KeyY);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kU,           keyboardId, gainput::KeyU);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kI,           keyboardId, gainput::KeyI);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kO,           keyboardId, gainput::KeyO);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kP,           keyboardId, gainput::KeyP);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kLBRACKET,    keyboardId, gainput::KeyBraceLeft);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kRBRACKET,    keyboardId, gainput::KeyBracketRight);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kBACKSLASH,   keyboardId, gainput::KeyBackslash);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kDELETE,      keyboardId, gainput::KeyDelete);
    //m_keyboardMap->MapBool(KEYBOARD_KEYS::kEND,         keyboardId, gainput::KeyEnd);
    //m_keyboardMap->MapBool(KEYBOARD_KEYS::kPGDOWN,      keyboardId, gainput::KeyPageDown);
    //m_keyboardMap->MapBool(KEYBOARD_KEYS::kCAPS,        keyboardId, gainput::KeyCapsLock);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kA,           keyboardId, gainput::KeyA);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kS,           keyboardId, gainput::KeyS);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kD,           keyboardId, gainput::KeyD);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kF,           keyboardId, gainput::KeyF);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kG,           keyboardId, gainput::KeyG);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kH,           keyboardId, gainput::KeyH);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kJ,           keyboardId, gainput::KeyJ);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kK,           keyboardId, gainput::KeyK);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kL,           keyboardId, gainput::KeyL);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kSEMICOLON,   keyboardId, gainput::KeySemicolon);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kAPOSTROPHE,  keyboardId, gainput::KeyApostrophe);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kENTER,       keyboardId, gainput::KeyKpEnter);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kLSHIFT,      keyboardId, gainput::KeyShiftL);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kZ,           keyboardId, gainput::KeyZ);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kX,           keyboardId, gainput::KeyX);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kC,           keyboardId, gainput::KeyC);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kV,           keyboardId, gainput::KeyV);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kB,           keyboardId, gainput::KeyB);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kN,           keyboardId, gainput::KeyN);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kM,           keyboardId, gainput::KeyM);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kCOMMA,       keyboardId, gainput::KeyComma);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kDOT,         keyboardId, gainput::KeyPeriod);     //
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kSLASH,       keyboardId, gainput::KeySlash);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kRSHIFT,      keyboardId, gainput::KeyShiftR);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kLCTRL,       keyboardId, gainput::KeyCtrlL);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kLALT,        keyboardId, gainput::KeyAltL);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kSPACE,        keyboardId, gainput::KeySpace);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kRALT,        keyboardId, gainput::KeyAltGr);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kRCTRL,       keyboardId, gainput::KeyCtrlR);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kUP,          keyboardId, gainput::KeyUp);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kLEFT,        keyboardId, gainput::KeyLeft);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kDOWN,        keyboardId, gainput::KeyDown);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kRIGHT,       keyboardId, gainput::KeyRight);
    //m_keyboardMap->MapBool(KEYBOARD_KEYS::kNUMLOCK,     keyboardId, gainput::KeyNumLock);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kDIV,         keyboardId, gainput::KeyKpDivide);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kMUL,         keyboardId, gainput::KeyKpMultiply);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kSUB,         keyboardId, gainput::KeyKpSubtract);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kINC,         keyboardId, gainput::KeyKpAdd);
    /*m_keyboardMap->MapBool(KEYBOARD_KEYS::kNUMPAD0,     keyboardId, gainput::KeyKpInsert);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kNUMPAD1,     keyboardId, gainput::KeyKpEnd);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kNUMPAD2,     keyboardId, gainput::KeyKpDown);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kNUMPAD3,     keyboardId, gainput::KeyKpPageDown);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kNUMPAD4,     keyboardId, gainput::KeyKpLeft);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kNUMPAD5,     keyboardId, gainput::KeyKpBegin);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kNUMPAD6,     keyboardId, gainput::KeyKpRight);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kNUMPAD7,     keyboardId, gainput::KeyKpHome);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kNUMPAD8,     keyboardId, gainput::KeyKpPageUp);
    m_keyboardMap->MapBool(KEYBOARD_KEYS::kNUMPAD9,     keyboardId, gainput::KeyKpDelete);*/
    
    //Mouse
    m_mouseButtonsMap->MapBool(MOUSE_BUTTONS::kLEFTCLIC,  mouseId, gainput::MouseButtonLeft);
    m_mouseButtonsMap->MapBool(MOUSE_BUTTONS::kRIGHTCLIC, mouseId, gainput::MouseButtonRight);
    m_mouseButtonsMap->MapBool(MOUSE_BUTTONS::kMIDCLIC,   mouseId, gainput::MouseButtonMiddle);
    m_mouseButtonsMap->MapBool(MOUSE_BUTTONS::kBUTTON3,   mouseId, gainput::MouseButton3);
    m_mouseButtonsMap->MapBool(MOUSE_BUTTONS::kBUTTON4,   mouseId, gainput::MouseButton4);
    m_mouseButtonsMap->MapBool(MOUSE_BUTTONS::kBUTTON5,   mouseId, gainput::MouseButton5);
    m_mouseButtonsMap->MapBool(MOUSE_BUTTONS::kBUTTON6,   mouseId, gainput::MouseButton6);
    m_mouseButtonsMap->MapBool(MOUSE_BUTTONS::kBUTTON7,   mouseId, gainput::MouseButton7);

    m_mouseAxisMap->MapFloat(MOUSE_MOVEMENTS::kXAxis, mouseId, gainput::MouseAxisX);
    m_mouseAxisMap->MapFloat(MOUSE_MOVEMENTS::kYAxis, mouseId, gainput::MouseAxisY);
    m_mouseAxisMap->MapFloat(MOUSE_MOVEMENTS::kWheelUp,   mouseId, gainput::MouseButtonWheelUp);
    m_mouseAxisMap->MapFloat(MOUSE_MOVEMENTS::kWheelDown, mouseId, gainput::MouseButtonWheelDown);

    //Control

  }
}