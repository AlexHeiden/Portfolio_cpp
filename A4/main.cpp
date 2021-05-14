#include <iostream>
#include <stdexcept>
#include <memory>
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "base-types.hpp"
#include "matrix.hpp"
#include "composite-shape.hpp"

int main()
{
  try
  {
    stepanov::Rectangle rectangleForFirstLayer({ 4.0, 2.0, {0.0, 0.0} });
    stepanov::Circle circleForFirstLayer({ 3.0, 0.0 }, 1.0);
    stepanov::CompositeShape compositeShapeForFirstLayer;
    stepanov::CompositeShape newTestCompositeShape;

    stepanov::Circle circleForCompositeShape({ 0.0, 2.0 }, 1.0);
    stepanov::Rectangle rectangleForCompositeShape({ 4.0, 2.0, {3.0, 2.0} });
    stepanov::Rectangle rectangleForSecondLayer({ 4.0, 2.0, {5.0, -1.0} });

    try
    {
      compositeShapeForFirstLayer.add(std::make_shared<stepanov::Rectangle>(rectangleForCompositeShape));
      compositeShapeForFirstLayer.add(std::make_shared<stepanov::Circle>(circleForCompositeShape));
    }
    catch (const std::invalid_argument& error)
    {
      std::cerr << "Invalid argument error: " << error.what();
      return 1;
    }

    stepanov::CompositeShape compositeShapeForSplit;

    try
    {
      compositeShapeForSplit.add(std::make_shared<stepanov::Rectangle>(rectangleForFirstLayer));
      compositeShapeForSplit.add(std::make_shared<stepanov::Circle>(circleForFirstLayer));
      compositeShapeForSplit.add(std::make_shared<stepanov::CompositeShape>(compositeShapeForFirstLayer));
      compositeShapeForSplit.add(std::make_shared<stepanov::Rectangle>(rectangleForSecondLayer));
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

    std::cout << "The data of matrix after adding shapes\n";

    stepanov::Matrix matrix = compositeShapeForSplit.split();
    matrix.print();

    std::cout << "Rotate demonstration\n"
        << "The data of rectangle before rotate:\n";
    rectangleForFirstLayer.print();
    std::cout << "The data of rectangle after rotate:\n";
    rectangleForFirstLayer.rotate(45);
    rectangleForFirstLayer.print();

    std::cout << "The data of circle before rotate:\n";
    circleForFirstLayer.print();
    std::cout << "The data of circle after rotate:\n";
    circleForFirstLayer.rotate(30);
    circleForFirstLayer.print();

    std::cout << "The data of composite-shape before rotate:\n";
    compositeShapeForFirstLayer.print();
    std::cout << "The data of composite-shape after rotate:\n";
    compositeShapeForFirstLayer.rotate(45);
    compositeShapeForFirstLayer.print();
  }
  catch (const std::exception& error)
  {
    std::cerr << "An unexpected error occured";
    return 1;
  }
  return 0;
}
