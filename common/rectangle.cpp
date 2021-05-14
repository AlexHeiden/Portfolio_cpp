#include "rectangle.hpp"
#include <math.h>
#include <iostream>
#include "base-types.hpp"

stepanov::Rectangle::Rectangle(const rectangle_t& rectangle, double turn) :
  center_({ rectangle.pos.x, rectangle.pos.y }),
  positions_{ {center_.x + rectangle.height / 2, center_.y - rectangle.width / 2},
             {center_.x + rectangle.height / 2, center_.y + rectangle.width / 2},
             {center_.x - rectangle.height / 2, center_.y + rectangle.width / 2},
             {center_.x - rectangle.height / 2, center_.y - rectangle.width / 2} }
{
  if ((rectangle.width <= 0) || (rectangle.height <= 0))
  {
    throw std::invalid_argument("Height and width can't be negative or equal zero");
  }

  rotate(turn);
}

double stepanov::Rectangle::getArea() const
{
  return getWidth() * getHeight();
}

double stepanov::Rectangle::getWidth() const
{
  return std::sqrt((positions_[1].x - positions_[0].x) * (positions_[1].x - positions_[0].x)
      + (positions_[1].y - positions_[0].y) * (positions_[1].y - positions_[0].y));
}

double stepanov::Rectangle::getHeight() const
{
  return std::sqrt((positions_[3].x - positions_[0].x) * (positions_[3].x - positions_[0].x)
      + (positions_[3].y - positions_[0].y) * (positions_[3].y - positions_[0].y));
}

stepanov::rectangle_t stepanov::Rectangle::getFrameRect() const
{
  return rectangle_t{ getWidth(), getHeight(), getCenter() };
}

void stepanov::Rectangle::move(const point_t& pos)
{
  move(pos.x - getCenter().x, pos.y - getCenter().y);
}

void stepanov::Rectangle::move(const double dx, const double dy)
{
  const int numberOfAngles = 4;

  for (int i = 0; i <= numberOfAngles - 1; i++)
  {
    positions_[i].x += dx;
    positions_[i].y += dy;
  }
  center_.x += dx;
  center_.y += dy;
}

stepanov::point_t stepanov::Rectangle::getCenter() const
{
  return center_;
}

void stepanov::Rectangle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Scale coefficient can't be negative or equal zero");
  }

  const int numberOfAngles = 4;

  for (int i = 0; i <= numberOfAngles - 1; i++)
  {
    positions_[i].x = center_.x + coefficient * (positions_[i].x - center_.x);
    positions_[i].y = center_.y + coefficient * (positions_[i].y - center_.y);
  }
}

void stepanov::Rectangle::rotate(const double turn)
{
  const int numberOfAngles = 4;

  for (int i = 0; i <= numberOfAngles - 1; i++)
  {
    positions_[i] = functions::getRotatedPointAroundPoint(positions_[i], center_, turn);
  }
}

void stepanov::Rectangle::print() const
{
  std::cout << "Rectangle data:\nheight: " << getHeight() << '\n'
      << "width: " << getWidth() << '\n'
      << "coordinates of the center: x = " << center_.x
      << " y = " << center_.y << '\n';
}
