#include "giVector4.h"


giVector4::giVector4(float inX, float inY, float inZ, float inW) {
  x = inX;
  y = inY;
  z = inZ;
  w = inW;
}

giVector4::giVector4(giVector4& inVect) {
  x = inVect.getX();
  y = inVect.getY();
  z = inVect.getZ();
  w = inVect.getW();
}

giVector4::~giVector4() {

}

giVector4
giVector4::operator+(const giVector4& otherVect) const
{
  return giVector4(x + otherVect.x, 
                   y + otherVect.y, 
                   z + otherVect.z, 
                   w + otherVect.w);
}

giVector4
giVector4::operator-(const giVector4& otherVect) const 
{
  return giVector4(x - otherVect.x, 
                   y - otherVect.y, 
                   z - otherVect.z, 
                   w - otherVect.w);
}

giVector4
giVector4::operator*(const giVector4& otherVect) const 
{
  return giVector4(x * otherVect.x, 
                   y * otherVect.y, 
                   z * otherVect.z, 
                   w * otherVect.w);
}

giVector4
giVector4::operator/(const giVector4& otherVect) const 
{
  return giVector4(x / otherVect.x, 
                   y / otherVect.y, 
                   z / otherVect.z, 
                   w / otherVect.w);
}

giVector4
giVector4::operator+(const float& otherVal)
{
  return giVector4(x + otherVal, 
                   y + otherVal, 
                   z + otherVal, 
                   w + otherVal);
}

giVector4
giVector4::operator-(const float& otherVal)
{
  return giVector4(x - otherVal, 
                   y - otherVal, 
                   z - otherVal, 
                   w - otherVal);
}

giVector4
giVector4::operator*(const float& otherVal)
{
  return giVector4(x * otherVal, 
                   y * otherVal, 
                   z * otherVal, 
                   w * otherVal);
}

giVector4
giVector4::operator/(const float& otherVal)
{
  return giVector4(x / otherVal, 
                   y / otherVal, 
                   z / otherVal, 
                   w / otherVal);
}

bool
giVector4::operator>=(const giVector4& otherVect) const
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
giVector4::operator<=(const giVector4& otherVect) const
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
giVector4::operator==(const giVector4& otherVect) const
{
  if (otherVect.x == x && 
      otherVect.y == y && 
      otherVect.z == z && 
      otherVect.w == w) {

    return true;
  }
  return false;
}

bool giVector4::operator!=(const giVector4& otherVect) const
{
    if (otherVect.x != x && 
        otherVect.y != y && 
        otherVect.z != z && 
        otherVect.w != w) {

    return true;
  }
  return false;
}

bool
giVector4::operator<(const giVector4& otherVect) const
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
giVector4::operator>(const giVector4& otherVect) const
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
giVector4::operator>=(const float& otherVal)
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
giVector4::operator<=(const float& otherVal)
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
giVector4::operator==(const float& otherVal)
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
giVector4::operator<(const float& otherVal)
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
giVector4::operator>(const float& otherVal)
{
  if (otherVal < x && 
      otherVal < y && 
      otherVal < z && 
      otherVal < w) {

    return true;
  }
  return false;
}

float
giVector4::dotProd(const giVector4& inVect)
{
  return ((x * inVect.x) + 
          (y * inVect.y) + 
          (z * inVect.z) + 
          (w * inVect.w));
}

float
giVector4::crossProd(const giVector4& inVect)
{
  return (((y * inVect.z) - (z * inVect.y)),
          ((z * inVect.x) - (x * inVect.z)),
          ((x * inVect.y) - (y * inVect.z)),
          0.f);
}

void
giVector4::normalize()
{
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
giVector4::magnitude()
{
  return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2) + powf(w, 2));
}


