/**
 * @file    giFile.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/05/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giFile.h"

namespace giEngineSDK {

  void
  FILE::evaluateExtension(wString inExtension) {
    if(inExtension == L"json") {
      m_extension == EXTENSION_TYPE::kJSON;
    }
    else if(inExtension == L"bmp") {
      m_extension == EXTENSION_TYPE::kBMP;
    }
    else if(inExtension == L"jpeg") {
      m_extension == EXTENSION_TYPE::kJPEG;
    }
    else if(inExtension == L"png") {
      m_extension == EXTENSION_TYPE::kPNG;
    }
    else if(inExtension == L"tga") {
      m_extension == EXTENSION_TYPE::kTGA;
    }
    else if(inExtension == L"fbx") {
      m_extension == EXTENSION_TYPE::kFBX;
    }
    else if(inExtension == L"obj") {
      m_extension == EXTENSION_TYPE::kOBJ;
    }
    else if(inExtension == L"txt") {
      m_extension == EXTENSION_TYPE::kTXT;
    }
    else if(inExtension == L"hlsl") {
      m_extension == EXTENSION_TYPE::kHLSL;
    }
    else if(inExtension == L"giTex2D") {
      m_extension == EXTENSION_TYPE::kgiTEX2D;
    }
    else if(inExtension == L"giModel") {
      m_extension == EXTENSION_TYPE::kgiModel;
    }
    else if(inExtension == L"giShader") {
      m_extension == EXTENSION_TYPE::kgiShader;
    }
    else if(inExtension == L"giProject") {
      m_extension == EXTENSION_TYPE::kgiProject;
    }
    else if(inExtension == L"giFile") {
      m_extension == EXTENSION_TYPE::kgiFile;
    }
    else if(inExtension == L"giSettings") {
      m_extension == EXTENSION_TYPE::kgiSettings;
    }
  }

}