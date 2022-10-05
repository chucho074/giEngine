/**
 * @file    giBaseInput
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    30/09/2021
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giBaseInput.h"

namespace giEngineSDK {

  BaseInput&
    g_inputManager() {
    return BaseInput::instance();
  }

}