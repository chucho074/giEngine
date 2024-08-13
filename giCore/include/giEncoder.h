/**
 * @file    giEncoder.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/05/2022
 * @brief   A basic implementation to set the information for own types files.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giFile.h"
#include "giModel.h"

namespace giEngineSDK {

  class GI_CORE_EXPORT Encoder
  {
   public:

  	Encoder() = default;

  	~Encoder() = default;

    /**
     * @brief    .
     * @param    inFileData    .
     */
    static void
    encodeFile(FILE inFileData);

    static void 
    exportObj(Path inPath, SharedPtr<Model> inModel);


    static void 
    exportMtl(Path inPath);


    static void
    encodeData(FILE& inFile);

   private:

  	/**
  	 * @brief    Encode the information for the giProject Files.
  	 * @param    inFileData    The file data structure.
  	 */
  	static void
    encodeGiProject(FILE inFileData);

  };

}