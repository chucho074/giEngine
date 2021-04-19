/**
 * @file    giLibraryLoader.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/04/2021
 * @brief   For export the librarys of the proyects.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giLibraryLoader.h"

namespace giEngineSDK {

  bool 
  LibraryLoader::loadPlugin(const String& inName) {
    if (!m_instance) {
      DWORD err = GetLastError();
      destroy();
      return false;
    }
  }

  void* 
  LibraryLoader::getProcedureByName(const String& inName) {
    auto func = GetProcAddress(reinterpret_cast<HINSTANCE>(m_instance), inName.c_str());
    
    if (!func) {
      //Failed to load
    }
    return func;
  }

  void 
  LibraryLoader::destroy() {
    FreeLibrary(reinterpret_cast<HINSTANCE>(m_instance));

  }

}