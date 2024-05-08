/**
 * @file    giLibraryLoader.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/04/2021
 * @brief   For export the librarys of the proyects.
 */

 /**
  * @include
  */
#pragma once
#include "giPrerequisitesUtilities.h"
#include <giLogger.h>
#include <Windows.h>
#include <iostream>


namespace giEngineSDK {

  /**
   * @class    LibraryLoader.   
   */
  class LibraryLoader
  {
  public:
    //Default Constructor.
    LibraryLoader() = default;

    //Destructor.
    ~LibraryLoader() = default;

    /**
     * @brief    Load the library.
     * @param    inName        Name of the library.
     * @return
     */
    bool
    loadPlugin(const String& inName);

    /**
     * @brief    Get the library with the name.
     * @param    inName        Name of the library.
     * @return
     */
    void*
    getProcedureByName(const String& inName);

    /**
     * @brief    Clear the instance.
     */
    void
    destroy();

    //Library instance
    void*
    m_instance = nullptr;

  };


  inline bool
  LibraryLoader::loadPlugin(const String& inName) {
    m_instance = LoadLibraryExA(inName.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
    if (!m_instance) {
      ConsoleOut << GetLastError();
      Logger::instance().SetError(ERROR_TYPE::kPluginLoading,
                                  "Error to load a dll: " + inName);
      destroy();
      return false;
    }
    return true;
  }

  inline void* 
  LibraryLoader::getProcedureByName(const String& inName) {
    auto func = GetProcAddress(reinterpret_cast<HINSTANCE>(m_instance), inName.c_str());
    
    if (!func) {
      Logger::instance().SetError(ERROR_TYPE::kPluginLoading,
                                  "Error to load a dll: " + inName);
    }
    return func;
  }

  inline void 
  LibraryLoader::destroy() {
    FreeLibrary(reinterpret_cast<HINSTANCE>(m_instance));

  }
}