/**
 * @file    giTime.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    11/06/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giTime.h"

namespace giEngineSDK {
  using namespace std::chrono;

  Time::Time() {
    
  }


  void 
  Time::restart() {
    m_startTime = m_clock.now();
  }
  
  
  void 
  Time::update() {
    
  }
}