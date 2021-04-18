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