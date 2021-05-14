#ifndef POINT_HPP
#define POINT_HPP

#include <iterator>
#include <vector>

struct Point
{
  int x, y;
};

enum typeOfShape
{
  TRIANGLE,
  SQUARE,
  RECTANGLE,
  PENTAGON,
  OTHER_TYPE
};

using Shape = std::vector<Point>;
typeOfShape getTypeOfShape(const Shape& shape);
std::istream& operator>>(std::istream& inputStream, Shape& shape);
std::ostream& operator<<(std::ostream& outputStream, const Shape& shape);
std::istream& operator>>(std::istream& inputStream, Point& point);
std::ostream& operator<<(std::ostream& outputStream, const Point& point);

#endif
