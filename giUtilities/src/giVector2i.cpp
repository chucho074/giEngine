#include "giVector2i.h"


giVector2i::giVector2i(int32 inX, int32 inY) {
  x = inX;
  y = inY;
}

giVector2i::giVector2i(giVector2i& inVect) {
  x = inVect.getX();
  y = inVect.getY();
}

giVector2i::~giVector2i() {

}

giVector2i
giVector2i::operator+(const giVector2i& otherVect)
{
  return giVector2i(x + otherVect.x, y + otherVect.y);
}

giVector2i
giVector2i::operator-(const giVector2i& otherVect)
{
  return giVector2i(x - otherVect.x, y - otherVect.y);
}

giVector2i
giVector2i::operator*(const giVector2i& otherVect)
{
  return giVector2i(x * otherVect.x, y * otherVect.y);
}

giVector2i
giVector2i::operator/(const giVector2i& otherVect)
{
  return giVector2i(x / otherVect.x, y / otherVect.y);
}

giVector2i
giVector2i::operator+(const int32& otherVal)
{
  return giVector2i(x + otherVal, y + otherVal);
}

giVector2i
giVector2i::operator-(const int32& otherVal)
{
  return giVector2i(x - otherVal, y - otherVal);
}

giVector2i
giVector2i::operator*(const int32& otherVal)
{
  return giVector2i(x * otherVal, y * otherVal);
}

giVector2i
giVector2i::operator/(const int32& otherVal)
{
  return giVector2i(x / otherVal, y / otherVal);
}

bool
giVector2i::operator>=(const giVector2i& otherVect)
{
  if (otherVect.x <= x && otherVect.y <= y) {
    return true;
  }
  return false;
}

bool
giVector2i::operator<=(const giVector2i& otherVect)
{
  if (otherVect.x >= x && otherVect.y >= y) {
    return true;
  }
  return false;
}

bool
giVector2i::operator==(const giVector2i& otherVect)
{
  if (otherVect.x == x && otherVect.y == y) {
    return true;
  }
  return false;
}

bool
giVector2i::operator<(const giVector2i& otherVect)
{
  if (otherVect.x > x && otherVect.y > y) {
    return true;
  }
  return false;
}

bool
giVector2i::operator>(const giVector2i& otherVect)
{
  if (otherVect.x < x && otherVect.y < y) {
    return true;
  }
  return false;
}

bool
giVector2i::operator>=(const int32& otherVal)
{
  if (otherVal <= x && otherVal <= y) {
    return true;
  }
  return false;
}

bool
giVector2i::operator<=(const int32& otherVal)
{
  if (otherVal >= x && otherVal >= y) {
    return true;
  }
  return false;
}

bool
giVector2i::operator==(const int32& otherVal)
{
  if (otherVal == x && otherVal == y) {
    return true;
  }
  return false;
}

bool
giVector2i::operator<(const int32& otherVal)
{
  if (otherVal > x && otherVal > y) {
    return true;
  }
  return false;
}

bool
giVector2i::operator>(const int32& otherVal)
{
  if (otherVal < x && otherVal < y) {
    return true;
  }
  return false;
}

int32
giVector2i::dotProd(const giVector2i& inVect)
{
  return ((x * inVect.x) + (y * inVect.y));
}

int32
giVector2i::crossProd(const giVector2i& inVect)
{
  return ((x * inVect.y) - (y * inVect.x));
}

void
giVector2i::normalize()
{
  int32 mag = magnitude();
  if (mag > 0) {
    int32 tmp = 1.0f / mag;
    x *= tmp;
    y *= tmp;
  }
  else {
    x = 0.0f;
    y = 0.0f;
  }
}

int32
giVector2i::magnitude()
{
  return sqrtf(powf(x, 2) + powf(y, 2));
}


