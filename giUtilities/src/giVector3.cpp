#include "giVector3.h"

namespace giEngineSDK {

  giVector3::giVector3(float inX, float inY, float inZ) {
    x = inX;
    y = inY;
    z = inZ;
  }
  
  giVector3::giVector3(giVector3& inVect) {
    x = inVect.getX();
    y = inVect.getY();
    z = inVect.getZ();
  }
  
  giVector3::~giVector3() {
  
  }
  
  giVector3
  giVector3::operator+(const giVector3& otherVect)
{
  return giVector3(x + otherVect.x, y + otherVect.y, z + otherVect.z);
}
  
  giVector3
  giVector3::operator-(const giVector3& otherVect)
{
  return giVector3(x - otherVect.x, y - otherVect.y, z - otherVect.z);
}
  
  giVector3
  giVector3::operator*(const giVector3& otherVect)
{
  return giVector3(x * otherVect.x, y * otherVect.y, z * otherVect.z);
}
  
  giVector3
  giVector3::operator/(const giVector3& otherVect)
{
  return giVector3(x / otherVect.x, y / otherVect.y, z / otherVect.z);
}
  
  giVector3
  giVector3::operator+(const float& otherVal)
{
  return giVector3(x + otherVal, y + otherVal, z + otherVal);
}
  
  giVector3
  giVector3::operator-(const float& otherVal)
{
  return giVector3(x - otherVal, y - otherVal, z - otherVal);
}
  
  giVector3
  giVector3::operator*(const float& otherVal)
{
  return giVector3(x * otherVal, y * otherVal, z * otherVal);
}
  
  giVector3
  giVector3::operator/(const float& otherVal)
{
  return giVector3(x / otherVal, y / otherVal, z / otherVal);
}
  
  bool
  giVector3::operator>=(const giVector3& otherVect)
{
  if (otherVect.x <= x && otherVect.y <= y && otherVect.z <= z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3::operator<=(const giVector3& otherVect)
{
  if (otherVect.x >= x && otherVect.y >= y && otherVect.z >= z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3::operator==(const giVector3& otherVect)
{
  if (otherVect.x == x && otherVect.y == y && otherVect.z == z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3::operator<(const giVector3& otherVect)
{
  if (otherVect.x > x && otherVect.y > y && otherVect.z > z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3::operator>(const giVector3& otherVect)
{
  if (otherVect.x < x && otherVect.y < y && otherVect.z < z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3::operator>=(const float& otherVal)
{
  if (otherVal <= x && otherVal <= y && otherVal <= z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3::operator<=(const float& otherVal)
{
  if (otherVal >= x && otherVal >= y && otherVal >= z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3::operator==(const float& otherVal)
{
  if (otherVal == x && otherVal == y && otherVal == z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3::operator<(const float& otherVal)
{
  if (otherVal > x && otherVal > y && otherVal > z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3::operator>(const float& otherVal)
{
  if (otherVal < x && otherVal < y && otherVal < z) {
    return true;
  }
  return false;
}
  
  float
  giVector3::dotProd(const giVector3& inVect)
{
  return ((x * inVect.x) + (y * inVect.y)+ (z * inVect.z));
}
  
  float
  giVector3::crossProd(const giVector3& inVect)
{
  return (((y * inVect.z) - (z * inVect.y)),
          ((z * inVect.x) - (x * inVect.z)),
          ((x * inVect.y) - (y * inVect.z)));
}
  
  void
  giVector3::normalize()
{
  float mag = magnitude();
  if (mag > 0) {
    float tmp = 1.0f / mag;
    x *= tmp;
    y *= tmp;
    z *= tmp;
  }
  else {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }
}
  
  float
  giVector3::magnitude()
{
  return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
}

}