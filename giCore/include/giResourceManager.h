/**
 * @file    giResourceManager.h
 * @author  Jesus Alberto Del Moral Cupil
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
#include "giMaterial.h"
#include "giModule.h"

namespace giEngineSDK {

  class ResourceManager : Module<ResourceManager> 
  {
   public:
  	//Default Constructor.
    ResourceManager() = default;
  	//Default destructor.
    ~ResourceManager() = default;

    /**
     * @brief    Getter for Materials by an a ID.
     * @param    inID          The ID of the material wanted.
     * @return   A reference of the material as a Weak Pointer.
     */
    WeakPtr<Material>
    getMaterialByID(uint32 inID);


   protected:
  	

   private:
    //Reference of the encoder.
    SharedPtr<Encoder> m_encoder;

    //Reference of the Decoder.
    //SharedPtr<Decoder> m_decoder;

    //The map of Materials loaded.
    Map<uint32, SharedPtr<Material>> m_materials;

  };

}