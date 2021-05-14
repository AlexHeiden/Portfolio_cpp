#include "base-types.hpp"
#include <cmath>

stepanov::point_t functions::getRotatedPointAroundPoint(const stepanov::point_t& changingPosition, const stepanov::point_t& center, double turn)
{
  turn = turn / 180 * M_PI;
  stepanov::point_t temp = changingPosition;
  temp = { center.x + (changingPosition.x - center.x) * std::cos(turn) - (changingPosition.y - center.y) * std::sin(turn),
      center.y + (changingPosition.x - center.x) * std::sin(turn) + (changingPosition.y - center.y) * std::cos(turn) };
  return temp;
}

bool functions::isCrossed(const stepanov::rectangle_t& firstRect, const stepanov::rectangle_t& secondRect)
{
  return ((std::fabs(secondRect.pos.x - firstRect.pos.x) < (secondRect.width + firstRect.width) / 2)
      && (std::fabs(secondRect.pos.y - firstRect.pos.y) < (secondRect.height + firstRect.height) / 2));
}
