/**
 * @file    giUUID.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/08/2022
 * @brief   Universal Unique Identifiers.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"

namespace giEngineSDK {

  class UUID
  {
   public:
  	//Default constructor.
    UUID();

    //Copy constructor.
    UUID(const UUID& inUUID) = default;

    //Destructor
  	~UUID() = default;
   
    operator uint64() const { 
      return m_uuid; 
    }

    static const UUID
    ZERO;

   private:

    //Constructor for own purposes.
    UUID(int32);

    uint64 m_uuid;

  };
}

namespace std {
  template<>
  struct hash<giEngineSDK::UUID> {
    giEngineSDK::size_T operator()(const giEngineSDK::UUID& inUUID) const {
      return hash<giEngineSDK::uint64>()((giEngineSDK::uint64)inUUID);
    }
  };
}