#pragma once

#include <cmath>
#include"../include/giPlatformTypes.h"

//using std::sqrt;
//using std::sqrtf;
//using std::atan;
//using std::pow;
//using std::powf;

class PlatformMath
{
 public:
  static const float PI;
  static const float DEG2RAD;
  static const float RAD2DEG;
  //Invert Sqrt
  template<typename Type>
  Type
  invSqr(Type val) {
    return Type(1) / std::sqrt(val);
  }

  //Invert Sqrt Specialization
  template<>
  float
  invSqr(float val) {
    return 1.0f / std::sqrtf(val);
  }

  //Sqrt
  template<typename Type>
  Type
  sqr(Type val) {
    return std::sqrt(val);
  }

  //Sqrt Specialization
  template<>
  float
  sqr(float val) {
    return std::sqrtf(val);
  }

  //pow
  template<typename Type>
  Type
  pow(Type val, giEngineSDK::int32 inExp) {
    return std::pow(val, static_cast<float>(inExp));
  }

  //pow Specialization
  template<>
  float
  pow(float val, giEngineSDK::int32 inExp) {
    return std::powf(val, static_cast<float>(inExp));
  }
  
  //coseno 
  template<typename Type>
  Type
  cos(Type inValue) {
    return std::cos(inValue);
  }

  //coseno Specialization
  template<>
  float
  cos(float inValue) {
    return std::cosf(inValue);
  }

  //seno 
  template<typename Type>
  Type
  sin(Type inValue) {
    return std::sin(inValue);
  }

  //seno Specialization
  template<>
  float
  sin(float inValue) {
    return std::sinf(inValue);
  }

  //tan
  template<typename Type>
  Type
  tan(Type inValue) {
    return std::tan(inValue);
  }

  //tan Specialization
  template<>
  float
  tan(float inValue) {
    return std::tanf(inValue);
  }
  
  //cos hiper
  template<typename Type>
  Type
  cosh(Type inValue) {
    return std::cosh(inValue);
  }

  //cos hiper Specialization
  template<>
  float
  cosh(float inValue) {
    return std::coshf(inValue);
  }

  //sen hiper
  template<typename Type>
  Type
  sinh(Type inValue) {
    return std::sinh(inValue);
  }

  //sen hiper Specialization
  template<>
  float
  sinh(float inValue) {
    return std::sinhf(inValue);
  }

  //tan hiper
  template<typename Type>
  Type
  tanh(Type inValue) {
    return std::tanh(inValue);
  }

  //tan hiper Specialization
  template<>
  float
  tanh(float inValue) {
    return std::tanhf(inValue);
  }
  
  //arcos
  template<typename Type>
  Type
  arcos(Type inValue) {
    return std::acos(inValue);
  }

  //arcos Specialization
  template<>
  float
  arcos(float inValue) {
    return std::acos(inValue);
  }

  //arsen
  template<typename Type>
  Type
  arsin(Type inValue) {
    return std::asin(inValue);
  }

  //arsen Specialization
  template<>
  float
  arsin(float inValue) {
    return std::asinf(inValue);
  }

  //artan
  template<typename Type>
  Type
  artan(Type inValue) {
    return std::atan(inValue);
  }

  //artan Specialization
  template<>
  float
  artan(float inValue) {
    return std::atanf(inValue);
  }

  //logaritmo natural
  template<typename Type>
  Type
  ln(Type inValue) {
    return std::log(inValue);
  }

  //log Specialization
  template<>
  float
  ln(float inValue) {
    return std::logf(inValue);
  }
  
  



};