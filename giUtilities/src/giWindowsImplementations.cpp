/**
 * @file    giWindowsImplementations.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    27/09/2022
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giWindowsImplementations.h"
#if GI_PLATFORM == GI_PLATFORM_WIN32
#include <windows.h>
#endif

namespace giEngineSDK {
  
  String 
  WindowsFileDialogs::openFileDialog(void* inWindowHandle) {
    OPENFILENAMEA ofn;
    char szFile[260] = { 0 };
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = (HWND)inWindowHandle;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = m_fileFilters;
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetOpenFileNameA(&ofn) == TRUE) {
      return ofn.lpstrFile;
    }
    return String();
  }

  String 
  WindowsFileDialogs::saveFileDialog(void* inWindowHandle, const char* inFilters) {
    OPENFILENAMEA ofn;
    char szFile[260] = { 0 };
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = (HWND)inWindowHandle;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);

    if (inFilters[0] != ' ') {
      ofn.lpstrFilter = inFilters;
    }
    else {
      ofn.lpstrFilter = m_fileFilters;
    }
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetSaveFileNameA(&ofn) == TRUE) {
      return ofn.lpstrFile;
    }
    return String();
  }

}