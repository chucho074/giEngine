/**
 * @file    giBaseInput.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    21/09/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include <giPrerequisitesCore.h>
#include <giModule.h>
#include <giVector2.h>
#include <Windows.h>
#include <SFML/Window.hpp>

using sf::WindowHandle;

namespace giEngineSDK {
  /**
   * @brief    Keys for ANSI keyboard.
   */
  namespace KEYBOARD_KEYS {
    enum E {
      kESQ = 0,
      kF1,
      kF2,
      kF3,
      kF4,
      kF5,
      kF6,
      kF7,
      kF8,
      kF9,
      kF10,
      kF11,
      kF12,
      kPRTSC,
      kSCRLK,
      kPAUSE,
      kGRAVEACCENT,     //?
      k1,
      k2,
      k3,
      k4,
      k5,
      k6,
      k7,
      k8,
      k9,
      k0,
      kMINUS, 
      kEQUAL,
      kBACKSPACE,
      kINSERT,
      kHOME,
      kPGUP,
      kTAB,
      kQ,
      kW,
      kE,
      kR,
      kT,
      kY,
      kU,
      kI,
      kO,
      kP,
      kLBRACKET,
      kRBRACKET,
      kBACKSLASH,
      kDELETE,
      kEND,
      kPGDOWN,
      kCAPS,
      kA,
      kS,
      kD,
      kF,
      kG,
      kH,
      kJ,
      kK,
      kL,
      kSEMICOLON,
      kAPOSTROPHE,
      kENTER,
      kLSHIFT,
      kZ,
      kX,
      kC,
      kV,
      kB,
      kN,
      kM,
      kCOMMA,
      kDOT,
      kSLASH,
      kRSHIFT,
      kLCTRL,
      kLALT,
      kSPACE,
      kRALT,
      kRCTRL,
      kUP,
      kLEFT,
      kDOWN,
      kRIGHT,
      kNUMLOCK,
      kDIV,
      kMUL,
      kSUB,
      kINC,
      kNUMPAD0,
      kNUMPAD1,
      kNUMPAD2,
      kNUMPAD3,
      kNUMPAD4,
      kNUMPAD5,
      kNUMPAD6,
      kNUMPAD7,
      kNUMPAD8,
      kNUMPAD9
    };
  }

  namespace MOUSE_BUTTONS {
    enum E {
      kLEFTCLIC = 0,
      kRIGHTCLIC,
      kMIDCLIC,
      kBUTTON3,
      kBUTTON4,
      kBUTTON5,
      kBUTTON6,
      kBUTTON7
    };
  }

  namespace MOUSE_MOVEMENTS {
    enum E {
      kXAxis = 0,
      kYAxis,
      kWheelUp,
      kWheelDown
    };
  }

  namespace CONTROL_BUTTONS {
    enum E {
      k = 0
    };
  }

  namespace STATUS_BUTTONS {
    enum E {
      kIDLE = 0,
      kPRESSED,
      kRELEASED
    };
  }

  class BaseInput : public Module<BaseInput>
  {
   public:
    //Desfault Constructor
    BaseInput() = default;

    //Destructor
    ~BaseInput() = default;

    /**
     * @brief   Initialize the input manager.
     */
    virtual void 
    init(WindowHandle wHndl) {}

    /**
     * @brief   Update the information of the input manager.
     */
    virtual void
    update() {}

    /**
     * @brief   Update the display size of the display.
     */
    virtual void
    updateSize(int inWidth, int inHeight) {}

    /**
     * @brief   Verify if a key of the keyboard was pressed.
     * @return  Returns a true if the key was pressed.
     */
    virtual bool 
    isKeyPressed(KEYBOARD_KEYS::E inKey) {
      GI_UNREFERENCED_PARAMETER(inKey);
      return false;
    }

    /**
     * @brief   Verify if a button of the mouse was pressed.
     * @return  Returns a true if the key was pressed.
     */
    virtual bool 
    isMouseButtonPressed(MOUSE_BUTTONS::E inButton) {
      GI_UNREFERENCED_PARAMETER(inButton);
      return false;
    }

    /**
     * @brief   Verify if a button of the control was pressed.
     * @return  Returns a true if the key was pressed.
     */
    virtual bool 
    isButtonPressed(CONTROL_BUTTONS::E inButton) {
      GI_UNREFERENCED_PARAMETER(inButton);
      return false;
    }

    /**
     * @brief   Verify if a key of the keyboard was Releassed.
     * @return  Returns a true if the key was Releassed.
     */
    virtual bool 
    isKeyReleassed(KEYBOARD_KEYS::E inKey) {
      GI_UNREFERENCED_PARAMETER(inKey);
      return false;
    }

    /**
     * @brief   Verify if a button of the mouse was Releassed.
     * @return  Returns a true if the key was Releassed.
     */
    virtual bool 
    isMouseButtonReleassed(MOUSE_BUTTONS::E inButton) {
      GI_UNREFERENCED_PARAMETER(inButton);
      return false;
    }

    /**
     * @brief   Verify if a button of the control was Releassed.
     * @return  Returns a true if the key was Releassed.
     */
    virtual bool 
    isButtonReleassed(CONTROL_BUTTONS::E inButton) {
      GI_UNREFERENCED_PARAMETER(inButton);
      return false;
    }

    /**
     * @brief   Verify the distance.
     * @return  Returns .
     */
    virtual Vector2 
    isMouseMoved() {
      return Vector2();
    }

    /**
     * @brief 
     * @return 
     */
    virtual float
    getXAxis() { 
      return 0.f; 
    }

    /**
     * @brief 
     * @return 
     */
    virtual float
    getYAxis() { 
      return 0.f; 
    }

   protected: 
     bool m_keyboardPress = false;
     bool m_keyboardRelease = false;
     bool m_mousePressed = false;
     bool m_mouseReleased = false;


     Map<KEYBOARD_KEYS::E, STATUS_BUTTONS::E> m_keyState;

     Map<MOUSE_BUTTONS::E, STATUS_BUTTONS::E> m_mouseState;
  };

  GI_CORE_EXPORT BaseInput& 
  g_inputManager();

  //For load the DLL
  using funCreateInputManager = BaseInput * (*)();
}