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
        kgiShader,
        kgiProject,
        kgiFile,
        kgiSettings,
        kUnknown,
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
    FILE(Path inPath) : m_path(inPath) {
      //Saves the path as m_path.
      //Gets the extension and evaluates for m_extension.
      evaluateExtension(m_path.extension());
      //Saves the name of the file as the m_name.
      m_name = m_path.stem().string();
      
    };

    //Destructor.
    ~FILE() = default;

   private:
    /**
     * @brief    
     * @param    inExtension   .
     */
    void
    evaluateExtension(wString inExtension);

   protected:

    Path m_path;

    String m_name;

    EXTENSION_TYPE::E m_extension = EXTENSION_TYPE::E::kUnknown;

  };
}