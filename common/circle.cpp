#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <cassert>
#include <iostream>
#include "base-types.hpp"

stepanov::Circle::Circle(const point_t& center, const double radius) :
  center_(center),
  radius_(radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Radius can't be negative or equal zero");
  }
}

double stepanov::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

stepanov::rectangle_t stepanov::Circle::getFrameRect() const
{
  return rectangle_t{ 2 * radius_, 2 * radius_, center_ };
}

void stepanov::Circle::move(const point_t& pos)
{
  center_ = pos;
}

void stepanov::Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

stepanov::point_t stepanov::Circle::getCenter() const
{
  return center_;
}

double stepanov::Circle::getRadius() const
{
  return radius_;
}

void stepanov::Circle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Scale coefficient can't be negative or equal zero");
  }
  radius_ *= coefficient;
}

void stepanov::Circle::rotate(const double)
{

}

void stepanov::Circle::print() const
{
  std::cout << "Circle data:\nradius: " << radius_ << '\n'
      << "coordinates of the center: x = " << center_.x
      << " y = " << center_.y << '\n';
}
