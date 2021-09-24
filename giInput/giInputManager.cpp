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
  }

  void
  Input::createInputDevice() {

  }
  
  void 
  Input::update() {
    Manager.Update();
  }
  
  void 
  Input::updateSize(int inWidth, int inHeight) {
    Manager.SetDisplaySize(inWidth, inHeight);
  }

}