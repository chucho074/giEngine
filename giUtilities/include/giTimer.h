/**
 * @file    giTimer.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    27/06/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesUtilities.h"
#include <chrono>

using std::chrono::time_point;
using std::chrono::high_resolution_clock;

namespace giEngineSDK {
  
  /**
   * @enum     TimeType
   * @brief    The ways to count the time.
   */
  namespace TimeType {
    enum E {
      kNanoSeconds,
      kMicroSeconds,
      kMilliSeconds,
      kSeconds,
      kMinutes,
      kHours
    };
  }

  /**
   * @class    Timer.
   * @brief    .
   * @bug      No known Bugs.
   */
  class GI_UTILITY_EXPORT Timer
  {
   public:
    //Default Constructor.
    Timer();

    //Destructor.
    ~Timer() = default;

    /**
     * @brief    Restart the time counter.
     */
    void 
    restart();

    /**
     * @brief    Get the elapsed time in nanoseconds.
     * @return   Returns the time in Nanoseconds.
     */
    uint32
    getNanoseconds();

    /**
     * @brief    Get the elapsed time in microseconds.
     * @return   Returns the time in Microseconds.
     */
    uint32 
    getMicroseconds();

    /**
     * @brief    Get the elapsed time in Milliseconds.
     * @return   Retunrs the time in Miliseconds
     */
    uint32
    getMilliseconds();

   protected:
    uint32
    getTimeByType(TimeType::E inTimeType);

    high_resolution_clock m_clock;
    time_point<high_resolution_clock> m_startTime;

   private:

  };


}