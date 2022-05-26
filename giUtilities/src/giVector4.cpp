/**
 * @file    giVector4.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    26/03/2021
 * @brief   A basic Vector 4.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giVector4.h"
#include "giVector4i.h"

namespace giEngineSDK {
  
  Vector4::Vector4(float inX, float inY, float inZ, float inW) {
    x = inX;
    y = inY;
    z = inZ;
    w = inW;
  }

  Vector4::Vector4(Vector4i inVect) {
    x = float(inVect.x);
    y = float(inVect.y);
    z = float(inVect.w);
    w = float(inVect.z);
  }
  
  Vector4::Vector4(Vector4& inVect) {
    x = inVect.x;
    y = inVect.y;
    z = inVect.z;
    w = inVect.w;
  }
  
  Vector4::~Vector4() {

  }
  
  void
  Vector4::operator+=(const Vector4& otherVect) {
    x += otherVect.x;
    y += otherVect.y;
    z += otherVect.z;
    w += otherVect.w;
  }
  
  void
  Vector4::operator-=(const Vector4& otherVect) {
    x -= otherVect.x;
    y -= otherVect.y;
    z -= otherVect.z;
    w -= otherVect.w;
  }
  
  void
  Vector4::operator*=(const Vector4& otherVect) {
    x *= otherVect.x;
    y *= otherVect.y;
    z *= otherVect.z;
    w *= otherVect.w;
  }
  
  void
  Vector4::operator/=(const Vector4& otherVect) {
    x /= otherVect.x;
    y /= otherVect.y;
    z /= otherVect.z;
    w /= otherVect.w;
  }
  
  Vector4
  Vector4::operator+(const Vector4& otherVect) const {
    return Vector4(x + otherVect.x, 
                     y + otherVect.y, 
                     z + otherVect.z, 
                     w + otherVect.w);
  }
  
  Vector4
  Vector4::operator-(const Vector4& otherVect) const {
    return Vector4(x - otherVect.x, 
                     y - otherVect.y, 
                     z - otherVect.z, 
                     w - otherVect.w);
  }
  
  Vector4
  Vector4::operator*(const Vector4& otherVect) const {
    return Vector4(x * otherVect.x, 
                     y * otherVect.y, 
                     z * otherVect.z, 
                     w * otherVect.w);
  }
  
  Vector4
  Vector4::operator/(const Vector4& otherVect) const {
    return Vector4(x / otherVect.x, 
                     y / otherVect.y, 
                     z / otherVect.z, 
                     w / otherVect.w);
  }

  void
  Vector4::operator=(const Vector4& otherVect) {
    x = otherVect.x;
    y = otherVect.y;
    z = otherVect.z;
    w = otherVect.w;
  }
  
  Vector4
  Vector4::operator+(const float& otherVal) {
    return Vector4(x + otherVal, 
                     y + otherVal, 
                     z + otherVal, 
                     w + otherVal);
  }
  
  Vector4
  Vector4::operator-(const float& otherVal) {
    return Vector4(x - otherVal, 
                     y - otherVal, 
                     z - otherVal, 
                     w - otherVal);
  }
  
  Vector4
  Vector4::operator*(const float& otherVal) {
    return Vector4(x * otherVal, 
                     y * otherVal, 
                     z * otherVal, 
                     w * otherVal);
  }
  
  Vector4
  Vector4::operator/(const float& otherVal) {
    return Vector4(x / otherVal, 
                     y / otherVal, 
                     z / otherVal, 
                     w / otherVal);
  }

  Vector4 
  Vector4::operator-() const {
    Vector4 tmpVect(-x,-y,-z,-w);
    return tmpVect;
  }
  
  bool
  Vector4::operator>=(const Vector4& otherVect) const {
    return (otherVect.x <= x && 
            otherVect.y <= y && 
            otherVect.z <= z && 
            otherVect.w <= w);
  
  }
    
  bool
  Vector4::operator<=(const Vector4& otherVect) const {
    return (otherVect.x >= x &&
            otherVect.y >= y &&
            otherVect.z >= z &&
            otherVect.w >= w);
  }
  
  bool
  Vector4::operator==(const Vector4& otherVect) const {
    return (otherVect.x == x && 
            otherVect.y == y && 
            otherVect.z == z && 
            otherVect.w == w);
  }
  
  bool 
  Vector4::operator!=(const Vector4& otherVect) const {
      return (otherVect.x != x && 
              otherVect.y != y && 
              otherVect.z != z && 
              otherVect.w != w);
  }
  
  bool
  Vector4::operator<(const Vector4& otherVect) const {
    return (otherVect.x > x && 
            otherVect.y > y && 
            otherVect.z > z && 
            otherVect.w > w);
  }
  
  bool
  Vector4::operator>(const Vector4& otherVect) const {
    return (otherVect.x < x && 
            otherVect.y < y && 
            otherVect.z < z && 
            otherVect.w < w); 

  }
  
  bool
  Vector4::operator>=(const float& otherVal) {
    return (otherVal <= x &&
            otherVal <= y &&
            otherVal <= z &&
            otherVal <= w);
  }
  
  bool
  Vector4::operator<=(const float& otherVal) {
    return (otherVal >= x &&
            otherVal >= y &&
            otherVal >= z &&
            otherVal >= w);
  }
  
  bool
  Vector4::operator==(const float& otherVal) {
    return (otherVal == x &&
            otherVal == y &&
            otherVal == z &&
            otherVal == w);
  }
  
  bool
  Vector4::operator<(const float& otherVal) {
    return (otherVal > x &&
            otherVal > y &&
            otherVal > z &&
            otherVal > w);
  }
  
  bool
  Vector4::operator>(const float& otherVal) {
    return (otherVal < x &&
            otherVal < y &&
            otherVal < z &&
            otherVal < w);
  }
  
  float
  Vector4::dotProd(const Vector4& inVectA) {
    return ((x * inVectA.x) + 
            (y * inVectA.y) + 
            (z * inVectA.z) + 
            (w * inVectA.w));
  }

  Vector4 
  Vector4::cross(Vector4 inVector) {
    Vector4 tmpVect;
    tmpVect.x = 0.f;
    tmpVect.y = 0.f;
    tmpVect.z = 0.f;
    tmpVect.w = 0.f;


    tmpVect.x = ((y * inVector.z) - (z * inVector.y));
    tmpVect.y = ((z * inVector.x) - (x * inVector.z));
    tmpVect.z = ((x * inVector.y) - (y * inVector.x));
    tmpVect.w = 0.f;

    return tmpVect;
  }
   
  void
  Vector4::normalize() {

    float mag = magnitude();
    if (mag > 0) {
      float tmp = 1.0f / mag;
      x *= tmp;
      y *= tmp;
      z *= tmp;
      w *= tmp;
    }
    else {
      x = 0.0f;
      y = 0.0f;
      z = 0.0f;
      w = 0.0f;
    }
    
  }
  
  float
  Vector4::magnitude() {
    return sqrtf(powf(x, 2) 
                 + powf(y, 2) 
                 + powf(z, 2) 
                 + powf(w, 2));
  }
 
}