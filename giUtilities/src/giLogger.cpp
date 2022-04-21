/**
 * @file    giLogger.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    08/07/2021
 * @brief   A log creator for the engine.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giLogger.h"

namespace giEngineSDK {
  Logger::Logger() {
    time_t timer;
    struct tm* timeinfo;
    time(&timer);
    timeinfo = localtime(&timer);

    m_logId = timeinfo->tm_hour + "-"+ timeinfo->tm_min, "-" + timeinfo->tm_mday, "-" +
              timeinfo->tm_mon, "-" + timeinfo->tm_yday;
    //m_path =  ("Log/Log" + m_logId + ".txt");
  }
  
  void
  Logger::SetError(ERROR_TYPE::E inProcess, String inError) {
    ++m_numErrors;
    m_errors.insert(m_errors.end(), 
                    Pair<ERROR_TYPE::E, 
                    String>(inProcess, inError));
    
  }
  
  void 
  Logger::sendToConsole() {
    ConsoleOut << "> The number of errors in total is: " + m_numErrors << "\n";
    for (auto errors : m_errors) {
      ConsoleOut << errors.second << "\n";
    }
  }

  void 
  Logger::SendToFile() {
    std::fstream fs;
    fs.open(m_path, std::fstream::out );//| std::fstream::app);
    fs << "The number of errors in total is: " + m_numErrors;
    for(auto errors : m_errors) {
      fs << errors.second;
    }
    sendToConsole();
  }

  Logger&
  g_logger() {
    return Logger::instance();
  }

}