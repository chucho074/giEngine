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


namespace giEngineSDK {
  Input::~Input() {
    if (m_inputManager) {
      OIS::InputManager::destroyInputSystem(m_inputManager);
    }
  }

  void
  Input::init(WindowHandle wHndl) {
    OIS::ParamList pl;
    std::ostringstream windowHndStr;
    windowHndStr << (size_T)wHndl;
    pl.insert(make_pair(String("WINDOW"), windowHndStr.str()));
    pl.insert(make_pair(String("w32_mouse"), String("DISCL_FOREGROUND")));
    pl.insert(make_pair(String("w32_mouse"), String("DISCL_NONEXCLUSIVE")));

    m_inputManager = OIS::InputManager::createInputSystem(pl);
    uint32 v = m_inputManager->getVersionNumber();
    ConsoleOut << "OIS Version " << (v >> 16) << "." << ((v >> 8) & 0x000000FF) << "." << (v & 0x000000FF)
      << "\nRelease Name: "    << m_inputManager->getVersionName()
      << "\nManager: "         << m_inputManager->inputSystemName()
      << "\nTotal Keyboards: " << m_inputManager->getNumberOfDevices(OIS::OISKeyboard)
      << "\nTotal Mouses: "      << m_inputManager->getNumberOfDevices(OIS::OISMouse)
      << "\nTotal JoySticks: " << m_inputManager->getNumberOfDevices(OIS::OISJoyStick);

    m_keyBoard = static_cast<OIS::Keyboard*>(m_inputManager->createInputObject(OIS::OISKeyboard, true));
    m_keyBoard->setEventCallback(this);

    m_mouse = static_cast<OIS::Mouse*>(m_inputManager->createInputObject(OIS::OISMouse, true));
    m_mouse->setEventCallback(this);
    
    setButtons();
    
  }
  
  void 
  Input::update() {
    m_keyBoard->capture();
    m_mouse->capture();
  }
  
  void 
  Input::updateSize(int inWidth, int inHeight) {
    const OIS::MouseState& ms = m_mouse->getMouseState();
    ms.width = inWidth;
    ms.height = inHeight;
  }

  bool 
  Input::isKeyPressed(KEYBOARD_KEYS::E inKey) {
    return m_keyState[inKey] == STATUS_BUTTONS::kPRESSED ? true : false;
  }

  bool
  Input::isKeyReleassed(KEYBOARD_KEYS::E inKey) {
    if (m_keyState[inKey] == STATUS_BUTTONS::kRELEASED) {
      m_keyState[inKey] == STATUS_BUTTONS::kIDLE;
      return true;
    }
    else {
      return false;
    }
    //return m_keyState[inKey] == STATUS_BUTTONS::kRELEASED ? true : false;
  }

  bool 
  Input::isMouseButtonPressed(MOUSE_BUTTONS::E inButton) {
    return m_mouseState[inButton] == STATUS_BUTTONS::kPRESSED ? true : false;
  }

  bool
  Input::isMouseButtonReleassed(MOUSE_BUTTONS::E inButton) {
    if(m_mouseState[inButton] == STATUS_BUTTONS::kRELEASED) {
      m_mouseState[inButton] == STATUS_BUTTONS::kIDLE;
      return true;
    }
    else {
      return false;
    }
    //return m_mouseState[inButton] == STATUS_BUTTONS::kRELEASED ? true : false;
  }

  bool 
  Input::isButtonPressed(CONTROL_BUTTONS::E inButton) {
    return false; 
  }

  bool 
  Input::isButtonReleassed(CONTROL_BUTTONS::E inButton) {
    return false;
  }

  Vector2 
  Input::isMouseMoved() {
  Vector2 tmpVect;
    const OIS::MouseState& ms = m_mouse->getMouseState();
    tmpVect.x = (float)ms.X.rel;
    tmpVect.y = (float)ms.Y.rel;
    return tmpVect;
  }

  void
  Input::setButtons() {
    m_keys.insert(make_pair(OIS::KeyCode::KC_ESCAPE,     KEYBOARD_KEYS::kESQ));
    m_keys.insert(make_pair(OIS::KeyCode::KC_1,          KEYBOARD_KEYS::k1));
    m_keys.insert(make_pair(OIS::KeyCode::KC_2,          KEYBOARD_KEYS::k2));
    m_keys.insert(make_pair(OIS::KeyCode::KC_3,          KEYBOARD_KEYS::k3));
    m_keys.insert(make_pair(OIS::KeyCode::KC_4,          KEYBOARD_KEYS::k4));
    m_keys.insert(make_pair(OIS::KeyCode::KC_5,          KEYBOARD_KEYS::k5));
    m_keys.insert(make_pair(OIS::KeyCode::KC_6,          KEYBOARD_KEYS::k6));
    m_keys.insert(make_pair(OIS::KeyCode::KC_7,          KEYBOARD_KEYS::k7));
    m_keys.insert(make_pair(OIS::KeyCode::KC_8,          KEYBOARD_KEYS::k8));
    m_keys.insert(make_pair(OIS::KeyCode::KC_9,          KEYBOARD_KEYS::k9));
    m_keys.insert(make_pair(OIS::KeyCode::KC_0,          KEYBOARD_KEYS::k0));
    m_keys.insert(make_pair(OIS::KeyCode::KC_MINUS,      KEYBOARD_KEYS::kMINUS));
    m_keys.insert(make_pair(OIS::KeyCode::KC_EQUALS,     KEYBOARD_KEYS::kEQUAL));
    m_keys.insert(make_pair(OIS::KeyCode::KC_BACK,       KEYBOARD_KEYS::kBACKSPACE));
    m_keys.insert(make_pair(OIS::KeyCode::KC_TAB,        KEYBOARD_KEYS::kTAB));
    m_keys.insert(make_pair(OIS::KeyCode::KC_Q,          KEYBOARD_KEYS::kQ));
    m_keys.insert(make_pair(OIS::KeyCode::KC_W,          KEYBOARD_KEYS::kW));
    m_keys.insert(make_pair(OIS::KeyCode::KC_E,          KEYBOARD_KEYS::kE));
    m_keys.insert(make_pair(OIS::KeyCode::KC_R,          KEYBOARD_KEYS::kR));
    m_keys.insert(make_pair(OIS::KeyCode::KC_T,          KEYBOARD_KEYS::kT));
    m_keys.insert(make_pair(OIS::KeyCode::KC_Y,          KEYBOARD_KEYS::kY));
    m_keys.insert(make_pair(OIS::KeyCode::KC_U,          KEYBOARD_KEYS::kU));
    m_keys.insert(make_pair(OIS::KeyCode::KC_I,          KEYBOARD_KEYS::kI));
    m_keys.insert(make_pair(OIS::KeyCode::KC_O,          KEYBOARD_KEYS::kO));
    m_keys.insert(make_pair(OIS::KeyCode::KC_P,          KEYBOARD_KEYS::kP));
    m_keys.insert(make_pair(OIS::KeyCode::KC_A,          KEYBOARD_KEYS::kA));
    m_keys.insert(make_pair(OIS::KeyCode::KC_S,          KEYBOARD_KEYS::kS));
    m_keys.insert(make_pair(OIS::KeyCode::KC_D,          KEYBOARD_KEYS::kD));
    m_keys.insert(make_pair(OIS::KeyCode::KC_F,          KEYBOARD_KEYS::kF));
    m_keys.insert(make_pair(OIS::KeyCode::KC_G,          KEYBOARD_KEYS::kG));
    m_keys.insert(make_pair(OIS::KeyCode::KC_H,          KEYBOARD_KEYS::kH));
    m_keys.insert(make_pair(OIS::KeyCode::KC_J,          KEYBOARD_KEYS::kJ));
    m_keys.insert(make_pair(OIS::KeyCode::KC_K,          KEYBOARD_KEYS::kK));
    m_keys.insert(make_pair(OIS::KeyCode::KC_L,          KEYBOARD_KEYS::kL));
    m_keys.insert(make_pair(OIS::KeyCode::KC_Z,          KEYBOARD_KEYS::kZ));
    m_keys.insert(make_pair(OIS::KeyCode::KC_X,          KEYBOARD_KEYS::kX));
    m_keys.insert(make_pair(OIS::KeyCode::KC_C,          KEYBOARD_KEYS::kC));
    m_keys.insert(make_pair(OIS::KeyCode::KC_V,          KEYBOARD_KEYS::kV));
    m_keys.insert(make_pair(OIS::KeyCode::KC_B,          KEYBOARD_KEYS::kB));
    m_keys.insert(make_pair(OIS::KeyCode::KC_N,          KEYBOARD_KEYS::kN));
    m_keys.insert(make_pair(OIS::KeyCode::KC_M,          KEYBOARD_KEYS::kM));
    m_keys.insert(make_pair(OIS::KeyCode::KC_UP,         KEYBOARD_KEYS::kUP));
    m_keys.insert(make_pair(OIS::KeyCode::KC_DOWN,       KEYBOARD_KEYS::kDOWN));
    m_keys.insert(make_pair(OIS::KeyCode::KC_LEFT,       KEYBOARD_KEYS::kLEFT));
    m_keys.insert(make_pair(OIS::KeyCode::KC_RIGHT,      KEYBOARD_KEYS::kRIGHT));
    m_keys.insert(make_pair(OIS::KeyCode::KC_LBRACKET,   KEYBOARD_KEYS::kLBRACKET));
    m_keys.insert(make_pair(OIS::KeyCode::KC_RBRACKET,   KEYBOARD_KEYS::kRBRACKET));
    //m_keys.insert(make_pair(OIS::KeyCode::KC_RETURN,     KEYBOARD_KEYS::kRETURN));
    m_keys.insert(make_pair(OIS::KeyCode::KC_LCONTROL,   KEYBOARD_KEYS::kLCTRL));
    m_keys.insert(make_pair(OIS::KeyCode::KC_RCONTROL,   KEYBOARD_KEYS::kRCTRL));
    m_keys.insert(make_pair(OIS::KeyCode::KC_SEMICOLON,  KEYBOARD_KEYS::kSEMICOLON));
    m_keys.insert(make_pair(OIS::KeyCode::KC_APOSTROPHE, KEYBOARD_KEYS::kAPOSTROPHE));
    m_keys.insert(make_pair(OIS::KeyCode::KC_GRAVE,      KEYBOARD_KEYS::kGRAVEACCENT));
    m_keys.insert(make_pair(OIS::KeyCode::KC_LSHIFT,     KEYBOARD_KEYS::kLSHIFT));
    m_keys.insert(make_pair(OIS::KeyCode::KC_BACKSLASH,  KEYBOARD_KEYS::kBACKSLASH));
    m_keys.insert(make_pair(OIS::KeyCode::KC_COMMA,      KEYBOARD_KEYS::kCOMMA));
    m_keys.insert(make_pair(OIS::KeyCode::KC_PERIOD,     KEYBOARD_KEYS::kDOT));
    m_keys.insert(make_pair(OIS::KeyCode::KC_SLASH,      KEYBOARD_KEYS::kSLASH));
    m_keys.insert(make_pair(OIS::KeyCode::KC_RSHIFT,     KEYBOARD_KEYS::kRSHIFT));
    m_keys.insert(make_pair(OIS::KeyCode::KC_LMENU,      KEYBOARD_KEYS::kLALT));
    m_keys.insert(make_pair(OIS::KeyCode::KC_RMENU,      KEYBOARD_KEYS::kRALT));
    m_keys.insert(make_pair(OIS::KeyCode::KC_SPACE,      KEYBOARD_KEYS::kSPACE));
    m_keys.insert(make_pair(OIS::KeyCode::KC_CAPITAL,    KEYBOARD_KEYS::kCAPS));
    m_keys.insert(make_pair(OIS::KeyCode::KC_F1,         KEYBOARD_KEYS::kF1));
    m_keys.insert(make_pair(OIS::KeyCode::KC_F2,         KEYBOARD_KEYS::kF2));
    m_keys.insert(make_pair(OIS::KeyCode::KC_F3,         KEYBOARD_KEYS::kF3));
    m_keys.insert(make_pair(OIS::KeyCode::KC_F4,         KEYBOARD_KEYS::kF4));
    m_keys.insert(make_pair(OIS::KeyCode::KC_F5,         KEYBOARD_KEYS::kF5));
    m_keys.insert(make_pair(OIS::KeyCode::KC_F6,         KEYBOARD_KEYS::kF6));
    m_keys.insert(make_pair(OIS::KeyCode::KC_F7,         KEYBOARD_KEYS::kF7));
    m_keys.insert(make_pair(OIS::KeyCode::KC_F8,         KEYBOARD_KEYS::kF8));
    m_keys.insert(make_pair(OIS::KeyCode::KC_F9,         KEYBOARD_KEYS::kF9));
    m_keys.insert(make_pair(OIS::KeyCode::KC_F10,        KEYBOARD_KEYS::kF10));
    m_keys.insert(make_pair(OIS::KeyCode::KC_F11,        KEYBOARD_KEYS::kF11));
    m_keys.insert(make_pair(OIS::KeyCode::KC_F12,        KEYBOARD_KEYS::kF12));
    m_keys.insert(make_pair(OIS::KeyCode::KC_NUMLOCK,    KEYBOARD_KEYS::kNUMLOCK));
    m_keys.insert(make_pair(OIS::KeyCode::KC_SCROLL,     KEYBOARD_KEYS::kSCRLK));
    m_keys.insert(make_pair(OIS::KeyCode::KC_NUMPAD1,    KEYBOARD_KEYS::kNUMPAD1));
    m_keys.insert(make_pair(OIS::KeyCode::KC_NUMPAD2,    KEYBOARD_KEYS::kNUMPAD2));
    m_keys.insert(make_pair(OIS::KeyCode::KC_NUMPAD3,    KEYBOARD_KEYS::kNUMPAD3));
    m_keys.insert(make_pair(OIS::KeyCode::KC_NUMPAD4,    KEYBOARD_KEYS::kNUMPAD4));
    m_keys.insert(make_pair(OIS::KeyCode::KC_NUMPAD5,    KEYBOARD_KEYS::kNUMPAD5));
    m_keys.insert(make_pair(OIS::KeyCode::KC_NUMPAD6,    KEYBOARD_KEYS::kNUMPAD6));
    m_keys.insert(make_pair(OIS::KeyCode::KC_NUMPAD7,    KEYBOARD_KEYS::kNUMPAD7));
    m_keys.insert(make_pair(OIS::KeyCode::KC_NUMPAD8,    KEYBOARD_KEYS::kNUMPAD8));
    m_keys.insert(make_pair(OIS::KeyCode::KC_NUMPAD9,    KEYBOARD_KEYS::kNUMPAD9));
    m_keys.insert(make_pair(OIS::KeyCode::KC_NUMPAD0,    KEYBOARD_KEYS::kNUMPAD0));
    m_keys.insert(make_pair(OIS::KeyCode::KC_SUBTRACT,   KEYBOARD_KEYS::kSUB));
    m_keys.insert(make_pair(OIS::KeyCode::KC_ADD,        KEYBOARD_KEYS::kINC));
    //m_keys.insert(make_pair(OIS::KeyCode::KC_DECIMAL,    KEYBOARD_KEYS::kDECIMAL));
    m_keys.insert(make_pair(OIS::KeyCode::KC_DIVIDE,     KEYBOARD_KEYS::kDIV));
    m_keys.insert(make_pair(OIS::KeyCode::KC_MULTIPLY,   KEYBOARD_KEYS::kMUL));
    m_keys.insert(make_pair(OIS::KeyCode::KC_PGDOWN,     KEYBOARD_KEYS::kPGDOWN));
    m_keys.insert(make_pair(OIS::KeyCode::KC_PGUP,       KEYBOARD_KEYS::kPGUP));
    m_keys.insert(make_pair(OIS::KeyCode::KC_INSERT,     KEYBOARD_KEYS::kINSERT));
    m_keys.insert(make_pair(OIS::KeyCode::KC_DELETE,     KEYBOARD_KEYS::kDELETE));
    m_keys.insert(make_pair(OIS::KeyCode::KC_HOME,       KEYBOARD_KEYS::kHOME));
    m_keys.insert(make_pair(OIS::KeyCode::KC_END,        KEYBOARD_KEYS::kEND));
    m_keys.insert(make_pair(OIS::KeyCode::KC_INSERT,     KEYBOARD_KEYS::kINSERT));

    //Mouse
    m_mouseKeys.insert(make_pair(OIS::MouseButtonID::MB_Left, MOUSE_BUTTONS::kLEFTCLIC));
    m_mouseKeys.insert(make_pair(OIS::MouseButtonID::MB_Right, MOUSE_BUTTONS::kRIGHTCLIC));
    m_mouseKeys.insert(make_pair(OIS::MouseButtonID::MB_Middle, MOUSE_BUTTONS::kMIDCLIC));
    m_mouseKeys.insert(make_pair(OIS::MouseButtonID::MB_Button3, MOUSE_BUTTONS::kBUTTON3));
    m_mouseKeys.insert(make_pair(OIS::MouseButtonID::MB_Button4, MOUSE_BUTTONS::kBUTTON4));
    m_mouseKeys.insert(make_pair(OIS::MouseButtonID::MB_Button5, MOUSE_BUTTONS::kBUTTON5));
    m_mouseKeys.insert(make_pair(OIS::MouseButtonID::MB_Button6, MOUSE_BUTTONS::kBUTTON6));
    m_mouseKeys.insert(make_pair(OIS::MouseButtonID::MB_Button7, MOUSE_BUTTONS::kBUTTON7));

  }
  
  bool 
  Input::keyPressed(const OIS::KeyEvent& arg) {
    if(m_keyState[m_keys[arg.key]] = STATUS_BUTTONS::kPRESSED) {
      return true;
    }
    return false;
  }
  
  bool 
  Input::keyReleased(const OIS::KeyEvent& arg) {
    m_keyState[m_keys[arg.key]] = STATUS_BUTTONS::kRELEASED;
    return true;
  }
  
  bool 
  Input::mouseMoved(const OIS::MouseEvent& arg) {
    GI_UNREFERENCED_PARAMETER(arg);
    //const OIS::MouseState& s = arg.state;
    /*std::cout << "\nMouseMoved: Abs("
              << s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel(" << s.X.rel
              << ", " << s.Y.rel << ", " << s.Z.rel << ")";*/
    return true;
  }
  
  bool 
  Input::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {
    GI_UNREFERENCED_PARAMETER(arg);
    m_mouseState[m_mouseKeys[id]] = STATUS_BUTTONS::kPRESSED;
    return false;
  }
  
  bool 
  Input::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {
    GI_UNREFERENCED_PARAMETER(arg);
    m_mouseState[m_mouseKeys[id]] = STATUS_BUTTONS::kRELEASED;
    return false;
  }
  
}