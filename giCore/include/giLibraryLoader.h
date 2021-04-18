#pragma once
#include "giPrerequisitesCore.h"
#include <Windows.h>

namespace giEngineSDK {

  /**
   * @class    LibraryLoader.
   * @brief    .
   * @bug      No known Bugs.
   */
  class LibraryLoader
  {
   public:
    //Default Constructor.
    LibraryLoader() = default;
    //Destructor.
    ~LibraryLoader() = default;
    
   /**
    * @brief 
    * @param inName 
    * @return 
    */
   bool
   loadPlugin(const String & inName);

   /**
    * @brief 
    * @param inName 
    * @return 
    */
   void *
   getProcedureByName(const String & inName);

   /**
    * @brief 
    */
   void 
   destroy();

   void* 
   m_instance = nullptr;

  };
}