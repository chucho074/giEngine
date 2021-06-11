/**
 * @file    giTime.h
 * @author  Jesús Alberto Del Moral Cupil
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
#include <chrono>

namespace giEngineSDK {
  using std::chrono::time_point;
  using std::chrono::high_resolution_clock;

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
    
    void
    restart();

    void
    update();

    /**
     * @brief    Gets the time elapsed since application start.
     * @return   Returns .
     */
    float
    getTime() const {
      return m_deltaTime;
    }

   protected:
     high_resolution_clock m_clock;
     time_point<high_resolution_clock> m_startTime;
     float m_deltaTime;
   
   private:
  };
  
  
  
}