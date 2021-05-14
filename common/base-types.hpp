#ifndef BASETYPES_HPP
#define BASETYPES_HPP

namespace stepanov
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };
};

namespace functions
{
  stepanov::point_t getRotatedPointAroundPoint(const stepanov::point_t& changingPosition, const stepanov::point_t& center, double turn);
  bool isCrossed(const stepanov::rectangle_t& firstRect, const stepanov::rectangle_t& secondRect);
}

#endif
