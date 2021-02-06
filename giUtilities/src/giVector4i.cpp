#include "giVector4i.h"


giVector4i::giVector4i(int32 inX, int32 inY, int32 inZ, int32 inW) {
  x = inX;
  y = inY;
  z = inZ;
  w = inW;
}

giVector4i::giVector4i(giVector4i& inVect) {
  x = inVect.getX();
  y = inVect.getY();
  z = inVect.getZ();
  w = inVect.getW();
}

giVector4i::~giVector4i() {

}

giVector4i
giVector4i::operator+(const giVector4i& otherVect)
{
  return giVector4i(x + otherVect.x, 
                   y + otherVect.y, 
                   z + otherVect.z, 
                   w + otherVect.w);
}

giVector4i
giVector4i::operator-(const giVector4i& otherVect)
{
  return giVector4i(x - otherVect.x, 
                   y - otherVect.y, 
                   z - otherVect.z, 
                   w - otherVect.w);
}

giVector4i
giVector4i::operator*(const giVector4i& otherVect)
{
  return giVector4i(x * otherVect.x, 
                   y * otherVect.y, 
                   z * otherVect.z, 
                   w * otherVect.w);
}

giVector4i
giVector4i::operator/(const giVector4i& otherVect)
{
  return giVector4i(x / otherVect.x, 
                   y / otherVect.y, 
                   z / otherVect.z, 
                   w / otherVect.w);
}

giVector4i
giVector4i::operator+(const int32& otherVal)
{
  return giVector4i(x + otherVal, 
                   y + otherVal, 
                   z + otherVal, 
                   w + otherVal);
}

giVector4i
giVector4i::operator-(const int32& otherVal)
{
  return giVector4i(x - otherVal, 
                   y - otherVal, 
                   z - otherVal, 
                   w - otherVal);
}

giVector4i
giVector4i::operator*(const int32& otherVal)
{
  return giVector4i(x * otherVal, 
                   y * otherVal, 
                   z * otherVal, 
                   w * otherVal);
}

giVector4i
giVector4i::operator/(const int32& otherVal)
{
  return giVector4i(x / otherVal, 
                   y / otherVal, 
                   z / otherVal, 
                   w / otherVal);
}

bool
giVector4i::operator>=(const giVector4i& otherVect)
{
  if (otherVect.x <= x && 
      otherVect.y <= y && 
      otherVect.z <= z && 
      otherVect.w <= w) {

    return true;
  }
  return false;
}

bool
giVector4i::operator<=(const giVector4i& otherVect)
{
  if (otherVect.x >= x && 
      otherVect.y >= y && 
      otherVect.z >= z && 
      otherVect.w >= w) {

    return true;
  }
  return false;
}

bool
giVector4i::operator==(const giVector4i& otherVect)
{
  if (otherVect.x == x && 
      otherVect.y == y && 
      otherVect.z == z && 
      otherVect.w == w) {

    return true;
  }
  return false;
}

bool
giVector4i::operator<(const giVector4i& otherVect)
{
  if (otherVect.x > x && 
      otherVect.y > y && 
      otherVect.z > z && 
      otherVect.w > w) {

    return true;
  }
  return false;
}

bool
giVector4i::operator>(const giVector4i& otherVect)
{
  if (otherVect.x < x && 
      otherVect.y < y && 
      otherVect.z < z && 
      otherVect.w < w) {

    return true;
  }
  return false;
}

bool
giVector4i::operator>=(const int32& otherVal)
{
  if (otherVal <= x && 
      otherVal <= y && 
      otherVal <= z && 
      otherVal <= w) {

    return true;
  }
  return false;
}

bool
giVector4i::operator<=(const int32& otherVal)
{
  if (otherVal >= x && 
      otherVal >= y && 
      otherVal >= z && 
      otherVal >= w) {

    return true;
  }
  return false;
}

bool
giVector4i::operator==(const int32& otherVal)
{
  if (otherVal == x && 
      otherVal == y && 
      otherVal == z && 
      otherVal == w) {

    return true;
  }
  return false;
}

bool
giVector4i::operator<(const int32& otherVal)
{
  if (otherVal > x && 
      otherVal > y && 
      otherVal > z && 
      otherVal > w) {

    return true;
  }
  return false;
}

bool
giVector4i::operator>(const int32& otherVal)
{
  if (otherVal < x && 
      otherVal < y && 
      otherVal < z && 
      otherVal < w) {

    return true;
  }
  return false;
}

int32
giVector4i::dotProd(const giVector4i& inVect)
{
  return ((x * inVect.x) + 
          (y * inVect.y) + 
          (z * inVect.z) + 
          (w * inVect.w));
}

int32
giVector4i::crossProd(const giVector4i& inVect)
{
  return (((y * inVect.z) - (z * inVect.y)),
          ((z * inVect.x) - (x * inVect.z)),
          ((x * inVect.y) - (y * inVect.z)),
          0.f);
}

void
giVector4i::normalize()
{
  int32 mag = magnitude();
  if (mag > 0) {
    int32 tmp = 1.0f / mag;
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

int32
giVector4i::magnitude()
{
  return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2) + powf(w, 2));
}