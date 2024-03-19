/**
 * @file    giBaseImplementations.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    27/09/2022
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesUtilities.h"
#include "giFile.h"

namespace giEngineSDK {
  class GI_UTILITY_EXPORT BaseFileDialogs
  {
   public:
    
    /**
     * @brief    For opens the open file dialog.
     * @param    inWindowHandle The handle of the appp window.
     * @return   Returns the path of the file selected in the dialog.
     */
    static String 
    openFileDialog(void* inWindowHandle) {
      GI_UNREFERENCED_PARAMETER(inWindowHandle);
      return String();
    };
    
    /**
     * @brief    For save as a new file in a dialog.
     * @param    inWindowHandle The handle of the app window.
     * @return   Returns the path where the file is going to be saved.
     */
    static String 
    saveFileDialog(void* inWindowHandle) {
      GI_UNREFERENCED_PARAMETER(inWindowHandle);
      return String();
    };

    static inline const char* m_fileFilters = "All\0*.*\0Text\0*.txt\0giEngine Scenes\0*.giScene\0";
    static inline const char* m_fileFiltersProject = "giEngine Projects\0*.giProject\0";
  };
}