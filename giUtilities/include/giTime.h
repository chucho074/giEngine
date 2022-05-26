/**
 * @file    giTime.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    12/04/2021
 * @brief   A basic use of the time.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesUtilities.h"
#include "giModule.h"
#include "giTimer.h"

namespace giEngineSDK {
  
  /**
   * @class    Time.
   * @brief    .
   * @bug      No known Bugs.
   */
  class GI_UTILITY_EXPORT Time : public Module<Time>
  {
   public:
    //Default Constructor.
    Time();
    
    //Destructor.
    ~Time() = default;
    
    /**
     * @brief 
     */
    void
    update();

    /**
     * @brief    Gets the time elapsed since application start.
     * @return   Returns .
     */
    float
    getTime() const;

    static const double MICRO_TO_SEC;
   
   private:

    SharedPtr<Timer> m_timer;

    float m_deltaTime;

    uint64 m_lastFrameTime = 0u;

    uint64 m_timeSinceStartMs = 0u;

    bool m_firstFrame = true;

    /**
     * @brief    Time since start in seconds.
     */
    float m_timeSinceStart = 0.0f;


  };
  
  GI_UTILITY_EXPORT Time&
  g_time();
  
}