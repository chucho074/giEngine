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

  const double Time::MICRO_TO_SEC = 1.0 / 1000000.0;

  Time::Time() {
    m_timer = std::make_unique<Timer>();
    m_lastFrameTime = m_timer->getMicroseconds();
  }  
  
  void 
  Time::update() {
    uint64 currentFrameTime = m_timer->getMicroseconds();

    if (!m_firstFrame) {
      m_deltaTime = static_cast<float>((currentFrameTime - m_lastFrameTime) *
                                        MICRO_TO_SEC);
    }
    else {
      m_deltaTime = 0.0f;
      m_firstFrame = false;
    }

    m_timeSinceStartMs = static_cast<uint64>(currentFrameTime / 1000);
    m_timeSinceStart = m_timeSinceStartMs / 1000.0f;
    m_lastFrameTime = currentFrameTime;
  }


  float 
  Time::getTime() const {
    return m_deltaTime;
  }

  Time&
  g_time() {
    return Time::instance();
  }
}