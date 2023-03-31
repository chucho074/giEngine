/**
 * @file    giEncoder.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/05/2022
 * @brief   A basic implementation to set the information for own types files.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giResourceManager.h"
#include "giFile.h"


namespace giEngineSDK {

  struct ResourceRef;

  class Encoder
  {
   public:

  	Encoder() = default;

  	~Encoder() = default;

    /**
     * @brief    Encode the file given.
     * @param    inFileData    The file data structure.
     */
    static void
    encodeFile(FILE& inFileData);

    static void
    encodeOBJ(Path inPath, ResourceRef inModel);

    static void
    encodeData(FILE& inFile);

    static void 
    exportFromFile(Path inPath, String inFileType);

    static void 
    exportModelFromMem(Path inPath, ResourceRef inResource);


   private:

  	/**
  	 * @brief    Encode the information for the giProject Files.
  	 * @param    inFileData    The file data structure.
  	 */
  	static void
    encodeGiProject(FILE& inFileData);

  	/**
  	 * @brief    Encode the information for the Scene Files.
  	 * @param    inFileData    The file data structure.
  	 */
  	static void
    encodeGiScene(FILE& inFileData);



   protected:


  };

}