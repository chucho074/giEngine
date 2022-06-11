#include "giVector2i.h"

namespace giEngineSDK {

  const Vector2i Vector2i::ZERO = Vector2i(0, 0);
  const Vector2i Vector2i::UNIT = Vector2i(1, 1);

  Vector2i::Vector2i() {
    *this = ZERO;
  }

  Vector2i::Vector2i(int32 inX, int32 inY) {
    x = inX;
    y = inY;
  }
  
  Vector2i::Vector2i(Vector2i& inVect) {
    x = inVect.x;
    y = inVect.y;
  }
  
  Vector2i::~Vector2i() {

  }
  
  Vector2i
  Vector2i::operator+(const Vector2i& otherVect) {
    return Vector2i(x + otherVect.x, y + otherVect.y);
  }
  
  Vector2i
  Vector2i::operator-(const Vector2i& otherVect) {
    return Vector2i(x - otherVect.x, y - otherVect.y);
  }
  
  Vector2i
  Vector2i::operator*(const Vector2i& otherVect) {
    return Vector2i(x * otherVect.x, y * otherVect.y);
  }
  
  Vector2i
  Vector2i::operator/(const Vector2i& otherVect) {
    return Vector2i(x / otherVect.x, y / otherVect.y);
  }
  
  Vector2i
  Vector2i::operator+(const int32& otherVal) {
    return Vector2i(x + otherVal, y + otherVal);
  }
  
  Vector2i
  Vector2i::operator-(const int32& otherVal) {
    return Vector2i(x - otherVal, y - otherVal);
  }
  
  Vector2i
  Vector2i::operator*(const int32& otherVal) {
    return Vector2i(x * otherVal, y * otherVal);
  }
  
  Vector2i
  Vector2i::operator/(const int32& otherVal) {
    return Vector2i(x / otherVal, y / otherVal);
  }
  
  bool
  Vector2i::operator>=(const Vector2i& otherVect) {
    return (otherVect.x <= x && otherVect.y <= y);
  }
  
  bool
  Vector2i::operator<=(const Vector2i& otherVect) {
    return (otherVect.x >= x && otherVect.y >= y); 
  }
  
  bool
  Vector2i::operator==(const Vector2i& otherVect) {
    return (otherVect.x == x && otherVect.y == y);
  }
  
  bool
  Vector2i::operator<(const Vector2i& otherVect) {
    return (otherVect.x > x && otherVect.y > y);
  }
  
  bool
  Vector2i::operator>(const Vector2i& otherVect) {
    return (otherVect.x < x && otherVect.y < y);
  }
  
  bool
  Vector2i::operator>=(const int32& otherVal) {
    return (otherVal <= x && otherVal <= y);
  }
  
  bool
  Vector2i::operator<=(const int32& otherVal) {
    return (otherVal >= x && otherVal >= y);
  }
  
  bool
  Vector2i::operator==(const int32& otherVal)
  {
    if (otherVal == x && otherVal == y) {
      return true;
    }
    return false;
  }
  
  bool
  Vector2i::operator<(const int32& otherVal) {
    return (otherVal > x && otherVal > y);
  }
  
  bool
  Vector2i::operator>(const int32& otherVal) {
    return (otherVal < x && otherVal < y);
  }
  
  int32
  Vector2i::dotProd(const Vector2i& inVect) {
    return ((x * inVect.x) + (y * inVect.y));
  }
  
  int32
  Vector2i::crossProd(const Vector2i& inVect) {
    return ((x * inVect.y) - (y * inVect.x));
  }
  
  void
  Vector2i::normalize() {
    int32 mag = magnitude();
    if (mag > 0) {
      int32 tmp = 1 / mag;
      x *= tmp;
      y *= tmp;
    }
    else {
      x = 0;
      y = 0;
    }
  }
  
  int32
  Vector2i::magnitude() {
    return int32(sqrt(pow(x, 2) + pow(y, 2)));
  }
  
}