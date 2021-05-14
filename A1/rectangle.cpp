#include "rectangle.hpp"
#include <cassert>

Rectangle::Rectangle(const rectangle_t& rectangle): 
  rectangleData_(rectangle)
{
  assert((rectangleData_.width > 0) && (rectangleData_.height > 0));
}

double Rectangle::getArea() const
{
  return rectangleData_.height * rectangleData_.width;
}

rectangle_t Rectangle::getFrameRect() const 
{
  return rectangleData_; 
}

void Rectangle::move(const point_t& pos)
{
  rectangleData_.pos = pos;
}

void Rectangle::move(const double dx, const double dy)
{
  rectangleData_.pos.x += dx;
  rectangleData_.pos.y += dy;
}

point_t Rectangle::getCenter() const
{
  return rectangleData_.pos;
}

