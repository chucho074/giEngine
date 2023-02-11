/**
 * @file    giBaseAMR.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    08/02/2023
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giBaseAMR.h"

namespace giEngineSDK {
  BaseAMR& 
  g_AMR() {
    return BaseAMR::instance();
  }
}