/**
 * @file    giInputManager.h
 * @author  Jesús Alberto Del Moral Cupil
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
   protected:
  	
   private:
    //
    gainput::InputManager Manager;
    //
    gainput::InputMap InputMap;
  };
}