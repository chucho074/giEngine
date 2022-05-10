/**
 * @file    giFileSystem.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/05/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giFileSystem.h"
#include "giFile.h"

namespace giEngineSDK {

  bool 
  FileSystem::writeFile(FILE inFile) {
    //
    std::ofstream tmpFileWrite(inFile.m_path);

    //Write the information on the file
    tmpFileWrite << inFile.m_data;

    //Close the file.
    tmpFileWrite.close();
    
    //
    return true;
  }

  FILE 
  FileSystem::readFile(Path inPath) {
    //
    FILE tmpFile(inPath);

    //Validate if the file exists.
    if(exist(inPath)){
      //Reads the information of the file.
      std::ifstream tmpReadFile(inPath);

      //The line data.
      String tmpData;

      //Get the file information.
      while (getline(tmpReadFile, tmpData)) {
        //Write the data in the object.
        tmpFile.m_data = tmpFile.m_data + tmpData;
      }
      
      //Close the file.
      tmpReadFile.close();
    }

    //Returns the file.
    return tmpFile;
  }

  bool 
  FileSystem::exist(Path inPath) {
    //Verify with the fileSystem::exist function.
    return fsys::exists(inPath);
  }

}