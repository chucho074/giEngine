#include "giVector2.h"

namespace giEngineSDK {

  giVector2::giVector2(float inX, float inY) {
  x = inX;
  y = inY;
}
  
  giVector2::giVector2(giVector2& inVect) {
  x = inVect.getX();
  y = inVect.getY();
}
  
  giVector2::~giVector2() {

}
  
  giVector2 
  giVector2::operator+(const giVector2& otherVect)
{
  return giVector2(x + otherVect.x, y + otherVect.y);
}
  
  giVector2 
  giVector2::operator-(const giVector2& otherVect)
{
  return giVector2(x - otherVect.x, y - otherVect.y);
}
  
  giVector2 
  giVector2::operator*(const giVector2& otherVect)
{
  return giVector2(x * otherVect.x, y * otherVect.y);
}
  
  giVector2 
  giVector2::operator/(const giVector2& otherVect)
{
  return giVector2(x / otherVect.x, y / otherVect.y);
}
  
  giVector2 
  giVector2::operator+(const float& otherVal)
{
  return giVector2(x + otherVal, y + otherVal);
}
  
  giVector2 
  giVector2::operator-(const float& otherVal)
{
  return giVector2(x - otherVal, y - otherVal);
}
  
  giVector2 
  giVector2::operator*(const float& otherVal)
{
  return giVector2(x * otherVal, y * otherVal);
}
  
  giVector2 
  giVector2::operator/(const float& otherVal)
{
  return giVector2(x / otherVal, y / otherVal);
}
  
  bool 
  giVector2::operator>=(const giVector2& otherVect)
{
  if (otherVect.x <= x && otherVect.y <= y) {
    return true;
  }
  return false;
}
  
  bool 
  giVector2::operator<=(const giVector2& otherVect)
{
  if (otherVect.x >= x && otherVect.y >= y) {
    return true;
  }
  return false;
}
  
  bool 
  giVector2::operator==(const giVector2& otherVect)
{
  if (otherVect.x == x && otherVect.y == y) {
    return true;
  }
  return false;
}
  
  bool 
  giVector2::operator<(const giVector2& otherVect)
{
  if (otherVect.x > x && otherVect.y > y) {
    return true;
  }
  return false;
}
  
  bool 
  giVector2::operator>(const giVector2& otherVect)
{
  if (otherVect.x < x && otherVect.y < y) {
    return true;
  }
  return false;
}
  
  bool 
  giVector2::operator>=(const float& otherVal)
{
  if (otherVal <= x && otherVal <= y) {
    return true;
  }
  return false;
}
  
  bool 
  giVector2::operator<=(const float& otherVal)
{
  if (otherVal >= x && otherVal >= y) {
    return true;
  }
  return false;
}
  
  bool 
  giVector2::operator==(const float& otherVal)
{
  if (otherVal == x && otherVal == y) {
    return true;
  }
  return false;
}
  
  bool 
  giVector2::operator<(const float& otherVal)
{
  if (otherVal > x && otherVal > y) {
    return true;
  }
  return false;
}
  
  bool 
  giVector2::operator>(const float& otherVal)
{
  if (otherVal < x && otherVal < y) {
    return true;
  }
  return false;
}
  
  float 
  giVector2::dotProd(const giVector2& inVect)
{
  return ((x * inVect.x) + (y * inVect.y));
}
  
  float 
  giVector2::crossProd(const giVector2& inVect)
{
  return ((x * inVect.y) - (y * inVect.x));
}
  
  void 
  giVector2::normalize()
{
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
  giVector2::magnitude()
{
  return sqrtf(powf(x, 2) + powf(y, 2));
}


}