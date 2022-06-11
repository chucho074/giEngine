/**
 * @file    giVector3i.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    26/03/2021
 * @brief   A basic Vector 3 for ints.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giVector3i.h"

namespace giEngineSDK {
  const Vector3i Vector3i::ZERO = Vector3i(0, 0, 0);
  const Vector3i Vector3i::UNIT = Vector3i(1, 1, 1);

  Vector3i::Vector3i() {
    *this = ZERO;
  }

  Vector3i::Vector3i(int32 inX, int32 inY, int32 inZ) {
    x = inX;
    y = inY;
    z = inZ;
  }
  
  Vector3i::Vector3i(Vector3i& inVect) {
    x = inVect.x;
    y = inVect.y;
    z = inVect.z;
  }
  
  Vector3i::~Vector3i() {

  }
  
  Vector3i
  Vector3i::operator+(const Vector3i& otherVect) {
    return Vector3i(x + otherVect.x, y + otherVect.y, z + otherVect.z);
  }
  
  Vector3i
  Vector3i::operator-(const Vector3i& otherVect) {
    return Vector3i(x - otherVect.x, y - otherVect.y, z - otherVect.z);
  }
  
  Vector3i
  Vector3i::operator*(const Vector3i& otherVect) {
    return Vector3i(x * otherVect.x, y * otherVect.y, z * otherVect.z);
  }
  
  Vector3i
  Vector3i::operator/(const Vector3i& otherVect) {
    return Vector3i(x / otherVect.x, y / otherVect.y, z / otherVect.z);
  }
  
  Vector3i
  Vector3i::operator+(const int32& otherVal) {
    return Vector3i(x + otherVal, y + otherVal, z + otherVal);
  }
  
  Vector3i
  Vector3i::operator-(const int32& otherVal) {
    return Vector3i(x - otherVal, y - otherVal, z - otherVal);
  }
  
  Vector3i
  Vector3i::operator*(const int32& otherVal) {
    return Vector3i(x * otherVal, y * otherVal, z * otherVal);
  }
  
  Vector3i
  Vector3i::operator/(const int32& otherVal) {
    return Vector3i(x / otherVal, y / otherVal, z / otherVal);
  }
  
  bool
  Vector3i::operator>=(const Vector3i& otherVect) {
    return (otherVect.x <= x && otherVect.y <= y && otherVect.z <= z);
  }
  
  bool
  Vector3i::operator<=(const Vector3i& otherVect) {
    return (otherVect.x >= x && otherVect.y >= y && otherVect.z >= z);
  }
  
  bool
  Vector3i::operator==(const Vector3i& otherVect) {
    return (otherVect.x == x && otherVect.y == y && otherVect.z == z);
  }
  
  bool
  Vector3i::operator<(const Vector3i& otherVect) {
    return (otherVect.x > x && otherVect.y > y && otherVect.z > z);
  }
  
  bool
  Vector3i::operator>(const Vector3i& otherVect) {
    return (otherVect.x < x && otherVect.y < y && otherVect.z < z);
  }
  
  bool
  Vector3i::operator>=(const int32& otherVal) {
    return (otherVal <= x && otherVal <= y && otherVal <= z);
  }
  
  bool
  Vector3i::operator<=(const int32& otherVal) {
    return (otherVal >= x && otherVal >= y && otherVal >= z);
  }
  
  bool
  Vector3i::operator==(const int32& otherVal) {
    return (otherVal == x && otherVal == y && otherVal == z);
  }
  
  bool
  Vector3i::operator<(const int32& otherVal) {
    return (otherVal > x && otherVal > y && otherVal > z);
  }
  
  bool
  Vector3i::operator>(const int32& otherVal) {
    return (otherVal < x && otherVal < y && otherVal < z);
  }
  
  int32
  Vector3i::dotProd(const Vector3i& inVect) {
    return ((x * inVect.x) + (y * inVect.y) + (z * inVect.z));
  }
  
  int32
  Vector3i::crossProd(const Vector3i& inVect) {
    return (((y * inVect.z) - (z * inVect.y)),
            ((z * inVect.x) - (x * inVect.z)),
            ((x * inVect.y) - (y * inVect.z)));
  }
  
  void
  Vector3i::normalize() {
    int32 mag = magnitude();
    if (mag > 0) {
      int32 tmp = 1 / mag;
      x *= tmp;
      y *= tmp;
      z *= tmp;
    }
    else {
      x = 0;
      y = 0;
      z = 0;
    }
  }
  
  int32
  Vector3i::magnitude() {
    return int32(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
  }

}