/**
 * @file    giFileSystem.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/11/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesUtilities.h"

namespace giEngineSDK {
  
  /**
   * @brief    The types of files than can read.
   */
  namespace FILE_TYPE {
    enum E { 
      kShaderDX = 0,
      kShaderOGL,
      kJSON,
      k
    };
  }
  
  class FileSystem {
   public:
    //Default Constructor
  	FileSystem() = default;
    
    //Destructor
  	~FileSystem() = default;

    /**
     * @brief   Read file by type.
     * @param   inFileName   The name of the file to read.
     * @param   inFileType   The type of the file to read.
     * @return  Returns the readed data.
     */
    String
    readFile(String inFileName, 
             FILE_TYPE::E inFileType, 
             String inEntryPoint = NULL);
    
    /**
     * @brief   
     * @param   inFileName 
     * @param   inFileTypem 
     * @param   inData 
     * @return  
     */
    bool
    writeFile(String inFileName, FILE_TYPE::E inFileTypem, void * inData);

   protected:
    
    /**
     * @brief 
     * @param    inFileName 
     * @param    inEntryPoint 
     * @return 
     */
    String 
    readShaderDX(String inFileName, String inEntryPoint);

    /**
     * @brief    Read the shader files with extension 
     * @param    inFileName
     * @param    inEntryPoint
     * @return
     */
    String 
    readShaderOGL(String inFileName, String inEntryPoint);
    
    /**
     * @brief    Read the JSON files with extension 
     * @param    inFileName
     * @return
     */
    String 
    readJSON(String inFileName);

   private:
    
    /**
     * @brief    Internal function to get all file data.
     * @param    inFileName     The name of the file.
     * @return   Returns the File information.
     */
    String 
    readData(String inFileName);

    inStream io;
  };
}