/**
 * @file    giInputManager.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    23/09/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include <giPrerequisitesUtilities.h>
#include <giBaseInput.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISEvents.h>
#include <OISException.h>

namespace giEngineSDK {
  enum Button {
    FrontMovement,
    BackMovement,
    LeftMovement,
    RightMovement
  };

  /**
   * @class:    Input.
   */
  class Input final : public BaseInput,
                      public OIS::KeyListener,
                      public OIS::MouseListener
  {
   public:
    //Default Constructor
  	Input() = default;

    //Destructor
  	~Input();

    /**
     * 
     */
    void 
    init(WindowHandle wHndl);

    /**
     * 
     */
    void 
    update();

    /**
     * 
     */
    void
    updateSize(int inWidth, int inHeight);

    /**
     * @brief   Verify if a key of the keyboard was pressed.
     * @return  Returns a true if the key was pressed.
     */
    bool
    isKeyPressed(KEYBOARD_KEYS::E inKey) override;

    /**
     * @brief   Verify if a key of the keyboard was Releassed.
     * @return  Returns a true if the key was Releassed.
     */
    bool 
    isKeyReleassed(KEYBOARD_KEYS::E inKey) override;

    /**
     * @brief   Verify if a key of the keyboard was pressed.
     * @return  Returns a true if the key was pressed.
     */
    bool
    isMouseButtonPressed(MOUSE_BUTTONS::E inButton) override;

    /**
     * @brief   Verify if a button of the mouse was Releassed.
     * @return  Returns a true if the key was Releassed.
     */
    bool 
    isMouseButtonReleassed(MOUSE_BUTTONS::E inButton) override;

    /**
     * @brief   Verify if a key of the keyboard was pressed.
     * @return  Returns a true if the key was pressed.
     */
    bool
    isButtonPressed(CONTROL_BUTTONS::E inButton) override;

    /**
     * @brief   Verify if a button of the control was Releassed.
     * @return  Returns a true if the key was Releassed.
     */
    bool 
    isButtonReleassed(CONTROL_BUTTONS::E inButton) override;


    /**
     * @brief   Verify the distance.
     * @return  Returns .
     */
    Vector2 
    isMouseMoved() override;

   protected:
    /**
    * 
    */
  	void 
    setButtons();

   private:

     OIS::InputManager* m_inputManager = nullptr;

     //Devices
     OIS::Keyboard* m_keyBoard = nullptr;

     OIS::Mouse* m_mouse = nullptr;

     Map<OIS::KeyCode, KEYBOARD_KEYS::E> m_keys;

     Map<OIS::MouseButtonID, MOUSE_BUTTONS::E> m_mouseKeys;

     bool
     keyPressed(const OIS::KeyEvent& arg) override;
     
     bool
     keyReleased(const OIS::KeyEvent& arg) override;
     
     bool
     mouseMoved(const OIS::MouseEvent& arg) override;
     
     bool
     mousePressed(const OIS::MouseEvent& arg,
                  OIS::MouseButtonID id) override;
     
     bool
     mouseReleased(const OIS::MouseEvent& arg,
                   OIS::MouseButtonID id) override;

    
  };

  /**
   * @brief   Create the Input Manager with a dll.
   */
  extern "C" GI_PLUGIN_EXPORT Input *
    createInputManager() {
    auto in = new Input();
    return in;
  }
}