#include "giVector2.h"

namespace giEngineSDK {

  Vector2::Vector2(float inX, float inY) {
    x = inX;
    y = inY;
  }
  
  /*Vector2::Vector2(const Vector2& inVect) {
    x = inVect.x;
    y = inVect.y;
  }*/
  
  Vector2::~Vector2() {

  }
  
  Vector2 
  Vector2::operator+(const Vector2& otherVect) {
    return Vector2(x + otherVect.x, y + otherVect.y);
  }
  
  Vector2 
  Vector2::operator-(const Vector2& otherVect) {
    return Vector2(x - otherVect.x, y - otherVect.y);
  }
  
  Vector2 
  Vector2::operator*(const Vector2& otherVect) {
    return Vector2(x * otherVect.x, y * otherVect.y);
  }
  
  Vector2 
  Vector2::operator/(const Vector2& otherVect) {
    return Vector2(x / otherVect.x, y / otherVect.y);
  }
  
  Vector2 
  Vector2::operator+(const float& otherVal) {
    return Vector2(x + otherVal, y + otherVal);
  }
  
  Vector2 
  Vector2::operator-(const float& otherVal) {
    return Vector2(x - otherVal, y - otherVal);
  }
  
  Vector2 
  Vector2::operator*(const float& otherVal) {
    return Vector2(x * otherVal, y * otherVal);
  }
  
  Vector2 
  Vector2::operator/(const float& otherVal) {
    return Vector2(x / otherVal, y / otherVal);
  }
  
  bool 
  Vector2::operator>=(const Vector2& otherVect) {
    return (otherVect.x <= x && otherVect.y <= y);
  }
  
  bool 
  Vector2::operator<=(const Vector2& otherVect) {
    return (otherVect.x >= x && otherVect.y >= y);
  }
  
  bool 
  Vector2::operator==(const Vector2& otherVect) {
    return (otherVect.x == x && otherVect.y == y);
  }
  
  bool 
  Vector2::operator<(const Vector2& otherVect) {
    return (otherVect.x > x && otherVect.y > y);
  }
  
  bool 
  Vector2::operator>(const Vector2& otherVect) {
    return (otherVect.x < x && otherVect.y < y);
  }
  
  bool 
  Vector2::operator>=(const float& otherVal) {
    return (otherVal <= x && otherVal <= y);
  }
  
  bool 
  Vector2::operator<=(const float& otherVal) {
    return (otherVal >= x && otherVal >= y);
  }
  
  bool 
  Vector2::operator==(const float& otherVal) {
    return (otherVal == x && otherVal == y);
  }
  
  bool 
  Vector2::operator<(const float& otherVal) {
    return (otherVal > x && otherVal > y);
  }
  
  bool 
  Vector2::operator>(const float& otherVal) {
    return (otherVal < x && otherVal < y);
  }
  
  float 
  Vector2::dotProd(const Vector2& inVect) {
    return ((x * inVect.x) + (y * inVect.y));
  }
  
  float 
  Vector2::crossProd(const Vector2& inVect) {
    return ((x * inVect.y) - (y * inVect.x));
  }
  
  void 
  Vector2::normalize() {
    float mag = magnitude();
    if (mag > 0) {
      float tmp = 1.0f / mag;
      x *= tmp;
      y *= tmp;
    }
    else {
      x = 0.0f;
      y = 0.0f;
    }
  }
  
  float 
  Vector2::magnitude() {
    return sqrtf(powf(x, 2) + powf(y, 2));
  }
}