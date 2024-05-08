/**
 * @file    giBaseOmniverse.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    24/01/2022
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giBaseOmniverse.h"

namespace giEngineSDK {
  GI_CORE_EXPORT BaseOmni& 
  g_omniverse() {
    return BaseOmni::instance();
  }
}