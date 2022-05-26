/**
 * @file    giPlatformTypes.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    22/01/2021
 * @brief   Define the basic platform type variables. For porting, this might 
 *          be place to start.
 * @bug     No known Bugs.
 */

#pragma once


#include <cstdint>
#include "giPlatformDefines.h"

namespace giEngineSDK {
  using std::uint8_t;
  using std::uint16_t;
  using std::uint32_t;
  using std::uint64_t;
  using std::int8_t;
  using std::int16_t;
  using std::int32_t;
  using std::int64_t;


/*****************************************************************************/
/**
 * Basic unsigned types
 */
 /****************************************************************************/
  using uint8 = uint8_t;      //8-bit unsigned int
  using uint16 = uint16_t;    //16-bit unsigned int
  using uint32 = uint32_t;    //32-bit unsigned int
  using uint64 = uint64_t;    //64-bit unsigned int


/*****************************************************************************/
/**
 * Basic signed types
 */
 /****************************************************************************/
  using int8 = int8_t;        //8-bit signed int
  using int16 = int16_t;      //16-bit signed int
  using int32 = int32_t;      //32-bit signed int
  using int64 = int64_t;      //64-bit signed int


/*****************************************************************************/
/**
 * 
 */
 /****************************************************************************/
 using size_T = size_t;
}