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
#include <gainput/gainput.h>
#include <windows.h>

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
  class Input : public BaseInput
  {
   public:
    //Default Constructor
  	Input() = default;

    //Destructor
  	~Input() = default;

    /**
     * 
     */
    void 
    init();

    /**
     * 
     */
    void
    createInputDevice();

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
     * 
     */
    void
    sendEvent(MSG inMessage);

    /**
     * @brief   Verify if a key of the keyboard was pressed.
     * @return  Returns a true if the key was pressed.
     */
    bool
    isKeyPressed(KEYBOARD_KEYS::E inKey) override;

    /**
     * @brief   Verify if a key of the keyboard was pressed.
     * @return  Returns a true if the key was pressed.
     */
    bool
    isMouseButtonPressed(MOUSE_BUTTONS::E inButton) override;

    /**
     * @brief   Verify if a key of the keyboard was pressed.
     * @return  Returns a true if the key was pressed.
     */
    bool
    isButtonPressed(CONTROL_BUTTONS::E inButton) override;

    
    /**
     * @brief   Verify if a key of the keyboard was Releassed.
     * @return  Returns a true if the key was Releassed.
     */
    bool 
    isKeyReleassed(KEYBOARD_KEYS::E inKey) override;

    /**
     * @brief   Verify if a button of the mouse was Releassed.
     * @return  Returns a true if the key was Releassed.
     */
    bool 
    isMouseButtonReleassed(MOUSE_BUTTONS::E inButton) override;

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
    virtual Vector2 
    isMouseMoved(Vector2) override;

   protected:
    /**
    * 
    */
  	void 
    setButtons();

   private:

    //
    gainput::InputManager m_manager;
    //
    gainput::InputMap * m_inputMap;

    gainput::DeviceId mouseId;

    gainput::DeviceId keyboardId;
    
    gainput::DeviceId padId;
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