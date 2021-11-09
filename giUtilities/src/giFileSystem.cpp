/**
 * @file    giFileSystem.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/11/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giFileSystem.h"

namespace giEngineSDK {

  String
  FileSystem::readFile(String inFileName, 
                       FILE_TYPE::E inFileType, 
                       String inEntryPoint) {

    switch (inFileType) {
      //case giEngineSDK::FILE_TYPE::kShaderDX: {
      //  return readShaderDX(inFileName, inEntryPoint);
      //}
      //case giEngineSDK::FILE_TYPE::kShaderOGL: {
      //  return readShaderOGL(inFileName, inEntryPoint);
      //}
      //case giEngineSDK::FILE_TYPE::kJSON: {
      //  //return readFile();
      //}
      default: {
        return readData(inFileName);
      }
    }
  }

  bool 
  FileSystem::writeFile(String inFileName, FILE_TYPE::E inFileTypem, void* inData) {
    return false;
  }

  String
  FileSystem::readShaderDX(String inFileName,
                           String inEntryPoint) {
  
  }

  String
  FileSystem::readShaderOGL(String inFileName,
                            String inEntryPoint) {
  
  }
  
  String 
  FileSystem::readData(String inFileName) {
    String tmpData;
    try {
      io.open(inFileName);
      std::stringstream tmpFileData;
      tmpFileData << io.rdbuf();
      tmpData = tmpFileData.str();
      io.close();
    }
    catch (inStream::failure e) {
      g_logger().SetError(ERROR_TYPE::kReadingFile, 
                          "The File: " + inFileName + " can't be readed");
    }
    
    return tmpData;
  }
  
  String 
  FileSystem::readJSON(String inFileName) {
    return String();
  }
}