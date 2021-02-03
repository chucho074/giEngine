#pragma once

#include <cmath>

using std::sqrt;
using std::sqrtf;
using std::atan;

class PlatformMath
{

  static const float PI;
  static const float DEG2RAD;
  static const float RAD2DEG;

  template<typename Type>
  Type
  invSqr(Type val) {
    return Type(1) / sqrt(val);
  }

  //Specialization
  template<>
  float
  invSqr(float val) {
    return 1.0f / sqrtf(val);
  }
  //Raiz cuadrada
  //coseno seno tangente
  //Exponentes
  //logaritmo natural
  //logaritmo
  //Lo anterior pero float


};