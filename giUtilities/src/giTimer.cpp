/**
 * @file    giTimer.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    27/06/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giTimer.h"

namespace giEngineSDK {
  using namespace std::chrono;

  Timer::Timer() {
    restart();
  }

  void 
  Timer::restart() {
    m_startTime = m_clock.now();
  }

  uint32 
  Timer::getNanoseconds() {
    return getTimeByType(TimeType::kNanoSeconds);
  }

  uint32 
  Timer::getMicroseconds() {
    return getTimeByType(TimeType::kMicroSeconds);
  }

  uint32 
  Timer::getMilliseconds() {
    return getTimeByType(TimeType::kMilliSeconds);
  }

  uint32 
  Timer::getTimeByType(TimeType::E inTimeType) {

    auto newTime = m_clock.now();
    duration<double> dur = newTime - m_startTime;

    switch (inTimeType) {
    //Nano seconds case
    case TimeType::kNanoSeconds:{
      //nanoseconds startTimeNs = m_startTime.time_since_epoch();
      //return duration_cast<milliseconds>(startTimeNs).count();
      return 0;
    }
    case TimeType::kMicroSeconds: {
      return duration_cast<microseconds>(dur).count();
    }

    case TimeType::kMilliSeconds: {
      return duration_cast<milliseconds>(dur).count();
    }
    case TimeType::kSeconds: {
      return duration_cast<seconds>(dur).count();
    }
    case TimeType::kMinutes: {
      return duration_cast<seconds>(dur).count() / 60;
    }
    case TimeType::kHours: {
      return duration_cast<seconds>(dur).count() / 3600;
    }

    }

  }


}