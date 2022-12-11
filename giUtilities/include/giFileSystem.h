/**
 * @file    giFileSystem.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    16/03/2022
 * @brief   A basic description of the what do the doc.
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
   * @brief    File Writer and reader.   
   */
  class FileSystem
  {
   public:
    //Default Constructor.
    FileSystem() = default;

    //Default Destructor.
    ~FileSystem() = default;
    
    /**
     * @brief    Write the info from a file with the given data.
     * @param    inFile        The file information needed to write.
     * @return   Returns true if the file can be created and writed correctly.
     */
    bool
    writeFile(FILE inFile);
    
    /**
     * @brief    Read a file with an given path.
     * @param    inPath        The path to read the file.
     * @return   Returns the file information in a FILE object.
     */
    FILE
    readFile(Path inPath);

    /**
     * @brief    Evaluates if a file exist.
     * @param    inPath        The path of the file to evaluate if exists.
     * @return   Returns a true if the file exists.
     */
    static bool
    exist(Path inPath);


    friend class FILE;
  };
}