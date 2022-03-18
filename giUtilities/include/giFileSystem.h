/**
 * @file    giFileSystem.h
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
#include "giFile.h"

namespace giEngineSDK {
  /**
   * @class    FileSystem.
   * @brief    .
   * @bug      No known Bugs.
   */
  class FileSystem
  {
   public:
    //Default Constructor.
    FileSystem();

    //Destructor.
    ~FileSystem();
    


    bool
    writeFile(FILE inFile);
    

    FILE
    readFile(String inPath);

    bool
    exist(String inPath);
   protected:
    
   
   private:
   
  };
  
  
}