/**
 * @file    giLogger.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    08/07/2021
 * @brief   A log creator for the engine.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesUtilities.h"
#include "giModule.h"
#include <fstream>
#include <ctime>

namespace giEngineSDK {

  namespace ERROR_TYPE {
    enum E {
      kModelLoading = 0,
      kWindowCreation,
      kPluginLoading,
      kAnimationLoading,
      kTextureCreation,
      kBufferCreation,
      kBlendStateCreation,
      kDepthStencilStateCreation,
      kSamplerCreation,
      kUAVCreation,
      kOmniConnection
    };
  }


  class GI_UTILITY_EXPORT Logger : public Module<Logger>
  {
   public:
    //Constructor
    Logger();

    //Destructor
    ~Logger() = default;

    /**
     * @brief    .
     * @param    inProcess     . 
     * @param    inError       .
     */
    void
    SetError(ERROR_TYPE::E inProcess, String inError);

    /**
     * @brief    .
     */
    void
    SendToFile();

    /**
     * @brief    .
     */
    void
    sendToConsole();

   private:
    /**
     * @brief    .
     */
    String m_logId;
    
    /**
     * @brief    The path to save the file.
     */
    String m_path = ("Log/LogDefault.txt");

    /**
     * @brief    The number of errors.
     */
    uint32 m_numErrors = 0;

    /**
     * @brief    Errors by type.
     */
    Map<ERROR_TYPE::E, String> m_errors;
  };

  GI_UTILITY_EXPORT Logger&
  g_logger();

}