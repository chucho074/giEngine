#include "giVector3i.h"

namespace giEngineSDK {

  giVector3i::giVector3i(int32 inX, int32 inY, int32 inZ) {
  x = inX;
  y = inY;
  z = inZ;
}
  
  giVector3i::giVector3i(giVector3i& inVect) {
  x = inVect.getX();
  y = inVect.getY();
  z = inVect.getZ();
}
  
  giVector3i::~giVector3i() {

}
  
  giVector3i
  giVector3i::operator+(const giVector3i& otherVect)
{
  return giVector3i(x + otherVect.x, y + otherVect.y, z + otherVect.z);
}
  
  giVector3i
  giVector3i::operator-(const giVector3i& otherVect)
{
  return giVector3i(x - otherVect.x, y - otherVect.y, z - otherVect.z);
}
  
  giVector3i
  giVector3i::operator*(const giVector3i& otherVect)
{
  return giVector3i(x * otherVect.x, y * otherVect.y, z * otherVect.z);
}
  
  giVector3i
  giVector3i::operator/(const giVector3i& otherVect)
{
  return giVector3i(x / otherVect.x, y / otherVect.y, z / otherVect.z);
}
  
  giVector3i
  giVector3i::operator+(const int32& otherVal)
{
  return giVector3i(x + otherVal, y + otherVal, z + otherVal);
}
  
  giVector3i
  giVector3i::operator-(const int32& otherVal)
{
  return giVector3i(x - otherVal, y - otherVal, z - otherVal);
}
  
  giVector3i
  giVector3i::operator*(const int32& otherVal)
{
  return giVector3i(x * otherVal, y * otherVal, z * otherVal);
}
  
  giVector3i
  giVector3i::operator/(const int32& otherVal)
{
  return giVector3i(x / otherVal, y / otherVal, z / otherVal);
}
  
  bool
  giVector3i::operator>=(const giVector3i& otherVect)
{
  if (otherVect.x <= x && otherVect.y <= y && otherVect.z <= z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3i::operator<=(const giVector3i& otherVect)
{
  if (otherVect.x >= x && otherVect.y >= y && otherVect.z >= z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3i::operator==(const giVector3i& otherVect)
{
  if (otherVect.x == x && otherVect.y == y && otherVect.z == z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3i::operator<(const giVector3i& otherVect)
{
  if (otherVect.x > x && otherVect.y > y && otherVect.z > z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3i::operator>(const giVector3i& otherVect)
{
  if (otherVect.x < x && otherVect.y < y && otherVect.z < z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3i::operator>=(const int32& otherVal)
{
  if (otherVal <= x && otherVal <= y && otherVal <= z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3i::operator<=(const int32& otherVal)
{
  if (otherVal >= x && otherVal >= y && otherVal >= z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3i::operator==(const int32& otherVal)
{
  if (otherVal == x && otherVal == y && otherVal == z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3i::operator<(const int32& otherVal)
{
  if (otherVal > x && otherVal > y && otherVal > z) {
    return true;
  }
  return false;
}
  
  bool
  giVector3i::operator>(const int32& otherVal)
{
  if (otherVal < x && otherVal < y && otherVal < z) {
    return true;
  }
  return false;
}
  
  int32
  giVector3i::dotProd(const giVector3i& inVect)
{
  return ((x * inVect.x) + (y * inVect.y) + (z * inVect.z));
}
  
  int32
  giVector3i::crossProd(const giVector3i& inVect)
{
  return (((y * inVect.z) - (z * inVect.y)),
    ((z * inVect.x) - (x * inVect.z)),
    ((x * inVect.y) - (y * inVect.z)));
}
  
  void
  giVector3i::normalize()
{
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
  giVector3i::magnitude()
  {
    return int32(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
  }


}