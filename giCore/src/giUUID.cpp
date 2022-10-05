/**
 * @file    giUUID.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/08/2022
 * @brief   An implementation for the Universal Unique IDentifiers.
 */
 
/**
 * @include
 */
#include "giUUID.h"

#include <random>


namespace giEngineSDK {

  static std::random_device s_randomDevice;
  static std::mt19937_64 s_Engine(s_randomDevice());
  static std::uniform_int_distribution<uint64> s_UniformDistribution;

  UUID::UUID() 
    : m_uuid(s_UniformDistribution(s_Engine)) {
    
  }

  UUID::UUID(uint64 inData) {
    m_uuid = inData;
  }

  const UUID
  UUID::ZERO = UUID(0);

}