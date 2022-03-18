/**
 * @file    giFile.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    16/03/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesUtilities.h"
#include "giStdHeaders.h"

namespace giEngineSDK {

  namespace EXTENSION_TYPE {
    enum E {
        kJSON = 0,
        kBMP,
        kJPEG,
        kPNG,
        kTGA,
        kFBX,
        kOBJ,
        kTXT,
        kHLSL,
        kgiTEX2D,
        kgiModel,
        kgiShade,
        kgiProject,
        kgiFile,
        kTotalExtansions
    };
  }

  /**
   * @class    FILE.
   * @brief    .
   * @bug      No known Bugs.
   */
  class GI_UTILITY_EXPORT FILE
  {
   public:
    //Default Constructor.
    FILE();

    //Destructor.
    ~FILE();

   protected:

    String m_path;

    String m_name;

    EXTENSION_TYPE::E m_extension;

  };
}