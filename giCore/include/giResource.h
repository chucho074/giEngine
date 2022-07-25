/**
 * @file    giResource.h
 * @author  Jesus Alberto Del Moral Cupil
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
   * @brief    .
   */
  namespace RESOURCE_TYPE {
    enum E {
      kModel = 0,
      kMaterial,
      kTexture,
      kAudio,
      kFont,
      kSuportedResourceTypes
    };
  }

  /**
   * @class    Resource.
   * @brief    .
   */
  class Resource
  {
   public:
    //Default Constructor.
    Resource() = default;
  
    //Destructor.
    virtual 
    ~Resource() = default;
  
    /**
     * @brief 
     * @param    inPath 
     * @return 
     */
    //virtual bool 
    //loadFromFile(const Path& inPath) = 0;
  
    /**
     * @brief 
     * @param    inData 
     * @param    inSizeOfData 
     * @return 
     */
    //virtual bool
    //loadFromMemory(const char* inData, size_T inSizeOfData) = 0;
  
    /**
     * @brief 
     */
    virtual void 
    unload() = 0;
    
    ///A reference of the type of resource;
    RESOURCE_TYPE::E m_resourceType;
   
  };

}