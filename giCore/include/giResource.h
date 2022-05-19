/**
 * @file    giResource.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    30/07/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"

namespace giEngineSDK {
/**
 * @class    Resource.
 * @brief    .
 * @bug      No known Bugs.
 */
class Resource
{
 public:
  //Default Constructor.
  Resource() = default;

  //Destructor.
  virtual 
  ~Resource() = default;

  virtual bool 
  loadFromFile(const Path& inPath) = 0;

  virtual bool
  loadFromMemory(const char* inData, size_T inSizeOfData) = 0;

  virtual void 
  unload() = 0;

  virtual void 
  saveToFile(const String& inFile) =  0;

 protected:
  
 
 private:
 
};

}