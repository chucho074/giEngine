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

namespace giEngineSDK {

  class Encoder
  {
   public:

  	Encoder() = default;

  	~Encoder() = default;

    /**
     * @brief    .
     * @param    inFileData    .
     */
    void
    encodeData(FILE inFileData);


   private:

  	/**
  	 * @brief    Encode the information for the giProject Files.
  	 * @param    inFileData    The file data structure.
  	 */
  	void
    encodeGiProject(FILE inFileData);

   protected:
  };

}