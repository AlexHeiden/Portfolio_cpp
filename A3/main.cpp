#include <iostream>
#include <memory>
#include <stdexcept>
#include "base-types.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
  try
  {
    stepanov::CompositeShape firstCompositeShape;
    stepanov::Rectangle rectangle({ 1.2, 3.4, {5.6, 7.8} });

    try
    {
      firstCompositeShape.add(std::make_shared<stepanov::Rectangle>(rectangle));
    }
    catch (const std::invalid_argument& error)
    {
      std::cerr << "Invalid argument error: " << error.what();
      return 1;
    }

    stepanov::Circle circle({ 1.2, 3.4, }, 5.6);

    try
    {
      firstCompositeShape.add(std::make_shared<stepanov::Circle>(circle));
    }
    catch (const std::invalid_argument& error)
    {
      std::cerr << "Invalid argument error: " << error.what();
      return 1;
    }

    stepanov::CompositeShape compositeShape(firstCompositeShape);

    std::cout << "The data of composite-shape after 2 addings:\n";
    compositeShape.print();

    std::cout << "The area of composite-shape equals: " << compositeShape.getArea() << '\n';

    std::cout << "The data of composite-shape's frame rectangle is:\n"
        << "height: " << compositeShape.getFrameRect().height << '\n'
        << "width: " << compositeShape.getFrameRect().width << '\n';

    try
    {
      std::cout << "centre x coordiante: " << compositeShape.getCenter().x << '\n'
          << "centre y coordiante: " << compositeShape.getCenter().y << '\n';
    }
    catch (const std::runtime_error& error)
    {
      std::cerr << "Runtime error: " << error.what();
      return 1;
    }

    try
    {
      compositeShape.move({ 0.0, 0.0 });
      std::cout << "The data of composite-shape after move in point:\n";
      compositeShape.print();

      compositeShape.move(1.0, 1.0);
    }
    catch (const std::runtime_error& error)
    {
      std::cerr << "Runtime error: " << error.what();
      return 1;
    }

    std::cout << "The data of composite-shape after move with dx and dy:\n";
    compositeShape.print();

    try
    {
      compositeShape.scale(2.0);
    }
    catch (const std::invalid_argument& error)
    {
      std::cerr << "Invalid argument error: " << error.what();
      return 1;
    }

    std::cout << "The data of composite-shape after scaling:\n";
    compositeShape.print();

    try
    {
      compositeShape.remove(1);
    }
    catch (const std::runtime_error& error)
    {
      std::cerr << "Runtime error: " << error.what();
      return 1;
    }
    catch (const std::out_of_range& error)
    {
      std::cerr << "Out of range error: " << error.what();
      return 1;
    }

    std::cout << "The data of composite-shape after removing one element:\n";
    compositeShape.print();

    stepanov::CompositeShape newCompositeShape = compositeShape;
    std::cout << "The data of copied composite-shape equals\n";
    newCompositeShape.print();

    std::cout << "If operator[] works, *IT WORKS* will be written\n";

    try
    {
      if (compositeShape[0] != nullptr)
      {
        std::cout << "IT WORKS\n";
      }
    }
    catch (const std::out_of_range& error)
    {
      std::cerr << "Out of range error: " << error.what();
      return 1;
    }

    stepanov::CompositeShape testCompositeShape;

    try
    {
      testCompositeShape.add(std::make_shared<stepanov::CompositeShape>(compositeShape));
    }
    catch (const std::invalid_argument& error)
    {
      std::cerr << "Invalid argument error: " << error.what();
      return 1;
    }
    catch (const std::logic_error& error)
    {
      std::cerr << "Logic error: " << error.what();
      return 1;
    }

    std::cout << "The data of composite-shape with composite-shape inside equals\n";
    testCompositeShape.print();
  }
  catch (const std::exception& error)
  {
    std::cerr << "An unexpected error occured";
    return 1;
  }
  return 0;
}
