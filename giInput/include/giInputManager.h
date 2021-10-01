/**
 * @file    giInputManager.h
 * @author  Jes�s Alberto Del Moral Cupil
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

enum Button
{
  ButtonMenu,
  ButtonConfirm,
  MouseX,
  MouseY
};

namespace giEngineSDK {
  class Input : BaseInput
  {
   public:
    //Default Constructor
  	Input() = default;

    //Destructor
  	~Input() = default;

    void 
    init();

    void
    createInputDevice();

    void 
    update();

    void
    updateSize(int inWidth, int inHeight);

    void
    sendEvent();

   protected:
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