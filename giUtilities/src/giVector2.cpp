#include "giVector2.h"


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
