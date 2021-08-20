/**
 * @file    giBaseRenderer
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    20/08/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giBaseRenderer.h"

namespace giEngineSDK {
  BaseRenderer&
  g_renderer() {
    return BaseRenderer::instance();
  }
}