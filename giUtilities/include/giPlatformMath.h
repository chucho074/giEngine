#pragma once
#include <cmath>
#include "giPrerequisitesUtilities.h"
#include "giPlatformTypes.h"

namespace giEngineSDK {
  class GI_UTILITY_EXPORT platformMath
  {
   public:
    static const float PI;
    static const float DEG2RAD;
    static const float RAD2DEG;
    static const float SMALL_NUMBER;
    static const float KINDA_SMALL_NUMBER;
    static const float BIG_NUMBER;
    static const float EULER_NUMBER;
    static const float DELTA;
    static const uint32 SELECT0;
    static const uint32 SELECT1;

    //Invert Sqrt
    template<typename Type>
    static Type
    invSqrt(Type val) {
      return Type(1) / std::sqrt(val);
    }
  
    //Invert Sqrt Specialization
    template<>
    static float
    invSqrt(float val) {
      return 1.0f / std::sqrtf(val);
    }
  
    //Sqrt
    template<typename Type>
    static Type
    sqrt(Type val) {
      return std::sqrt(val);
    }
  
    //Sqrt Specialization
    template<>
    static float
    sqrt(float val) {
      return std::sqrtf(val);
    }
  
    //pow
    template<typename Type>
    static Type
    pow(Type val, giEngineSDK::int32 inExp) {
      return std::pow(val, static_cast<float>(inExp));
    }
  
    //pow Specialization
    template<>
    static float
    pow(float val, giEngineSDK::int32 inExp) {
      return std::powf(val, static_cast<float>(inExp));
    }
    
    //coseno 
    template<typename Type>
    static float
    cos(Type inValue) {
      return std::cos(inValue);
    }
  
    //coseno Specialization
    template<>
    static float
    cos(float inValue) {
      return std::cosf(inValue);
    }
  
    //seno 
    template<typename Type>
    static float
    sin(Type inValue) {
      return std::sin(inValue);
    }
  
    //seno Specialization
    template<>
    static float
    sin(float inValue) {
      return std::sinf(inValue);
    }
  
    //tan
    template<typename Type>
    static float
    tan(Type inValue) {
      return std::tan(inValue);
    }
  
    //tan Specialization
    template<>
    static float
    tan(float inValue) {
      return std::tanf(inValue);
    }
    
    //cos hiper
    template<typename Type>
    static float
    cosh(Type inValue) {
      return std::cosh(inValue);
    }
  
    //cos hiper Specialization
    template<>
    static float
    cosh(float inValue) {
      return std::coshf(inValue);
    }
  
    //sen hiper
    template<typename Type>
    static float
    sinh(Type inValue) {
      return std::sinh(inValue);
    }
  
    //sen hiper Specialization
    template<>
    static float
    sinh(float inValue) {
      return std::sinhf(inValue);
    }
  
    //tan hiper
    template<typename Type>
    static float
    tanh(Type inValue) {
      return std::tanh(inValue);
    }
  
    //tan hiper Specialization
    template<>
    static float
    tanh(float inValue) {
      return std::tanhf(inValue);
    }
    
    //arcos
    template<typename Type>
    static float
    arcos(Type inValue) {
      return std::acos(inValue);
    }
  
    //arcos Specialization
    template<>
    static float
    arcos(float inValue) {
      return std::acos(inValue);
    }
  
    //arsen
    template<typename Type>
    static float
    arsin(Type inValue) {
      return std::asin(inValue);
    }
  
    //arsen Specialization
    template<>
    static  float
    arsin(float inValue) {
      return std::asinf(inValue);
    }
  
    //artan
    template<typename Type>
    static float
    artan(Type inValue) {
      return std::atan(inValue);
    }
  
    //artan Specialization
    template<>
    static float
    artan(float inValue) {
      return std::atanf(inValue);
    }
  
    //logaritmo natural
    template<typename Type>
    static Type
    ln(Type inValue) {
      return std::log(inValue);
    }
  
    //log Specialization
    template<>
    static float
    ln(float inValue) {
      return std::logf(inValue);
    }
    
  };
}