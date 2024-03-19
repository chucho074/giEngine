/**
 * @file    giWindowsImplementations.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    27/09/2022
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#pragma once
#include "giBaseImplementations.h"
namespace giEngineSDK {

  class GI_UTILITY_EXPORT WindowsFileDialogs : public BaseFileDialogs 
  {
   public:

    /**
     * @brief    For opens the open file dialog.
     * @param    inWindowHandle The handle of the app window.
     * @return   Returns the path of the file selected in the dialog.
     */
    static String 
    openFileDialog(void* inWindowHandle);

    /**
     * @brief    For save as a new file in a dialog.
     * @param    inWindowHandle The handle of the app window.
     * @return   Returns the path where the file is going to be saved.
     */
    static String 
    saveFileDialog(void* inWindowHandle, const char* inFilters = " ");

    /**
     * @brief    For selecting a folder to use in a dialog.
     * @return   The selected path.
     */
    static Path
    selectFolderDialog();
    
  };
}