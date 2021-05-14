#include <iostream>
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  Shape* shape;
  Rectangle objectRectangle({ 2.1, 12.6, {6.6, 7.12} });
  shape = &objectRectangle;
  std::cout << "The area of the rectangle equals " << shape->getArea() << '\n';

  const rectangle_t rectFrameRect = shape->getFrameRect();
  std::cout << "The parameters of the rectangle's frame rectangle equal\n"
      << "height: " << rectFrameRect.height << '\n'
      << "width: " << rectFrameRect.width << '\n'
      << "coordinates of the center: x = " << rectFrameRect.pos.x
      << " y = " << rectFrameRect.pos.y << '\n';

  shape->move({12.42, 64.1});
  rectangle_t newPosRect = objectRectangle.getFrameRect(); 
  std::cout << "New coordinates of the rectangle's center equal x = " << newPosRect.pos.x
      << " y = " << newPosRect.pos.y << '\n';

  shape->move(7.58, 5.9);
  newPosRect = objectRectangle.getFrameRect();
  std::cout << "New coordinates of the rectangle's center equal x = " << newPosRect.pos.x
      << " y = " << newPosRect.pos.y << '\n';

  Circle objectCircle({9.73, 12.62}, 3.67);
  shape = &objectCircle;
  const point_t returnedCenterCircle = objectCircle.getCenter();
  std::cout << "The center of the circle is situated in coordinates x = " << returnedCenterCircle.x
      << " y = " << returnedCenterCircle.y << '\n';
  std::cout << "The radius of the circle equals " << objectCircle.getRadius() << '\n';

  std::cout << "The area of the circle equals " << shape->getArea() << '\n';
  const rectangle_t circleFrameRect = shape->getFrameRect();
  std::cout << "The parameters of the circle's frame rectangle equal\n"
      << "height: " << circleFrameRect.height << '\n'
      << "width: " << circleFrameRect.width << '\n'
      << "coordinates of the center: x = " << circleFrameRect.pos.x
      << " y = " << circleFrameRect.pos.y << '\n';

  shape->move({12.42, 64.1});
  point_t newCenterCircle = objectCircle.getCenter();
  std::cout << "New coordinates of the circle's center equal x = " << newCenterCircle.x
      << " y = " << newCenterCircle.y << '\n';

  shape->move(7.58, 5.9);
  newCenterCircle = objectCircle.getCenter();
  std::cout << "New coordinates of the circle's center equal x = " << newCenterCircle.x
      << " y = " << newCenterCircle.y << '\n';

  return 0;
}
