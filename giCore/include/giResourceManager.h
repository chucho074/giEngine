/**
 * @file    giResourceManager.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/05/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giEncoder.h"


namespace giEngineSDK {

  class ResourceManager 
  {
   public:
  	//Default Constructor.
    ResourceManager() = default;
  	//Default destructor.
    ~ResourceManager() = default;


   protected:
  	

   private:
    SharedPtr<Encoder> m_encoder;
  };

}