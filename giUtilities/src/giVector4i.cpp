/**
 * @file    giVector4i.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    05/03/2021
 * @brief   Vectors 4 for ints management.
 * @bug     No known Bugs.
 */

/**
 * @include
 */
#include "giVector4i.h"
#include "giVector4.h"


namespace giEngineSDK {
  
  const Vector4i Vector4i::ZERO = Vector4i(0, 0, 0, 0);
  const Vector4i Vector4i::UNIT = Vector4i(1, 1, 1, 1);

  Vector4i::Vector4i() {
    *this = ZERO;  
  }
  
  Vector4i::Vector4i(int32 inX, int32 inY, int32 inZ, int32 inW)  {
    x = inX;
    y = inY;
    z = inZ;
    w = inW;
  }

  Vector4i::Vector4i(Vector4 inVect) {
    x = int32(inVect.x);
    y = int32(inVect.y);
    z = int32(inVect.z);
    w = int32(inVect.w);
  }
  
  Vector4i::Vector4i(Vector4i& inVect) {
    x = inVect.x;
    y = inVect.y;
    z = inVect.z;
    w = inVect.w;
  }
  
  
  Vector4i
  Vector4i::operator+(const Vector4i& otherVect) {
    return Vector4i(x + otherVect.x, 
                     y + otherVect.y, 
                     z + otherVect.z, 
                     w + otherVect.w);
  }
  
  Vector4i
  Vector4i::operator-(const Vector4i& otherVect) {
    return Vector4i(x - otherVect.x, 
                      y - otherVect.y, 
                      z - otherVect.z, 
                      w - otherVect.w);
  }
  
  Vector4i
  Vector4i::operator*(const Vector4i& otherVect) {
    return Vector4i(x * otherVect.x, 
                      y * otherVect.y, 
                      z * otherVect.z, 
                      w * otherVect.w);
  }
  
  Vector4i
  Vector4i::operator/(const Vector4i& otherVect) {
    return Vector4i(x / otherVect.x, 
                      y / otherVect.y, 
                      z / otherVect.z, 
                      w / otherVect.w);
  }

  void 
  Vector4i::operator=(const Vector4i& otherVect) {
    x = otherVect.x;
    y = otherVect.y;
    z = otherVect.z;
    w = otherVect.w;
  }
  
  Vector4i
  Vector4i::operator+(const int32& otherVal) {
    return Vector4i(x + otherVal, 
                      y + otherVal, 
                      z + otherVal, 
                      w + otherVal);
  }
  
  Vector4i
  Vector4i::operator-(const int32& otherVal) {
    return Vector4i(x - otherVal, 
                      y - otherVal, 
                      z - otherVal, 
                      w - otherVal);
  }
  
  Vector4i
  Vector4i::operator*(const int32& otherVal) {
    return Vector4i(x * otherVal, 
                      y * otherVal, 
                      z * otherVal, 
                      w * otherVal);
  }
  
  Vector4i
  Vector4i::operator/(const int32& otherVal) {
    return Vector4i(x / otherVal, 
                      y / otherVal, 
                      z / otherVal, 
                      w / otherVal);
  }
  
  bool
  Vector4i::operator>=(const Vector4i& otherVect) {
    return (otherVect.x <= x &&
            otherVect.y <= y &&
            otherVect.z <= z &&
            otherVect.w <= w);
  }
  
  bool
  Vector4i::operator<=(const Vector4i& otherVect) {
    return (otherVect.x >= x && 
            otherVect.y >= y &&
            otherVect.z >= z &&
            otherVect.w >= w);
  }
  
  bool
  Vector4i::operator==(const Vector4i& otherVect) {
    return (otherVect.x == x &&
            otherVect.y == y &&
            otherVect.z == z &&
            otherVect.w == w);
  }
  
  bool
  Vector4i::operator<(const Vector4i& otherVect) {
    return (otherVect.x > x &&
            otherVect.y > y &&
            otherVect.z > z &&
            otherVect.w > w);
  }
  
  bool
  Vector4i::operator>(const Vector4i& otherVect) {
    return (otherVect.x < x &&
            otherVect.y < y && 
            otherVect.z < z && 
            otherVect.w < w);
  }
  
  bool
  Vector4i::operator>=(const int32& otherVal) {
    return (otherVal <= x &&
            otherVal <= y && 
            otherVal <= z && 
            otherVal <= w);
  }
  
  bool
  Vector4i::operator<=(const int32& otherVal) {
    return (otherVal >= x &&
            otherVal >= y && 
            otherVal >= z && 
            otherVal >= w);
  }
  
  bool
  Vector4i::operator==(const int32& otherVal) {
    return (otherVal == x &&
            otherVal == y && 
            otherVal == z && 
            otherVal == w);
  }
  
  bool
  Vector4i::operator<(const int32& otherVal) {
    return (otherVal > x &&
            otherVal > y && 
            otherVal > z && 
            otherVal > w);
  }
  
  bool
  Vector4i::operator>(const int32& otherVal) {
    return (otherVal < x &&
            otherVal < y && 
            otherVal < z && 
            otherVal < w);
  }
  
  int32
  Vector4i::dotProd(const Vector4i& inVect) {
    return ((x * inVect.x) + 
            (y * inVect.y) + 
            (z * inVect.z) + 
            (w * inVect.w));
  }
  
  Vector4i
  Vector4i::crossProd(const Vector4i& inVectA, const Vector4i& inVectB) {
    return Vector4i(((inVectA.y * inVectB.z) - (inVectA.z * inVectB.y)),
                    ((inVectA.z * inVectB.x) - (inVectA.x * inVectB.z)),
                    ((inVectA.x * inVectB.y) - (inVectA.y * inVectB.z)),
                    0);
  }
  
  void
  Vector4i::normalize() {

    float mag = magnitude();
    if (mag > 0) {
      int32 tmp = 1.0f / mag;
      x *= tmp;
      y *= tmp;
      z *= tmp;
      w *= tmp;
    }
    else {
      x = 0;
      y = 0;
      z = 0;
      w = 0;
    }
  }
  
  int32
  Vector4i::magnitude() {
    return Math::sqrt(pow(x, 2) 
                      + pow(y, 2) 
                      + pow(z, 2) 
                      + pow(w, 2));
  }

}