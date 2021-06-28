/**
 * @file    giBaseGraphicsAPI.cpp
 * @author  Jes�s Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giBaseGraphicsAPI.h"

namespace giEngineSDK {
  GraphicsAPI&
    g_graphicsAPI() {
    return GraphicsAPI::instance();
  }
}