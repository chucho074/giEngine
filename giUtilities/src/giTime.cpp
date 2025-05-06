/**
 * @file    giTime.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    11/06/2021
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giTime.h"

namespace giEngineSDK {

  const double Time::MICRO_TO_SEC = 1.0 / 1000000.0;

  Time::Time() {
    m_timer = make_unique<Timer>();
  }  

  void 
  Time::startTimer() {
    m_timerRunning = true;
    m_lastFrameTime = m_timer->getMicroseconds();

  }

  void 
  Time::stopTimer() {
    update();
    m_timerRunning = false;
  }

  void 
  Time::restartTimer() {
    m_timer->restart();
    m_timerRunning = true;
    m_timeSinceStartMs = 0;
    m_timeSinceStart = 0.0f;
    m_deltaTime = 0.0f;
    m_firstFrame = true;
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