#include <iostream>
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "base-types.hpp"

int main()
{
  stepanov::Shape* shape;
  stepanov::Rectangle objectRectangle({ 2.1, 12.6, {6.6, 7.12} });
  shape = &objectRectangle;
  std::cout << "The area of the rectangle equals " << shape->getArea() << '\n';

  std::cout << "The parameters of the rectangle equal\n";
  shape->print();

  const stepanov::rectangle_t rectFrameRect = shape->getFrameRect();
  std::cout << "The parameters of the rectangle's frame rectangle equal\n"
      << "height: " << rectFrameRect.height << '\n'
      << "width: " << rectFrameRect.width << '\n'
      << "coordinates of the center: x = " << rectFrameRect.pos.x
      << " y = " << rectFrameRect.pos.y << '\n';

  shape->move({12.42, 64.1});
  std::cout << "The parameters of the rectangle after first move equal\n";
  shape->print();

  shape->move(7.58, 5.9);
  std::cout << "The parameters of the rectangle after second move equal\n";
  shape->print();

  shape->scale(2.0);
  std::cout << "The parameters of the rectangle after scale equal\n";
  shape->print();

  stepanov::Circle objectCircle({9.73, 12.62}, 3.67);
  shape = &objectCircle;
  std::cout << "The parameters of the circle equal\n";
  shape->print();

  const stepanov::rectangle_t circleFrameRect = shape->getFrameRect();
  std::cout << "The parameters of the circle's frame rectangle equal\n"
      << "height: " << circleFrameRect.height << '\n'
      << "width: " << circleFrameRect.width << '\n'
      << "coordinates of the center: x = " << circleFrameRect.pos.x
      << " y = " << circleFrameRect.pos.y << '\n';

  shape->move({12.42, 64.1});
  std::cout << "Parameters of the circle after the first move equal\n";
  shape->print();

  shape->move(7.58, 5.9);
  std::cout << "Parameters of the circle after the second move equal\n";
  shape->print();

  shape->scale(3.1);
  std::cout << "The parameters of the circle after scale equal\n";
  shape->print();

  return 0;
}
